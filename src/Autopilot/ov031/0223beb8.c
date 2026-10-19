#include <m2c.h>

void *ov13_0224128C(s32, M2C_UNK);

void ov13_022401F8(s32 arg0) {
    void *temp_r0;

    temp_r0 = ov13_0224128C(((arg0 + 1) * 4) + 8, 4);
    M2C_FIELD(temp_r0, s16 *, 0) = (s16) (arg0 + 1);
    M2C_FIELD(temp_r0, s8 *, 2) = 0;
    M2C_FIELD(temp_r0, s8 *, 3) = 0;
}
