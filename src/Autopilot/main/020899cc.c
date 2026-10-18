#include <m2c.h>

s16 _ZNK6Script9Parameter5ToIntEv();
extern void *data_02108efc;

s32 func_020899bc(void) {
    M2C_FIELD(data_02108efc, s16 *, 8) = _ZNK6Script9Parameter5ToIntEv();
    return 1;
}
