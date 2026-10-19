#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, s32);
s32 func_ov031_02215fcc();
void *ov00_021EC2A8(M2C_UNK, s32);
extern M2C_UNK data_ov031_0224e5dc;

s32 func_ov031_022162f0(s32 arg0, s32 arg1) {
    void *temp_r0;

    M2C_FIELD(&data_ov031_0224e5dc, void **, 4) = ov00_021EC2A8(1, func_ov031_02215fcc());
    temp_r0 = ov00_021EC2A8(1, 0x794);
    M2C_FIELD(&data_ov031_0224e5dc, void **, 0) = temp_r0;
    VectorizedMemset(temp_r0, 0, 0x794);
    M2C_FIELD(M2C_FIELD(&data_ov031_0224e5dc, void **, 0), s32 *, 0) = arg0;
    M2C_FIELD(M2C_FIELD(&data_ov031_0224e5dc, void **, 0), s32 *, 0x790) = arg1;
    M2C_FIELD(&data_ov031_0224e5dc, s32 *, 8) = 0;
    return 1;
}
