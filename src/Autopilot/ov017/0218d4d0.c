#include <m2c.h>


void func_ov017_0218d4d0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x4331) = (u8) (M2C_FIELD(arg0, u8 *, 0x4331) & ~(1 << arg1));
}
