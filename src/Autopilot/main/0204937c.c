#include <m2c.h>


s32 func_0204936c(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (M2C_FIELD(temp_r0, s32 *, 0x20) & 0x10) {
        return 1;
    }
    return 0;
}
