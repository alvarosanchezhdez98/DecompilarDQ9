#include <m2c.h>


void func_020397ac(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x1CE) = (u8) (M2C_FIELD(arg0, u8 *, 0x1CE) & ~arg1);
}
