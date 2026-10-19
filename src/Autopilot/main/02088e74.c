#include <m2c.h>


void func_02088e64(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x1000);
    M2C_FIELD(arg0, s8 *, 0x7E) = 0;
    M2C_FIELD(arg0, s8 *, 0xA1) = 0;
}
