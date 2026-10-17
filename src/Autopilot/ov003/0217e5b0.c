#include <m2c.h>

M2C_UNK func_ov003_02168324();
M2C_UNK func_ov003_0217e36c(void *);

void func_ov003_0217e5b0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x20) != 0) {
        func_ov003_02168324();
    }
    func_ov003_0217e36c(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
