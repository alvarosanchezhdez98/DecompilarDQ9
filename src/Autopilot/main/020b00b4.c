#include <m2c.h>

M2C_UNK func_020b0108(s32);
s32 func_020b0288(M2C_UNK, s32);

s32 func_020b00a4(M2C_UNK arg0, s32 *arg1) {
    s32 temp_r0;

    temp_r0 = func_020b0288(arg0, 0x4345424B);
    if (temp_r0 == 0) {
        *arg1 = 0;
        return 0;
    }
    func_020b0108(temp_r0 + 8);
    *arg1 = temp_r0 + 8;
    return 1;
}
