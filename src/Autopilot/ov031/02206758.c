#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, s32, s32);

s32 SOCLi_MemCpy(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_r0;
    s32 var_r4;
    s32 var_r5;

    var_r4 = M2C_FIELD(arg2, s32 *, 0x14);
    var_r5 = M2C_FIELD(arg2, s32 *, 0x1C);
    if (var_r4 > arg1) {
        var_r4 = arg1;
        var_r5 = 0;
    } else {
        temp_r0 = arg1 - var_r4;
        if (var_r5 > temp_r0) {
            var_r5 = temp_r0;
        }
    }
    if (var_r4 > 0) {
        VectorizedInvertedMemcpy(M2C_FIELD(arg2, s32 *, 0x10), arg0, var_r4);
        M2C_FIELD(arg2, s32 *, 0x10) = (s32) (M2C_FIELD(arg2, s32 *, 0x10) + var_r4);
        M2C_FIELD(arg2, s32 *, 0x14) = (s32) (M2C_FIELD(arg2, s32 *, 0x14) - var_r4);
    }
    if (var_r5 > 0) {
        VectorizedInvertedMemcpy(M2C_FIELD(arg2, s32 *, 0x18), arg0 + var_r4, var_r5);
        M2C_FIELD(arg2, s32 *, 0x18) = (s32) (M2C_FIELD(arg2, s32 *, 0x18) + var_r5);
        M2C_FIELD(arg2, s32 *, 0x1C) = (s32) (M2C_FIELD(arg2, s32 *, 0x1C) - var_r5);
    }
    return var_r4 + var_r5;
}
