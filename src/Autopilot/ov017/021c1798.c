#include <m2c.h>

M2C_UNK func_02046a3c(s32, void *);
M2C_UNK func_ov017_021c17cc(void *);

void func_ov017_021c1798(void *arg0, s8 arg1) {
    func_ov017_021c17cc(M2C_FIELD(arg0, void **, 0x3B54));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B54), s8 *, 0x1D) = arg1;
    func_02046a3c(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, void **, 0x3B54));
}
