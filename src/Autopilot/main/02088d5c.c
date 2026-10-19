#include <m2c.h>


void func_02088d4c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x10);
    M2C_FIELD(arg0, s8 *, 0x7B) = 0;
    M2C_FIELD(arg0, s8 *, 0x9E) = 0;
}
