#include <m2c.h>

M2C_UNK func_ov025_021ed11c(s32, s32);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e74d0(void *arg0) {
    func_ov025_021ed11c(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x22C, M2C_FIELD(arg0, s32 *, 8));
    return 1;
}
