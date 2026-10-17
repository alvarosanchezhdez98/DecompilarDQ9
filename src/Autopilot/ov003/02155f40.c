#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, M2C_UNK);
s32 func_ov003_02156034(M2C_UNK);

s32 func_ov003_02155f40(M2C_UNK arg0, M2C_UNK arg1) {
    s32 temp_r4;
    s32 var_r0;
    void *temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 != NULL) {
        temp_r4 = M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x150), s32 *, 0x950);
        if (temp_r4 == func_ov003_02156034(arg0)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
