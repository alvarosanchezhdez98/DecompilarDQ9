#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_ov017_0218b5b0();
s32 func_ov017_021a278c(s32, s32);

s32 func_ov017_021c5a1c(s32 arg0) {
    s32 temp_r0;

    if ((arg0 >= 0x8000) && (arg0 <= 0x8004)) {
        return 1;
    }
    if (arg0 < 1) {
        return 0;
    }
    if (arg0 > 0x7FFF) {
        return 0;
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_ov017_0218b5b0();
    if (temp_r0 == 0) {
        return 0;
    }
    if (func_ov017_021a278c(temp_r0, arg0) != 0) {
        return 1;
    }
    return 0;
}
