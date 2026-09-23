#include "System/CP15.h"

// The NitroSDK's os_protectionUnit.c: the protection unit, through the coprocessor CP15, in assembly

#ifdef __MWERKS__
extern "C"
{
    // usa: func_020c89f8
    // OS_EnableProtectionUnit
    asm void func_020c89f8()
    {
        mrc p15, 0, r0, c1, c0, 0
        orr r0, r0, #1
        mcr p15, 0, r0, c1, c0, 0
        bx lr
    }

    // usa: func_020c8a08
    // OS_DisableProtectionUnit
    asm void func_020c8a08()
    {
        mrc p15, 0, r0, c1, c0, 0
        bic r0, r0, #1
        mcr p15, 0, r0, c1, c0, 0
        bx lr
    }
}
#endif
