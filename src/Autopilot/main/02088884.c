#include <m2c.h>


void func_02088874(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x40);
    M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    M2C_FIELD(arg0, s8 *, 0x82) = 0;
}
