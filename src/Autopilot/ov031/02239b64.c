#include <m2c.h>

M2C_UNK ov13_0223D6A8(M2C_UNK);
M2C_UNK ov13_0223D724(u16);

void ov13_0223DEA4(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        ov13_0223D6A8(9);
        ov13_0223D724(M2C_FIELD(arg0, u16 *, 2));
        return;
    }
    ov13_0223D6A8(1);
}
