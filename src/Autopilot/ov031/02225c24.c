#include <m2c.h>

extern void *data_ov031_02250c00;

u8 ov13_0222A070(void) {
    return M2C_FIELD(data_ov031_02250c00, u8 *, 0x60);
}
