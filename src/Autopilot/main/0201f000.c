#include <m2c.h>

s32 _ZNK6Script9Parameter8ToStringEv();
M2C_UNK func_0201f308(s32, s32, s32);
extern M2C_UNK data_020fdc40;

s32 func_0201eff0(void) {
    s32 temp_r0;

    temp_r0 = _ZNK6Script9Parameter8ToStringEv();
    if (temp_r0 != 0) {
        func_0201f308(M2C_FIELD(&data_020fdc40, s32 *, 8), temp_r0, M2C_FIELD(&data_020fdc40, s32 *, 4));
    }
    return 1;
}
