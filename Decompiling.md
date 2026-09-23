# Decompiling
## Setting up Ghidra
If you haven't already, set up the version of ghidra and the plugin linked in [the primary Readme.](Readme.md) Once you've done that, load the game in Ghidra using the plugin by opening the .nds file in a new project. Open it, and don't auto-analyze it; just close the auto-analyze window, and open the script window. The button for it should look like a green circle with an arrow inside it. Search for SyncDsd inside here, and add tick the "Add to tool" box next to it. Now you can close the script window and press the DS button at the top of the primary window for the game, and you will be asked to load the config.yaml for the game. Open the proper one for your version of the game (config/usa/arm9/config.yaml for USA, config/jpn/arm9/config.yaml for JPN, config/eur/arm9/config.yaml for EUR) and it will sync symbols from the decompilation into ghidra, helping with decompilation efforts.

If you are receiving an error when trying to load the config.yaml, make sure you're using the correct version of the plugin as well as have made a successful build with ninja at least once.

## The basics
Decide on a piece of code you want to decompile; either from looking at already decompiled code and wishing to decompile functions it references, or through other means such as debugging. Once you have it, Ghidra can be an excellent base for understanding what the code is trying to achieve, and decomp.me can ensure the code you write matches the assembly.

## Matching functions locally
`tools/diff_function.py` compiles a source file with the same flags as the build and diffs its functions against the original game with objdiff, marking every instruction that differs. It's a local alternative to decomp.me scratches that doesn't need GCC. It needs `build.ninja` and the delinked objects, so run `python tools/configure.py eur` and `ninja delink` first.
```shell
python tools/diff_function.py src/Bestiary/HabitatTable.cpp              # every function in the file
python tools/diff_function.py src/Bestiary/HabitatTable.cpp --summary    # only the match percentages
python tools/diff_function.py test.cpp func_ov014_021842a0=MyFunction    # an original function against one with another name
```
To get the assembly of every function, run `dsd dis --config-path config/eur/arm9/config.yaml --asm-path build/eur/asm --ual`.

Functions are matched by name, so after naming a function, rename it in `symbols.txt` to the name the compiler gives it (e.g. `_ZN8NatTable7ForEachEPFvPS_P8NatEntryE`) and run `ninja delink` again.

A function whose instructions only differ in the symbols they reference is shown as `100.0 % (except ...)`. References to the same external symbols happen because the original object defines data that ours only declares. References to symbols with other names are listed as `original = ours`, so you can rename the data in `symbols.txt`.

Nintendo's libraries (the NitroSDK and NitroSystem) were compiled with an older compiler version than the game's code, 2.0/sp2 or earlier. From 2.0/sp2p2 on, the compiler handles some 64-bit arithmetic differently, so when a library function almost matches, try `--mwcc 2.0/sp2`. If that matches, add the file to `MWCC_VERSIONS` in `tools/configure.py`, so that the build and `diff_function.py` compile it with that version. Also, their `u32` and `s32` types are `long`, and the compiler can assign registers differently for a `long` variable than for an `int` one. Some library code matches with `#pragma optimization_level 4` (`-O4`) instead of the game's `-O2`: loops over arrays are strength-reduced, and compiled as a check followed by a do-while loop instead of a jump to their condition. Parameters that NitroSystem declares `const` can matter too (see `src/Graphics/NSBXX/NameList.cpp`). Library code accesses the DTCM through the symbols of its variables (e.g. `data_027e0000`), not through fixed addresses (see `src/System/InterruptHandler.cpp`). How a global is declared matters as well: an array accessed as a member of a global struct compiles differently than the same array as its own symbol (see `src/Graphics/NSBXX/RenderCommand_9.cpp`).

The compiler sorts a file's variables by size, from the smallest, when they're defined before the end of the first function in the file, and places the ones that are defined after it at the end, in order. So a variable after a bigger one can mean that the original defined it after a function that isn't in the ROM, since the linker strips the functions that nothing calls (see `decodeBufferArea` in `src/Sound/SoundArchiveStream.cpp`). The order of the variables of the same size depends on the order of their definitions.

A variable that's `static` inside a function can compile differently than a global one (see `InitializeGamecardBusOwnership` in `src/System/GamecardBusOwnership.cpp`). The compiler names it like `isInitialized$126`: give the variable that name in `symbols.txt`, marked `local`, and add the file's `.bss` (or `.data`) section to `delinks.txt`. Functions with variable arguments can include `<stdarg.h>`, which works like the compiler's own (see `src/System/Printf.cpp`).

