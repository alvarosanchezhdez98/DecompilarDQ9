#include <m2c.h>

M2C_UNK ov13_0223D6A8(M2C_UNK);
M2C_UNK ov13_0223D724();
s32 ov13_0223DE18();
M2C_UNK ov13_0223E6B4();

void ov13_0223DDE4(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        ov13_0223D724();
        ov13_0223E6B4();
        return;
    }
    if (ov13_0223DE18() != 0) {
        return;
    }
    ov13_0223D6A8(9);
}
