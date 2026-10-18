#include <m2c.h>

s32 ov13_0224022C(M2C_UNK, void *, M2C_UNK);
void *ov13_0224128C(M2C_UNK, M2C_UNK);
extern void *data_ov031_02290c40;

void ov13_0222BA08(void) {
    void *temp_r0;

    temp_r0 = ov13_0224128C(0x64, 4);
    data_ov031_02290c40 = temp_r0;
    M2C_FIELD(data_ov031_02290c40, s32 *, 0x60) = ov13_0224022C(8, temp_r0, 0xC);
}
