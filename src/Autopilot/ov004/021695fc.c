#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov004_021695fc(void *arg0) {
    VectorizedMemset(arg0, 0, 6);
    memset(arg0 + 6, 0, 0xB);
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) (M2C_FIELD(arg0, u16 *, 0x12) & ~0x3FFF);
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) (M2C_FIELD(arg0, u16 *, 0x12) & ~0x4000);
    VectorizedMemset(arg0 + 0x14, 0, 0x18);
}
