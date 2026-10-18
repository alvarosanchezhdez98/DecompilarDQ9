#include <m2c.h>


void func_02088a34(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x64) = 4;
    M2C_FIELD(arg0, s8 *, 0x87) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x20000000);
}
