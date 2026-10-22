#include <m2c.h>

M2C_UNK _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(M2C_UNK, s32, u32, M2C_UNK, s32, s32);
s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
s32 func_020bb7cc(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK memcpy(s32, s32, M2C_UNK);

void func_02047f70(void *arg0, s32 arg1, M2C_UNK arg2, s32 arg3) {
    s32 temp_r0;
    s32 var_r7;
    s32 var_r9;
    u32 temp_r4;

    var_r7 = arg1;
    temp_r4 = (u32) (func_020bb7cc(arg2, 0, 0) << 0x10) >> 0xD;
    var_r9 = 1;
    if ((((u32) (M2C_FIELD(arg0, u8 *, 0x84) << 0x1D) >> 0x1F) != 0) && (arg3 != 0)) {
        temp_r0 = _ZN13SafeAllocator8AllocateEj(arg3, arg2);
        if (temp_r0 != 0) {
            memcpy(temp_r0, var_r7, arg2);
            var_r7 = temp_r0;
            var_r9 = 0;
        }
    }
    _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(0, var_r7, temp_r4, arg2, 0, var_r9);
    M2C_FIELD(arg0, u32 *, 0x10) = temp_r4;
}
