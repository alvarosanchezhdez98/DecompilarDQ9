#include <m2c.h>

extern M2C_UNK data_ov031_02250c0c;

u8 ov13_0222B9C8(void) {
    if (M2C_FIELD(&data_ov031_02250c0c, u8 *, 0) == 6) {
        return 0x38U;
    }
    if ((M2C_FIELD(&data_ov031_02250c0c, u8 *, 0) == 1) && !(((u32) M2C_FIELD(&data_ov031_02250c0c, u32 *, 8) >> 4) & 2)) {
        return 0x37U;
    }
    return (u8) (M2C_FIELD(&data_ov031_02250c0c, u8 *, 0) + 0x31);
}
