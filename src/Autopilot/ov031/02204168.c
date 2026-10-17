#include <m2c.h>

M2C_UNK VectorizedMemset(s32, M2C_UNK, s32);

s32 pad_mem(M2C_UNK arg0, u32 arg1, s32 arg2, u32 arg3) {
    s32 temp_r4;
    s32 var_r5;

    var_r5 = arg2;
    if (arg3 < arg1) {
        temp_r4 = arg1 - arg3;
        VectorizedMemset(var_r5, arg0, temp_r4);
        var_r5 += temp_r4;
    }
    return var_r5;
}
