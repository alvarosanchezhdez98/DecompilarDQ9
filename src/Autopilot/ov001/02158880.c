#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_ov001_021588e4(void *);

void func_ov001_02158880(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    memset(arg0 + 0x4C, 0, 0xC);
    memset(arg0 + 0x58, 0, 0xC);
    func_ov001_021588e4(arg0);
}
