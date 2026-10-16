#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_020100bc();
M2C_UNK func_0202ea10(s32, s16, u16);

s32 func_ov025_021e8100(void *arg0) {
    s32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_020100bc();
    if (temp_r0 != 0) {
        func_0202ea10(temp_r0, M2C_FIELD(arg0, s16 *, 0xA), M2C_FIELD(arg0, u16 *, 8));
    }
    return 1;
}
