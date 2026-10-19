#include <m2c.h>

M2C_UNK ov13_0223D66C(void *);
extern void *data_ov031_02290d14;

void ov13_0223C9D4(void *arg0) {
    data_ov031_02290d14 = arg0;
    ov13_0223D66C(arg0 + 0x1B160);
    M2C_FIELD(data_ov031_02290d14, s32 *, 0x1B140) = 0;
    M2C_FIELD(data_ov031_02290d14, s32 *, 0x1B144) = 0;
}
