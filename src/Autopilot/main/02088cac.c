#include <m2c.h>


void func_02088c9c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~4);
    M2C_FIELD(arg0, s8 *, 0x6D) = 0;
    M2C_FIELD(arg0, s8 *, 0x90) = 0;
}
