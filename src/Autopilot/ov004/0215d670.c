#include <m2c.h>

s32 func_0202c578(s32 *, M2C_UNK);
M2C_UNK func_ov004_0215c0c0(void *);
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
M2C_UNK *func_0202ae18(void);

s32 func_ov004_0215d670(void *arg0) {
    s32 *temp_r0;
    u32 temp_r1;
    void *temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv() + 0x26C;
    temp_r0 = func_0202ae18();
    temp_r1 = (u32) (M2C_FIELD(temp_r4, u16 *, 0x5D0C) << 0x10) >> 0x1D;
    if (temp_r1 == 1) {
        func_ov004_0215c0c0(arg0);
        return 0;
    }
    if (temp_r1 == 2) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x2367);
        return 0;
    }
    if (func_0202c578(temp_r0, 0) == 0) {
        return 1;
    }
    _ZN10MenuScript10StartEntryEi(arg0, 0x2369);
    return 0;
}
