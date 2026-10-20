#include <m2c.h>


s32 *func_0203dce4(s32 arg0, u32 arg1) {
    s32 *var_r0;

    if (arg1 >= 0x20U) {
        return NULL;
    }
    var_r0 = M2C_FIELD((arg0 + (arg1 * 4)), s32 **, 0xC);
    if (var_r0 == NULL) {
        return var_r0;
    }
    if (*var_r0 & 0x8000) {
        var_r0 = NULL;
    }
    return var_r0;
}
