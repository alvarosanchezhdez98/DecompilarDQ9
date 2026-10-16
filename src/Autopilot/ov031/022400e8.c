#include <m2c.h>


s32 ov38_02221E10(void *arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32 *, 0) != 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 0x1C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x18) = arg2;
    return 1;
}
