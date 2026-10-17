#include <m2c.h>

extern void *data_ov017_021d83ac;

u8 func_ov017_021a5a48(void) {
    u8 var_r0;

    var_r0 = 0xFF;
    if (data_ov017_021d83ac != NULL) {
        var_r0 = M2C_FIELD(data_ov017_021d83ac, u8 *, 0x1C79);
    }
    return var_r0;
}
