#include <m2c.h>

M2C_UNK ov13_02227924(M2C_UNK *, M2C_UNK *);
extern M2C_UNK LoadToMainBG2CharacterData;
extern M2C_UNK LoadToMainBG2ScreenData;
extern M2C_UNK LoadToMainBGStandardPalette;
extern M2C_UNK data_ov031_0224bb8c;
extern M2C_UNK data_ov031_0224bba4;
extern M2C_UNK data_ov031_0224bbbc;

void ov13_022352F0(void) {
    ov13_02227924(&data_ov031_0224bb8c, &LoadToMainBG2CharacterData);
    ov13_02227924(&data_ov031_0224bba4, &LoadToMainBGStandardPalette);
    ov13_02227924(&data_ov031_0224bbbc, &LoadToMainBG2ScreenData);
    M2C_FIELD((void *)0x04001008, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x04001008, u16 *, 0) & ~3) | 3);
    M2C_FIELD((void *)0x04001008, u16 *, 2) = (u16) ((M2C_FIELD((void *)0x04001008, u16 *, 2) & ~3) | 3);
    M2C_FIELD((void *)0x0400000A, u16 *, 0) = (u16) ((M2C_FIELD((void *)0x0400000A, u16 *, 0) & ~3) | 3);
    M2C_FIELD((void *)0x0400000A, u16 *, 2) = (u16) ((M2C_FIELD((void *)0x0400000A, u16 *, 2) & ~3) | 3);
}
