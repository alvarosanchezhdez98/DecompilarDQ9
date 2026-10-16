#include <m2c.h>

extern void *data_ov031_02250ba8;

void ov13_0222726C(s8 arg0) {
    if (M2C_FIELD(data_ov031_02250ba8, s8 *, 0x16) == -1) {
        M2C_FIELD(data_ov031_02250ba8, s8 *, 0x16) = arg0;
    }
}
