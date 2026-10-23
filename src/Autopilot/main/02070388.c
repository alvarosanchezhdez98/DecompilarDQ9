#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);

void func_02070378(void *arg0) {
    VectorizedMemset(arg0, 0, 0x70);
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 8) = 1;
    M2C_FIELD(arg0, s8 *, 9) = 1;
    M2C_FIELD(arg0, s8 *, 0xB) = -1;
    M2C_FIELD(arg0, s32 *, 0x20) = -1;
    M2C_FIELD(arg0, s32 *, 0x24) = -1;
    M2C_FIELD(arg0, s32 *, 0x28) = -1;
    M2C_FIELD(arg0, s32 *, 0x2C) = -1;
    M2C_FIELD(arg0, s16 *, 0x1E) = -1;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0x6C) = -1;
}
