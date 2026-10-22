#include <m2c.h>

s32 func_0205d81c(void *, u8);

s32 func_0205d8c4(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x98) == 0) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x9C) == 0) {
        return 0;
    }
    if (M2C_FIELD(arg0, u8 *, 0xB4) == 0) {
        return 0;
    }
    return func_0205d81c(arg0, M2C_FIELD(arg0, u8 *, 0xB0));
}
