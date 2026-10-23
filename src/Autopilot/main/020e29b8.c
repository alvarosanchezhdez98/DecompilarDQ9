#include <m2c.h>


void func_020e29a8(void *arg0, s32 arg1) {
    s32 var_r1;

    var_r1 = arg1;
    if (var_r1 >= 3) {
        var_r1 = 2;
    }
    M2C_FIELD(arg0, s8 *, 0x16) = (s8) var_r1;
}
