#include <m2c.h>

extern s32 data_ov002_0216c9c0[7];

void func_ov002_0215a9cc(void *arg0, s8 arg1) {
    M2C_FIELD((arg0 + data_ov002_0216c9c0[M2C_FIELD(arg0, s16 *, 0x1C0A)]), s8 *, 0x1C7C) = arg1;
}
