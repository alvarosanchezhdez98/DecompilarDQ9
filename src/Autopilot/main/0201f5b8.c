#include <m2c.h>

s32 _ZNK6Script9Parameter5ToIntEv();
M2C_UNK func_02027910();
extern M2C_UNK data_020fdc4c;

s32 func_0201f5a8(s32 arg0) {
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;

    temp_r6 = _ZNK6Script9Parameter5ToIntEv();
    temp_r5 = _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
    temp_r4 = _ZNK6Script9Parameter5ToIntEv(arg0 + 0x10);
    func_02027910(M2C_FIELD(&data_020fdc4c, s32 *, 0x10), temp_r6, temp_r5, temp_r4, _ZNK6Script9Parameter5ToIntEv(arg0 + 0x18));
    return 1;
}
