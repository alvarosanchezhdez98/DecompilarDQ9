#include <m2c.h>

s32 _ZNK6Script9Parameter5ToIntEv();
extern M2C_UNK data_02108d70;

s32 func_02071004(void) {
    if ((M2C_FIELD(&data_02108d70, s32 *, 0x1C) == _ZNK6Script9Parameter5ToIntEv()) || (M2C_FIELD(&data_02108d70, u8 *, 0) != 0)) {
        M2C_FIELD(&data_02108d70, s32 *, 0x10) = (s32) (M2C_FIELD(&data_02108d70, s32 *, 0x10) + 1);
    }
    return 1;
}
