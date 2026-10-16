#include <m2c.h>

M2C_UNK func_ov025_021e9d14(s32);
M2C_UNK func_ov025_021e9edc(s32);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e7fb4(void) {
    func_ov025_021e9d14(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC));
    func_ov025_021e9edc(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC));
    return 1;
}
