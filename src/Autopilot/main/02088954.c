#include <m2c.h>


void func_02088944(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x66) = 5;
    M2C_FIELD(arg0, s8 *, 0x89) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x04000000);
}
