#include <m2c.h>


void func_020863c4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16) M2C_FIELD(arg0, u16 *, 0x6C);
    M2C_FIELD(arg0, u16 *, 0x1E) = (u16) M2C_FIELD(arg0, u16 *, 0x6E);
}
