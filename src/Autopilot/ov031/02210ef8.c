#include <m2c.h>

extern s32 *data_ov031_0224e588;

s32 func_ov031_02210ef8(void) {
    if (data_ov031_0224e588 == NULL) {
        return 0;
    }
    if (*data_ov031_0224e588 == 7) {
        return 1;
    }
    return 0;
}
