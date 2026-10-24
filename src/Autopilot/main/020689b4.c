#include <m2c.h>

void *_ZN9GameState21GetPartyMemberByIndexEi(M2C_UNK, M2C_UNK);
s32 func_02067fec(M2C_UNK, s32, M2C_UNK);

s32 func_020689a4(M2C_UNK arg0, s32 arg1, M2C_UNK arg2) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(arg0, 0);
    if (temp_r0 != NULL) {
        if (func_02067fec(0, M2C_FIELD(temp_r0, s32 *, 0x134), arg2) == 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
