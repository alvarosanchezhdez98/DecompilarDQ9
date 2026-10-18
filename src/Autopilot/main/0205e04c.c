#include <m2c.h>

s16 _ZNK6Script9Parameter5ToIntEv();
extern M2C_UNK data_02108740;

s32 func_0205e03c(void) {
    M2C_FIELD(M2C_FIELD(&data_02108740, void **, 4), s16 *, 0x2A) = _ZNK6Script9Parameter5ToIntEv();
    return 1;
}
