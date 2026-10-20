#include <m2c.h>

M2C_UNK ov13_0223D6A8(M2C_UNK);
M2C_UNK ov13_0223D724();
s32 ov13_0223D7F4();
s32 ov13_0223D890();
extern M2C_UNK data_ov031_02290d18;

void ov13_0223D788(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        ov13_0223D724();
        ov13_0223D6A8(9);
        return;
    }
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x13AC) != 0) {
        if (ov13_0223D7F4() != 0) {
            return;
        }
        ov13_0223D6A8(9);
        return;
    }
    if (ov13_0223D890() != 0) {
        return;
    }
    ov13_0223D6A8(9);
}
