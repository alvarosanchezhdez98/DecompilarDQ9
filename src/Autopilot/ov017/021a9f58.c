#include <m2c.h>

M2C_UNK _Z17SetMainBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetUnknownGameObjectEv(s32);
M2C_UNK func_020397c0();
M2C_UNK func_020421a0();
M2C_UNK func_02043204();
M2C_UNK func_02094a00();
M2C_UNK func_02094ab0();
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_021a9fa0(M2C_UNK);

void func_ov017_021a9f58(M2C_UNK arg0) {
    s32 temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    func_020421a0();
    func_02043204();
    func_02094a00();
    func_02094ab0();
    _Z17SetMainBrightnessP13GameResourcesii(func_ov017_0218b5b0(), 0, 0x14);
    _ZN9GameState20GetUnknownGameObjectEv(temp_r4);
    func_020397c0();
    func_ov017_021a9fa0(arg0);
}
