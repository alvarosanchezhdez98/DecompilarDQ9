#include <m2c.h>

M2C_UNK _ZN8Object3D10MakeHiddenEv();
M2C_UNK _ZN8Object3D11MakeVisibleEv();
s32 func_ov017_0218b5b0();
s32 func_ov017_021bdbc0();
s32 func_ov017_021bdbcc();
s32 func_ov017_021d60f4();

s32 func_ov001_02162174(s32 arg0, s32 arg1) {
    s32 var_r4;
    s32 temp_r5;
    s32 temp_r6;

    temp_r6 = func_ov017_021d60f4();
    var_r4 = 0;
    if (arg1 >= 2) {
        var_r4 = func_ov017_021d60f4(arg0 + 8);
    }
    temp_r5 = func_ov017_0218b5b0();
    if (((var_r4 == 0) || (var_r4 & 1)) && (func_ov017_021bdbc0(temp_r5) != 0)) {
        if (temp_r6 != 0) {
            _ZN8Object3D11MakeVisibleEv();
        } else {
            _ZN8Object3D10MakeHiddenEv();
        }
    }
    if ((var_r4 & 2) && (func_ov017_021bdbcc(temp_r5) != 0)) {
        if (temp_r6 != 0) {
            _ZN8Object3D11MakeVisibleEv();
        } else {
            _ZN8Object3D10MakeHiddenEv();
        }
    }
    return 1;
}
