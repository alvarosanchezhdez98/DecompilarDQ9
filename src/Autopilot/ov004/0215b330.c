#include <m2c.h>

M2C_UNK func_ov004_0215a2f8(s32);
extern M2C_UNK data_ov004_021707d8;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_0215b330(void *arg0) {
    func_ov004_0215a2f8(M2C_FIELD(&data_ov004_021707d8, s32 *, 8));
    _ZN10MenuScript10StartEntryEi(arg0, 0x39E);
    return 0;
}
