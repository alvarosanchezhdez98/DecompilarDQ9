#include <m2c.h>

M2C_UNK func_02041cc0(s32, M2C_UNK);
s32 func_020421a0();
M2C_UNK func_02046608(s32, M2C_UNK, M2C_UNK *, s32, s32, s32, s32);
M2C_UNK func_0205d0e0(void *, M2C_UNK);
M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_0205def8(void *, M2C_UNK, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_0215be00(void *, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov002_0216d26c;

void func_ov002_0215c028(void *arg0) {
    s32 temp_r5;

    func_ov002_0215be00(arg0, 0x28, 0x15, 0x13);
    temp_r5 = func_020421a0();
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_02046608(temp_r5, 8, &data_ov002_0216d26c, M2C_FIELD(arg0, s32 *, 0x1BD0), 0x100, 0, 0);
    func_02041cc0(M2C_FIELD(arg0, s32 *, 0x1BD0), 0x11);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 1, 0, 0);
    func_0205d0e0(arg0 + 0xEC8, 4);
    func_0205def8(arg0 + 0xEC8, 0, 0x28);
}
