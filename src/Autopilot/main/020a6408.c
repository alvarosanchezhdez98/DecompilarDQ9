#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();

void func_020a63f8(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r1;
    s32 temp_r1_2;

    _ZN9GameState11GetInstanceEv();
    if (M2C_FIELD(arg0, u8 *, 0xB) != 0) {
        return;
    }
    *(s32 *)0x04001014 = (M2C_FIELD(arg0, s32 *, 0) & 0x1FF) | (0x01FF0000 & (M2C_FIELD(arg0, s32 *, 4) << 0x10));
    temp_r0 = M2C_FIELD(arg0, s32 *, 0) + M2C_FIELD(arg0, s8 *, 8);
    M2C_FIELD(arg0, s32 *, 0) = temp_r0;
    if (temp_r0 >= 0x100) {
        M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_r0 - 0x100);
    }
    temp_r1 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_r1 <= -1) {
        M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_r1 + 0x100);
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 4) + M2C_FIELD(arg0, s8 *, 9);
    M2C_FIELD(arg0, s32 *, 4) = temp_r0_2;
    if (temp_r0_2 >= 0x100) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) - 0x100);
    }
    temp_r1_2 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_r1_2 <= -1) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_r1_2 + 0x100);
    }
}
