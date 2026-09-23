#include "System/CP15.h"

// The NitroSDK's os_tcm.c: the tightly coupled memories, through the coprocessor CP15, in assembly

#ifdef __MWERKS__
extern "C"
{
    // usa: func_020c89c4
    // OS_EnableITCM
    asm void func_020c89c4()
    {
        mrc p15, 0, r0, c1, c0, 0
        orr r0, r0, #0x40000 // ITCM enabled
        mcr p15, 0, r0, c1, c0, 0
        bx lr
    }

    // usa: func_020c89d4
    // OS_EnableDTCM
    asm void func_020c89d4()
    {
        mrc p15, 0, r0, c1, c0, 0
        orr r0, r0, #0x10000 // DTCM enabled
        mcr p15, 0, r0, c1, c0, 0
        bx lr
    }

    // usa: func_020c89e4
    // OS_GetDTCMAddress
    asm unsigned long func_020c89e4()
    {
        mrc p15, 0, r0, c9, c1, 0
        ldr r1, =0xfffff000 // the base address, without the size
        and r0, r0, r1
        bx lr
    }
}
#endif
