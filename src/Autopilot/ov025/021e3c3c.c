#include <m2c.h>

M2C_UNK func_ov025_021eb044(s32, M2C_UNK);
s32 func_ov025_021eb050(s32);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e3c3c(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 8) == func_ov025_021eb050(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC))) {
        func_ov025_021eb044(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC), 0);
    }
    return 1;
}
