#include <m2c.h>

s32 ov13_0223E8FC();
M2C_UNK ov13_022425D0(M2C_UNK, M2C_UNK);
extern void *data_ov031_02290c44;

void ov13_0222BC2C(M2C_UNK arg0) {
    if (ov13_0223E8FC() == 0) {
        return;
    }
    M2C_FIELD(data_ov031_02290c44, s8 *, 0x1E2A1) = 1;
    ov13_022425D0(0, arg0);
}
