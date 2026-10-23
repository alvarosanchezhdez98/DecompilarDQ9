#include <m2c.h>


s32 func_02011b50(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x63DC) & arg1) {
        return 1;
    }
    return 0;
}
