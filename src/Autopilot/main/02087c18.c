#include <m2c.h>


void func_02087c08(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x4000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x7000);
    M2C_FIELD(arg0, s8 *, 0x72) = 0;
    M2C_FIELD(arg0, s8 *, 0x95) = 0;
}
