#include <m2c.h>


void func_02088234(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x800000);
    M2C_FIELD(arg0, s8 *, 0x24) = 0;
}
