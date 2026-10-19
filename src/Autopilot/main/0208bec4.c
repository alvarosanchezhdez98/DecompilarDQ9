#include <m2c.h>


void func_0208beb4(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xD4) != 3) {
        M2C_FIELD(arg0, u16 *, 0xDA) = (u16) (M2C_FIELD(arg0, u16 *, 0xDA) | 2);
    }
}
