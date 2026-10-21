#include <m2c.h>


void func_0208902c(void *arg0, s16 arg1) {
    s32 var_r3;

    var_r3 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x14) & 4) {
        var_r3 = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    if (var_r3 != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 4);
    }
    M2C_FIELD(arg0, s16 *, 0) = arg1;
}
