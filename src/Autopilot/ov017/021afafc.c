#include <m2c.h>


void func_ov017_021afafc(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | (1 << arg1));
}
