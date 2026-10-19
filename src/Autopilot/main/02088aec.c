#include <m2c.h>


void func_02088adc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) ((M2C_FIELD(arg0, s32 *, 0x14) | 0x200000) & ~0x100000);
}
