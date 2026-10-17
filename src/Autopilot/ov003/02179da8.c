#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();
s32 func_02086bf4(void *, s16);

s32 func_ov003_02179da8(void *arg0, s32 arg1) {
    s32 temp_r2;
    s32 var_ip;
    u16 temp_r3;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_02010828();
    var_ip = 1;
    if (arg1 != 0) {
        var_ip = func_02086bf4(temp_r0, M2C_FIELD(arg0, s16 *, 0x18));
    }
    temp_r3 = M2C_FIELD(arg0, u16 *, 0x1A);
    temp_r2 = M2C_FIELD(temp_r0, s32 *, 0xF6C);
    if ((u32) (temp_r2 + temp_r3) > 0x98967FU) {
        return 2;
    }
    if (var_ip == 1) {
        return 1;
    }
    if ((u32) (temp_r2 + (temp_r3 * 2)) > 0x98967FU) {
        return 1;
    }
    return 0;
}
