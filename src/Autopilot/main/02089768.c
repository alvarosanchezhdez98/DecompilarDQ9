#include <m2c.h>


void func_02089758(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x3B) = (u8) (M2C_FIELD(arg0, u8 *, 0x3B) & ~2);
    M2C_FIELD(arg0, u8 *, 0x3C) = (u8) (M2C_FIELD(arg0, u8 *, 0x3C) & ~0x40);
    M2C_FIELD(arg0, s8 *, 0x3A) = 0;
}
