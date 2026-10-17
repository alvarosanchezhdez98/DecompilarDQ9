#include <m2c.h>


void func_ov017_021b2bf4(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((M2C_FIELD(arg0, s32 *, 0x38) & ~0x10) | ((u32) (arg1 << 0x1F) >> 0x1B));
}
