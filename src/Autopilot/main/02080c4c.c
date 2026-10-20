#include <m2c.h>

void *func_02081da8();

s32 func_02080c3c(void) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = func_02081da8();
    if (temp_r0 != NULL) {
        if (!(M2C_FIELD(temp_r0, u8 *, 0xC5) & 0x20)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
