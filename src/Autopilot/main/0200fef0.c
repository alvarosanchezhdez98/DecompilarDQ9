#include <m2c.h>


u16 *func_0200fee0(s32 arg0, s32 arg1) {
    u16 *var_r0;

    if (arg1 < 0) {
        return NULL;
    }
    if (arg1 >= 0xE9) {
        return NULL;
    }
    var_r0 = M2C_FIELD((arg0 + (arg1 * 4)), u16 **, 8);
    if (var_r0 == NULL) {
        return NULL;
    }
    if (!(*var_r0 & 0x200)) {
        var_r0 = NULL;
    }
    return var_r0;
}
