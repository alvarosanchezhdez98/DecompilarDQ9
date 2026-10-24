#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();

s32 func_ov003_02169938(s32 arg0, s32 arg1) {
    s32 temp_r2;
    s32 temp_r2_2;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_02010828();
    temp_r2 = M2C_FIELD(temp_r0, s32 *, 0xF6C);
    if (temp_r2 < (s32) (0 - arg1)) {
        return 0;
    }
    temp_r2_2 = temp_r2 + arg1;
    M2C_FIELD(temp_r0, s32 *, 0xF6C) = temp_r2_2;
    if ((u32) temp_r2_2 > 0x98967FU) {
        M2C_FIELD(temp_r0, s32 *, 0xF6C) = 0x98967F;
    }
    return 1;
}
