#include <m2c.h>


s32 func_020797bc(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x17E) == 0xFF) {
        return 1;
    }
    return 0;
}
