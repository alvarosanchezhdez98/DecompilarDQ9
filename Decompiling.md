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
