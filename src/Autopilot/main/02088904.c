#include <m2c.h>


void func_020888f4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x61) = 5;
    M2C_FIELD(arg0, s8 *, 0x84) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x200);
}
