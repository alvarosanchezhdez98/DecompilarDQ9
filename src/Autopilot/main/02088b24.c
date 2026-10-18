#include <m2c.h>


void func_02088b14(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x67) = 6;
    M2C_FIELD(arg0, s8 *, 0x8A) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x400000);
}
