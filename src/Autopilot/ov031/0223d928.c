#include <m2c.h>

M2C_UNK func_020ca458(M2C_UNK, void *, M2C_UNK);
s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
s32 ov13_0224022C(M2C_UNK, void *, M2C_UNK);
void *ov13_0224128C(s32, M2C_UNK);
extern void *data_ov031_02290d60;
extern M2C_UNK ov13_02241D04;

void ov13_02241C68(void) {
    s32 temp_r0_2;
    s32 var_r5;
    s32 var_r6;
    void *temp_r0;
    void *temp_r1;

    temp_r0 = ov13_0224128C(0x80C, 4);
    data_ov031_02290d60 = temp_r0;
    func_020ca458(0x200, temp_r0, 0x800);
    var_r5 = 0;
    var_r6 = 0;
    do {
        temp_r0_2 = ov13_0224022C(0x40, data_ov031_02290d60 + var_r6, 8);
        var_r6 += 0x400;
        temp_r1 = data_ov031_02290d60 + (var_r5 * 4);
        var_r5 += 1;
        M2C_FIELD(temp_r1, s32 *, 0x800) = temp_r0_2;
    } while (var_r5 < 2);
    M2C_FIELD(data_ov031_02290d60, s32 *, 0x808) = func_ov031_0223e218(1, &ov13_02241D04, 0, 0xC8);
}
