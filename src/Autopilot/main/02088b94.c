#include <m2c.h>


void func_02088b84(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x40000000);
    M2C_FIELD(arg0, s8 *, 0x68) = 0;
    M2C_FIELD(arg0, s8 *, 0x8B) = 0;
}
