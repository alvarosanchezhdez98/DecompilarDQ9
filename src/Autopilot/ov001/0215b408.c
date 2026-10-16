#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii();
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_0200fb8c();
M2C_UNK func_ov017_0218b5b0();
s32 func_ov017_021d60f4();

s32 func_ov001_0215b408(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    if (arg1 >= 2) {
        func_ov017_021d60f4(arg0 + 8);
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_0200fb8c();
    if (temp_r0 != 0) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, 0, temp_r4);
        func_ov017_0218b5b0();
    }
    return 1;
}
