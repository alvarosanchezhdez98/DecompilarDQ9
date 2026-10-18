#include <m2c.h>

M2C_UNK func_ov001_021588bc(s32, s32, M2C_UNK);
extern M2C_UNK data_ov001_02165880;
extern M2C_UNK data_ov001_021658b8;

void func_ov001_0215a954(void) {
    M2C_FIELD((void *)0x04000060, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x04000060, u16 *, 0) & ~0x3000) | 4);
    M2C_FIELD((void *)0x04000060, s16 *, 0x2E0) = 0;
    func_ov001_021588bc(M2C_FIELD(&data_ov001_02165880, s32 *, 0x24), M2C_FIELD(&data_ov001_02165880, s32 *, 8), 8);
    M2C_FIELD(&data_ov001_021658b8, s32 *, 0xEC) = 0;
    if (M2C_FIELD(&data_ov001_021658b8, s32 *, 0xE4) != 0) {
        M2C_FIELD(&data_ov001_021658b8, s32 *, 0xE4) = 0;
    }
}
