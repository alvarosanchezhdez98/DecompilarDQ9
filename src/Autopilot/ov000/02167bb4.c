#include <m2c.h>

s32 func_02049ee8();
void * _ZN9GameState11GetInstanceEv(void);
void * _ZN9GameState19GetCombatantByIndexEi(void *, s32);

s32 func_ov000_02167bb4(void *arg0, s32 arg1) {
    s32 var_r0;

    if (_ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), (s32) (u8) M2C_FIELD((M2C_FIELD(arg0, s32 *, 0x29C) + (arg1 * 4)), s32 *, 0x8DE0)) != NULL) {
        if (func_02049ee8() != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        return 0;
    }
    if ((arg1 < 0) || (arg1 >= 8)) {
        return 0;
    }
    return 0x7FFFFFFF;
}
