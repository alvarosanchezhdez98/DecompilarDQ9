#include <m2c.h>


void func_020890a4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x40);
    M2C_FIELD(arg0, s8 *, 0x7A) = 0;
    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
}
