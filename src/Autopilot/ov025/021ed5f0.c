#include <m2c.h>


void func_ov025_021ed5f0(void *arg0, s32 arg1, s32 arg2, s8 arg3) {
    u8 temp_ip;

    if (arg2 >= 6) {
        return;
    }
    temp_ip = M2C_FIELD(arg0, u8 *, 0x151);
    if ((u32) temp_ip >= 0x10U) {
        return;
    }
    M2C_FIELD((arg0 + (temp_ip * 4)), s32 *, 0xF0) = arg1;
    M2C_FIELD((arg0 + M2C_FIELD(arg0, u8 *, 0x151)), s8 *, 0x130) = (s8) arg2;
    M2C_FIELD((arg0 + M2C_FIELD(arg0, u8 *, 0x151)), s8 *, 0x140) = arg3;
    M2C_FIELD(arg0, u8 *, 0x151) = (u8) (M2C_FIELD(arg0, u8 *, 0x151) + 1);
}
