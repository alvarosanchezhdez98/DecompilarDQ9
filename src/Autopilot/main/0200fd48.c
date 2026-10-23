#include <m2c.h>


void func_0200fd38(s32 arg0, s16 arg1, void *arg2) {
    M2C_FIELD((arg0 + (arg1 * 4)), void **, 8) = arg2;
    M2C_FIELD(arg2, s16 *, 4) = arg1;
}
