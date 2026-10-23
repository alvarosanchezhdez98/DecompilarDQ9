#include <m2c.h>

void *func_020421a0();
extern M2C_UNK data_ov004_02171048;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_0216f824(void *arg0) {
    _ZN10MenuScript10StartEntryEi(arg0, 0x67);
    M2C_FIELD(func_020421a0(), s32 *, 0x2C8) = 1;
    M2C_FIELD(M2C_FIELD(&data_ov004_02171048, void **, 4), s8 *, 0x31) = 1;
    return 0;
}
