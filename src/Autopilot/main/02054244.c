#include <m2c.h>
#pragma optimization_level 4


void func_02054234(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18C) = (s32) ((M2C_FIELD(arg0, s32 *, 0x18C) & ~0x80) | 0x100);
}
