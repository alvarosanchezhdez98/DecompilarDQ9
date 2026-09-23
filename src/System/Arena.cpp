#include "System/Arena.h"
#include "System/CP15.h"
#include "System/DTCM.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_arena.c

extern "C"
{
    // usa: func_020c7dcc
    // OS_GetConsoleType
    unsigned long func_020c7dcc();
}

#define CONSOLE_TYPE_MEMORY_SIZE_MASK 3
#define CONSOLE_TYPE_MEMORY_SIZE_4MB 1

#define ADDR_MAIN_MEMORY 0x02000000
// The main memory's end without the ARM7's part
#define ADDR_MAIN_MEMORY_MAIN_END 0x023e0000
#define ADDR_MAIN_MEMORY_EXTENDED_END 0x02700000
#define ADDR_ITCM_END 0x02000000
#define ADDR_SHARED_ARENA_LO 0x027ff000
#define ADDR_SHARED_ARENA_HI 0x027ff680
#define ADDR_WRAM_MAIN_ARENA 0x037f8000

// Where the arenas start by default, after the program: the linker script defines them in the NitroSDK
#define ADDR_MAIN_ARENA_LO 0x022a3200
#define ADDR_ITCM_ARENA_LO 0x01fff280
#define ADDR_DTCM_ARENA_LO 0x027e0080

static int isArenaInitialized = false;
// Whether the extended main memory of debuggers can be used
static int isMainExArenaEnabled = false;

