#include <m2c.h>


s32 func_020416cc(void *arg0) {
    s32 *temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 **, 0x18);
    if (temp_r0 != NULL) {
        return *temp_r0;
    }
    return 0;
}
