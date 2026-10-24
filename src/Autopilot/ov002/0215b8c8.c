#include <m2c.h>

M2C_UNK func_02041a28(s32, s32);
M2C_UNK func_02041acc(s32, s32);
M2C_UNK func_02042058(s32, M2C_UNK);
s32 func_020420e8(M2C_UNK, u8);

void func_ov002_0215b8c8(s32 *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r0 = func_020420e8(arg1, arg2);
    temp_r4 = (s32) (((temp_r0 + 0x17) & ~7) - temp_r0) >> 1;
    func_02041a28(*arg0, temp_r4);
    func_02042058(*arg0, arg1);
    func_02041acc(*arg0, temp_r4 - 5);
}
