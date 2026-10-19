#include <m2c.h>

void *ov00_021FAE14(M2C_UNK);
extern M2C_UNK data_ov031_0224e5c4;

void ov00_021FAC8C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u8 temp_r2;
    void *temp_r0;

    temp_r0 = ov00_021FAE14(1);
    if (temp_r0 == NULL) {
        return;
    }
    temp_r2 = M2C_FIELD(temp_r0, u8 *, 8);
    if (!(temp_r2 & arg0)) {
        return;
    }
    M2C_FIELD(temp_r0, u8 *, 8) = (u8) (temp_r2 & ~arg0);
    M2C_FIELD(temp_r0, M2C_UNK (**)(s32, M2C_UNK, M2C_UNK), 4)(arg0, arg1, arg2);
    if (arg0 == 1) {
        M2C_FIELD(&data_ov031_0224e5c4, s32 *, 0xC) = 0;
    }
}
