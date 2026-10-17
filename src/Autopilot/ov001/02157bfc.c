#include <m2c.h>
#pragma optimization_level 4

M2C_UNK memcpy(s32, s32, M2C_UNK);

s32 func_ov001_02157bfc(s32 arg0, s32 arg1) {
    memcpy(arg1 + 0x4C, arg0 + 4, 0xC);
    return 0;
}
