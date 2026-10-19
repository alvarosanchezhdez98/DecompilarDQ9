#include <m2c.h>


void func_02088a04(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x10000000);
    M2C_FIELD(arg0, s8 *, 0x63) = 0;
    M2C_FIELD(arg0, s8 *, 0x86) = 0;
}
