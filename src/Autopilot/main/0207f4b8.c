#include <m2c.h>

s16 _ZNK6Script9Parameter5ToIntEv(s32);
void *func_0207f700(void *, s16);
extern M2C_UNK data_02108ee0;

s32 func_0207f4a8(s32 arg0) {
    void *temp_r0;

    temp_r0 = func_0207f700(M2C_FIELD(&data_02108ee0, void **, 4), (s16) (M2C_FIELD(M2C_FIELD(&data_02108ee0, void **, 4), s16 *, 4) - 1));
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s16 *, 0x18) = _ZNK6Script9Parameter5ToIntEv(arg0);
        M2C_FIELD(temp_r0, s16 *, 0x1C) = _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
        M2C_FIELD(temp_r0, s16 *, 0x20) = _ZNK6Script9Parameter5ToIntEv(arg0 + 0x10);
        M2C_FIELD(temp_r0, s16 *, 0x24) = _ZNK6Script9Parameter5ToIntEv(arg0 + 0x18);
    }
    return 1;
}
