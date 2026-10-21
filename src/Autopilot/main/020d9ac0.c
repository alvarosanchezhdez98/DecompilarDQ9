#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_020100f8(s32);
M2C_UNK func_020421a0();
M2C_UNK func_02043204();
M2C_UNK func_02094a00();
M2C_UNK func_02094ab0();
M2C_UNK func_020a27ac();

void func_020d9ab0(void *arg0) {
    s32 temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    func_020421a0();
    func_02043204();
    func_02094a00();
    func_02094ab0();
    func_020100f8(temp_r4);
    func_020a27ac();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
