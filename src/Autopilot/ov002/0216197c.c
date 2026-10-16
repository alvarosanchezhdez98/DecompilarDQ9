#include <m2c.h>

void *func_0205d81c(M2C_UNK, M2C_UNK);

s32 func_ov002_0216197c(M2C_UNK arg0, M2C_UNK arg1) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = func_0205d81c(arg1, arg0);
    if (temp_r0 != NULL) {
        if (M2C_FIELD(temp_r0, u8 *, 0xC5) & 0x40) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
