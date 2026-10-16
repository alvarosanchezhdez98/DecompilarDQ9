#include <m2c.h>

extern M2C_UNK data_ov031_02250c0c;

void ov13_0222B8F8(s32 arg0, s32 arg1) {
    M2C_FIELD(&data_ov031_02250c0c, s32 *, 0x10) = arg0;
    M2C_FIELD(&data_ov031_02250c0c, s32 *, 0x14) = arg1;
}
