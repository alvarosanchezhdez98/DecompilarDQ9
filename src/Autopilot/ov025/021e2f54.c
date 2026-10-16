#include <m2c.h>

s32 func_020797dc();
void * func_02079e2c();
s32 func_ov000_0215fc60();
s32 func_ov000_0215ffa0();
s32 func_ov000_021600f8();
M2C_UNK func_ov025_021ecc54();
extern M2C_UNK data_ov025_021ef988;

void func_ov025_021e2f54(void *arg0, s16 *arg1, M2C_UNK arg2) {
    s32 temp_r7;
    s32 var_r0;
    void *temp_r4;
    void *temp_r8;

    temp_r4 = M2C_FIELD(&data_ov025_021ef988, void **, 0xC);
    temp_r8 = func_02079e2c(func_020797dc(), *arg1);
    temp_r7 = func_ov000_021600f8(arg1, 0);
    if ((temp_r8 != NULL) && (temp_r7 != 0)) {
        if ((func_ov000_0215ffa0() >= 0xC0) && (func_ov000_0215ffa0(temp_r7) <= 0xC7)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if ((var_r0 != 0) && (((u32) M2C_FIELD(temp_r8, u32 *, 0x14) >> 0x1C) == 4)) {
            M2C_FIELD(arg0, u16 *, 0x26) = (u16) (M2C_FIELD(arg0, u16 *, 0x26) | 8);
            func_ov025_021ecc54(temp_r4 + 0x22C, arg0);
            M2C_FIELD(arg0, u16 *, 0x26) = 7U;
            func_ov025_021ecc54(temp_r4 + 0x22C, arg0);
        } else {
            func_ov025_021ecc54(temp_r4 + 0x22C, arg0);
        }
    } else {
        func_ov025_021ecc54(temp_r4 + 0x22C, arg0);
    }
    if (func_ov000_0215fc60(arg2) != 0) {
        M2C_FIELD(M2C_FIELD(&data_ov025_021ef988, void **, 0xC), s32 *, 0x1C4) = (s32) (M2C_FIELD(M2C_FIELD(&data_ov025_021ef988, void **, 0xC), s32 *, 0x1C4) | 0x10);
    }
}
