#include <m2c.h>

void *func_02055080();

s32 func_02055138(void) {
    void *temp_r0;

    temp_r0 = func_02055080();
    if (temp_r0 == NULL) {
        return 0;
    }
    return M2C_FIELD(temp_r0, s32 *, 0x1C);
}
