#include <m2c.h>


void func_020d771c(void *arg0) {
    M2C_FIELD(arg0, u16 *, 0xA26) = (u16) (M2C_FIELD(arg0, u16 *, 0xA26) | (u16) (M2C_FIELD(arg0, u16 *, 0xA24) & 0xFF0));
}
