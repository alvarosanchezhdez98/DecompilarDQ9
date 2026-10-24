#include <m2c.h>

s32 func_020100a8(M2C_UNK);
M2C_UNK memcpy(s32, void *, M2C_UNK);
void *func_ov017_021b8470(s32);

void func_ov017_021ca918(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_r2;
    s32 temp_r5_2;
    void *temp_r0;
    void *temp_r5;

    temp_r0 = func_ov017_021b8470(M2C_FIELD(arg3, s32 *, 0x3718));
    if (temp_r0 != NULL) {
        temp_r5 = M2C_FIELD(temp_r0, void **, 0x8E18);
        if (temp_r5 != NULL) {
            if (M2C_FIELD(temp_r5, s8 *, 0x2A) == func_020100a8(arg2)) {
                return;
            }
            if (M2C_FIELD(temp_r5, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
                return;
            }
            temp_r2 = M2C_FIELD(arg1, u16 *, 6) - 0xC0;
            if (temp_r2 < 0) {
                return;
            }
            if (temp_r2 >= 8) {
                return;
            }
            temp_r5_2 = (temp_r2 * 0xA4) + (s32) (temp_r5 + 0x158);
            memcpy(temp_r5_2 + 0x58, arg1 + 8, 4);
            M2C_FIELD(temp_r5_2, s16 *, 0x28) = (s16) M2C_FIELD(arg1, s16 *, 0xC);
            M2C_FIELD(temp_r5_2, s16 *, 0x2A) = (s16) M2C_FIELD(arg1, s16 *, 0xE);
            M2C_FIELD(temp_r5_2, s16 *, 0x2C) = (s16) M2C_FIELD(arg1, s16 *, 0x10);
            M2C_FIELD(temp_r5_2, s16 *, 0x2E) = (s16) M2C_FIELD(arg1, s16 *, 0x12);
        }
    }
}
