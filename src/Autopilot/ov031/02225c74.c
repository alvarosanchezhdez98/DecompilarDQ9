#include <m2c.h>

extern s32 data_ov031_02250c00;

s32 func_ov031_02225c74(void) {
    if (data_ov031_02250c00 != 0) {
        return 1;
    }
    return 0;
}
