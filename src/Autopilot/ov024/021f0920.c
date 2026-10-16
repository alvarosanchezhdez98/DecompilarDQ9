#include <m2c.h>

s32 _Z16GetCombatantByIDii(s32);
s32 func_ov024_021eda60();

s32 func_ov024_021f0920(s32 *arg0) {
    if (_Z16GetCombatantByIDii(*arg0) == 0) {
        return 0;
    }
    if (func_ov024_021eda60() == 0) {
        return 1;
    }
    return 0;
}
