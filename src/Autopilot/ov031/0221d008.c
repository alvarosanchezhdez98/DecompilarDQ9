#include <m2c.h>

M2C_UNK func_ov031_0221e52c(M2C_UNK *, s32, s32);
extern M2C_UNK data_ov031_0224e6e0;
extern M2C_UNK data_ov031_0224e700;
extern M2C_UNK data_ov031_0224e704;
extern M2C_UNK data_ov031_0224f440;

#pragma thumb on
void func_ov031_0221d008(void *arg0) {
    func_ov031_0221e52c(&data_ov031_0224f440, 0, 8);
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x10) = 1;
    func_ov031_0221e52c(&data_ov031_0224e704, 0, 0x1C);
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x24) = (s32) (arg0 + 6);
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x28) = (s32) M2C_FIELD(arg0, u16 *, 4);
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x2C) = (s32) (0xF & M2C_FIELD(arg0, u16 *, 0));
    M2C_FIELD(&data_ov031_0224e700, u8 *, 0x1D) = (u8) M2C_FIELD(arg0, u8 *, 2);
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x30) = 0;
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x34) = 0xC0A80B01;
    M2C_FIELD(&data_ov031_0224e700, s8 *, 0x1C) = 0;
}
#pragma thumb off
