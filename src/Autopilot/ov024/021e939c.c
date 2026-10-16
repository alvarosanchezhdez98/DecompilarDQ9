#include <m2c.h>

void *_Z16GetCombatantByIDii(s32);
s32 func_02088514(s32);
s32 func_020885b4(s32);
s32 func_ov024_021da644(M2C_UNK, s32, M2C_UNK);

s32 func_ov024_021e939c(void *arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    s32 temp_r0_2;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    void *temp_r0;

    temp_r0 = _Z16GetCombatantByIDii(M2C_FIELD(arg0, s32 *, 0x10));
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r4 = func_02088514(M2C_FIELD(temp_r0, s32 *, 0x138));
    temp_r0_2 = func_020885b4(M2C_FIELD(temp_r0, s32 *, 0x138));
    if (arg2 != 0) {
        if (arg3 != 0) {
            if (temp_r4 != 0) {
                var_r0_2 = 0x10C;
            } else {
                var_r0_2 = 0x10A;
            }
            return var_r0_2;
        }
        if (temp_r4 != 0) {
            return 0x10B;
        }
        return func_ov024_021da644(arg1, 0x26D, 0x1B);
    }
    if (arg3 != 0) {
        if (temp_r0_2 != 0) {
            var_r0 = 0x53;
        } else {
            var_r0 = 0x3F;
        }
        return var_r0;
    }
    if (temp_r4 != 0) {
        return 0x10B;
    }
    if (temp_r0_2 != 0) {
        return 0x52;
    }
    return func_ov024_021da644(arg1, 0x26D, 0x1B);
}
