#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
void *_ZN9GameState15GetGrottoStructEv();

void func_ov017_021cfcb4(s32 arg0, void *arg1) {
    s8 var_r1;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN9GameState15GetGrottoStructEv();
    if (M2C_FIELD(arg1, u8 *, 4) != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(temp_r0, s8 *, 3) = var_r1;
    if (M2C_FIELD(arg1, u8 *, 4) != 0) {
        M2C_FIELD(temp_r0, s8 *, 4) = 0;
    }
}
