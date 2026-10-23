#include <m2c.h>

extern void *data_ov004_02171010;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_0216583c(void *arg0) {
    M2C_FIELD(data_ov004_02171010, s8 *, 0x18FD) = 1;
    _ZN10MenuScript10StartEntryEi(arg0, 0x65);
    return 0;
}
