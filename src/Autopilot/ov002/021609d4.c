#include <m2c.h>

M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_02157030(void *, M2C_UNK, s16 *, s16 *, s16 *, s16 *);
M2C_UNK func_ov002_0215be00(void *, u8, M2C_UNK, s16);
M2C_UNK func_ov002_02160aa0(void *, s32, M2C_UNK);

void func_ov002_021609d4(void *arg0) {
    s16 sp16;
    s16 sp14;
    s16 sp12;
    s16 sp10;

    sp16 = 0;
    sp14 = 0;
    sp12 = 1;
    sp10 = 1;
    func_ov002_02157030(arg0, 0x21, &sp16, &sp14, &sp12, &sp10);
    sp16 += 0xC;
    func_ov002_0215be00(arg0, (u8) M2C_FIELD(arg0, s32 *, 0x1BB8), 4, sp14);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_ov002_02160aa0(arg0, M2C_FIELD(arg0, s32 *, 0x1BD0), 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 1, 1, 0, 0);
}
