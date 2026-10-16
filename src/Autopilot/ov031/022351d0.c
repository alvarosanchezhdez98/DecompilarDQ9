#include <m2c.h>

extern void *data_ov031_02290cf4;

u8 ov13_02239550(void) {
    return M2C_FIELD(data_ov031_02290cf4, u8 *, 0x1A);
}
