#include <m2c.h>

u8 *func_ov017_0219219c();

u8 func_ov017_02191b58(void) {
    u8 *temp_r0;

    temp_r0 = func_ov017_0219219c();
    if (temp_r0 != NULL) {
        return *temp_r0;
    }
    return 0U;
}
