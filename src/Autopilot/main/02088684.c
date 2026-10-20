#include <m2c.h>


void func_02088674(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x80);
    M2C_FIELD(arg0, u16 *, 0x22) = (u16) (M2C_FIELD(arg0, u16 *, 0x22) & ~0xE00);
    M2C_FIELD(arg0, s8 *, 0x6A) = 0;
    M2C_FIELD(arg0, s8 *, 0x8D) = 0;
}
