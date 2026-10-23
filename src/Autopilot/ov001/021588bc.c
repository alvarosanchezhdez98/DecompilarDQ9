#include <m2c.h>

M2C_UNK func_ov001_02158880();
M2C_UNK func_ov001_021588e4(void *);

void func_ov001_021588bc(void *arg0, s32 arg1, s32 arg2) {
    func_ov001_02158880();
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    func_ov001_021588e4(arg0);
}
