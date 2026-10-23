#include <m2c.h>

void *func_ov004_0215e47c(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov004_021707e8;

s32 func_ov004_02163284(M2C_UNK arg0) {
    void *temp_r0;

    M2C_FIELD(&data_ov004_021707e8, s32 *, 0x20) = -1;
    M2C_FIELD(&data_ov004_021707e8, s32 *, 0x24) = 0;
    temp_r0 = func_ov004_0215e47c(arg0, 9);
    M2C_FIELD(temp_r0, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0, u8 *, 0xC) | 1);
    return 0;
}
