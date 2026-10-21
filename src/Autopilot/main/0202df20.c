#include <m2c.h>

s32 func_020d503c(M2C_UNK (*)());
M2C_UNK func_0202d664();
extern M2C_UNK data_021015a0;

s32 func_0202df10(void) {
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    if (func_020d503c(func_0202d664) != 2) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
        return 0;
    }
    M2C_FIELD(&data_021015a0, s16 *, 0xE) = 0;
    return 1;
}
