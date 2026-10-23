#include <m2c.h>


void func_02050440(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0xDA) = arg1;
    M2C_FIELD(arg0, u8 *, 0xD8) = (u8) (M2C_FIELD(arg0, u8 *, 0xD8) | 2);
}
