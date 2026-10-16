#include <m2c.h>

extern M2C_UNK data_ov031_02250c0c;

u32 ov13_0222B980(void) {
    return (u32) (M2C_FIELD(&data_ov031_02250c0c, s32 *, 8) << 0x1C) >> 0x1C;
}
