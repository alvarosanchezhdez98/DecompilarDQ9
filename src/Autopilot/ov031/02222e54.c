#include <m2c.h>

extern void *data_ov031_02250ba8;

s32 ov13_022272A0(void) {
    if (data_ov031_02250ba8 == NULL) {
        return 1;
    }
    if (M2C_FIELD(data_ov031_02250ba8, u8 *, 0x19) == 0) {
        return 1;
    }
    return 0;
}
