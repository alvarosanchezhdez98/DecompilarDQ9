#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(s32, s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_020100bc();
void *func_ov000_02160130();

s32 func_ov025_021e5a2c(s32 arg0) {
    s32 temp_r0;
    void *temp_r0_2;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_020100bc();
    if (temp_r0 != 0) {
        _ZN8Vector3iaSERKS_(temp_r0 + 4, arg0 + 8);
    }
    temp_r0_2 = func_ov000_02160130();
    if (temp_r0_2 != NULL) {
        M2C_FIELD(temp_r0_2, s8 *, 0x6FD5) = 1;
    }
    return 1;
}
