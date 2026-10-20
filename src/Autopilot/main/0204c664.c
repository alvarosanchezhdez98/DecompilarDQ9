#include <m2c.h>


void func_0204c654(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    void *temp_ip;

    if (arg1 < 0) {
        return;
    }
    if (arg1 >= 0x12) {
        return;
    }
    temp_ip = arg0 + (arg1 * 2);
    M2C_FIELD(temp_ip, s16 *, 0xC) = arg2;
    M2C_FIELD(temp_ip, s16 *, 0x30) = arg3;
    M2C_FIELD(temp_ip, s16 *, 0x54) = arg4;
    M2C_FIELD(temp_ip, s16 *, 0x78) = arg5;
}
