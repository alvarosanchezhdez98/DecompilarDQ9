#include <m2c.h>

extern M2C_UNK data_0210cf88;

void func_020bb948(void) {
    M2C_FIELD(&data_0210cf88, s32 *, 0) = 0;
    M2C_FIELD(&data_0210cf88, s32 *, 4) = (s32) M2C_FIELD(&data_0210cf88, s32 *, 8);
}
