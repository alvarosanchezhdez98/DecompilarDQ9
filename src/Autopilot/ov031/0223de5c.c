#include <m2c.h>

M2C_UNK DisableMainBGVRAMBanks();
M2C_UNK DisableMainObjVRAMBanks();
M2C_UNK DisableSubBGVRAMBanks();
M2C_UNK DisableSubObjVRAMBanks();
M2C_UNK MapVRAMBanksToClearTextures(s32);
M2C_UNK MapVRAMBanksToLCDC(s32);
M2C_UNK MapVRAMBanksToMainBG(s32);
M2C_UNK MapVRAMBanksToMainBGExtendedPalette(s32);
M2C_UNK MapVRAMBanksToMainObj(s32);
M2C_UNK MapVRAMBanksToMainObjExtendedPalette(s32);
M2C_UNK MapVRAMBanksToSubBG(s32);
M2C_UNK MapVRAMBanksToSubBGExtendedPalette(s32);
M2C_UNK MapVRAMBanksToSubObj(s32);
M2C_UNK MapVRAMBanksToSubObjExtendedPalette(s32);
M2C_UNK MapVRAMBanksToTextureImage(s32);
M2C_UNK MapVRAMBanksToTexturePalette(s32);
M2C_UNK ov13_0224225C();
extern M2C_UNK data_ov031_02290d68;

void func_ov031_0223de5c(void) {
    DisableMainBGVRAMBanks();
    DisableMainObjVRAMBanks();
    DisableSubBGVRAMBanks();
    DisableSubObjVRAMBanks();
    ov13_0224225C();
    MapVRAMBanksToMainBG(M2C_FIELD(&data_ov031_02290d68, s32 *, 0));
    MapVRAMBanksToMainObj(M2C_FIELD(&data_ov031_02290d68, s32 *, 4));
    MapVRAMBanksToMainBGExtendedPalette(M2C_FIELD(&data_ov031_02290d68, s32 *, 8));
    MapVRAMBanksToMainObjExtendedPalette(M2C_FIELD(&data_ov031_02290d68, s32 *, 0xC));
    MapVRAMBanksToTextureImage(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x10));
    MapVRAMBanksToTexturePalette(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x14));
    MapVRAMBanksToClearTextures(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x18));
    MapVRAMBanksToSubBG(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x1C));
    MapVRAMBanksToSubObj(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x20));
    MapVRAMBanksToSubBGExtendedPalette(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x24));
    MapVRAMBanksToSubObjExtendedPalette(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x28));
    MapVRAMBanksToLCDC(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x30));
    M2C_FIELD((void *)0x04000050, s16 *, 0) = 0;
    M2C_FIELD((void *)0x04000050, s16 *, 0x1000) = 0;
    M2C_FIELD((void *)0x04000050, s32 *, -0x40) = 0;
    M2C_FIELD((void *)0x04000050, s32 *, -0x3C) = 0;
    M2C_FIELD((void *)0x04000050, s32 *, -0x38) = 0;
    M2C_FIELD((void *)0x04000050, s32 *, -0x34) = 0;
    M2C_FIELD((void *)0x04000050, s32 *, 0xFC0) = 0;
    M2C_FIELD((void *)0x04001014, s32 *, 0) = 0;
    M2C_FIELD((void *)0x04001014, s32 *, 4) = 0;
    M2C_FIELD((void *)0x04001014, s32 *, 8) = 0;
}
