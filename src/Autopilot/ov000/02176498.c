#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0205d5d0(s32, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_ov000_02176500(void *, s32, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_02176498(void *arg0, M2C_UNK arg1) {
    s32 temp_r4;

    if (M2C_FIELD(arg0, s32 *, 0x38) != 0) {
        temp_r4 = M2C_FIELD(func_020421a0(), s32 *, 0x5C);
        memset(temp_r4, 0, 0x960);
        func_ov000_02176500(arg0, temp_r4, arg1);
        func_0205d5d0(M2C_FIELD(arg0, s32 *, 0x38), 0xD, temp_r4, 1, 0);
    }
}
