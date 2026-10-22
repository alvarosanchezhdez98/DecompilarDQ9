#include <m2c.h>

s8 _ZN7Model3D12GetBoneIndexEPKc(s32, M2C_UNK *);
extern M2C_UNK data_020f048a;
extern M2C_UNK data_020f048f;
extern M2C_UNK data_020f0495;
extern M2C_UNK data_020f049b;
extern M2C_UNK data_020f04a1;
extern M2C_UNK data_020f04a7;
extern M2C_UNK data_020f04ad;

void func_02053e10(void *arg0) {
    s32 temp_r4;

    temp_r4 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_r4 == 0) {
        return;
    }
    M2C_FIELD(arg0, s8 *, 0x1A0) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f048a);
    M2C_FIELD(arg0, s8 *, 0x1A1) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f048f);
    M2C_FIELD(arg0, s8 *, 0x1A2) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f0495);
    M2C_FIELD(arg0, s8 *, 0x1A3) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f049b);
    M2C_FIELD(arg0, s8 *, 0x1A4) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f04a1);
    M2C_FIELD(arg0, s8 *, 0x1A5) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f04a7);
    M2C_FIELD(arg0, s8 *, 0x1A6) = _ZN7Model3D12GetBoneIndexEPKc(temp_r4, &data_020f04ad);
}
