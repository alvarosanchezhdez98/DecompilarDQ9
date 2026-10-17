#include <m2c.h>

extern void *data_ov031_02290d34;

u8 ov13_02240394(s32 arg0) {
    void *var_r0;

    if (arg0 == 1) {
        var_r0 = data_ov031_02290d34;
    } else {
        var_r0 = data_ov031_02290d34 + 0xC;
    }
    return M2C_FIELD(var_r0, u8 *, 9);
}
