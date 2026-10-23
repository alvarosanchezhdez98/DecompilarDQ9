#include <m2c.h>


void func_020340c4(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0xC2) = (u8) (M2C_FIELD(arg0, u8 *, 0xC2) & ~0x80);
}
