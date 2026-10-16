#include <m2c.h>


void func_ov003_0215ca90(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x3C8) = arg1;
    M2C_FIELD(arg0, s32 *, 0x3CC) = (s32) (arg1 * M2C_FIELD(arg0, u8 *, 0x3C3));
}
