#include <m2c.h>


s32 func_ov024_021edc80(void *arg0) {
    u32 var_r0;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x138), u8 *, 0x21) == 4) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        return 1;
    }
    return 0;
}
