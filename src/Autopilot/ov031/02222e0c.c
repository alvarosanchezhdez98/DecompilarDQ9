#include <m2c.h>

extern void *data_ov031_02250ba8;

s8 ov13_02227258(void) {
    return M2C_FIELD(data_ov031_02250ba8, s8 *, 0x16);
}
