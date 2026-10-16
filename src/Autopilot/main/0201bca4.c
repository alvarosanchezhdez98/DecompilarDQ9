#include <m2c.h>


s32 func_0201bc94(void *arg0) {
    s32 var_r3;
    u16 temp_r2;
    u16 temp_r2_2;

    temp_r2 = M2C_FIELD(arg0, u16 *, 0);
    var_r3 = 1;
    if (temp_r2 == 0x2710) {
        var_r3 = 0;
    } else if (temp_r2 == 0x2774) {
        var_r3 = 0;
    } else {
        temp_r2_2 = M2C_FIELD(arg0, u16 *, 4);
        if (temp_r2_2 == 0x170C) {
            var_r3 = 0;
        } else if (temp_r2_2 == 0x1901) {
            var_r3 = 0;
        } else if (((u32) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0xC) << 0x1B) >> 0x1F) == 0) {
            var_r3 = 0;
        }
    }
    return var_r3;
}
