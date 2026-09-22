# Dragon Quest IX: Sentinels of the Starry Skies Decompilation Project

[![EUR functions](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Falvarosanchezhdez98%2FDecompilarDQ9%2Fbadges%2Feur%2Ffunctions.json)](https://github.com/alvarosanchezhdez98/DecompilarDQ9/actions/workflows/match.yml)
[![EUR bytes](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Falvarosanchezhdez98%2FDecompilarDQ9%2Fbadges%2Feur%2Fbytes.json)](https://github.com/alvarosanchezhdez98/DecompilarDQ9/actions/workflows/match.yml)

## 📖 About
This project aims to create a **1:1 disassembly and decompilation** of *Dragon Quest IX: Sentinels of the Starry Skies* for the Nintendo DS.  
The upstream project, [DQIX/dqix-decomp](https://github.com/DQIX/dqix-decomp), focuses on the USA and Japanese versions of the game, with the goal of making it fully recompilable.  
This fork focuses on the European version, which is built from the same code as the USA version (see [The EUR version](#-the-eur-version)). It's the version that CI builds and that new work is matched against, while the USA and JPN configs are kept as they came from upstream.

---

## ⚙️ Setup

### 🛠️ Prerequisites
#### Programs
[Python 3.11 or newer](https://www.python.org/downloads/)

GCC 9+ (available through installers like MINGW on windows, usually included on linux)

[Ninja build system](https://github.com/ninja-build/ninja/releases)

#### Setup
Place a clean ROM of the original game in the 'extract' folder and name it <baserom_dqix_(region).nds>, with (region) being the appropriate region identifier. ex: baserom_dqix_usa.nds

(Note: currently only the usa, jpn and eur roms are supported. See [extract/README.md](extract/README.md) to check that your ROM matches)

Install the Python dependencies with pip
```shell
python -m pip install -r tools/requirements.txt
```
Run the script to configure Ninja (Do this any time a file is added or removed)
```shell
python tools/configure.py <usa|jpn|eur>
```

If using ghidra, be sure to create a successful build using ninja (see: [Building the Project](#-building-the-project)) at least once before loading the game's config.yaml with ghidra. (For more information see See [Decompiling.md](Decompiling.md))

Lastly, if you want the final ROM to be perfectly byte accurate you need to dump the ARM7 BIOS from your DS and place them in the root folder, under the name arm7_bios.bin

---

### 🚀 Building the Project
Once everything is set up:
1. Open the command line in the root folder of the repository.
2. Run the following command:
   ```bash
   ninja
   ```
This builds the ROM, verifies every module against the original, generates a decomp.me context for each object (requires GCC), creates an objdiff configuration and progress report, and verifies the SHA-1 of the whole built ROM (needs the ARM7 BIOS dump). If you're only interested in building the ROM, you can instead use `ninja min`. This will still verify the modules but not the final SHA-1 and as such does not require GCC or the ARM7 BIOS dump.

---

### 🌍 The EUR version
The European version (English, French, German, Italian and Spanish) was built from the same code as the USA version. Every module is at the same address, and the only code differences are in the ARM9 main module: the BIOS call stubs in the secure area are laid out differently, and two functions check for more system languages, which shifts the rest of main's `.text` and `.rodata` by 0x10 bytes.

Because of this, `config/eur` was ported from `config/usa` by [tools/port_eur_config.py](tools/port_eur_config.py):
- It keeps USA's symbol names, including the addresses in automatic names: `func_0200fb40` is at `0x0200fb50` in EUR. Only the address in `symbols.txt` tells where a symbol is.
- New work goes directly into `config/eur`, while `config/usa` and `config/jpn` aren't updated. Don't run `port_eur_config.py --force` again: it regenerates `config/eur` from `config/usa`, which would discard that work.
- Source files are compiled with both `-d usa` and `-d eur`, and decomp.me contexts and scratches get the same macros. So `#if defined(usa)` also applies to the EUR version, and `#if defined(eur)` is for code that only exists in the European version.

---

### 🤖 Continuous integration
On every push and pull request, the `Match` workflow builds the EUR ROM and checks that every module matches. On `main`, it also publishes the progress badges at the top of this page. The workflow needs the base ROM, which can't be part of the repository, so it fetches it from a release of a private repository:

| Name | Kind | Value |
| ---- | ---- | ----- |
| `BASEROM_REPO` | Secret | The private repository, e.g. `user/dqix-baseroms` |
| `BASEROM_TOKEN` | Secret | A token that can read that repository's releases |
| `BASEROM_TAG` | Variable | The tag of the release that contains `baserom_dqix_eur.nds`, and optionally `arm7_bios.bin` |

Until `BASEROM_REPO` is set, the build job is skipped. Without `arm7_bios.bin`, the workflow runs `ninja min report`, which verifies the modules but not the SHA-1 of the whole ROM.

---

## 🤝 Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for the full guide.

We recommend joining the DQIX discord server **The Quester's Rest** (https://discord.gg/DQIX) so you can participate in discussions in the **[DQI-haX: SWEs of the Starry Skies](https://discord.com/channels/655390550698098700/1266135635014582332)** thread to claim a function, ask for help, or share a scratch.

### 📤 Submitting Contributions

> [!Important]
> Ensure the decompiled code you submit produces the **same binary** as the original release game. The build script should throw errors should your code not match.

### Decompiling code
See [Decompiling.md](Decompiling.md), and [docs/module-map.md](docs/module-map.md) for where each part of the game lives.

Contributions are welcome, though make sure you've read the pages linked above first. If you're new to decompilation, some possible tasks to get started with include:
1. Find and decompile additional uses for [the game's scripting system](src/Resource/Script.cpp). Some existing uses can be found [here](src/World/LootableContainer.cpp) and [here](src/Graphics/AtmosphericEffect.cpp) as a guideline. (You don't need to worry about matching global variables, it's okay to mark everything as extern for the time being - just focus on matching the .text section). You may find [this script disassembler](https://github.com/DQIX/dqix-script-disasm) helpful.
2. Help to match additional pieces of the Zone3D class. This is very experimental/WIP, so we have [a separate branch](https://github.com/DQIX/dqix-decomp/tree/zone3d-experimental) to work off of for this.
3. Start decompiling one of the game's standalone overlays/systems, such as overlay 6 (the alchemy pot), overlay 8 (battle records) or overlay 14 (bestiary). This will likely interact with some as of yet unknown systems e.g. input, sound or text processing, but partial progress on the rest would still be very interesting!

---

### 🔧 Useful Tools
1. **Ghidra** (with the NTRGhidra plugin):  
   - A powerful reverse engineering tool for DS games and code.  
   - [Download Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_11.2.1_build) 
   - [Get dsd-ghidra Plugin (use version 0.5.0 for compatibility with dsd 0.10.2)](https://github.com/AetiasHax/dsd-ghidra/releases/tag/v0.5.0)
   
2. **Desmume**:  
   - A DS emulator with excellent debugging features.  
   - [Download nightly builds](https://desmume.org/download/)

3. **No$GBA**:  
   - Another popular DS emulator for debugging, though less user-friendly.  
   - [Download No$GBA](https://problemkaputt.de/gba.htm)

4. **objdiff**:
   - Compares each object built from the source code with the same part of the original game, function by function, and rebuilds it as you edit. It can also create a decomp.me scratch from a function.
   - Run `ninja objdiff` to generate its project file (`objdiff.json`), then open the repository folder with it.
   - [Download objdiff (use version 2.7.1, the same as the build)](https://github.com/encounter/objdiff/releases/tag/v2.7.1)

5. **Decomp.me**:
   - A powerful website designed to aid decompilation of games on different platforms. Select the DS platform and input the assembly of the function you want to decompile, and it will show you how closely the code you write matches the output assembly.
   - Additionally, it's great for collaboration, as you can share a "scratch" of the function you're working on with others and they can seamlessly fork it and contribute.
   - [Check it out here](https://decomp.me)

