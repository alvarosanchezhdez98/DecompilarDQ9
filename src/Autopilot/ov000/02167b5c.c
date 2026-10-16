#include <m2c.h>


s32 func_ov000_02167b5c(s32 arg0, u32 arg1) {
    s32 temp_ip;
    s32 temp_lr;
    s32 var_r4;

    temp_lr = arg1 - 1;
    var_r4 = 0xB33;
    temp_ip = (temp_lr * 0x199) + 0x4000;
    if ((s32) ((temp_lr * 0xB33) + arg0) >= temp_ip) {
        if (temp_ip < arg0) {
            var_r4 = 0x199;
        } else if (arg1 > 1U) {
            var_r4 = (s32) (temp_ip - arg0) / temp_lr;
        }
    }
    return var_r4;
}
