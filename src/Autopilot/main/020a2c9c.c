#include <m2c.h>


void func_020a2c8c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2C5) != 0) {
        M2C_FIELD(arg0, s8 *, 0x2C4) = 2;
    }
}
