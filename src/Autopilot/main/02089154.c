#include <m2c.h>


void func_02089144(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x400);
    M2C_FIELD(arg0, s8 *, 0x79) = 0;
    M2C_FIELD(arg0, s8 *, 0x9C) = 0;
}
