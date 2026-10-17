#include <m2c.h>

s32 func_020797dc();
void *func_02079e2c(s32, s16);
u16 *func_ov000_02160f20();
s32 func_ov000_02163690(u16);

s32 func_ov000_021627fc(void) {
    u16 *temp_r0;
    u16 var_r4;
    u32 temp_r0_3;
    void *temp_r0_2;

    temp_r0 = func_ov000_02160f20();
    if (temp_r0 == NULL) {
        return 0;
    }
    var_r4 = *temp_r0;
    if (func_ov000_02163690(var_r4) != 0) {
        var_r4 = 1;
    }
    temp_r0_2 = func_02079e2c(func_020797dc(), (s16) var_r4);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    temp_r0_3 = (u32) M2C_FIELD(temp_r0_2, u32 *, 0x14) >> 0x1C;
    if (temp_r0_3 == 5) {
        return 1;
    }
    if (temp_r0_3 == 2) {
        return 1;
    }
    return 0;
}
