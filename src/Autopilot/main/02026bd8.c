#include <m2c.h>


void func_02026bc8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0xA96) = (u8) (M2C_FIELD(arg0, u8 *, 0xA96) | (1 << arg1));
}
