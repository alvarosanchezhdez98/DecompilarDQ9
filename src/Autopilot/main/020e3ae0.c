#include <m2c.h>

void *func_020e385c();

s32 func_020e3ad0(void) {
    u8 temp_r1;
    void *temp_r0;

    temp_r0 = func_020e385c();
    if (temp_r0 == NULL) {
        return 1;
    }
    temp_r1 = M2C_FIELD(temp_r0, u8 *, 5);
    if ((temp_r1 != 0) && (temp_r1 == M2C_FIELD(temp_r0, u8 *, 6))) {
        return 1;
    }
    return 0;
}
