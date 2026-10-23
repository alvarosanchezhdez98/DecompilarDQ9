#include <m2c.h>

s32 _ZN9GameState21GetPartyMemberByIndexEi(M2C_UNK, s8);
M2C_UNK func_02039d84();

void func_ov017_021d443c(s8 arg0, void *arg1, M2C_UNK arg2) {
    s8 temp_ip;
    s8 var_r1;

    temp_ip = M2C_FIELD(arg1, s8 *, 4);
    var_r1 = arg0;
    if (temp_ip != -1) {
        var_r1 = temp_ip;
    }
    if (_ZN9GameState21GetPartyMemberByIndexEi(arg2, var_r1) == 0) {
        return;
    }
    func_02039d84();
}
