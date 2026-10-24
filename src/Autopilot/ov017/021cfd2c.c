#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
void *_ZN9GameState15GetGrottoStructEv();
M2C_UNK func_02012fe4();
M2C_UNK func_0201bfd4();

void func_ov017_021cfd2c(s32 arg0, void *arg1) {
    s8 var_r1;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN9GameState15GetGrottoStructEv();
    if (M2C_FIELD(arg1, u8 *, 4) != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(temp_r0, s8 *, 4) = var_r1;
    func_02012fe4();
    func_0201bfd4();
}
