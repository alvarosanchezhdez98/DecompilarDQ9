# Decompiling
## Setting up Ghidra
If you haven't already, set up the version of ghidra and the plugin linked in [the primary Readme.](Readme.md) Once you've done that, load the game in Ghidra using the plugin by opening the .nds file in a new project. Open it, and don't auto-analyze it; just close the auto-analyze window, and open the script window. The button for it should look like a green circle with an arrow inside it. Search for SyncDsd inside here, and add tick the "Add to tool" box next to it. Now you can close the script window and press the DS button at the top of the primary window for the game, and you will be asked to load the config.yaml for the game. Open the proper one for your version of the game (config/usa/arm9/config.yaml for USA, config/jpn/arm9/config.yaml for JPN, config/eur/arm9/config.yaml for EUR) and it will sync symbols from the decompilation into ghidra, helping with decompilation efforts.

If you are receiving an error when trying to load the config.yaml, make sure you're using the correct version of the plugin as well as have made a successful build with ninja at least once.

## The basics
Decide on a piece of code you want to decompile; either from looking at already decompiled code and wishing to decompile functions it references, or through other means such as debugging. Once you have it, Ghidra can be an excellent base for understanding what the code is trying to achieve, and decomp.me can ensure the code you write matches the assembly.

## First drafts of game code
For the game's own code, [m2c](https://github.com/matt-kempster/m2c) turns a function of the disassembly into a C draft, with its `if`s, loops and `switch`es. It isn't part of the repository: clone it into `build/`, which git ignores, and run it on the disassembly of the module:
```shell
git clone --depth 1 https://github.com/matt-kempster/m2c build/m2c
python build/m2c/m2c.py -t arm-mwcc-c++ build/eur/asm/ov010_2.s -f func_ov010_02184354
```
The draft names members by their offsets (`arg0->unk4`) and calls functions by their symbols, since m2c can't read our C++ headers. Give it the types from the headers, and the structures that the offsets suggest, then diff it (see `src/World/Overlay_10/PitEvent.cpp`, drafted this way). It's a draft of what the code does, not of how the source was written: the order of the declarations, the local variables and the repeated blocks still come from the diff.

## Matching functions locally
`tools/diff_function.py` compiles a source file with the same flags as the build and diffs its functions against the original game with objdiff, marking every instruction that differs. It's a local alternative to decomp.me scratches that doesn't need GCC. It needs `build.ninja` and the delinked objects, so run `python tools/configure.py eur` and `ninja delink` first.
```shell
python tools/diff_function.py src/Bestiary/HabitatTable.cpp              # every function in the file
python tools/diff_function.py src/Bestiary/HabitatTable.cpp --summary    # only the match percentages
python tools/diff_function.py test.cpp func_ov014_021842a0=MyFunction    # an original function against one with another name
```
To get the assembly of every function, run `dsd dis --config-path config/eur/arm9/config.yaml --asm-path build/eur/asm --ual`.

Functions are matched by name, so after naming a function, rename it in `symbols.txt` to the name the compiler gives it (e.g. `_ZN8NatTable7ForEachEPFvPS_P8NatEntryE`) and run `ninja delink` again.

Under the diff of a function that doesn't match, `Hint:` lines tell likely causes, from the patterns below: only the registers differ, the same instructions in another order, a block copy, a `bool` of C++, the branches of an `-O4` loop, and so on.

