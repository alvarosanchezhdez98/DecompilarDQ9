#include <m2c.h>


void func_020a367c(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x34) = (u8) (M2C_FIELD(arg0, u8 *, 0x34) & ~(1 << arg1));
}
