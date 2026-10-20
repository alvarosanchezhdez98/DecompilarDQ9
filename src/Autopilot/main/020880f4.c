#include <m2c.h>


void func_020880e4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~1);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x07000000);
    M2C_FIELD(arg0, s8 *, 0x76) = 0;
    M2C_FIELD(arg0, s8 *, 0x99) = 0;
}
