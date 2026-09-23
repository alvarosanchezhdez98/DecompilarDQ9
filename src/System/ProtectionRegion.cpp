#include "System/CP15.h"

// The NitroSDK's os_protectionRegion.c: the regions of the protection unit, through the coprocessor CP15, in assembly

#ifdef __MWERKS__
extern "C"
{
    // usa: func_020c8a18
    // OS_SetDPermissionsForProtectionRegion
    asm void func_020c8a18(register unsigned long clearMask, register unsigned long flags)
    {
        mrc p15, 0, r2, c5, c0, 2
        bic r2, r2, clearMask
        orr r2, r2, flags
        mcr p15, 0, r2, c5, c0, 2
        bx lr
    }

    // usa: func_020c8a2c
    // OS_SetProtectionRegion1
    asm void func_020c8a2c(register unsigned long region)
    {
        mcr p15, 0, region, c6, c1, 0
        bx lr
    }

    // usa: func_020c8a34
    // OS_SetProtectionRegion2
    asm void func_020c8a34(register unsigned long region)
    {
        mcr p15, 0, region, c6, c2, 0
        bx lr
    }
}
#endif
