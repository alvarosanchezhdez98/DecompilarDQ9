#include <m2c.h>


s32 func_ov000_02171674(s32 arg0, s32 arg1) {
    if ((arg1 < 0) || (arg1 >= 0x42)) {
        return 0;
    }
    return M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0x9C);
}
