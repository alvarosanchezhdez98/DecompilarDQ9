#include <m2c.h>

extern M2C_UNK data_ov004_021707d8;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_0215d6f8(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x11) == 1) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x236A);
    } else {
        _ZN10MenuScript10StartEntryEi(arg0, 0x38A);
    }
    return 0;
}
