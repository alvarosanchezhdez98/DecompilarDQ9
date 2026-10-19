#include <m2c.h>

M2C_UNK ov13_0223FF18(s32, M2C_UNK, u16, s32);
extern void *data_ov031_02290cf4;

void ov13_02239AC4(s8 arg0) {
    ov13_0223FF18(M2C_FIELD(data_ov031_02290cf4, s32 *, 0), -1, M2C_FIELD(data_ov031_02290cf4, u16 *, 0x10), arg0 + M2C_FIELD(data_ov031_02290cf4, u16 *, 0x12));
    M2C_FIELD(data_ov031_02290cf4, s8 *, 0x1A) = arg0;
}
