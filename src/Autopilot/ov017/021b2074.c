#include <m2c.h>

s32 func_ov031_02245710();

s32 func_ov017_021b2074(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x24) == 0) {
        return 0;
    }
    return func_ov031_02245710();
}
