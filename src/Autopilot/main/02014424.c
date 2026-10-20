#include <m2c.h>

s32 _Z34DecompressLZ77FileIntoScratchSpaceR13SafeAllocatorPKvRj(s32, M2C_UNK, s32 *);
M2C_UNK _ZN12LightingInfo10InitializeEv(void *);
M2C_UNK _ZN12LightingInfo14LoadFromScriptEPKvjP13SafeAllocator(void *, s32, s32, s32);

s32 func_02014414(void *arg0, M2C_UNK arg1) {
    s32 sp0;
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = M2C_FIELD(arg0, s32 *, 0x68);
    temp_r4 = _Z34DecompressLZ77FileIntoScratchSpaceR13SafeAllocatorPKvRj(temp_r5, arg1, &sp0);
    _ZN12LightingInfo10InitializeEv(arg0 + 0x10C);
    _ZN12LightingInfo14LoadFromScriptEPKvjP13SafeAllocator(arg0 + 0x10C, temp_r4, sp0, temp_r5);
    return 1;
}
