#include <m2c.h>

M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_ov017_021a967c(s32);
extern s8 data_ov017_021d76d8[4];

void func_ov017_021a4dd0(void *arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r4 = M2C_FIELD(arg0, s32 *, 0x36FC);
    temp_r5 = M2C_FIELD(arg0, s32 *, 0x3B84);
    if ((s32) *data_ov017_021d76d8 < 0) {
        return;
    }
    func_ov017_021a967c(temp_r5);
    func_020469b4(temp_r4, temp_r5);
}
