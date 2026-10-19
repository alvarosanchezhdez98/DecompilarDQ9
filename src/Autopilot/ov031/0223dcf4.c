#include <m2c.h>

M2C_UNK ov13_02240288(s32, u32);
M2C_UNK ov13_02241BE0();
extern s32 data_ov031_02290d64;

void ov13_02242034(u32 arg0) {
    s32 var_r4;

    var_r4 = 0;
    ov13_02241BE0();
    if (arg0 >= (u32) (data_ov031_02290d64 + 0x1A0)) {
        var_r4 = 1;
    }
    ov13_02240288(M2C_FIELD(((var_r4 * 0x1A0) + data_ov031_02290d64), s32 *, 0x19C), arg0);
}
