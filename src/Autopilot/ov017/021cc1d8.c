#include <m2c.h>


void func_ov017_021cc1d8(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    void *temp_r3;

    temp_r3 = M2C_FIELD(arg3, void **, 0x3B2C);
    if (M2C_FIELD(temp_r3, s8 *, 0x10) == M2C_FIELD(arg1, u8 *, 4)) {
        M2C_FIELD(temp_r3, s8 *, 0xF) = (s8) M2C_FIELD(arg1, s32 *, 8);
    }
}
