#include <m2c.h>


void func_020a093c(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s16 *, 8) = arg3;
}
