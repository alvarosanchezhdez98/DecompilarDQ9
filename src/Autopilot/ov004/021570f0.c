#include <m2c.h>

extern M2C_UNK data_ov004_021707d8;

s8 func_ov004_021570f0(s32 arg0) {
    if (arg0 < 0) {
        return -1;
    }
    if (arg0 >= (s32) M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), s16 *, 0x3A)) {
        return -1;
    }
    return (s8) M2C_FIELD((M2C_FIELD(&data_ov004_021707d8, void **, 8) + (arg0 * 2)), s16 *, 0x32);
}
