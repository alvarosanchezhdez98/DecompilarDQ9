#include <m2c.h>


void func_020d76d8(void *arg0, s32 arg1) {
    s32 var_r1;

    var_r1 = arg1;
    if (var_r1 >= 0xC0) {
        var_r1 -= 0xBC;
    }
    M2C_FIELD(arg0, u16 *, 0xA26) = (u16) (M2C_FIELD(arg0, u16 *, 0xA26) & ~(1 << var_r1));
}
