#include <m2c.h>

s32 func_ov000_021536f8(s32);
s32 func_ov024_021edbd8();

s32 func_ov024_021f5768(s32 *arg0, s16 arg1, s32 arg2, s32 *arg3, s16 *arg4) {
    if (func_ov000_021536f8(*arg0) == 0) {
        return 0;
    }
    if (func_ov024_021edbd8() != 0) {
        return 0;
    }
    *arg3 = 1;
    *arg4 = arg1;
    return 1;
}
