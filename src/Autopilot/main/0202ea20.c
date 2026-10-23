#include <m2c.h>


void func_0202ea10(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x1E4) = arg1;
        M2C_FIELD(arg0, s32 *, 0x1E8) = arg2;
    }
}
