#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetUnknownGameObjectEv();
M2C_UNK func_020421a0();
M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_ov017_021bac58(s32);

void func_ov017_021bac24(void *arg0) {
    _ZN9GameState11GetInstanceEv();
    _ZN9GameState20GetUnknownGameObjectEv();
    func_020421a0();
    func_ov017_021bac58(M2C_FIELD(arg0, s32 *, 0x3728));
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, s32 *, 0x3728));
}
