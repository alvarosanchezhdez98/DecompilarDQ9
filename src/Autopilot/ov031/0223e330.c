#include <m2c.h>

extern s32 data_ov031_02290d9c;

void ov13_02242640(s32 arg0, s8 arg1) {
    M2C_FIELD((data_ov031_02290d9c + (arg0 << 6)), s8 *, 0x38) = arg1;
}
