#include <m2c.h>

M2C_UNK Mat4x3_WriteViewMatrix(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
M2C_UNK _ZN8Vector3iaSERKS_(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_0210a010;
extern M2C_UNK data_0210a05c;
extern M2C_UNK data_0210a250;
extern M2C_UNK data_0210a25c;
extern M2C_UNK data_0210a268;

void func_ov017_02196048(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    _ZN8Vector3iaSERKS_(&data_0210a250, arg0);
    _ZN8Vector3iaSERKS_(&data_0210a25c, arg1);
    _ZN8Vector3iaSERKS_(&data_0210a268, arg2);
    Mat4x3_WriteViewMatrix(arg0, arg1, arg2, &data_0210a05c);
    M2C_FIELD(&data_0210a010, s32 *, 0xFC) = (s32) (M2C_FIELD(&data_0210a010, s32 *, 0xFC) & ~0xE8);
}
