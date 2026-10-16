#include <m2c.h>

M2C_UNK _ZNK6Script9Parameter5ToIntEv();
s32 _ZNK6Script9Parameter8ToStringEv();

s32 func_0201f864(s32 arg0) {
    s32 temp_r4;

    _ZNK6Script9Parameter5ToIntEv();
    temp_r4 = _ZNK6Script9Parameter8ToStringEv(arg0 + 8);
    _ZNK6Script9Parameter5ToIntEv(arg0 + 0x10);
    if (temp_r4 != 0) {
        return 1;
    }
    return 0;
}
