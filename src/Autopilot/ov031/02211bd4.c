#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_ov031_02207ce0(M2C_UNK);
extern M2C_UNK data_ov031_0224e5b4;

void ov00_021EC3F0(void *arg0, s16 arg1, s32 arg2, M2C_UNK arg3) {
    if (M2C_FIELD(&data_ov031_0224e5b4, void **, 4) != NULL) {
        return;
    }
    VectorizedMemset(arg0, 0, 0x64);
    M2C_FIELD(arg0, s16 *, 8) = arg1;
    M2C_FIELD(arg0, s16 *, 0xA) = 1;
    M2C_FIELD(arg0, s16 *, 4) = 1;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(&data_ov031_0224e5b4, void **, 4) = arg0;
    func_ov031_02207ce0(arg3);
}
