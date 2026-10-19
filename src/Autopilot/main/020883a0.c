#include <m2c.h>


void func_02088390(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x10);
    M2C_FIELD(arg0, s8 *, 0x5D) = 0;
    M2C_FIELD(arg0, s8 *, 0x80) = 0;
}
