#include <m2c.h>

s16 _ZNK6Script9Parameter5ToIntEv();
extern M2C_UNK data_02109a28;

s32 func_02099c90(void) {
    M2C_FIELD(&data_02109a28, s16 *, 0x28) = _ZNK6Script9Parameter5ToIntEv();
    return 1;
}
