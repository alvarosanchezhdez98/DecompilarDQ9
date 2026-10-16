#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_020100bc();
M2C_UNK func_0202e874(s32, s16);
void *func_ov000_02160130();

s32 func_ov025_021e7214(void *arg0) {
    void *temp_r0;

    temp_r0 = func_ov000_02160130();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s8 *, 0x6FD5) = 1;
    }
    _ZN9GameState11GetInstanceEv();
    func_0202e874(func_020100bc(), M2C_FIELD(arg0, s16 *, 8));
    return 1;
}
