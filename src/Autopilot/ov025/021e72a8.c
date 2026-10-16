#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_020100bc();
M2C_UNK func_0202ed7c(s32, void *, s32, s32, s32);
void *func_ov000_02160130();

s32 func_ov025_021e72a8(void *arg0) {
    void *temp_r0;

    temp_r0 = func_ov000_02160130();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s8 *, 0x6FD5) = 1;
    }
    _ZN9GameState11GetInstanceEv();
    func_0202ed7c(func_020100bc(), arg0 + 8, M2C_FIELD(arg0, s32 *, 0x14), M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x1C));
    return 1;
}
