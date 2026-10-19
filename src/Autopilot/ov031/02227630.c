#include <m2c.h>

s32 ov13_0223F95C(M2C_UNK, M2C_UNK *, M2C_UNK);
void *ov13_022402E0(s32);
extern void *data_ov031_02290c40;

void *ov13_0222BA58(M2C_UNK arg0) {
    M2C_UNK sp0;
    s32 temp_r0;
    void *temp_r2;
    void *temp_r4;

    temp_r4 = ov13_022402E0(M2C_FIELD(data_ov031_02290c40, s32 *, 0x60));
    temp_r0 = ov13_0223F95C(arg0, &sp0, 4);
    temp_r2 = temp_r0 + 0x20;
    M2C_FIELD(temp_r4, s32 *, 8) = temp_r0;
    M2C_FIELD(temp_r4, s32 *, 0) = (s32) (temp_r2 + 0x10);
    M2C_FIELD(temp_r4, void **, 4) = (void *) (temp_r2 + M2C_FIELD(temp_r2, s32 *, 4) + 8);
    return temp_r4;
}
