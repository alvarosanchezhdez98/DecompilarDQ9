#include <m2c.h>

M2C_UNK ov13_0222936C(M2C_UNK);
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern void *data_ov031_02250bfc;

void ov13_02228C38(void) {
    M2C_UNK var_r0;

    if (M2C_FIELD(data_ov031_02250bfc, u8 *, 0x11D) != 1) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    ov13_0222936C(var_r0);
    ov13_0223ABB8(1);
}
