#include <m2c.h>

void *func_ov000_02160130();

s32 func_ov025_021e8898(void) {
    void *temp_r0;

    temp_r0 = func_ov000_02160130();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s8 *, 0x6FD8) = 1;
    }
    return 1;
}
