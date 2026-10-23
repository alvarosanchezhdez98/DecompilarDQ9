#include <m2c.h>


void func_02010124(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3B4) = 0x21;
    M2C_FIELD(arg0, s32 *, 0x3B8) = 0x21;
    M2C_FIELD(arg0, s16 *, 0x3BC) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0x3C4) = 2;
    M2C_FIELD(arg0, s32 *, 0x3C0) = 0x2000;
}
