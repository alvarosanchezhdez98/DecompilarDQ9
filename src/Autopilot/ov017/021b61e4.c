#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_0204693c();
M2C_UNK func_02046e08(s32);

void func_ov017_021b61e4(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x16;
    func_02046e08(arg0 + 0xC);
    M2C_FIELD(arg0, s8 *, 0xFC) = 0;
    M2C_FIELD(arg0, s16 *, 0xFE) = 0;
    M2C_FIELD(arg0, s16 *, 0x100) = 0;
    M2C_FIELD(arg0, s8 *, 0xFD) = 0;
}
