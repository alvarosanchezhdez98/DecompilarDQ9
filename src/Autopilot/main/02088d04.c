#include <m2c.h>


void func_02088cf4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~8);
    M2C_FIELD(arg0, s8 *, 0x6B) = 0;
    M2C_FIELD(arg0, s8 *, 0x8E) = 0;
}
