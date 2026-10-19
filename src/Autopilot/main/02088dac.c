#include <m2c.h>


void func_02088d9c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x100);
    M2C_FIELD(arg0, s8 *, 0x7D) = 0;
    M2C_FIELD(arg0, s8 *, 0xA0) = 0;
}
