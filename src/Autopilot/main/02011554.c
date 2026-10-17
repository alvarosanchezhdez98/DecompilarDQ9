#include <m2c.h>


void func_02011544(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x5CCC) = (s32) ((M2C_FIELD(arg0, s32 *, 0x5CCC) & ~1) | 1);
}
