#include <m2c.h>

M2C_UNK DWCi_BACKUPlRead(void *);
M2C_UNK _Z19GetCurrentTimestampv();
s32 func_ov031_02236474();
M2C_UNK ov13_0223C9D4(void *);
M2C_UNK ov13_0223F3BC();
extern void *data_ov031_02290d20;

void ov13_0223E80C(void *arg0, void *arg1) {
    data_ov031_02290d20 = arg0;
    ov13_0223C9D4(arg0 + 0xB00);
    M2C_FIELD(data_ov031_02290d20, s16 *, 0x648) = 0;
    M2C_FIELD(data_ov031_02290d20, s16 *, 0x64A) = 0;
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xA90) = 1;
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xA91) = 1;
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xA9C) = 0;
    ov13_0223F3BC();
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xAB4) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xAB8) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xABC) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xAC0) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xAC4) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xAC8) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(data_ov031_02290d20, u8 *, 0xA92) = (u8) M2C_FIELD(arg1, u8 *, 0x18);
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xACC) = 2;
    _Z19GetCurrentTimestampv();
    DWCi_BACKUPlRead(data_ov031_02290d20 + 0x64C);
    _Z19GetCurrentTimestampv();
    M2C_FIELD(data_ov031_02290d20, s32 *, 0xAA4) = func_ov031_02236474();
}
