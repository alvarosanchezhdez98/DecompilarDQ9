#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii(s32, M2C_UNK, s32);
s32 abs();
s32 func_0203b57c(s32, M2C_UNK);
s32 func_ov017_0218b5b0();

void func_02021428(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r0;
    s32 var_r5;

    var_r5 = arg1;
    temp_r0 = func_ov017_0218b5b0();
    var_r0 = func_0203b57c(temp_r0, 1);
    if ((s32) (var_r0 - 1) <= -0x10) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, -0x10, 0);
        return;
    }
    if ((s32) (var_r0 + 1) >= 0x10) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, 0x10, 0);
        return;
    }
    if (var_r0 > 0) {
        if (var_r0 < 0) {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            var_r5 = var_r5 / abs();
        }
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, 0x10, var_r5);
        return;
    }
    if (var_r0 > 0) {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        var_r5 = var_r5 / abs();
    }
    _Z16SetSubBrightnessP13GameResourcesii(temp_r0, -0x10, var_r5);
}
