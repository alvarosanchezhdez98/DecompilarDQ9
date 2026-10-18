#include <m2c.h>


void func_0205d594(void *arg0, s8 *arg1, s8 *arg2) {
    *arg1 = (s8) ((u32) (M2C_FIELD(arg0, u8 *, 0x1C) << 0x1C) >> 0x1C);
    *arg2 = (s8) ((u32) (M2C_FIELD(arg0, u8 *, 0x1C) << 0x18) >> 0x1C);
}
