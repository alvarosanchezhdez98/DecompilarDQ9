#include <m2c.h>

extern s32 data_ov000_02184220;

void func_ov000_02160d80(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xEA8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xEAC) = 0;
    data_ov000_02184220 = 1;
}
