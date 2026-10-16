#include <m2c.h>

extern s32 data_ov031_02290cfc;

u8 ov13_0223A3FC(s32 arg0) {
    return M2C_FIELD((data_ov031_02290cfc + (arg0 << 8)), u8 *, 0xE7);
}
