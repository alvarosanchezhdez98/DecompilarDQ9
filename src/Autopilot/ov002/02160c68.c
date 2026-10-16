#include <m2c.h>

M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_0215be00(void *, u8, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_02160ce8(void *, s32, M2C_UNK);

void func_ov002_02160c68(void *arg0) {
    func_ov002_0215be00(arg0, (u8) M2C_FIELD(arg0, s32 *, 0x1BB8), 1, 0xE);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_ov002_02160ce8(arg0, M2C_FIELD(arg0, s32 *, 0x1BD0), 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 0, 0, 0);
}
