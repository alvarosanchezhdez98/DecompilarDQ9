#include <m2c.h>

s32 func_020d2ff0(s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK sprintf(s32, M2C_UNK *, s32);
extern M2C_UNK data_ov003_0217fce0;

void func_ov003_02158140(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        return;
    }
    memset(arg0 + 0xC, 0, 0x38);
    sprintf(arg0 + 0xC + func_020d2ff0(arg0 + 0xC), &data_ov003_0217fce0, arg1);
}
