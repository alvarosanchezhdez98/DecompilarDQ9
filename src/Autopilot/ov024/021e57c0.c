#include <m2c.h>

void *_Z16GetCombatantByIDii(s32);

void func_ov024_021e57c0(void *arg0) {
    void *temp_r0;

    temp_r0 = _Z16GetCombatantByIDii(M2C_FIELD(arg0, s32 *, 0x10));
    if (temp_r0 != NULL) {
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s8 *, 0x21) = 1;
    }
}
