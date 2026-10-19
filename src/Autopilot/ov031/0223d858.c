#include <m2c.h>

void *ov13_0224128C(M2C_UNK, M2C_UNK);

void ov13_02241B98(void) {
    void *temp_r0;

    temp_r0 = ov13_0224128C(0x10, 4);
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, void **, 4) = (void *) (temp_r0 + 8);
    M2C_FIELD(temp_r0, void **, 8) = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0xC) = 0;
}
