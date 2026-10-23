#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
M2C_UNK func_02012a84(M2C_UNK *, s32 *, s32 *);
s32 func_02080dd4(void *, s16, s16, s16, u8 *, s32);
M2C_UNK func_020813ec(void *, s16);
s32 func_020e28dc();
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;
s8 func_020e2918(void *arg0);

u8 func_ov003_021550dc(void *arg0) {
    s32 sp10;
    s32 spC;
    u8 sp8;
    s16 temp_r2;
    s32 temp_r0;
    s32 temp_r0_2;
    void *temp_r4;

    sp8 = 0;
    if (func_02012444(&data_02114e30, 0x401) != 0) {
        sp8 = 1;
    }
    if ((M2C_FIELD(arg0, void **, 0x1C) != NULL) && (func_020e28dc() != 0)) {
        temp_r0 = (s32) func_020e2918(M2C_FIELD(arg0, void **, 0x1C));
        if (temp_r0 >= 0) {
            sp8 = 1;
            *M2C_FIELD(arg0, s16 **, 8) = temp_r0 + 6;
        }
        goto block_14;
    }
    if ((M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) && (M2C_FIELD(arg0, s16 **, 8) != NULL)) {
        temp_r4 = M2C_FIELD(arg0, void **, 0x18);
        func_02012a84(&data_02114e54, &sp10, &spC);
        M2C_FIELD(arg0, s16 *, 0x1E8) = (s16) *M2C_FIELD(arg0, s16 **, 8);
        temp_r0_2 = func_02080dd4(temp_r4, M2C_FIELD(arg0, s16 *, 0x1E6), (s16) sp10, (s16) spC, &sp8, 1);
        if (temp_r0_2 < 0) {
            return 0U;
        }
        *M2C_FIELD(arg0, s16 **, 8) = (s16) temp_r0_2;
        temp_r2 = *M2C_FIELD(arg0, s16 **, 8);
        if (M2C_FIELD(arg0, s16 *, 0x1E8) != temp_r2) {
            M2C_FIELD(temp_r4, s16 *, 0x36) = temp_r2;
            func_020813ec(temp_r4, M2C_FIELD(arg0, s16 *, 0x1E6));
        }
        goto block_14;
    }
block_14:
    return sp8;
}
