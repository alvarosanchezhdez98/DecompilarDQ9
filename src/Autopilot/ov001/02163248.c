#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_020100bc();
s32 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_02163248(M2C_UNK arg0) {
    s8 var_r0;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_020100bc();
    if (temp_r0 == NULL) {
        return 1;
    }
    if (func_ov017_021d60f4(arg0) == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    M2C_FIELD(temp_r0, s8 *, 0x265) = var_r0;
    return 1;
}
