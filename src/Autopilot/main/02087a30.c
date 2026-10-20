#include <m2c.h>


void func_02087a20(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x1000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x1C0);
    M2C_FIELD(arg0, s8 *, 0x70) = 0;
    M2C_FIELD(arg0, s8 *, 0x93) = 0;
}
