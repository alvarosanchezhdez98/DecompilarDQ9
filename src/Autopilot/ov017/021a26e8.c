#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, M2C_UNK);
s32 func_02011584(s32);
s32 func_02033fa0();
s32 func_0204bd7c();
s32 func_02099a68(s32, s32);

s32 func_ov017_021a26e8(s32 arg0, M2C_UNK arg1) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (func_0200ff1c(temp_r0, arg1) == 0) {
        return 0;
    }
    if (func_02033fa0() == 0) {
        return 0;
    }
    temp_r4 = func_0204bd7c();
    return func_02099a68(func_02011584(temp_r0), temp_r4);
}
