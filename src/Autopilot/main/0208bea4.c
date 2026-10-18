#include <m2c.h>


void func_0208be94(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xD4) != 2) {
        M2C_FIELD(arg0, s16 *, 0xD0) = 0;
        M2C_FIELD(arg0, u16 *, 0xDA) = (u16) (M2C_FIELD(arg0, u16 *, 0xDA) | 1);
    }
}
