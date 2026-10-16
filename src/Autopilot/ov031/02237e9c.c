#include <m2c.h>

extern void *data_ov031_02290d10;

s8 ov13_0223C1DC(void) {
    return M2C_FIELD(data_ov031_02290d10, s8 *, 0x1B);
}
