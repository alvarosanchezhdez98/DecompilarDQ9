#include <m2c.h>

s32 func_020d2ff0(void *);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK sprintf(void *, M2C_UNK *, s32);
extern M2C_UNK data_ov002_0216d2fc;

void func_ov002_02168ca8(void *arg0, void *arg1) {
    s32 temp_r0;
    s32 temp_r4;

    if (arg1 == NULL) {
        return;
    }
    temp_r0 = arg0 + 0x44;
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 4) = temp_r0;
    temp_r4 = M2C_FIELD(arg1, s32 *, 4);
    if (temp_r4 == 0) {
        return;
    }
    memset(temp_r0, 0, 0x200);
    sprintf(arg0 + 0x44 + func_020d2ff0(arg0 + 0x44), &data_ov002_0216d2fc, temp_r4);
}
