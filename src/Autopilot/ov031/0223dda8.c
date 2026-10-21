#include <m2c.h>

s32 DisableArm7WorkVRAMBanks();
s32 DisableClearTextureVRAMBanks();
s32 DisableLCDCMappedVRAMBanks();
s32 DisableMainBGExtendedPaletteVRAMBanks();
s32 DisableMainBGVRAMBanks();
s32 DisableMainObjExtendedPaletteVRAMBanks();
s32 DisableMainObjVRAMBanks();
s32 DisableSubBGExtendedPaletteVRAMBanks();
s32 DisableSubBGVRAMBanks();
s32 DisableSubObjExtendedPaletteVRAMBanks();
s32 DisableSubObjVRAMBanks();
s32 DisableTextureImageVRAMBanks();
s32 DisableTexturePaletteVRAMBanks();
M2C_UNK MapVRAMBanksToArm7WorkRAM(s32);
M2C_UNK ov13_0224225C();
extern M2C_UNK data_ov031_02290d68;

void ov13_022420A0(void) {
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0) = DisableMainBGVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 4) = DisableMainObjVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 8) = DisableMainBGExtendedPaletteVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0xC) = DisableMainObjExtendedPaletteVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x10) = DisableTextureImageVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x14) = DisableTexturePaletteVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x18) = DisableClearTextureVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x1C) = DisableSubBGVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x20) = DisableSubObjVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x24) = DisableSubBGExtendedPaletteVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x28) = DisableSubObjExtendedPaletteVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x2C) = DisableArm7WorkVRAMBanks();
    M2C_FIELD(&data_ov031_02290d68, s32 *, 0x30) = DisableLCDCMappedVRAMBanks();
    MapVRAMBanksToArm7WorkRAM(M2C_FIELD(&data_ov031_02290d68, s32 *, 0x2C));
    ov13_0224225C();
}
