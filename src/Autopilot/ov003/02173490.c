#include <m2c.h>

s32 func_ov003_0217bdb8(s32);

void func_ov003_02173490(void *arg0) {
    s32 var_r0;

    if (func_ov003_0217bdb8(arg0 + 0x1E0) != 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        return;
    }
    M2C_FIELD(arg0, s8 *, 0xCC) = 1;
    M2C_FIELD(arg0, s8 *, 0xD4) = 0;
    M2C_FIELD(arg0, s8 *, 0xEC) = 4;
    M2C_FIELD(arg0, s8 *, 0xEE) = 0;
    M2C_FIELD(arg0, s8 *, 0xED) = 4;
    M2C_FIELD(arg0, s8 *, 0xEF) = 0;
}
