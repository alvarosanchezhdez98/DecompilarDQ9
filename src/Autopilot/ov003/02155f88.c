#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, M2C_UNK);

s32 func_ov003_02155f88(s32 arg0, M2C_UNK arg1) {
    s32 var_r1;
    void *temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    var_r1 = 1;
    if ((temp_r0 != NULL) && !(*M2C_FIELD(temp_r0, s32 **, 0x130) & 4)) {
        var_r1 = 0;
    }
    return var_r1;
}
