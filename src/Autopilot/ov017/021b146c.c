#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_020469b4(s32, void *);
M2C_UNK func_ov017_021b14a0(void *);

void func_ov017_021b146c(void *arg0, s8 arg1) {
    func_ov017_021b14a0(M2C_FIELD(arg0, void **, 0x3B44));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B44), s8 *, 0x49) = arg1;
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, void **, 0x3B44));
}
