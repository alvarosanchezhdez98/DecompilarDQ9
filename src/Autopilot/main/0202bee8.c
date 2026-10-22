#include <m2c.h>

void *func_0202c178(s32, s32);
s32 func_0202c1c0();
s32 func_0202df58();

s32 func_0202bed8(s32 arg0, s32 arg1) {
    void *var_r0;

    if (func_0202c1c0() == 0) {
        return 0;
    }
    if (arg1 == M2C_FIELD((arg0 + func_0202df58()), s8 *, 0x1038)) {
        var_r0 = arg0 + 0x7C0;
    } else {
        var_r0 = func_0202c178(arg0, arg1);
    }
    if (var_r0 == NULL) {
        return 0;
    }
    if (((u32) (M2C_FIELD(var_r0, u16 *, 2) << 0x11) >> 0x1F) != 0) {
        return 1;
    }
    return 0;
}
