#include <m2c.h>


s32 func_02024d48(void *arg0, s32 arg1) {
    s32 var_r2;
    s32 var_r3;
    u8 temp_ip;

    temp_ip = M2C_FIELD(arg0, u8 *, 0x12);
    var_r2 = 1;
    var_r3 = 1;
    if ((temp_ip != 0) && ((temp_ip == 0) || (M2C_FIELD(arg0, u8 *, 0x11) != 0))) {
        var_r3 = 0;
    }
    if ((var_r3 == 0) && ((temp_ip == 0) || (arg1 != 0))) {
        var_r2 = 0;
    }
    return var_r2;
}
