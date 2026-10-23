#include <m2c.h>

s32 func_020421a0();
s32 func_02045d14(s32, s32, void *, M2C_UNK);
s32 func_02046170(s32, void *, M2C_UNK, M2C_UNK);

void func_0205cb74(void *arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r1;

    if (arg1 == 0) {
        return;
    }
    temp_r0 = func_020421a0();
    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x232) * 2)), u16 *, 0x220) = (u16) M2C_FIELD(arg0, u16 *, 0x230);
    M2C_FIELD(arg0, u16 *, 0x230) = (u16) (M2C_FIELD(arg0, u16 *, 0x230) + func_02045d14(temp_r0, arg1, arg0 + 0x120 + (M2C_FIELD(arg0, u16 *, 0x230) * 2), 1));
    temp_r0_2 = func_02046170(temp_r0, arg0 + 0x120 + (M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x232) * 2)), u16 *, 0x220) * 2), 0x100, 1);
    if ((s32) M2C_FIELD(arg0, s32 *, 0xD0) < temp_r0_2) {
        M2C_FIELD(arg0, s32 *, 0xD0) = temp_r0_2;
    }
    M2C_FIELD(arg0, u8 *, 0x232) = (u8) (M2C_FIELD(arg0, u8 *, 0x232) + 1);
    temp_r1 = M2C_FIELD(arg0, s32 *, 0xDC);
    if (temp_r1 >= 8) {
        M2C_FIELD(arg0, s32 *, 0xDC) = 7;
    } else {
        M2C_FIELD((arg0 + (temp_r1 * 2)), s16 *, 0x100) = (s16) temp_r0_2;
        M2C_FIELD((arg0 + (M2C_FIELD(arg0, s32 *, 0xDC) * 2)), s16 *, 0x110) = 0xC;
    }
    M2C_FIELD(arg0, s32 *, 0xDC) = (s32) (M2C_FIELD(arg0, s32 *, 0xDC) + 1);
}