`tools/try_variants.py` compiles several versions of a function and prints how much each one matches. Its variants file has a line `//// name` before each variant, which is either the whole function, or substitutions in the file (see the tool's help):
```shell
python tools/try_variants.py src/System/VRAMExclusive.cpp func_020c9a88 variants.cpp           # the match of each variant
python tools/try_variants.py src/System/VRAMExclusive.cpp func_020c9a88 variants.cpp --apply b # writes variant b to the file
```

A function whose instructions only differ in the symbols they reference is shown as `100.0 % (except ...)`. References to the same external symbols happen because the original object defines data that ours only declares. References to symbols with other names are listed as `original = ours`, so you can rename the data in `symbols.txt`.

Nintendo's libraries (the NitroSDK and NitroSystem) were compiled with an older compiler version than the game's code, 2.0/sp2 or earlier. From 2.0/sp2p2 on, the compiler handles some 64-bit arithmetic differently, so when a library function almost matches, try `--mwcc 2.0/sp2`. If that matches, add the file to `MWCC_VERSIONS` in `tools/configure.py`, so that the build and `diff_function.py` compile it with that version. The NitroSDK is in C, which copies a structure as a block (with `ldmia`/`stmia`, or pairs of `ldrh`/`strh`), while C++ copies it member by member: copy it through a structure with an array (see `CopySample` in `src/System/TouchPanel.cpp`). In C, `!x` is an `int`, and in C++ a `bool` that the compiler may turn into 0 or 1: an inline function that returns it can be a macro (see `IsLeapYear` in `src/System/RealTimeClockConvert.cpp`). Also, their `u32` and `s32` types are `long`, and the compiler can assign registers differently for a `long` variable than for an `int` one. Some library code matches with `#pragma optimization_level 4` (`-O4`) instead of the game's `-O2`: loops over arrays are strength-reduced, and compiled as a check followed by a do-while loop instead of a jump to their condition. Parameters that NitroSystem declares `const` can matter too (see `src/Graphics/NSBXX/NameList.cpp`). Library code accesses the DTCM through the symbols of its variables (e.g. `data_027e0000`), not through fixed addresses (see `src/System/InterruptHandler.cpp`). How a global is declared matters as well: an array accessed as a member of a global struct compiles differently than the same array as its own symbol (see `src/Graphics/NSBXX/RenderCommand_9.cpp`).

In the game's code, when the callee-saved registers (`r4`-`r11`) hold the variables in another order, declare the variables at the top of the function and assign them later: the order of the declarations decides the registers (see `PitEvent::Update` in `src/World/Overlay_10/PitEvent.cpp`). `GetInstance()->Method(member_)` loads the member before the call, and the original's reload after it means `Loader* loader = GetInstance(); loader->Method(member_);`. The compiler only inlines small functions: none with a conditional (`if`, `?:`, `!x`, a conversion to `bool`), and with the game's flags, up to about 6 calls, or 2 stores through a pointer, constructors included. So a longer block repeated in the original, with its own stack slots in each copy, was written at each place, or as a macro. Assigning a structure that has an implicit `operator=`, like `Vector3fix`, calls the out-of-line copy that `src/World/Zone3D.cpp` defines (`_ZN8Vector3iaSERKS_`), while initializing one copies it with `ldmia`/`stmia`. A byte taken with `lsl #24` and `lsr #24` from a word is a bit field (`unsigned int x : 8`), and `and #0xff` a conversion to `unsigned char`. A 6-byte structure passed by value, like `Vector3fix16`, goes in `r3` and the stack, copied through `sub r3, sp, #4`. A loop that tests its condition at the top and jumps back from its end is `while (true) { if (!condition) break; ... }`, since `while (condition)` tests at the bottom (see `CharacterCreationScene::Run` in `src/Scene/Overlay_21/CharacterCreationScene.cpp`). An overlay's ID that's loaded from the literal pool instead of a `mov` is a symbol of the linker script, like the NitroSDK's `FS_OVERLAY_ID()`: dsd's defines `OVERLAY_9_ID` and so on, which `diff_function.py` counts as their values. A constant in `.rodata` that the code never loads (it uses the value as an immediate) was a constant with external linkage, since the compiler drops unused `static const` ones: `SaveErrorScreen::sBufferSize` in `src/Scene/Overlay_19/SaveErrorScreen.cpp`. In a function in assembly (NONMATCHING), the strings of the C go in one array like the compiler's pool, and the code loads them with `ldr r0, =sStrings+0x14`. The compiler never inlines a constructor with more than 2 stores in a `new` expression, unless the code is after `#pragma always_inline on`, which overlay 30's `GameResources` needs (see `src/Resource/Overlay_30/GameResources.cpp`); the old 1.2 compilers inlined them. It constructs the members that are arrays of classes with a constructor and a destructor with `__construct_array`, which takes their addresses, and it computes the arguments of an inlined function that are calls to inline functions before its body.

`tools/data_order.py` compares where the file's variables are in the ROM and in our object, and when they differ, it searches the orders of the definitions that give the original's, with the fewest moves:
```shell
python tools/data_order.py src/System/CartridgeInit.cpp
```
The compiler keeps one list of the file's variables, of `.bss`, `.data` and `.rodata` together, and sorts them by size, from the smallest, when they're defined before the end of the first function in the file (an inline function doesn't count), and places the ones that are defined after it at the end, in order. In C, a variable without an initializer (a tentative definition) goes after all of them, in the reverse order. So a variable after a bigger one can mean that the original defined it after a function that isn't in the ROM, since the linker strips the functions that nothing calls (see `decodeBufferArea` in `src/Sound/SoundArchiveStream.cpp`). The sort is a heap sort of the variables in the reverse order of their definitions, so the order of the variables of the same size depends on the others too. If no order of the definitions gives the original's, defining the variables after the first function keeps them in their order (see `src/System/SHA1.cpp`). Some NitroSDK files were compiled with `-ipa file`, which generates the code at the end of the file: then all the file's variables are sorted, including the function-local `static` ones of any function, and the compiler removes the variables that nothing in the file uses. Write `#pragma ipa file` before the includes, and the functions that aren't in the ROM but use variables that are (see `src/System/CartridgeInit.cpp`).

The build pools a file's strings in one variable (`@stringBase0`), which the compiler creates at the end of the file. With `#pragma pool_strings off`, each string, and each `char` array, goes in a section of its own, and the linker aligns each section to 4. The linker strips the data that nothing references by section, so a variable that nothing uses stays when it's in the section of one that's used (see the test vectors in `src/System/SHA1.cpp`). A local structure with an initializer is copied from a variable in `.rodata`, which has the addresses of the file's functions; when the original stores them at run time, the functions are in another file (see `src/System/HMAC.cpp`).

A variable that's `static` inside a function can compile differently than a global one (see `InitializeGamecardBusOwnership` in `src/System/GamecardBusOwnership.cpp`): the compiler knows that nothing else changes it, so it can read a register before writing it (see `CTRDGi_InitModuleInfo` in `src/System/CartridgeInit.cpp`). The compiler names it like `isInitialized$126`: give the variable that name in `symbols.txt`, marked `local`, and add the file's `.bss` (or `.data`) section to `delinks.txt`. Functions with variable arguments can include `<stdarg.h>`, which works like the compiler's own (see `src/System/Printf.cpp`).

Some NitroSDK code reads values that its linker script defines, such as the sizes of the stacks (`SDK_IRQ_STACKSIZE`, see `include/System/DTCM.h`). The compiler loads them from a literal pool, like addresses, so the code must reference the symbols to match. `tools/add_linker_symbols.py` defines them in the linker script, and `diff_function.py` counts such a reference as matching the original's value (`except N references to symbols of the linker script`). When the original has a plain number where ours has a relocation, dsd may also have missed a relocation, or given it the wrong symbol: fix it in `relocs.txt`, with `add:` for an address inside a symbol (e.g. `to:0x020c8be4 add:0x50` for a label inside a function), and run `ninja delink` again.

## Identifying library code
Much of main and overlay 31 is Nintendo's libraries, whose code is the same in every game with the same version. `tools/find_signatures.py` compares each of our functions with those of pret/pokeheartgold's libraries, which are in assembly with their official names, ignoring addresses and symbols. Download them first with `tools/fetch_references.py` (5 MB, in `build/references`).
```shell
python tools/fetch_references.py
python tools/find_signatures.py main --runs                   # consecutive matches, grouped by reference file
python tools/find_signatures.py main 0x020ca0b8 0x020cad28    # one function per line
```
A run of matches usually is one of our source files, and the official names tell which NitroSDK or NitroSystem file it is. The public decompilations of Sonic Rush Adventure (RushRE/SonicRushAdventure-Decomp) and pret/pokediamond have the C of many of those files. `--exact` only looks for exact matches, which takes seconds for a whole module, and `--rename` gives their official names in `symbols.txt` to the `func_` functions with one exact match (we did it for the C runtime and overlay 31; the NitroSDK's files keep the `func_` names, with the official ones in comments).

`tools/library_draft.py` writes a first version of a library file from that C: it takes the functions of a range, in the ROM's order, and translates their C to our names and types (see the tool's help). Put the reference's `.c` files in `build/references` (e.g. `build/references/c`), which isn't committed:
```shell
python tools/library_draft.py main 0x020d0050 0x020d085c -o src/System/CardBackup.cpp
```
The draft lists what it couldn't translate, and the functions of the reference that the linker stripped. A function without C in the references is in assembly.

The libraries wrote some functions in assembly (e.g. the NitroSDK's `mi_memory.c`), and they're `asm` functions in our files too. `tools/asm_to_mwcc.py` converts functions of the disassembly into MWCC's inline assembly, with local labels and `ldr rX, =value` for the literal pool (see `src/System/MemoryCopy.cpp`). Thumb functions go between `#pragma thumb on` and `#pragma thumb off`; when the original's symbol includes the 2 bytes of padding after a Thumb function, write them as `lsl r0, r0, #0` (see `src/System/Matrix43.cpp`). A function whose constants are before it loads them with `ldr rX, [pc, #offset]`: write the constants as an `asm` function with `dcd` just before it, and add it to `FORCE_ACTIVE` in `tools/configure.py`, since nothing references it (see `src/System/SHA1Block.cpp`).

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

`tools/complete_file.py` does both: it finds the file's code and variables in the ROM, writes its sections in `delinks.txt`, marked complete, and gives the symbols in `symbols.txt` the compiler's names, marking the static ones `local`. It also moves the relocations to symbols inside a variable, writes the sizes that dsd needs, and gives the strings and constants the compiler's names (`@stringBase0`, marked `local`), since the build checks that the linked binary has every global name of `symbols.txt`. When none of the file's functions is named like `symbols.txt` yet, give it where the code starts, and for overlays at the same address, it takes the one whose code there is the file's first function. A call to an address that several overlays share references the first overlay's symbol, so the linker strips a function that's only called that way: the tool notes it, to add it to `FORCE_ACTIVE` in `tools/configure.py` (which goes in the linker script, since `mwldarm`'s `-force_active` option aborts with more than about 256 characters of symbols):
```shell
python tools/complete_file.py src/System/CardBackup.cpp --dry-run    # only prints the changes
python tools/complete_file.py src/System/CardBackup.cpp --text-start 0x020d0050
python tools/configure.py eur
```

Once `ninja min` confirms that everything still matches, run `python tools/progress.py --record` to update [docs/progress.md](docs/progress.md), and commit it with your changes.
