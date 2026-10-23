#include <m2c.h>

s32 func_020421b0(M2C_UNK);
M2C_UNK func_0204e1c8(void *, s32, s16, s16, s32, s32, s32, s32);
M2C_UNK func_0204f914(void *, M2C_UNK, s16, s16, s32, s32);
s32 func_0204fd00(void *, M2C_UNK);

void func_0204ea5c(void *arg0) {
    s16 temp_lr;
    s16 temp_r2;
    s16 temp_r2_2;
    s16 temp_r3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;

    if (!(M2C_FIELD(arg0, u8 *, 0xC5) & 0x10)) {
        if (func_0204fd00(arg0, 1) == 0) {
            func_0204f914(arg0, 0, 0, 0, 8, 8);
            temp_r0 = func_020421b0(0x15);
            if (temp_r0 != 0) {
                func_0204e1c8(arg0, temp_r0, 0, 0, 8, 8, 0xF0, 0xF);
            }
        }
        if (func_0204fd00(arg0, 2) == 0) {
            temp_r3 = M2C_FIELD(arg0, s16 *, 0xA8);
            func_0204f914(arg0, 0, (s16) ((temp_r3 - 1) * 8), 0, (s32) (s16) (temp_r3 * 8), 8);
            temp_r0_2 = func_020421b0(0x16);
            if (temp_r0_2 != 0) {
                func_0204e1c8(arg0, temp_r0_2, (s16) ((M2C_FIELD(arg0, s16 *, 0xA8) - 1) * 8), 0, 8, 8, 0xF0, 0xF);
            }
        }
        if (func_0204fd00(arg0, 4) == 0) {
            temp_r2 = M2C_FIELD(arg0, s16 *, 0xAA);
            func_0204f914(arg0, 0, 0, (s16) ((temp_r2 - 1) * 8), 8, (s32) (s16) (temp_r2 * 8));
            temp_r0_3 = func_020421b0(0x18);
            if (temp_r0_3 != 0) {
                func_0204e1c8(arg0, temp_r0_3, 0, (s16) ((M2C_FIELD(arg0, s16 *, 0xAA) - 1) * 8), 8, 8, 0xF0, 0xF);
            }
        }
        if (func_0204fd00(arg0, 8) == 0) {
            temp_lr = M2C_FIELD(arg0, s16 *, 0xAA);
            temp_r2_2 = M2C_FIELD(arg0, s16 *, 0xA8);
            func_0204f914(arg0, 0, (s16) ((temp_r2_2 - 1) * 8), (s16) ((temp_lr - 1) * 8), (s32) (s16) (temp_r2_2 * 8), (s32) (s16) (temp_lr * 8));
            temp_r0_4 = func_020421b0(0x17);
            if (temp_r0_4 != 0) {
                func_0204e1c8(arg0, temp_r0_4, (s16) ((M2C_FIELD(arg0, s16 *, 0xA8) - 1) * 8), (s16) ((M2C_FIELD(arg0, s16 *, 0xAA) - 1) * 8), 8, 8, 0xF0, 0xF);
            }
        }
    }
}
