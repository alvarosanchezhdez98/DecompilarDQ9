#include <m2c.h>

s32 _Z16GetCombatantByIDii(s32, s16);
s32 func_02010088();
void *func_ov000_021536f8(s32);
s32 func_ov024_021e05e4();

s32 func_ov024_021edf00(s32 *arg0, s32 arg1, s16 *arg2) {
    void *temp_r0;

    temp_r0 = func_ov000_021536f8(*arg0);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (func_ov024_021e05e4() == 0) {
        return 0;
    }
    if ((_Z16GetCombatantByIDii(*arg0, M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s16 *, 0x2E)) != 0) && (func_02010088() == 0)) {
        *arg2 = M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s16 *, 0x2E);
        return 1;
    }
    return 0;
}
