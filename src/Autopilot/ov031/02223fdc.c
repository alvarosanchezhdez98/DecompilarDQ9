#include <m2c.h>

extern s32 data_ov031_02250bfc;

s32 func_ov031_02223fdc(void) {
    if (data_ov031_02250bfc != 0) {
        return 1;
    }
    return 0;
}
