#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState16GetTrueDeltaTimeEv();

void func_0202441c(void *arg0) {
    u32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = M2C_FIELD(arg0, u32 *, 0x9BC) + _ZNK9GameState16GetTrueDeltaTimeEv();
    M2C_FIELD(arg0, u32 *, 0x9BC) = temp_r0;
    if (temp_r0 >= 0x4B0U) {
        M2C_FIELD(arg0, s8 *, 0x9C0) = 0;
        M2C_FIELD(arg0, u32 *, 0x9BC) = 0U;
        return;
    }
    if (temp_r0 >= 0x1F4U) {
        M2C_FIELD(arg0, s8 *, 0x9C0) = 1;
    }
}
