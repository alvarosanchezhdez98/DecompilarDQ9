#include <m2c.h>

void *func_ov004_0215e47c(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov004_021707e8;
void _ZN16MenuObjectClass54LoadEii(void *, s32, s32);

s32 func_ov004_02162a9c(M2C_UNK arg0) {
    void *temp_r0;

    temp_r0 = func_ov004_0215e47c(arg0, 0x82);
    if (temp_r0 != NULL) {
        _ZN16MenuObjectClass54LoadEii(temp_r0, M2C_FIELD(&data_ov004_021707e8, s32 *, 0x1C), 1);
    }
    return 0;
}
