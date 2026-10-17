#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState21GetPartyMemberByIndexEi(s32, s8);
s32 func_02053c6c();
s32 func_02080468(s32, M2C_UNK);

void func_ov003_0217a220(void *arg0) {
    s16 var_r5;
    s32 temp_r5;

    var_r5 = -1;
    if (_ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), M2C_FIELD(arg0, s8 *, 0x1043)) != 0) {
        temp_r5 = func_02053c6c();
        var_r5 = M2C_FIELD((temp_r5 + ((s32) ((M2C_FIELD(arg0, s16 *, 0x100E) - func_02080468(M2C_FIELD(arg0, s32 *, 0x89C), 0x15)) << 0x10) >> 0xF)), s16 *, 0x454);
    }
    M2C_FIELD(arg0, s16 *, 0x103A) = var_r5;
}
