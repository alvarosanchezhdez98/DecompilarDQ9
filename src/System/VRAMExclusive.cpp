#include "System/Interrupts.h"
#include "System/VRAM.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_vramExclusive.c: which lock ID uses each bank of the VRAM. OSi_TryLockVram isn't in the ROM.

// The NitroSDK's OS_VRAM_BANK_KINDS and OS_VRAM_BANK_ID_ALL
#define VRAM_BANK_COUNT 9
#define VRAM_BANK_ALL 0x1ff

// OSi_vramExclusive: the banks in use
static unsigned long banksInUse;
// OSi_vramLockId
static unsigned short bankLockIDs[VRAM_BANK_COUNT];

extern "C"
{
    // usa: func_020c9a4c
    // OsCountZeroBits: the number of zero bits before the highest one
    asm unsigned long func_020c9a4c(unsigned long bits)
    {
        clz r0, r0
        bx lr
    }

    // usa: func_020c9a54
    // OSi_InitVramExclusive
    void func_020c9a54()
    {
        banksInUse = 0;
        for (long i = 0; i < VRAM_BANK_COUNT; i++)
        {
            bankLockIDs[i] = 0;
        }
    }

    // usa: func_020c9a88
    // OSi_UnlockVram: frees the banks that the lock ID uses
    void func_020c9a88(unsigned short banks, unsigned short lockID)
    {
        unsigned long remaining;
        long bank;
        int priorState = DisableIRQInterrupts();

        remaining = banks & banksInUse & VRAM_BANK_ALL;
        while (true)
        {
            bank = 31 - func_020c9a4c(remaining);
            if (bank < 0)
            {
                break;
            }

            remaining &= ~(1 << bank);
            if (bankLockIDs[bank] == lockID)
            {
                bankLockIDs[bank] = 0;
                banksInUse &= ~(1 << bank);
            }
        }

        SetIRQInterruptState(priorState);
    }
}