Some NitroSDK code reads values that its linker script defines, such as the sizes of the stacks (`SDK_IRQ_STACKSIZE`, see `include/System/DTCM.h`). The compiler loads them from a literal pool, like addresses, so the code must reference the symbols to match. `tools/add_linker_symbols.py` defines them in the linker script, and `diff_function.py` counts such a reference as matching the original's value (`except N references to symbols of the linker script`). When the original has a plain number where ours has a relocation, dsd may also have missed a relocation, or given it the wrong symbol: fix it in `relocs.txt`, with `add:` for an address inside a symbol (e.g. `to:0x020c8be4 add:0x50` for a label inside a function), and run `ninja delink` again.

## Identifying library code
Much of main and overlay 31 is Nintendo's libraries, whose code is the same in every game with the same version. `tools/find_signatures.py` compares each of our functions with those of pret/pokeheartgold's libraries, which are in assembly with their official names, ignoring addresses and symbols. Download them first with `tools/fetch_references.py` (5 MB, in `build/references`).
```shell
python tools/fetch_references.py
python tools/find_signatures.py main --runs                   # consecutive matches, grouped by reference file
python tools/find_signatures.py main 0x020ca0b8 0x020cad28    # one function per line
```
A run of matches usually is one of our source files, and the official names tell which NitroSDK or NitroSystem file it is. The public decompilations of Sonic Rush Adventure (RushRE/SonicRushAdventure-Decomp) and pret/pokediamond have the C of many of those files.

The libraries wrote some functions in assembly (e.g. the NitroSDK's `mi_memory.c`), and they're `asm` functions in our files too. `tools/asm_to_mwcc.py` converts functions of the disassembly into MWCC's inline assembly, with local labels and `ldr rX, =value` for the literal pool (see `src/System/MemoryCopy.cpp`). Thumb functions go between `#pragma thumb on` and `#pragma thumb off`; when the original's symbol includes the 2 bytes of padding after a Thumb function, write them as `lsl r0, r0, #0` (see `src/System/Matrix43.cpp`).

## Functions that don't match yet
A function whose C almost matches, but not quite, can block a whole file from being marked `complete`. Its original
instructions can be written in assembly meanwhile, so that the file's other functions and data count, and the C is kept
for later:
```cpp
// NONMATCHING: the C matches 97.2 %, ... (why it doesn't match)
#ifdef NONMATCHING
void MonsterInfoScreen::UpdateText()
{
    ...
}
#else
asm void MonsterInfoScreen::UpdateText()
{
    ...
}
#endif
```
`tools/asm_to_mwcc.py` converts the function (`python tools/asm_to_mwcc.py ov014 _ZN17MonsterInfoScreen10UpdateTextEv`).
Give the `asm` function the C function's return and parameter types. MWCC's assembler doesn't take qualified names like
`NatTable::FindEntry`, so the code calls member functions by their symbols, and the tool prints them declared as
`extern "C"` for the `#else` branch. Compiler functions like `__clear` need a declaration too (see
`src/Bestiary/MonsterInfoScreen.cpp`).

The build uses the assembly, and `python tools/diff_function.py <file> --nonmatching` compiles the C instead, to keep
working on it. `tools/progress.py` finds these functions in the complete files and doesn't count them as decompiled:
[docs/progress.md](docs/progress.md) lists them apart. Use it for the last functions of a file, after trying to match
them, not instead of decompiling.

## Referencing functions and data that have yet to be decompiled
Add a declaration to the file referencing the yet un-decompiled info. For example, if you wanted to reference a function in the main ARM9 file at 02074388, you would add
```C
extern float func_02074388(void*,float,float);
```
so you can reference it. The types may need inferencing, and the function name can be derived from the symbols.txt file under config.

## Creating new files
Once you've decompiled a function and it matches up, it's time to add it to the game. If a file hasn't already been created for this, or it needs tweaking, you need to open the delinks.txt file for the binary you're decompiling part of (ie. ARM9 main, ITCM, or an overlay) and add the file with the start and end address for the file to be inserted into. Example:
```
src/BasicAttackCalculation.cpp:
    complete
    .text start:0x020744c0 end:0x020745ec
```
Add the 'complete' qualifier to indicate the code is finished, or else it won't be included in the build.

Additionally, be sure to rename any symbols in symbols.txt to match the names you gave functions or data in the decompiled file.

Once `ninja min` confirms that everything still matches, run `python tools/progress.py --record` to update [docs/progress.md](docs/progress.md), and commit it with your changes.
