#include <m2c.h>


void func_02087ff0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x02000000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x38000000);
    M2C_FIELD(arg0, s8 *, 0x77) = 0;
    M2C_FIELD(arg0, s8 *, 0x9A) = 0;
}
