#include <m2c.h>

s32 *func_02055090();

s32 func_02055168(void) {
    s32 *temp_r0;

    temp_r0 = func_02055090();
    if (temp_r0 == NULL) {
        return 0;
    }
    return *temp_r0;
}
