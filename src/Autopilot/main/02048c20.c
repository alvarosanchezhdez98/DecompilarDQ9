#include <m2c.h>


s32 func_02048c10(void *arg0) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 != NULL) {
        if (M2C_FIELD(temp_r0, s32 *, 0x20) & 0x200) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
