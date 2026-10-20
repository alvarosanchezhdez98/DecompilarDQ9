#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s8 func_020100a8(s32);
M2C_UNK func_0203b4a0(void *, M2C_UNK);
void *func_ov017_0218b5b0();

void func_ov017_021b7104(void *arg0, void *arg1) {
    s32 temp_r4;
    s8 var_r0;
    void *temp_r5;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_ov017_0218b5b0();
    M2C_FIELD(arg0, s16 *, 0x22) = (s16) M2C_FIELD(arg1, u8 *, 1);
    M2C_FIELD(arg0, u16 *, 0x24) = (u16) M2C_FIELD(arg1, u16 *, 4);
    M2C_FIELD(arg0, u16 *, 0x26) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) M2C_FIELD(arg1, u8 *, 0);
    if (M2C_FIELD(arg1, u8 *, 0) == 0) {
        var_r0 = -1;
    } else {
        var_r0 = func_020100a8(temp_r4);
    }
    M2C_FIELD(arg0, s8 *, 0x46) = var_r0;
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, u8 *, 0x41) = (u8) M2C_FIELD(arg1, u8 *, 0xD);
    M2C_FIELD(arg0, u8 *, 0x40) = (u8) M2C_FIELD(arg1, u8 *, 0xC);
    M2C_FIELD(arg0, u8 *, 0x42) = (u8) M2C_FIELD(arg1, u8 *, 0xE);
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) M2C_FIELD(arg1, s16 *, 0x10);
    M2C_FIELD(arg0, u8 *, 0x51) = (u8) M2C_FIELD(arg1, u8 *, 0xF);
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg0, u8 *, 0x21) = (u8) M2C_FIELD(arg1, u8 *, 0x12);
    if ((M2C_FIELD(arg1, u8 *, 0) != 0) && (M2C_FIELD(arg1, s32 *, 0x14) == 0)) {
        func_0203b4a0(temp_r5, 0x800);
    }
    M2C_FIELD(temp_r5, s8 *, 0x42E8) = 0;
    M2C_FIELD(temp_r5, s16 *, 0x44C2) = 0;
}
