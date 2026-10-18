#include <m2c.h>


void func_020890d4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x78) = 5;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) | 0x200);
}
