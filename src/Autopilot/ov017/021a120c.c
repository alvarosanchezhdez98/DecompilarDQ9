#include <m2c.h>

M2C_UNK func_02046a3c(s32, void *);
M2C_UNK func_ov017_021a124c(void *);

void func_ov017_021a120c(void *arg0, s8 arg1, s8 arg2) {
    func_ov017_021a124c(M2C_FIELD(arg0, void **, 0x3708));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3708), s8 *, 0x20) = arg1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3708), s8 *, 0x21) = arg2;
    func_02046a3c(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, void **, 0x3708));
}
