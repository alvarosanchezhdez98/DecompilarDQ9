#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_02011b50(s32, M2C_UNK);
M2C_UNK func_ov017_021d6134(M2C_UNK, s32);

s32 func_ov001_021626a4(M2C_UNK arg0) {
    s32 temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (func_02011b50(temp_r0, 1) != 0) {
        func_ov017_021d6134(arg0, func_02011b50(temp_r0, 1));
    }
    return 1;
}
