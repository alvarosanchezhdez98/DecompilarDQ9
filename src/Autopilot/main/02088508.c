#include <m2c.h>


void func_020884f8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x80000);
    M2C_FIELD(arg0, u16 *, 0x22) = (u16) (M2C_FIELD(arg0, u16 *, 0x22) & ~0x3C);
}
