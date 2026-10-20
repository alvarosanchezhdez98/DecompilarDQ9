#include <m2c.h>

M2C_UNK sprintf(s32, M2C_UNK *, s32);
extern M2C_UNK data_020ef078;

void func_0204887c(void *arg0, s32 arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x148);
    M2C_FIELD(arg0, s32 *, 0x148) = arg1;
    if (temp_r2 == 0) {
        return;
    }
    sprintf(M2C_FIELD(arg0, s32 *, 0x148) + 0x2C, &data_020ef078, temp_r2 + 0x2C);
}
