#include <m2c.h>

M2C_UNK func_ov025_021ed110(s32, s16);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e6f20(void *arg0) {
    func_ov025_021ed110(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x22C, M2C_FIELD(arg0, s16 *, 8));
    return 1;
}
