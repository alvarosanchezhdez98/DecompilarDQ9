#include <m2c.h>

s32 func_020797dc();
void *func_02079e2c(s32, s16);
M2C_UNK func_ov000_02160130();
s16 *func_ov000_02160f20();

void func_ov025_021eba60(void *arg0) {
    s16 *temp_r5;
    void *temp_r0;

    func_ov000_02160130();
    temp_r5 = func_ov000_02160f20();
    temp_r0 = func_02079e2c(func_020797dc(), *temp_r5);
    if (temp_r0 == NULL) {
        return;
    }
    if ((((u32) M2C_FIELD(temp_r0, u32 *, 0x14) >> 0x1C) == 2) && (((u32) (M2C_FIELD(temp_r0, s32 *, 8) << 0x16) >> 0x1E) == 1)) {
        M2C_FIELD(arg0, s32 *, 0x1C4) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C4) | 0x80);
    }
}
