#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_020e2c7c(void *);
M2C_UNK func_020e2cc4(void *, M2C_UNK);

void func_020e2bd8(void *arg0, s8 arg1, s8 arg2) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = arg1;
    M2C_FIELD(arg0, s8 *, 2) = arg2;
    VectorizedMemset(arg0 + 0x14, 0, 0x10);
    M2C_FIELD(arg0, s32 *, 4) = 5;
    M2C_FIELD(arg0, s32 *, 8) = 1;
    M2C_FIELD(arg0, s32 *, 0xC) = 0x1F;
    M2C_FIELD(arg0, s32 *, 0x10) = 1;
    func_020e2cc4(arg0, 0);
    func_020e2c7c(arg0);
}
