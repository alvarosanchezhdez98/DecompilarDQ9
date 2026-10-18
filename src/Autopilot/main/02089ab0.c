#include <m2c.h>

s16 _ZNK6Script9Parameter5ToIntEv();
extern void *data_02108efc;

s32 func_02089aa0(void) {
    M2C_FIELD(data_02108efc, s16 *, 0x18) = _ZNK6Script9Parameter5ToIntEv();
    return 1;
}
