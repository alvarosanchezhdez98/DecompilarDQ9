#include <m2c.h>


void func_0208792c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x800);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x38);
    M2C_FIELD(arg0, s8 *, 0x6F) = 0;
    M2C_FIELD(arg0, s8 *, 0x92) = 0;
}
