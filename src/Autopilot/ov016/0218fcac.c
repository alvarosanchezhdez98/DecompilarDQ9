#include <m2c.h>

extern M2C_UNK data_ov016_0219d1c0;

void func_ov016_0218fcac(s32 arg0, s32 arg1) {
    M2C_FIELD(&data_ov016_0219d1c0, s32 *, 0x10) = arg0;
    M2C_FIELD(&data_ov016_0219d1c0, s32 *, 0xC) = (s32) (arg1 & ~3);
    M2C_FIELD(&data_ov016_0219d1c0, s32 *, 4) = 0;
    M2C_FIELD(&data_ov016_0219d1c0, s32 *, 0) = 0;
    M2C_FIELD(&data_ov016_0219d1c0, s32 *, 0x20) = 0;
}
