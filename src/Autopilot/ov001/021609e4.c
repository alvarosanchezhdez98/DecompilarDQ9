#include <m2c.h>

void *func_0205ec34();
s8 func_ov017_021d60f4();

s32 func_ov001_021609e4(void) {
    s8 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    M2C_FIELD(func_0205ec34(), s8 *, 0x490) = temp_r4;
    return 1;
}
