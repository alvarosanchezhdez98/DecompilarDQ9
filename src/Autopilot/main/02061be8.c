#include <m2c.h>


s32 func_02061bd8(void *arg0) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x150);
    if (temp_r0 != NULL) {
        if (((u32) (M2C_FIELD(temp_r0, u8 *, 0x56B) << 0x1C) >> 0x1C) != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
