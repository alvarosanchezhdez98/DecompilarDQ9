#include <m2c.h>

void *_Z16GetCombatantByIDii(s32, M2C_UNK);
s32 func_02083be8();
s32 func_ov000_02153710(s32);
s32 func_ov024_021dd010(void *arg0);
s32 func_ov024_021eda60(void *arg0);

s32 func_ov024_021ed9dc(s32 *arg0, M2C_UNK arg1) {
    void *temp_r0;

    if (func_ov000_02153710(*arg0) == 0) {
        return 0;
    }
    if (func_02083be8() == 0) {
        return 0;
    }
    temp_r0 = _Z16GetCombatantByIDii(*arg0, arg1);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), u16 *, 2) == 0) {
        return 0;
    }
    if (func_ov024_021dd010(temp_r0) != 0) {
        return 0;
    }
    if (func_ov024_021eda60(temp_r0) == 0) {
        return 1;
    }
    return 0;
}
