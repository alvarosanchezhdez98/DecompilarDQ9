#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState12GetTickCountEv(s32);
s32 func_020421a0();
M2C_UNK func_0204359c(s32, s32);
M2C_UNK func_020439b0(s32, M2C_UNK);

void func_ov017_021bef4c(void) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_020421a0();
    func_0204359c(temp_r4, _ZNK9GameState12GetTickCountEv(temp_r5));
    func_020439b0(temp_r4, 0);
}
