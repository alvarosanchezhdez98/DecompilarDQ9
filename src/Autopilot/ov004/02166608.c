#include <m2c.h>

M2C_UNK _Z18RefreshMenuObject6P10MenuScriptt(M2C_UNK, M2C_UNK);
M2C_UNK _Z20SetMenuObject8TextIdP10MenuScripttth(M2C_UNK, M2C_UNK, u16, M2C_UNK);
extern void *data_ov004_0217101c;

void func_ov004_02166608(M2C_UNK arg0) {
    void *temp_r5;

    temp_r5 = data_ov004_0217101c;
    _Z20SetMenuObject8TextIdP10MenuScripttth(arg0, 0xAA, (u16) (((u32) (M2C_FIELD(temp_r5, u8 *, 0x50) << 0x19) >> 0x1F) + 1), 0xF);
    _Z18RefreshMenuObject6P10MenuScriptt(arg0, 0x15);
    _Z20SetMenuObject8TextIdP10MenuScripttth(arg0, 0xA0, (u16) (((u32) (M2C_FIELD(temp_r5, u8 *, 0x50) << 0x18) >> 0x1F) + 3), 0xF);
    _Z18RefreshMenuObject6P10MenuScriptt(arg0, 0x16);
}
