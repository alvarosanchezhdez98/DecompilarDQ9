#include <m2c.h>

M2C_UNK MB_End();
extern void *data_ov031_02290d14;

void ov13_0223D0F4(void) {
    if ((M2C_FIELD(data_ov031_02290d14, u16 *, 0) == 4) && (M2C_FIELD(data_ov031_02290d14, u16 *, 2) == M2C_FIELD(data_ov031_02290d14, u16 *, 0xC))) {
        MB_End();
    }
}
