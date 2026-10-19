#include <m2c.h>


void func_020882dc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~8);
    M2C_FIELD(arg0, s8 *, 0x5C) = 0;
    M2C_FIELD(arg0, s8 *, 0x7F) = 0;
}
