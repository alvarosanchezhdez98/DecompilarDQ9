#include <m2c.h>

M2C_UNK func_0202c848(u16);
s32 func_0202d788(u16);
extern M2C_UNK data_021015a0;

void func_0202d840(void *arg0) {
    s32 temp_r0;
    u16 temp_ip;
    u16 temp_r1;
    u16 temp_r3;

    temp_r1 = M2C_FIELD(arg0, u16 *, 2);
    if (temp_r1 != 0) {
        func_0202c848(temp_r1);
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
        return;
    }
    temp_r3 = M2C_FIELD(arg0, u16 *, 0xA);
    temp_ip = M2C_FIELD(arg0, u16 *, 8);
    if ((u32) M2C_FIELD(&data_021015a0, u16 *, 6) > (u32) temp_r3) {
        M2C_FIELD(&data_021015a0, u16 *, 6) = temp_r3;
        M2C_FIELD(&data_021015a0, u16 *, 0xC) = (u16) (1 << (temp_ip - 1));
    } else if (M2C_FIELD(&data_021015a0, u16 *, 6) == temp_r3) {
        M2C_FIELD(&data_021015a0, u16 *, 0xC) = (u16) (M2C_FIELD(&data_021015a0, u16 *, 0xC) | (1 << (temp_ip - 1)));
    }
    temp_r0 = func_0202d788((u16) (temp_ip + 1));
    if (temp_r0 == 0x18) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 7;
        return;
    }
    if (temp_r0 != 2) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
    }
}
