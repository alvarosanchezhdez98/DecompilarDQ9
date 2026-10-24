#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, M2C_UNK);

s32 func_ov003_02155fc0(s32 arg0, M2C_UNK arg1) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 != NULL) {
        if (*M2C_FIELD(temp_r0, s32 **, 0x130) & 1) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
