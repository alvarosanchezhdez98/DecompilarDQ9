#include <m2c.h>

M2C_UNK func_ov025_021dcd28(void *);

void func_ov025_021dcc70(void *arg0, void *arg1) {
    u8 temp_r2;
    u8 temp_r2_2;

    temp_r2 = M2C_FIELD(arg0, u8 *, 0x6E4D);
    if ((u32) temp_r2 >= 5U) {
        return;
    }
    func_ov025_021dcd28(arg0 + 0x6E50 + (temp_r2 << 5));
    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x6E4D) << 5)), s16 *, 0x6E68) = (s16) M2C_FIELD(arg1, s16 *, 0x18);
    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x6E4D) << 5)), s16 *, 0x6E6A) = (s16) M2C_FIELD(arg1, s16 *, 0x1A);
    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x6E4D) << 5)), s16 *, 0x6E6C) = 0;
    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x6E4D) << 5)), s16 *, 0x6E6E) = 0;
    temp_r2_2 = M2C_FIELD(arg0, u8 *, 0x6E4D);
    if (temp_r2_2 != 0) {
        M2C_FIELD((arg0 + (temp_r2_2 << 5)), u16 *, 0x6E6E) = (u16) M2C_FIELD((arg0 + ((temp_r2_2 - 1) << 5)), u16 *, 0x6E6C);
    }
    M2C_FIELD(arg0, u8 *, 0x6E4D) = (u8) (M2C_FIELD(arg0, u8 *, 0x6E4D) + 1);
}
