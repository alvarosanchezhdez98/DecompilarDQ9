#include <m2c.h>

s32 func_ov000_02169aa4();

s32 func_02048ae0(void *arg0) {
    s32 *temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 **, 0x13C);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (*temp_r0 == 0) {
        return 0;
    }
    return func_ov000_02169aa4();
}
