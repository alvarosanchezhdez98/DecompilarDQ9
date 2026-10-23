#include <m2c.h>

M2C_UNK memcpy(s32, s32, M2C_UNK);

s32 func_ov001_021594ac(s32 arg0, s32 arg1) {
    memcpy(arg1 + 0x80, arg0 + 4, 0xC);
    return 0;
}
