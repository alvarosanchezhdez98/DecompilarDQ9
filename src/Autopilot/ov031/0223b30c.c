#include <m2c.h>

extern void *data_ov031_02290d20;

u16 ov13_0223F64C(void) {
    return M2C_FIELD(data_ov031_02290d20, u16 *, 0x144);
}
