#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();
s32 func_020797dc();
s32 func_02079e2c(s32, s16);
void *func_ov000_02161318(void *, s8);
s8 func_ov000_02171210(s32, void *);

void func_ov000_02175b54(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    void *temp_r0_3;

    temp_r0 = func_020797dc();
    if (temp_r0 == 0) {
        return;
    }
    temp_r0_2 = func_02079e2c(temp_r0, M2C_FIELD((arg0 + (M2C_FIELD(arg0, s8 *, 0x1D6D) * 2)), s16 *, 0x10));
    if (temp_r0_2 == 0) {
        return;
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0_3 = func_ov000_02161318(arg0, M2C_FIELD(func_02010828(), s8 *, 0xF78));
    if (temp_r0_3 == NULL) {
        return;
    }
    M2C_FIELD(arg0, s8 *, 0x1D68) = (s8) (M2C_FIELD(arg0, s8 *, 0x1D68) + 1);
    M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60) = func_ov000_02171210(temp_r0_2, temp_r0_3);
    M2C_FIELD(arg0, s8 *, 0x1C) = (s8) M2C_FIELD(temp_r0_3, s8 *, 0x1D);
}
