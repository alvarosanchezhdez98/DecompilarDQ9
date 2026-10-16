#include <m2c.h>

M2C_UNK func_ov025_021ed344(s32, u16);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e80d8(void *arg0) {
    func_ov025_021ed344(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x5E8, M2C_FIELD(arg0, u16 *, 8));
    return 1;
}
