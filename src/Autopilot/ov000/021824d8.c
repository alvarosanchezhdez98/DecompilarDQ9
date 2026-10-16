#include <m2c.h>


void func_ov000_021824d8(void *arg0) {
    s16 temp_r2;
    s16 temp_r2_2;

    temp_r2 = M2C_FIELD(arg0, s16 *, 0x6EA);
    if ((s32) temp_r2 > 0) {
        M2C_FIELD(arg0, s16 *, 0x6EA) = (s16) (temp_r2 - 1);
    }
    temp_r2_2 = M2C_FIELD(arg0, s16 *, 0x6EC);
    if ((s32) temp_r2_2 <= 0) {
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x6EC) = (s16) (temp_r2_2 - 1);
    if (M2C_FIELD(arg0, s16 *, 0x6EC) == 0) {
        M2C_FIELD(arg0, s8 *, 0x6E8) = 0;
        M2C_FIELD(arg0, s8 *, 0x6E9) = 0;
    }
}
