#include <m2c.h>

M2C_UNK ov13_02227924(M2C_UNK *, M2C_UNK *);
extern M2C_UNK LoadToMainBG2ScreenData;
extern M2C_UNK data_ov031_0224bbf8;

void func_ov031_022319c4(void) {
    ov13_02227924(&data_ov031_0224bbf8, &LoadToMainBG2ScreenData);
    M2C_FIELD((void *)0x04001008, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x04001008, u16 *, 0) & ~3) | 3);
    M2C_FIELD((void *)0x04001008, u16 *, 2) = (u16) ((M2C_FIELD((void *)0x04001008, u16 *, 2) & ~3) | 3);
    *(u16 *)0x04000008 = (*(u16 *)0x04000008 & ~3) | 3;
    M2C_FIELD((void *)0x0400000A, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x0400000A, u16 *, 0) & ~3) | 3);
    M2C_FIELD((void *)0x0400000A, u16 *, 2) = (u16) ((M2C_FIELD((void *)0x0400000A, u16 *, 2) & ~3) | 3);
}
