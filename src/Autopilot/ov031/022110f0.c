#include <m2c.h>

s32 func_ov031_022113c0();
M2C_UNK func_ov031_02211864(M2C_UNK, M2C_UNK);
extern void *data_ov031_0224e590;

void func_ov031_022110f0(s32 arg0) {
    if ((data_ov031_0224e590 == NULL) || (func_ov031_022113c0() != 0)) {
        func_ov031_02211864(9, -2);
        return;
    }
    M2C_FIELD(data_ov031_0224e590, s32 *, 0x3C) = arg0;
}
