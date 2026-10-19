#include <m2c.h>

M2C_UNK ov13_02233DCC();
void *ov13_02239FF0();
M2C_UNK ov13_0223A004(s32);
M2C_UNK ov13_0223A018(M2C_UNK);
extern M2C_UNK data_ov031_02290ca0;

void ov13_0223376C(s32 arg0) {
    M2C_UNK var_r5;
    void *temp_r0;

    temp_r0 = ov13_02239FF0();
    if (M2C_FIELD(temp_r0, u8 *, 0xF5) == arg0) {
        return;
    }
    if (arg0 != 0) {
        if (M2C_FIELD(M2C_FIELD(&data_ov031_02290ca0, void **, 8), u8 *, 0x43) != 0) {
            var_r5 = 1;
        } else {
            var_r5 = 0;
        }
    } else {
        var_r5 = 0;
        M2C_FIELD(M2C_FIELD(&data_ov031_02290ca0, void **, 8), u8 *, 0x43) = (u8) M2C_FIELD(temp_r0, u8 *, 0xF6);
    }
    ov13_0223A004(arg0);
    ov13_0223A018(var_r5);
    ov13_02233DCC();
}
