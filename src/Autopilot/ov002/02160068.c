#include <m2c.h>

M2C_UNK func_02041ea4(s32, s16);
M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_0205de24(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_0205deb4(void *, M2C_UNK, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_0215be00(void *, u8, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_021601e0(void *, s32, M2C_UNK);

void func_ov002_02160068(void *arg0) {
    func_0205de24(arg0 + 0xEC8, 0, 3);
    func_ov002_0215be00(arg0, 0x1DU, 0x15, 0xB);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_ov002_021601e0(arg0, M2C_FIELD(arg0, s32 *, 0x1BD0), 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 1, 0, 0);
    func_0205de24(arg0 + 0xEC8, 0, 3);
    func_ov002_0215be00(arg0, (u8) M2C_FIELD(arg0, s32 *, 0x1BB8), 4, 3);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_02041ea4(M2C_FIELD(arg0, s32 *, 0x1BD0), M2C_FIELD(arg0, s16 *, 0x1C06));
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 1, 0, 0);
    func_0205deb4(arg0 + 0xEC8, 0x1D, 0);
}
