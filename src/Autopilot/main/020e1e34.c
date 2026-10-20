#include <m2c.h>


void func_020e1e24(void *arg0, s16 *arg1, s16 *arg2, s32 arg3) {
    *arg1 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), u8 *, 0x38) + 0xC;
    *arg2 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), u8 *, 0x39) + 8 + (arg3 * 0x10);
}
