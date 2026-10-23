#include <m2c.h>

M2C_UNK func_020469b4(s32, void *);
M2C_UNK func_ov017_021b6790(void *);

void func_ov017_021b66f0(void *arg0) {
    func_ov017_021b6790(M2C_FIELD(arg0, void **, 0x3B00));
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, void **, 0x3B00));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B00), s8 *, 0x1F) = 2;
}
