#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState12GetTickCountEv(s32);
s32 func_020421a0();
M2C_UNK func_0204359c(s32, s32);
M2C_UNK func_020439b0(s32, M2C_UNK);
M2C_UNK func_0205d2bc();

void func_ov003_02170280(void *arg0) {
    s32 temp_r4;
    s32 temp_r5;

    if (M2C_FIELD(arg0, s32 *, 0x3C) == 0) {
        return;
    }
    if ((s32) M2C_FIELD(arg0, s8 *, 1) <= 1) {
        return;
    }
    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_020421a0();
    func_0204359c(temp_r4, _ZNK9GameState12GetTickCountEv(temp_r5));
    func_020439b0(temp_r4, 0);
    if (M2C_FIELD(arg0, s32 *, 0x3C) == 0) {
        return;
    }
    func_0205d2bc();
}
