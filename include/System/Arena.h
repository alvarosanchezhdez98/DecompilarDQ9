#pragma once

// The NitroSDK's arenas: ranges of free memory, from which memory is taken from the bottom (lo) or the top (hi)
enum ArenaID
{
    ARENA_MAIN,
    ARENA_MAIN_SUBPRIV, // for the ARM7
    ARENA_MAINEX,       // the extended main memory of debuggers
    ARENA_ITCM,
    ARENA_DTCM,
    ARENA_SHARED,
    ARENA_WRAM_MAIN,
    ARENA_WRAM_SUB,     // for the ARM7
    ARENA_WRAM_SUBPRIV, // for the ARM7
    ARENA_COUNT
};

// The bottom and the top of each arena
struct ArenaInfo
{
    void* lo[ARENA_COUNT];
    void* hi[ARENA_COUNT];
};

#define ARENA_INFO (*(ArenaInfo*)0x027ffda0)

extern "C"
{
    // usa: func_020c83b0
    // OS_InitArena
    void func_020c83b0();
    // usa: func_020c84b4
    // OS_InitArenaEx
    void func_020c84b4();

    // usa: func_020c8520
    // OS_GetArenaHi
    void* func_020c8520(ArenaID id);
    // usa: func_020c8534
    // OS_GetArenaLo
    void* func_020c8534(ArenaID id);
    // usa: func_020c8548
    // OS_GetInitArenaHi
    void* func_020c8548(ArenaID id);
    // usa: func_020c862c
    // OS_GetInitArenaLo
    void* func_020c862c(ArenaID id);
    // usa: func_020c86d4
    // OS_SetArenaHi
    void func_020c86d4(ArenaID id, void* hi);
    // usa: func_020c86e8
    // OS_SetArenaLo
    void func_020c86e8(ArenaID id, void* lo);

    // usa: func_020c86fc
    // OS_AllocFromArenaLo
    void* func_020c86fc(ArenaID id, unsigned long size, unsigned long align);
}
