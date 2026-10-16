#include <m2c.h>

extern void *data_ov031_02250bfc;

u8 ov13_022283EC(void) {
    return M2C_FIELD(data_ov031_02250bfc, u8 *, 0x11C);
}
