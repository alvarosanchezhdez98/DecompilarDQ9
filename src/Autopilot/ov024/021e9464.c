#include <m2c.h>

s32 _Z16GetCombatantByIDii(s32);
s32 func_ov024_021da644(M2C_UNK, s32, M2C_UNK);
s32 func_ov024_021da9b0();

s32 func_ov024_021e9464(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0;
    s32 var_r0;

    if (_Z16GetCombatantByIDii(M2C_FIELD(arg0, s32 *, 0x10)) == 0) {
        return 0;
    }
    temp_r0 = func_ov024_021da9b0();
    if (arg2 != 0) {
        if (temp_r0 != 0) {
            var_r0 = 0x6E;
        } else {
            var_r0 = 0x1E;
        }
        return var_r0;
    }
    if (temp_r0 != 0) {
        return 0x6F;
    }
    return func_ov024_021da644(arg1, 0x26D, 0x1B);
}
