#include <m2c.h>


void func_02088b64(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x68) = 6;
    M2C_FIELD(arg0, s8 *, 0x8B) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x40000000);
}
