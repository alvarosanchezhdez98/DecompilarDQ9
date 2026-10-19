#include <m2c.h>

M2C_UNK DWCi_BACKUPlRead(s32);
M2C_UNK func_020d1ba0(s32, s32);
s32 ov13_0224128C(s32, M2C_UNK);
extern s32 data_ov031_02290cfc;

void ov13_02239F98(void) {
    s32 temp_r0;

    temp_r0 = ov13_0224128C(0x6F8, 0x20);
    data_ov031_02290cfc = temp_r0;
    func_020d1ba0(temp_r0 + 0x4F8, 0xA001);
    DWCi_BACKUPlRead(data_ov031_02290cfc);
}
