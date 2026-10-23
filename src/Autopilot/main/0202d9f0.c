#include <m2c.h>

M2C_UNK VectorizedMemset(M2C_UNK *, M2C_UNK, M2C_UNK);
s32 func_020d4f7c(M2C_UNK *, M2C_UNK (*)(), M2C_UNK);
M2C_UNK func_0202c848();
M2C_UNK func_0202dae0();
M2C_UNK func_0202db08();
extern M2C_UNK data_021015a0;
extern M2C_UNK data_02101614;
extern M2C_UNK data_02101640;
extern M2C_UNK data_021016e0;
extern M2C_UNK data_02101b80;
extern M2C_UNK data_02103400;

s32 func_0202d9e0(void) {
    s32 var_r0;

    if (M2C_FIELD(&data_021015a0, u16 *, 0xE) != 0) {
        return 0;
    }
    if (M2C_FIELD(&data_021015a0, M2C_UNK (**)(), 0x40) == NULL) {
        M2C_FIELD(&data_021015a0, M2C_UNK (**)(), 0x40) = func_0202dae0;
    }
    M2C_FIELD(&data_021015a0, s32 *, 0x2C) = 0;
    M2C_FIELD(&data_021015a0, s32 *, 0x38) = 0;
    M2C_FIELD(&data_021015a0, s32 *, 0x28) = 0;
    M2C_FIELD(&data_021015a0, s16 *, 0) = 0;
    M2C_FIELD(&data_021015a0, s16 *, 0xA) = 1;
    M2C_FIELD(&data_021015a0, s32 *, 0x48) = 0;
    M2C_FIELD(&data_02101640, s32 *, 0) = 0;
    M2C_FIELD(&data_02101640, s16 *, 4) = 0;
    VectorizedMemset(&data_02101b80, 0, 0x400);
    VectorizedMemset(&data_021016e0, 0, 0xC0);
    VectorizedMemset(&data_02101614, 0, 0x18);
    M2C_FIELD(&data_021015a0, s32 *, 0x24) = 0;
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    if (func_020d4f7c(&data_02103400, func_0202db08, 2) == 2) {
        var_r0 = 1;
    } else {
        func_0202c848();
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 0xA;
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        return 0;
    }
    M2C_FIELD(&data_021015a0, u16 *, 0xE) = 1U;
    return 1;
}
