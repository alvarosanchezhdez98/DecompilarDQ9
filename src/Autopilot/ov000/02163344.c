#include <m2c.h>


void func_ov000_02163344(void *arg0, s32 arg1, s16 arg2, s8 arg3, u16 arg4, u16 arg5) {
    M2C_FIELD(arg0, s32 *, 0x58C4) = arg1;
    M2C_FIELD(arg0, s16 *, 0x58CC) = arg2;
    M2C_FIELD(arg0, s8 *, 0x58C8) = arg3;
    M2C_FIELD(arg0, s8 *, 0x58C9) = (s8) arg4;
    M2C_FIELD(arg0, u16 *, 0x58CA) = arg5;
    M2C_FIELD(arg0, s32 *, 0x55F4) = (s32) (M2C_FIELD(arg0, s32 *, 0x55F4) | 0x2000);
}
