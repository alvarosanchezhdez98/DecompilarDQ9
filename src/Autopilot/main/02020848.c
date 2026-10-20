#include <m2c.h>

M2C_UNK DisableSubBGVRAMBanks();
M2C_UNK DisableSubObjVRAMBanks();
M2C_UNK MapVRAMBanksToSubBG(M2C_UNK);
M2C_UNK MapVRAMBanksToSubObj(M2C_UNK);
void *func_02012fe4();
M2C_UNK func_020c3984(M2C_UNK);
M2C_UNK func_02020968(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_0202099c(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);

void func_02020838(void) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(func_02012fe4(), void **, 8);
    DisableSubBGVRAMBanks();
    DisableSubObjVRAMBanks();
    func_020c3984(0);
    MapVRAMBanksToSubBG(0x80);
    if (((u32) (M2C_FIELD(temp_r4, u8 *, 0xC) << 0x1C) >> 0x1C) == 0) {
        M2C_FIELD((void *)0x04001000, s32 *, 0) = (s32) ((M2C_FIELD((void *)0x04001000, s32 *, 0) & ~0x1F00) | 0x1100);
        func_02020968(0, 0, 0xF, 0, 0);
        func_0202099c(0, 0, 0x10, 0, 0);
    } else {
        M2C_FIELD((void *)0x04001000, s32 *, 0) = (s32) ((M2C_FIELD((void *)0x04001000, s32 *, 0) & ~0x1F00) | 0x1300);
        func_02020968(1, 0, 0xE, 0, 0);
        func_0202099c(0, 0, 0xD, 0, 0);
    }
    MapVRAMBanksToSubObj(0x100);
    M2C_FIELD((void *)0x04001000, s32 *, 0) = (s32) ((M2C_FIELD((void *)0x04001000, s32 *, 0) & 0xFFCFFFEF) | 0x10);
    M2C_FIELD((void *)0x04001000, u16 *, 8) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 8) & ~3) | 1);
    M2C_FIELD((void *)0x04001000, u16 *, 0xA) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 0xA) & ~3) | 2);
    M2C_FIELD((void *)0x04001000, u16 *, 0xC) = (u16) (M2C_FIELD((void *)0x04001000, u16 *, 0xC) & ~3);
    M2C_FIELD((void *)0x04001000, u16 *, 0xE) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 0xE) & ~3) | 3);
}
