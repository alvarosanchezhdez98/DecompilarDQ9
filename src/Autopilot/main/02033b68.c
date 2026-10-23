#include <m2c.h>


void func_02033b58(void *arg0, u8 arg1) {
    M2C_FIELD(arg0, u8 *, 0xBF) = (u8) M2C_FIELD(arg0, u8 *, 0xBE);
    M2C_FIELD(arg0, u8 *, 0xBE) = arg1;
}
