#include <m2c.h>


s32 ov00_021FBDF8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xB) == 0) {
        return 0xFFFF3C4D;
    }
    return 0xFFFF3865;
}
