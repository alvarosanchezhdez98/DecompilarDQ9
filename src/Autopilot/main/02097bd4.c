#include <m2c.h>

s32 DisableMainBGVRAMBanks();
s32 DisableMainObjVRAMBanks();
s32 DisableSubBGVRAMBanks();
s32 DisableSubObjVRAMBanks();
s32 DisableTextureImageVRAMBanks();
s32 DisableTexturePaletteVRAMBanks();

void func_02097bc4(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x1E) = arg1;
    if (arg1 & 1) {
        M2C_FIELD(arg0, s32 *, 0) = DisableTextureImageVRAMBanks();
        M2C_FIELD(arg0, s32 *, 4) = DisableTexturePaletteVRAMBanks();
        M2C_FIELD(arg0, s32 *, 8) = DisableMainBGVRAMBanks();
        M2C_FIELD(arg0, s32 *, 0xC) = DisableMainObjVRAMBanks();
    }
    if (!(arg1 & 2)) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x10) = DisableSubBGVRAMBanks();
    M2C_FIELD(arg0, s32 *, 0x14) = DisableSubObjVRAMBanks();
}
