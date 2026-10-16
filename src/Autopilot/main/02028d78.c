#include <m2c.h>

extern M2C_UNK data_020ef74c;

void func_02028d68(s32 arg0) {
    M2C_FIELD(&data_020ef74c, s32 *, 0xC) = arg0;
    if (arg0 == 0) {
        M2C_FIELD(&data_020ef74c, s32 *, 4) = 8;
        M2C_FIELD(&data_020ef74c, s32 *, 8) = 8;
        return;
    }
    if ((u32) (arg0 - 1) <= 1U) {
        M2C_FIELD(&data_020ef74c, s32 *, 8) = 6;
        M2C_FIELD(&data_020ef74c, s32 *, 4) = 0xC;
        return;
    }
    if ((u32) (arg0 - 3) <= 1U) {
        M2C_FIELD(&data_020ef74c, s32 *, 8) = 5;
        M2C_FIELD(&data_020ef74c, s32 *, 4) = 0xA;
        return;
    }
    if ((u32) (arg0 - 5) <= 1U) {
        M2C_FIELD(&data_020ef74c, s32 *, 8) = 6;
        M2C_FIELD(&data_020ef74c, s32 *, 4) = 0xC;
    }
}
