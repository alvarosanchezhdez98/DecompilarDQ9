#include <m2c.h>

M2C_UNK func_0205d5b8(s32, M2C_UNK);
s32 func_0205d81c(void *, M2C_UNK);

void func_0205def8(void *arg0, s32 arg1, M2C_UNK arg2) {
    M2C_UNK var_r1;
    s32 temp_r0;

    if ((M2C_FIELD(arg0, s32 *, 0x98) != 0) && (M2C_FIELD(arg0, s32 *, 0x9C) != 0)) {
        temp_r0 = func_0205d81c(arg0, arg2);
        if (temp_r0 == 0) {
            return;
        }
        if (arg1 == 0) {
            var_r1 = 1;
        } else {
            var_r1 = 0;
        }
        func_0205d5b8(temp_r0, var_r1);
    }
}
