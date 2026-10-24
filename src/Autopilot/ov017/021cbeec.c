#include <m2c.h>
#pragma optimization_level 4

s32 _ZN9GameState21GetPartyMemberByIndexEi(M2C_UNK, s8);
M2C_UNK func_02053f7c(s32, u16, M2C_UNK);

void func_ov017_021cbeec(s32 arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(arg2, M2C_FIELD(arg1, s8 *, 4));
    if (temp_r0 == 0) {
        return;
    }
    func_02053f7c(temp_r0, M2C_FIELD(arg1, u16 *, 6), 1);
}
