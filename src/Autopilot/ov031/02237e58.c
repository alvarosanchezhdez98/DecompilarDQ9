#include <m2c.h>

s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK ov13_022425D0(M2C_UNK, s32);
extern void *data_ov031_02290d10;
extern M2C_UNK ov13_0223C7FC;

void ov13_0223C198(void) {
    ov13_022425D0(0, M2C_FIELD(data_ov031_02290d10, s32 *, 0x14));
    M2C_FIELD(data_ov031_02290d10, s32 *, 0x14) = func_ov031_0223e218(1, &ov13_0223C7FC, 0, 0x78);
}
