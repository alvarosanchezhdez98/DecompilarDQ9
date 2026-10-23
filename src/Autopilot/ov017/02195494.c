#include <m2c.h>

M2C_UNK func_ov017_02195214(M2C_UNK, s32);

void func_ov017_02195494(s32 arg0, s32 arg1, M2C_UNK arg2) {
    s32 temp_r1;

    temp_r1 = arg1 - 1;
    if (temp_r1 < 0) {
        return;
    }
    if (temp_r1 > 2) {
        return;
    }
    func_ov017_02195214(arg2, arg0 + 0x42F1 + (temp_r1 * 0xF));
}
