#include <m2c.h>

void *_Z16GetCombatantByIDii(s32);
s32 func_020882f8(s32);
s32 func_ov024_021da644(M2C_UNK, s32, M2C_UNK);

s32 func_ov024_021e929c(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0_2;
    void *temp_r0;

    temp_r0 = _Z16GetCombatantByIDii(M2C_FIELD(arg0, s32 *, 0x10));
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r0_2 = func_020882f8(M2C_FIELD(temp_r0, s32 *, 0x138));
    if (arg2 != 0) {
        if (temp_r0_2 != 0) {
            return func_ov024_021da644(arg1, 0x42, 0x17E);
        }
        return func_ov024_021da644(arg1, 0x41, 0x92);
    }
    if (temp_r0_2 != 0) {
        return 0x43;
    }
    return func_ov024_021da644(arg1, 0x26D, 0x1B);
}
