#include <m2c.h>

u32 ov00_021FAECC();
extern M2C_UNK data_ov031_0224e5c4;

u8 ov00_021FAA40(void) {
    u32 temp_r0;
    u8 var_r4;

    var_r4 = 0xFF;
    temp_r0 = ov00_021FAECC();
    if ((temp_r0 >= 0xAU) && (temp_r0 <= 0x10U)) {
        var_r4 = M2C_FIELD(M2C_FIELD(&data_ov031_0224e5c4, void **, 0xC), u8 *, 0x17);
    }
    return var_r4;
}
