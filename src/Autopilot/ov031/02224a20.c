#include <m2c.h>

M2C_UNK ov13_022293F0(s8, M2C_UNK);
extern void *data_ov031_02250bfc;

void ov13_02228E6C(s8 arg0) {
    if (arg0 == M2C_FIELD(data_ov031_02250bfc, s8 *, 0x11F)) {
        return;
    }
    ov13_022293F0(arg0, 1);
    ov13_022293F0(M2C_FIELD(data_ov031_02250bfc, s8 *, 0x11F), 0);
    M2C_FIELD(data_ov031_02250bfc, s8 *, 0x11F) = arg0;
}
