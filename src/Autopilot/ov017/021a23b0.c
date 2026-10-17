#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN8Object3D10MakeHiddenEv(s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_02076a8c();
s32 func_ov017_021a278c(M2C_UNK, M2C_UNK);

void func_ov017_021a23b0(M2C_UNK arg0, M2C_UNK arg1) {
    s32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_ov017_021a278c(arg0, arg1);
    if (temp_r0 == 0) {
        return;
    }
    func_02076a8c();
    _ZN8Object3D10MakeHiddenEv(temp_r0);
}
