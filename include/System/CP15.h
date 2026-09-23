#pragma once

// The NitroSDK's functions for the ARM9's system control coprocessor (CP15): the tightly coupled memories (TCM) and
// the protection unit, in TCM.cpp, ProtectionUnit.cpp and ProtectionRegion.cpp

// The value of a protection region: its base address, its size (2 << value bytes), and enabled
#define PROTECTION_REGION(base, sizeValue) ((base) | ((sizeValue) << 1) | 1)
#define PROTECTION_REGION_SIZE_128KB 0x10
#define PROTECTION_REGION_SIZE_4MB 0x15

extern "C"
{
    // usa: func_020c89c4
    // OS_EnableITCM
    void func_020c89c4();
    // usa: func_020c89d4
    // OS_EnableDTCM
    void func_020c89d4();
    // usa: func_020c89e4
    // OS_GetDTCMAddress
    unsigned long func_020c89e4();

    // usa: func_020c89f8
    // OS_EnableProtectionUnit
    void func_020c89f8();
    // usa: func_020c8a08
    // OS_DisableProtectionUnit
    void func_020c8a08();

    // usa: func_020c8a18
    // OS_SetDPermissionsForProtectionRegion: clears the bits of clearMask in the data access permissions, then sets
    // the bits of flags
    void func_020c8a18(unsigned long clearMask, unsigned long flags);
    // usa: func_020c8a2c
    // OS_SetProtectionRegion1
    void func_020c8a2c(unsigned long region);
    // usa: func_020c8a34
    // OS_SetProtectionRegion2
    void func_020c8a34(unsigned long region);
}
