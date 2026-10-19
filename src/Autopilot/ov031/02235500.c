#include <m2c.h>

extern void *data_ov031_02290cf4;

void ov13_02239880(s8 arg0) {
    s8 var_r1;

    M2C_FIELD(data_ov031_02290cf4, s8 *, 0x1C) = arg0;
    if (arg0 == 2) {
        var_r1 = 4;
    } else {
        var_r1 = 6;
    }
    M2C_FIELD(data_ov031_02290cf4, s8 *, 0x1D) = var_r1;
}
