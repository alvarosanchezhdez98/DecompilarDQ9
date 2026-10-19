#include <m2c.h>

extern M2C_UNK data_ov031_02290d40;

s32 ov13_022416D4(s32 arg0) {
    if (((s32) (*(u16 *)0x027FFFA8 & 0x8000) >> 0xF) != 0) {
        return 0;
    }
    if (arg0 == (arg0 & M2C_FIELD(M2C_FIELD(&data_ov031_02290d40, void **, 4), u16 *, 0x34))) {
        return 1;
    }
    return 0;
}
