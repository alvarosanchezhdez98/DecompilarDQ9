#include <m2c.h>

M2C_UNK VectorizedMemset(M2C_UNK *, M2C_UNK, M2C_UNK);
s32 func_0202cddc();
extern M2C_UNK data_021015a0;
extern M2C_UNK data_02101680;
extern M2C_UNK data_0210168a;

s32 func_0202cd50(s32 arg0, void *arg1, s16 arg2) {
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 2;
    M2C_FIELD(&data_021015a0, s32 *, 0x44) = arg0;
    M2C_FIELD(&data_021015a0, s16 *, 8) = arg2;
    M2C_FIELD(&data_02101680, s16 *, 6) = 1;
    M2C_FIELD(&data_021015a0, s16 *, 4) = 0;
    if (arg1 != NULL) {
        M2C_FIELD(&data_02101680, u16 *, 0xE) = (u16) M2C_FIELD(arg1, u16 *, 4);
        M2C_FIELD(&data_02101680, u16 *, 0xC) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(&data_02101680, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0);
    } else {
        VectorizedMemset(&data_0210168a, 0xFF, 6);
    }
    if (func_0202cddc() == 0) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
        return 0;
    }
    return 1;
}
