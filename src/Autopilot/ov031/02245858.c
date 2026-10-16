#include <m2c.h>

extern M2C_UNK data_ov031_02291f24;

void func_ov031_02245858(s32 arg0, s8 arg1) {
    M2C_FIELD(&data_ov031_02291f24, s32 *, 0x14) = arg0;
    M2C_FIELD(&data_ov031_02291f24, s8 *, 0) = arg1;
}
