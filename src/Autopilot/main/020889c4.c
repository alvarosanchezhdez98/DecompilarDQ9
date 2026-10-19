#include <m2c.h>


void func_020889b4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x08000000);
    M2C_FIELD(arg0, s8 *, 0x62) = 0;
    M2C_FIELD(arg0, s8 *, 0x85) = 0;
}
