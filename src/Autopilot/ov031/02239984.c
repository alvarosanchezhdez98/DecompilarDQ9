#include <m2c.h>

M2C_UNK ov13_0223D724();
s32 ov13_0223DD18();
M2C_UNK ov13_0223E698();
extern M2C_UNK data_ov031_0224c3f4;
extern M2C_UNK (*data_ov031_02290d18)(M2C_UNK, M2C_UNK *);

void ov13_0223DCC4(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        ov13_0223D724();
        ov13_0223E698();
        return;
    }
    if (ov13_0223DD18() != 0) {
        return;
    }
    if (data_ov031_02290d18 != NULL) {
        data_ov031_02290d18(0x08000000, &data_ov031_0224c3f4);
    }
    ov13_0223E698();
}
