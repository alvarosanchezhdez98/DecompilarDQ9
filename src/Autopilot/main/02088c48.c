#include <m2c.h>


void func_02088c38(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~2);
    M2C_FIELD(arg0, s8 *, 0x6C) = 0;
    M2C_FIELD(arg0, s8 *, 0x8F) = 0;
}
