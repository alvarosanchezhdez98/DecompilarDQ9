#include <m2c.h>

u16 func_020bb964(void *, u16);
s32 func_020bb984();

s32 func_020bbc78(void *arg0) {
    if (func_020bb984() != 0) {
        return 0;
    }
    M2C_FIELD(arg0, u16 *, 8) = func_020bb964(arg0, M2C_FIELD(arg0, u16 *, 8));
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg0, u16 *, 0xC) - 1);
    return 1;
}
