#include <m2c.h>


void func_ov000_02163404(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x5901) = arg1;
    M2C_FIELD(arg0, s32 *, 0x55F4) = (s32) (M2C_FIELD(arg0, s32 *, 0x55F4) | 0x8000);
}
