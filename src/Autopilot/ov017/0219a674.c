#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);

void func_ov017_0219a674(void *arg0) {
    VectorizedMemset(arg0, 0, 0x14);
    M2C_FIELD(arg0, s8 *, 0) = 0xF;
    M2C_FIELD(arg0, s8 *, 1) = 0x12;
    M2C_FIELD(arg0, s16 *, 2) = 0xFF;
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0x3244;
}
