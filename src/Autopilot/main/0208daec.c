#include <m2c.h>

void *func_0208d994();

s32 func_0208dadc(void) {
    void *temp_r0;

    temp_r0 = func_0208d994();
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s32 *, 0x14);
    }
    return 0;
}
