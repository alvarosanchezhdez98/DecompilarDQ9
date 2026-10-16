#include <m2c.h>

void *_Z16GetCombatantByIDii(s32);
s32 func_02089160(s32);
M2C_UNK func_02089174(s32);
s32 func_ov000_0215e958(s32);

void func_ov024_021e5e80(void *arg0) {
    void *temp_r0;

    temp_r0 = _Z16GetCombatantByIDii(M2C_FIELD(arg0, s32 *, 0x10));
    if (temp_r0 == NULL) {
        return;
    }
    if (func_02089160(M2C_FIELD(temp_r0, s32 *, 0x138)) == 0) {
        return;
    }
    if (func_ov000_0215e958(M2C_FIELD(arg0, s32 *, 0x10)) == 0) {
        return;
    }
    func_02089174(M2C_FIELD(temp_r0, s32 *, 0x138));
}
