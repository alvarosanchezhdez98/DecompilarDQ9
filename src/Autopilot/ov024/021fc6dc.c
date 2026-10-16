#include <m2c.h>

M2C_UNK func_ov024_021fd954(void *, M2C_UNK);
s32 func_ov024_021fe698(void *, M2C_UNK);

void func_ov024_021fc6dc(void *arg0) {
    s16 temp_r0;
    s32 temp_r2;
    void *temp_r1;

    if (func_ov024_021fe698(arg0, 2) == 0) {
        return;
    }
    if (func_ov024_021fe698(arg0, 5) == 0) {
        return;
    }
    temp_r0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x64C), s16 *, 0x30);
    if ((s32) temp_r0 <= 0) {
        return;
    }
    if ((s32) temp_r0 > 5) {
        return;
    }
    temp_r1 = arg0 + (temp_r0 * 4);
    if ((s32) M2C_FIELD(temp_r1, s32 *, 0x154) >= 0x5A) {
        temp_r2 = M2C_FIELD(temp_r1, s32 *, 0x13C);
        if (temp_r2 >= 0x7D) {
            M2C_FIELD(arg0, s32 *, 0x16C) = temp_r2;
            func_ov024_021fd954(arg0, 0xD);
        }
    }
}
