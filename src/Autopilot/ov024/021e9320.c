#include <m2c.h>

s32 _Z16GetCombatantByIDii(s32);
s32 func_ov024_021da644(M2C_UNK, s32, M2C_UNK);
s32 func_ov024_021de25c();

s32 func_ov024_021e9320(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0;

    if (_Z16GetCombatantByIDii(M2C_FIELD(arg0, s32 *, 0x10)) == 0) {
        return 0;
    }
    temp_r0 = func_ov024_021de25c();
    if (arg2 != 0) {
        if (temp_r0 != 0) {
            return func_ov024_021da644(arg1, 0x83, 0x84);
        }
        return func_ov024_021da644(arg1, 0x81, 0x82);
    }
    if (temp_r0 != 0) {
        return 0x85;
    }
    return func_ov024_021da644(arg1, 0x26D, 0x1B);
}
