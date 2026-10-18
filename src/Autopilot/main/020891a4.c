#include <m2c.h>


void func_02089194(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x800);
    M2C_FIELD(arg0, s8 *, 0x7C) = 0;
    M2C_FIELD(arg0, s8 *, 0x9F) = 0;
}
