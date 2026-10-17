#include <m2c.h>


void func_ov017_021afae8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x1F) = (u8) (M2C_FIELD(arg0, u8 *, 0x1F) | (1 << arg1));
}
