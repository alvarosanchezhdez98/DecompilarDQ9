#include <m2c.h>
#pragma optimization_level 4

M2C_UNK memcpy(s32, s32, M2C_UNK);

s32 func_ov001_02157c1c(s32 arg0, s32 arg1) {
    memcpy(arg1 + 0x58, arg0 + 0x10, 0xC);
    return 0;
}
