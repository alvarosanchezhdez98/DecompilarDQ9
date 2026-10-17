#include <m2c.h>

extern void *data_ov031_0224e590;

s32 func_ov031_022112e4(void) {
    if ((data_ov031_0224e590 != NULL) && (M2C_FIELD(data_ov031_0224e590, s32 *, 0x30) == 0)) {
        return M2C_FIELD(data_ov031_0224e590, s32 *, 0x2C);
    }
    return 0;
}
