#include <m2c.h>

extern M2C_UNK data_ov031_02250c0c;

s32 ov13_0222B998(s32 arg0) {
    if (arg0 & ((u32) M2C_FIELD(&data_ov031_02250c0c, u32 *, 8) >> 4)) {
        return 1;
    }
    return 0;
}
