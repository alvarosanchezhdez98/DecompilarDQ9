#include <m2c.h>

extern M2C_UNK data_ov004_02171034;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_0216df7c(void *arg0) {
    M2C_FIELD(&data_ov004_02171034, s8 *, 3) = 5;
    _ZN10MenuScript10StartEntryEi(arg0, 0x12D);
    return 0;
}
