#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState21GetPartyMemberByIndexEi(s32, M2C_UNK);
void *func_02053c6c();
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);

s32 func_ov001_02162d68(M2C_UNK arg0) {
    M2C_UNK var_r1;

    if (_ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), 0) == 0) {
        return 0;
    }
    if (((u32) (M2C_FIELD(func_02053c6c(), u8 *, 0x49C) << 0x1F) >> 0x1F) == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0, var_r1);
    return 1;
}
