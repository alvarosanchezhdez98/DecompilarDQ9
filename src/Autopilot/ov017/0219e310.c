#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_0204693c();

void func_ov017_0219e310(void *arg0, s32 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 1;
    M2C_FIELD(arg0, s8 *, 0xB) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0;
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    M2C_FIELD(arg0, s16 *, 0x22) = 0;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    if ((M2C_FIELD(arg0, s16 *, 0x12) != 0) && (arg1 == 0)) {
        return;
    }
    VectorizedMemset(arg0 + 0x12, 0, 0xE);
}
