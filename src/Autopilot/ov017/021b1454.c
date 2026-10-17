#include <m2c.h>


void func_ov017_021b1454(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0xA) = (u8) (M2C_FIELD(arg0, u8 *, 0xA) & ~(1 << arg1));
}
