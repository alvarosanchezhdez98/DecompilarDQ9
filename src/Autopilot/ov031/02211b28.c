#include <m2c.h>


void *ov00_021EC26C(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = 0x4457434D;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    return arg0 + 0x20;
}
