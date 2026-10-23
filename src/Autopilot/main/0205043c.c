#include <m2c.h>


void func_0205042c(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0xD9) = arg1;
    M2C_FIELD(arg0, u8 *, 0xD8) = (u8) (M2C_FIELD(arg0, u8 *, 0xD8) | 2);
}
