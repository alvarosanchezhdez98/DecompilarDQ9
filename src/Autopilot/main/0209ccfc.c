#include <m2c.h>

s32 func_02012d88(M2C_UNK *, s32);
extern M2C_UNK data_02114e20;

void func_0209ccec(void *arg0, s32 arg1) {
    if (arg1 <= 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0) = func_02012d88(&data_02114e20, arg1 * 4);
    M2C_FIELD(arg0, s8 *, 5) = (s8) arg1;
    M2C_FIELD(arg0, s8 *, 4) = 0;
}
