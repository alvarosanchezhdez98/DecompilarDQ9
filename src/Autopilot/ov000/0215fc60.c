#include <m2c.h>


s32 func_ov000_0215fc60(void *arg0) {
    u16 temp_r1;

    temp_r1 = M2C_FIELD(arg0, u16 *, 0x81FE);
    if (temp_r1 == 0x320) {
        return 1;
    }
    if (temp_r1 == 0x321) {
        return 2;
    }
    return 0;
}
