#include <m2c.h>

void *func_0200ff1c(M2C_UNK, s32);

void func_ov017_021cee34(s32 arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_r4;
    s32 temp_r5;
    void *temp_r0;

    temp_r4 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_r5 = M2C_FIELD(arg1, s32 *, 8);
    temp_r0 = func_0200ff1c(arg2, M2C_FIELD(arg1, s32 *, 4));
    if (temp_r0 == NULL) {
        return;
    }
    if (temp_r4 != 0) {
        M2C_FIELD(temp_r0, s32 *, 0x18C) = (s32) (M2C_FIELD(temp_r0, s32 *, 0x18C) | temp_r5);
        return;
    }
    M2C_FIELD(temp_r0, s32 *, 0x18C) = (s32) (M2C_FIELD(temp_r0, s32 *, 0x18C) & ~temp_r5);
}
