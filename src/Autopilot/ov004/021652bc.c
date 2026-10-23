#include <m2c.h>

void *func_020421a0();
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_021652bc(void *arg0) {
    if (M2C_FIELD(func_020421a0(), s32 *, 0x998) == 0) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x65);
    }
    return 0;
}
