#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, s32);
M2C_UNK func_020d1ba0(void *, s32);
s32 func_020d4f8c(void *, s32, M2C_UNK, M2C_UNK);
s32 func_ov031_02215fcc();
extern void *data_ov031_0224e5d8;

s32 func_ov031_02215fd8(void *arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 var_r0;

    if (arg1 == 0) {
        return -1;
    }
    data_ov031_0224e5d8 = arg0;
    VectorizedMemset(data_ov031_0224e5d8, 0, func_ov031_02215fcc());
    M2C_FIELD(data_ov031_0224e5d8, s32 *, 0x1A90) = 0;
    M2C_FIELD(data_ov031_0224e5d8, s16 *, 0x1A94) = 0;
    func_020d1ba0(data_ov031_0224e5d8 + 0x1A96, 0xA001);
    var_r0 = func_020d4f8c(data_ov031_0224e5d8, arg1, arg2, arg3);
    if (var_r0 == 2) {
        var_r0 = 0;
    }
    return var_r0;
}
