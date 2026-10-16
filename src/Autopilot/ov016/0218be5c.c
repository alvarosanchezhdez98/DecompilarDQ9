#include <m2c.h>

extern M2C_UNK data_ov016_0219d0c0;

s32 func_ov016_0218be5c(void) {
    if (M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x18) == 0) {
        return 0x06820000;
    }
    return 0x06800000;
}
