#include <m2c.h>

s32 _ZNK6Script9Parameter5ToIntEv();
extern M2C_UNK data_020fdc20;

s32 func_0201d4ec(s32 arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = _ZNK6Script9Parameter5ToIntEv();
    temp_r4 = _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
    M2C_FIELD(M2C_FIELD(&data_020fdc20, void **, 8), s16 *, 0x7E) = (s16) (temp_r5 | (temp_r4 << 5) | (_ZNK6Script9Parameter5ToIntEv(arg0 + 0x10) << 0xA));
    return 1;
}
