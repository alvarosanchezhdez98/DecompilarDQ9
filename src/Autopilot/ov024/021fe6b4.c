#include <m2c.h>


void func_ov024_021fe6b4(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x3C) = arg1;
    M2C_FIELD(arg0, u8 *, 0x40) = (u8) M2C_FIELD((arg0 + arg1), u8 *, 0x10);
}
