#include <m2c.h>


void func_02088818(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u16 *, 0x22) = (u16) ((M2C_FIELD(arg0, u16 *, 0x22) & ~0xE00) | ((u32) (arg1 << 0x1D) >> 0x14));
    M2C_FIELD(arg0, s8 *, 0x6A) = 5;
    M2C_FIELD(arg0, s8 *, 0x8D) = 0;
}
