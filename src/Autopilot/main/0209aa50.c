#include <m2c.h>


s32 func_0209aa40(void **arg0) {
    void *temp_r0;

    temp_r0 = *arg0;
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s32 *, 0x108);
    }
    return 0;
}
