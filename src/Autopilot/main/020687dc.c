#include <m2c.h>


s32 func_020687cc(s32 arg0, void *arg1) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg1, void **, 0x18);
    if (temp_r0 != NULL) {
        if (((u32) (M2C_FIELD(temp_r0, s32 *, 8) << 5) >> 0x1F) == 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