extern "C"
{
    // usa: func_020c83b0
    // OS_InitArena: sets the arenas to their initial range, except the extended main memory's (see func_020c84b4)
    void func_020c83b0()
    {
        if (isArenaInitialized)
        {
            return;
        }
        isArenaInitialized = true;

        func_020c86d4(ARENA_MAIN, func_020c8548(ARENA_MAIN));
        func_020c86e8(ARENA_MAIN, func_020c862c(ARENA_MAIN));

        func_020c86e8(ARENA_MAINEX, NULL);
        func_020c86d4(ARENA_MAINEX, NULL);

        func_020c86d4(ARENA_ITCM, func_020c8548(ARENA_ITCM));
        func_020c86e8(ARENA_ITCM, func_020c862c(ARENA_ITCM));
        func_020c86d4(ARENA_DTCM, func_020c8548(ARENA_DTCM));
        func_020c86e8(ARENA_DTCM, func_020c862c(ARENA_DTCM));
        func_020c86d4(ARENA_SHARED, func_020c8548(ARENA_SHARED));
        func_020c86e8(ARENA_SHARED, func_020c862c(ARENA_SHARED));
        func_020c86d4(ARENA_WRAM_MAIN, func_020c8548(ARENA_WRAM_MAIN));
        func_020c86e8(ARENA_WRAM_MAIN, func_020c862c(ARENA_WRAM_MAIN));
    }

    // usa: func_020c84b4
    // OS_InitArenaEx: sets the extended main memory's arena. Without it, the protection unit only allows the normal
    // main memory.
    void func_020c84b4()
    {
        func_020c86d4(ARENA_MAINEX, func_020c8548(ARENA_MAINEX));
        func_020c86e8(ARENA_MAINEX, func_020c862c(ARENA_MAINEX));

        if (!isMainExArenaEnabled || (func_020c7dcc() & CONSOLE_TYPE_MEMORY_SIZE_MASK) == CONSOLE_TYPE_MEMORY_SIZE_4MB)
        {
            func_020c8a2c(PROTECTION_REGION(ADDR_MAIN_MEMORY, PROTECTION_REGION_SIZE_4MB));
            // The ARM7's part of the main memory
            func_020c8a34(PROTECTION_REGION(ADDR_MAIN_MEMORY_MAIN_END, PROTECTION_REGION_SIZE_128KB));
        }
    }

    // usa: func_020c8520
    // OS_GetArenaHi
    void* func_020c8520(ArenaID id)
    {
        return ARENA_INFO.hi[id];
    }

    // usa: func_020c8534
    // OS_GetArenaLo
    void* func_020c8534(ArenaID id)
    {
        return ARENA_INFO.lo[id];
    }

    // usa: func_020c8548
    // OS_GetInitArenaHi
    void* func_020c8548(ArenaID id)
    {
        switch (id)
        {
        case ARENA_MAIN:
            return (void*)ADDR_MAIN_MEMORY_MAIN_END;

        case ARENA_MAINEX:
            if (!isMainExArenaEnabled || (func_020c7dcc() & CONSOLE_TYPE_MEMORY_SIZE_MASK) == CONSOLE_TYPE_MEMORY_SIZE_4MB)
            {
                return NULL;
            }
            else
            {
                return (void*)ADDR_MAIN_MEMORY_EXTENDED_END;
            }

        case ARENA_ITCM:
            return (void*)ADDR_ITCM_END;

        case ARENA_DTCM:
        {
            // The system stack is below the IRQ stack
            unsigned long irqStackLo = ADDR_DTCM_IRQ_STACK_BOTTOM - IRQ_STACK_SIZE;
            unsigned long sysStackLo;

            if (SYS_STACK_SIZE == 0)
            {
                sysStackLo = (unsigned long)&data_027e0000;
                if (sysStackLo < ADDR_DTCM_ARENA_LO)
                {
                    sysStackLo = ADDR_DTCM_ARENA_LO;
                }
            }
            else if (SYS_STACK_SIZE < 0)
            {
                sysStackLo = ADDR_DTCM_ARENA_LO - SYS_STACK_SIZE;
            }
            else
            {
                sysStackLo = irqStackLo - SYS_STACK_SIZE;
            }

            return (void*)sysStackLo;
        }

        case ARENA_SHARED:
            return (void*)ADDR_SHARED_ARENA_HI;

        case ARENA_WRAM_MAIN:
            return (void*)ADDR_WRAM_MAIN_ARENA;

        default:
            break;
        }

        return NULL;
    }

    // usa: func_020c862c
    // OS_GetInitArenaLo
    void* func_020c862c(ArenaID id)
    {
        switch (id)
        {
        case ARENA_MAIN:
            return (void*)ADDR_MAIN_ARENA_LO;

        case ARENA_MAINEX:
            if (!isMainExArenaEnabled || (func_020c7dcc() & CONSOLE_TYPE_MEMORY_SIZE_MASK) == CONSOLE_TYPE_MEMORY_SIZE_4MB)
            {
                return NULL;
            }
            else
            {
                return (void*)ADDR_MAIN_MEMORY_MAIN_END;
            }

        case ARENA_ITCM:
            return (void*)ADDR_ITCM_ARENA_LO;

        case ARENA_DTCM:
            return (void*)ADDR_DTCM_ARENA_LO;

        case ARENA_SHARED:
            return (void*)ADDR_SHARED_ARENA_LO;

        case ARENA_WRAM_MAIN:
            return (void*)ADDR_WRAM_MAIN_ARENA;

        default:
            break;
        }

        return NULL;
    }

    // usa: func_020c86d4
    // OS_SetArenaHi
    void func_020c86d4(ArenaID id, void* hi)
    {
        ARENA_INFO.hi[id] = hi;
    }

    // usa: func_020c86e8
    // OS_SetArenaLo
    void func_020c86e8(ArenaID id, void* lo)
    {
        ARENA_INFO.lo[id] = lo;
    }

    // usa: func_020c86fc
    // OS_AllocFromArenaLo: takes size bytes from the bottom of an arena, aligned to align bytes. Returns NULL if the
    // arena is too small.
    void* func_020c86fc(ArenaID id, unsigned long size, unsigned long align)
    {
        void* ptr;
        char* arenaLo;

        ptr = func_020c8534(id);
        if (!ptr)
        {
            return NULL;
        }

        arenaLo = (char*)(ptr = (void*)(((unsigned long)ptr + align - 1) & ~(align - 1)));
        arenaLo += size;
        arenaLo = (char*)(((unsigned long)arenaLo + align - 1) & ~(align - 1));

        if (arenaLo > func_020c8520(id))
        {
            return NULL;
        }

        func_020c86e8(id, arenaLo);

        return ptr;
    }
}
