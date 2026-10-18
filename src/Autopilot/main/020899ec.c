#include <m2c.h>

s16 _ZNK6Script9Parameter5ToIntEv();
extern void *data_02108efc;

s32 func_020899dc(void) {
    M2C_FIELD(data_02108efc, s16 *, 0x10) = _ZNK6Script9Parameter5ToIntEv();
    return 1;
}
