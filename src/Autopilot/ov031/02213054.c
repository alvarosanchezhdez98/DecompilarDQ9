#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(void *, M2C_UNK, M2C_UNK);
u32 ov00_021FAECC();
extern M2C_UNK data_ov031_0224e5c4;

s32 ov00_021FAA70(M2C_UNK arg0) {
    s32 var_r4;
    u32 temp_r0;
    u8 temp_r0_2;

    var_r4 = 0;
    temp_r0 = ov00_021FAECC();
    if ((temp_r0 >= 0xAU) && (temp_r0 <= 0x10U)) {
        temp_r0_2 = M2C_FIELD(M2C_FIELD(&data_ov031_0224e5c4, void **, 0xC), u8 *, 0x17);
        if ((temp_r0_2 != 4) && (temp_r0_2 != 8)) {

        } else {
            VectorizedInvertedMemcpy(M2C_FIELD(&data_ov031_0224e5c4, void **, 0xC) + 0x18, arg0, 0xA);
            var_r4 = 1;
        }
    }
    return var_r4;
}
