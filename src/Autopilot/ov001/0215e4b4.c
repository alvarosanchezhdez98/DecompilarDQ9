#include <m2c.h>

void *func_020421a0();
s32 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_0215e4b4(M2C_UNK arg0) {
    s32 temp_r0_2;
    void *temp_r0;

    temp_r0 = func_020421a0();
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r0_2 = func_ov017_021d60f4(arg0);
    M2C_FIELD(temp_r0, u8 *, 0x195B) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x195B) | 4);
    M2C_FIELD(temp_r0, s32 *, 0x9A8) = temp_r0_2;
    return 1;
}
