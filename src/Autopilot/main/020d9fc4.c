#include <m2c.h>


void func_020d9fb4(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) | (1 << arg1));
}
