#include <m2c.h>

extern M2C_UNK data_0210cf88;

void func_020bb92c(void *arg0) {
    M2C_FIELD(&data_0210cf88, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(&data_0210cf88, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
}
