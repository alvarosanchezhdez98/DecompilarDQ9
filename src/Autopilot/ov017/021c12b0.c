#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState14GetProtagonistEv(s32);
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, s16);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021d2738(u8, M2C_UNK);

void func_ov017_021c12b0(M2C_UNK arg0) {
    s16 temp_r4;
    s32 temp_r0;
    void *var_r0;

    temp_r4 = M2C_FIELD(M2C_FIELD(func_ov017_0218b5b0(), void **, 0x371C), s16 *, 0x22);
    temp_r0 = _ZN9GameState11GetInstanceEv();
    var_r0 = _ZN9GameState21GetPartyMemberByIndexEi(temp_r0, temp_r4);
    if (var_r0 == NULL) {
        var_r0 = _ZN9GameState14GetProtagonistEv(temp_r0);
    }
    func_ov017_021d2738((u8) M2C_FIELD(var_r0, s16 *, 4), arg0);
}
