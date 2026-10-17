#include <m2c.h>

void *func_0209a594(s32);

u32 func_0201137c(s32 arg0) {
    u32 var_r4;
    void *temp_r0;

    var_r4 = 0;
    temp_r0 = func_0209a594(arg0 + 0x572C);
    if (temp_r0 != NULL) {
        var_r4 = (u32) (M2C_FIELD(temp_r0, s32 *, 4) << 0xC) >> 0x18;
    }
    return var_r4;
}
