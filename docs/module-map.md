# Module map

Where each part of the game lives in the European version, to plan the decompilation by systems instead of by address.
Addresses are EUR addresses, and remember that symbol names keep USA addresses (see [The EUR version](../README.md#-the-eur-version)).

Purposes marked *likely* come from the file paths and strings each module uses, and should be confirmed in a debugger,
e.g. by checking which overlays DeSmuME loads in each scene.

## Libraries

The game links these libraries besides its own code:

| Library | Version | Evidence |
| ------- | ------- | -------- |
| NitroSDK | 4.2 | `sdk_version` in the ARM9 header, `NITRO SDK %d.%d.%d` in overlay 20 |
| NitroSystem (G3D, 3D models and animations) | | `NITRO SYSTEM %d` in overlay 20 |
| NitroWiFi | 2.1 | `[SDK+NINTENDO:WiFi2.1.30003.0709200229]` in main |
| DWC-DL (Nintendo Wi-Fi Connection) | 3.1 | `[SDK+NINTENDO:DWC-DL3.1.30006.20090131.2235_DWC-DL_3_1_PLUS6]` in main |
| Ubiquitous CPS (TCP/IP) and SSL | | `[SDK+UBIQUITOUS:CPS]`, `[SDK+UBIQUITOUS:SSL]` in main |
| NitroCrypto, SWC | | `NITRO CRYPTO %d.%d.%d`, `SWC %d.%d.%d` in overlay 20 |
| Card backup library | | `[SDK+NINTENDO:BACKUP]` in main |
| Mobiclip (video) | 1.0.3 | `[SDK+Actimagine:Mobiclip SDK V1.0.3]` in main |

The project gives library functions its own names (e.g. `NitroVM` for the NitroSDK file system, `NSBXX` for NitroSystem G3D),
since the official names aren't known for this game.

## ARM9 main

`main` is always loaded, and holds 922 KB of code. It's laid out like this:

| Range | Size | Contents |
| ----- | ---- | -------- |
| `0x02000000-0x02000800` | 2 KB | Secure area, with the BIOS call stubs (`Div`, `CpuSet`...) |
| `0x02000800-0x02000c9c` | 1 KB | Startup: `Entry`, `AutoloadCallback`, `BuildInfo` and the library tags above |
| `0x02000c9c-0x020b2adc` | ~710 KB | Level-5 code: `main`, the C runtime (`memcpy`, `abs`...), then the game and its engine. Around 4400 functions |
| `0x020b2adc-0x020bbd24` | ~37 KB | NitroSystem G3D (`src/Graphics/NSBXX`), then GFD, its VRAM managers (`NNS_Gfd*`) |
| `0x020bbd24-0x020c0338` | ~18 KB | NitroSystem sound (`NNS_Snd*`, `src/Sound`), and a function that isn't identified at `0x020c02a0` |
| `0x020c0338-0x020dc300` | ~112 KB | NitroSDK: digests (DGT), fixed-point math (FX: `Mat3x3_*`, `Vector3fix_*`...), GX, VRAM, interrupts, cache, timers, DMA, IPC (`src/System`), file system and card access (`src/Filesystem`) |
| `0x020dc300-0x020e5930` | ~37 KB | More Level-5 code: it uses the game's classes (`GameState`, `SafeAllocator`...) |
| `0x020e5930-0x020eebd4` | ~36 KB | `.init`, `.rodata` and `.ctor` |
| `0x020eebe0-0x021536e0` | 17 KB + 386 KB | `.data` and `.bss` |

The ITCM (`0x01ff8000`, 6 KB of code) and DTCM (`0x027e0000`) are also loaded at all times.

## Overlays

Overlays at the same address replace each other, so each group is a set of modes that are never loaded together.
Sizes include code and data. [progress.md](progress.md) has how much of each one is decompiled.

| Overlay | Address | Size (KB) | Functions | Purpose | Evidence |
| ------- | ------- | --------- | --------- | ------- | -------- |
| 0 | `0x021536e0` | 194.8 | 826 | *Likely* battle: actors, actions and damage | `data/bin/actdef.nsarc`, `default.bact`, `damage`, battle effects `eb*.chr` |
| 1 | `0x021536e0` | 72.3 | 515 | *Likely* events and cutscenes | `data/event_lv5/%s`, `data/evspt_lv5/%s`, `%s.stb` scripts |
| 2 | `0x021536e0` | 103.2 | 213 | *Likely* item, spell and skill menus | `itemname`, `spelltable.bin`, `skilltable.bin`, `treasure.nsarc` |
| 3 | `0x021536e0` | 181.4 | 510 | *Likely* Alltrades Abbey (vocations; "Dharma" in Japanese) | `str_dam`, `bm_dama`, `lay_dama`, `level%d.bin` |
| 4 | `0x021536e0` | 116.2 | 532 | Unclear: accolades, treasure maps | `ttldata`, `dqa_%02d`, `tmap/param.pac` |
| 5 | `0x021536e0` | 37.8 | 89 | *Likely* equipment menu | `str_eq`, `itemsort` |
| 6 | `0x021536e0` | 51.2 | 132 | Alchemy pot ("renkin" in Japanese) | `ren_in`, `ren_out`, `obj_rri`, `bm_rri` |
| 7 | `0x021842a0` | 0.0 | 0 | Empty | |
| 8 | `0x021842a0` | 28.8 | 63 | *Likely* battle records and profile | `title_clr.stb`, `profstr`, `tlkpcstr` |
| 9 | `0x021842a0` | 26.7 | 43 | *Likely* character creation / name entry | `keyboard_cm.bin`, `keyboard_cs.bin`, `str_cm` |
| 10 | `0x021842a0` | 2.0 | 3 | Unclear | `str_pit`, `ana.chr` |
| 11 | `0x021842a0` | 18.2 | 186 | Unclear | `data/%s` only |
| 12 | `0x021842a0` | 28.1 | 71 | *Likely* profile editing (tag mode) | `profstr`, `profsen`, `keyboard_pr.bin` |
| 13 | `0x021842a0` | 15.1 | 40 | *Likely* skill point allocation | `obj_sklup_i`, `sklname` |
| 14 | `0x021842a0` | 21.3 | 69 | Bestiary | `mons_info2.nat`, `mon_list`, `mon_trv%d` |
| 15 | `0x0218b5a0` | 35.9 | 103 | *Likely* character model loading / viewer | `charaview4.bin`, `data/chara/%s.chr`, `%s.nsbca` |
| 16 | `0x0218b5a0` | 70.8 | 87 | *Likely* video player (Mobiclip) | `data/movie/movielist.bin`, `data/movie/%s` |
| 17 | `0x0218b5a0` | 307.3 | 1194 | Unclear, the largest overlay: game start and events | `opening.stb`, `upload.stb`, `kanoke.nsbmd` |
| 18 | `0x0218b5a0` | 0.0 | 0 | Empty | |
| 19 | `0x0218b5a0` | 3.4 | 5 | *Likely* error screen | `str_err`, `icon.nsarc` |
| 20 | `0x0218b5a0` | 9.9 | 18 | *Likely* title screen, with a debug version screen | `bg_title.pac`, `Chara Viewer`, library versions, `LEVEL5 INC.` |
| 21 | `0x0218b5a0` | 1.6 | 5 | Unclear | |
| 22 | `0x021d8a40` | 0.0 | 0 | Empty | |
| 23 | `0x021d8a40` | 155.9 | 827 | Unclear: list menus | `str_ii`, `bg_iilist`, `al_qu.spr` |
| 24 | `0x021d8a40` | 157.8 | 573 | Unclear, no strings | |
| 25 | `0x021d8a40` | 91.8 | 304 | *Likely* battle spell and skill animations | `actspl.nsarc`, `actskl.nsarc`, `sp%03d.bact`, `stand_battle` |
| 26 | `0x021d8a40` | 25.2 | 24 | *Likely* spell and skill effects | `skilltable.bin`, `spelltable.bin`, effects |
| 27 | `0x021d8a40` | 19.7 | 87 | Unclear, no strings | |
| 28 | `0x021d8a40` | 4.2 | 34 | Staff roll | `staffroll.bin` |
| 29 | `0x021d8a40` | 7.7 | 1 | *Likely* encrypted code: dsd only finds data, but `main()` calls three addresses in it at startup, as checks that decide whether to load overlay 33 or 34 | Calls from `main()` |
| 30 | `0x021d8a40` | 4.5 | 11 | Unclear, no strings. Needs `-force_active` to be linked | |
| 31 | `0x02200160` | 306.0 | 1962 | Wireless: Nintendo Wi-Fi Connection and DS Download Play | `nas.nintendowifi.net`, `DWCauth`, `MB_COMM_PSTATE_*` |
| 32 | `0x02200160` | 0.0 | 0 | 648 KB of `.bss` only, a buffer in overlay 31's place | |
| 33 | `0x022a2180` | 2.2 | 5 | Background loader (`src/Filesystem/Overlay_33`), fully decompiled | |
| 34 | `0x022a2180` | 2.2 | 5 | Overlay 33's background loader with a random memory leak, *likely* anti-piracy (`src/Filesystem/Overlay_34`), fully decompiled. Needs `-force_active` to be linked | Loaded by the functions that `main()` passes to overlay 29's checks |

## Progress baseline

On 2026-09-22, before starting the EUR decompilation, `ninja report` measured 142,700 of 2,959,494 bytes (4.82 %)
and 1072 of 14,790 functions (7.25 %). Most of it is in main (14.4 %) and the ITCM (70.6 %).
