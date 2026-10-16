#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0205d5d0(s32, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_ov000_02178938(s32, s32, M2C_UNK, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_021788d8(s32 arg0, s32 arg1, M2C_UNK arg2) {
    s32 temp_r4;

    if (arg1 == 0) {
        return;
    }
    temp_r4 = M2C_FIELD(func_020421a0(), s32 *, 0x5C);
    memset(temp_r4, 0, 0x960);
    func_ov000_02178938(arg0, arg1, arg2, temp_r4);
    func_0205d5d0(arg0 + 0x188, 0xE, temp_r4, 1, 0);
}
