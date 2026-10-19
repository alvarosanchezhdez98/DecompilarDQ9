#include <m2c.h>


void func_02088bd4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x80000000);
    M2C_FIELD(arg0, s8 *, 0x69) = 0;
    M2C_FIELD(arg0, s8 *, 0x8C) = 0;
}
