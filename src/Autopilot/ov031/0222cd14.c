#include <m2c.h>

M2C_UNK ov13_02227924(M2C_UNK *, M2C_UNK *);
extern M2C_UNK LoadToMainBG2CharacterData;
extern M2C_UNK LoadToMainBG2ScreenData;
extern M2C_UNK LoadToMainBGStandardPalette;
extern M2C_UNK LoadToMainObjStandardPalette;
extern M2C_UNK data_ov031_0224ba0c;
extern M2C_UNK data_ov031_0224ba20;
extern M2C_UNK data_ov031_0224ba38;
extern M2C_UNK data_ov031_0224ba50;

void func_ov031_0222cd14(void) {
    ov13_02227924(&data_ov031_0224ba0c, &LoadToMainObjStandardPalette);
    ov13_02227924(&data_ov031_0224ba20, &LoadToMainBG2CharacterData);
    ov13_02227924(&data_ov031_0224ba38, &LoadToMainBGStandardPalette);
    ov13_02227924(&data_ov031_0224ba50, &LoadToMainBG2ScreenData);
    M2C_FIELD((void *)0x04001008, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x04001008, u16 *, 0) & ~3) | 3);
    M2C_FIELD((void *)0x04001008, u16 *, 2) = (u16) ((M2C_FIELD((void *)0x04001008, u16 *, 2) & ~3) | 3);
    *(u16 *)0x04000008 = (*(u16 *)0x04000008 & ~3) | 2;
    M2C_FIELD((void *)0x0400000A, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x0400000A, u16 *, 0) & ~3) | 3);
    M2C_FIELD((void *)0x0400000A, u16 *, 2) = (u16) ((M2C_FIELD((void *)0x0400000A, u16 *, 2) & ~3) | 3);
}
