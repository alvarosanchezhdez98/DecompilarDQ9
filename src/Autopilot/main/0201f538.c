#include <m2c.h>

s32 _ZNK6Script9Parameter5ToIntEv();
s32 _ZNK6Script9Parameter8ToStringEv(s32);
M2C_UNK func_02023b0c(s32, s32);
M2C_UNK func_020277f4(s32, s32, s32, s32);
extern M2C_UNK data_020fdc4c;

s32 func_0201f528(s32 arg0) {
    s32 temp_r0;
    s32 temp_r5;

    temp_r5 = _ZNK6Script9Parameter5ToIntEv();
    temp_r0 = _ZNK6Script9Parameter8ToStringEv(arg0 + 8);
    if (temp_r0 == 0) {
        return 0;
    }
    func_02023b0c(M2C_FIELD(&data_020fdc4c, s32 *, 0x10), temp_r0);
    func_020277f4(M2C_FIELD(&data_020fdc4c, s32 *, 0x10), temp_r5, temp_r0, M2C_FIELD(&data_020fdc4c, s32 *, 8));
    return 1;
}
