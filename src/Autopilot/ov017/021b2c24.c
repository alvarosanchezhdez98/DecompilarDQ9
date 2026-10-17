#include <m2c.h>

M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_ov017_021b2c4c(s32);

void func_ov017_021b2c24(void *arg0) {
    func_ov017_021b2c4c(M2C_FIELD(arg0, s32 *, 0x3738));
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, s32 *, 0x3738));
}
