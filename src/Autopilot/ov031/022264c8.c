#include <m2c.h>

M2C_UNK ov13_0222AD5C(s8, M2C_UNK);
extern void *data_ov031_02250c00;

void ov13_0222A914(s8 arg0) {
    if (arg0 == M2C_FIELD(data_ov031_02250c00, s8 *, 0x62)) {
        return;
    }
    ov13_0222AD5C(arg0, 1);
    ov13_0222AD5C(M2C_FIELD(data_ov031_02250c00, s8 *, 0x62), 0);
    M2C_FIELD(data_ov031_02250c00, s8 *, 0x62) = arg0;
}
