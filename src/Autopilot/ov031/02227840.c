#include <m2c.h>

extern s32 data_ov031_02290c44;

s32 ov13_0222BC68(void) {
    if (data_ov031_02290c44 == 0) {
        return 1;
    }
    return 0;
}
