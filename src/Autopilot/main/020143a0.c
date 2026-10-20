#include <m2c.h>

s32 _Z34DecompressLZ77FileIntoScratchSpaceR13SafeAllocatorPKvRj(s32, M2C_UNK, s32 *);
M2C_UNK func_0201e248(void *);
M2C_UNK func_0201e2b4(void *, s32, s32, s32);

s32 func_02014390(void *arg0, M2C_UNK arg1) {
    s32 sp0;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;

    temp_r5 = M2C_FIELD(arg0, s32 *, 0x68);
    temp_r4 = _Z34DecompressLZ77FileIntoScratchSpaceR13SafeAllocatorPKvRj(temp_r5, arg1, &sp0);
    temp_r6 = M2C_FIELD(arg0, s32 *, 8);
    func_0201e248(arg0 + 0x6C);
    func_0201e2b4(arg0 + 0x6C, temp_r5, temp_r4, sp0);
    M2C_FIELD(arg0, s32 *, 8) = temp_r6;
    return 1;
}
