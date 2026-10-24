#include <m2c.h>

M2C_UNK _Z17SetMainBrightnessP13GameResourcesii();
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_0200fb8c();
M2C_UNK func_ov017_0218b5b0();
s32 func_ov017_021d60f4();

s32 func_ov001_0215b50c(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r4;
    s32 temp_r5;

    temp_r5 = func_ov017_021d60f4();
    var_r4 = -0x10;
    if (arg1 >= 2) {
        var_r4 = func_ov017_021d60f4(arg0 + 8);
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_0200fb8c();
    if (temp_r0 != 0) {
        _Z17SetMainBrightnessP13GameResourcesii(temp_r0, var_r4, temp_r5);
        func_ov017_0218b5b0();
    }
    return 1;
}
