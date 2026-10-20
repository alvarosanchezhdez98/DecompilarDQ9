#include <m2c.h>

s32 func_020d472c(M2C_UNK *);
M2C_UNK ov13_0223D6A8(M2C_UNK);
M2C_UNK ov13_0223D724();
extern M2C_UNK ov13_0223E380;

void ov13_0223E3EC(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        ov13_0223D724();
        ov13_0223D6A8(0xA);
        return;
    }
    if (func_020d472c(&ov13_0223E380) != 0) {
        ov13_0223D724();
        ov13_0223D6A8(0xA);
        return;
    }
    ov13_0223D6A8(1);
}
