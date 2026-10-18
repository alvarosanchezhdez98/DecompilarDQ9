#include <m2c.h>

M2C_UNK func_02046a3c(s32, void *);
M2C_UNK func_ov017_021acd7c(void *);

void func_ov017_021acd30(void *arg0, s8 arg1, s8 arg2, s8 arg3) {
    func_ov017_021acd7c(M2C_FIELD(arg0, void **, 0x3B20));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B20), s8 *, 0x27C) = arg1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B20), s8 *, 0x27D) = arg2;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B20), s8 *, 0x27E) = arg3;
    func_02046a3c(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, void **, 0x3B20));
}
