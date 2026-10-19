#include <m2c.h>


void func_02086598(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u16 *, 0x54) = (u16) (M2C_FIELD(arg0, u16 *, 0x54) | (1 << arg1));
    M2C_FIELD(arg0, s32 *, 0x50) = arg1;
}
