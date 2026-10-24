#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_0200ff94(s32, s32);

void func_ov000_021710ac(void *arg0, s32 arg1, s32 arg2) {
    s32 var_r0_2;
    u8 temp_r0;
    s32 var_r0;
    void *temp_r0_2;

    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
    temp_r0 = M2C_FIELD(arg0, u8 *, 0x24);
    if (arg2 != 0) {
        var_r0 = temp_r0 | 2;
    } else {
        var_r0 = temp_r0 & ~2;
    }
    M2C_FIELD(arg0, u8 *, 0x24) = var_r0;
    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 == 0) {
        return;
    }
    temp_r0_2 = func_0200ff94(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0_2 == NULL) {
        return;
    }
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x134), u16 *, 0x30);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x134), u16 *, 0x32);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x130), u16 *, 4);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x130), u16 *, 6);
}
