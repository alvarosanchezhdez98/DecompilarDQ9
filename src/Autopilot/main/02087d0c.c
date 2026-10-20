#include <m2c.h>


void func_02087cfc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x8000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x38000);
    M2C_FIELD(arg0, s8 *, 0x73) = 0;
    M2C_FIELD(arg0, s8 *, 0x96) = 0;
}
