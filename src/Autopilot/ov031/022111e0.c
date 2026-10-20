#include <m2c.h>

M2C_UNK func_ov031_0220f4a0();
M2C_UNK func_ov031_022101c4();
s32 func_ov031_022113c0();
M2C_UNK func_ov031_02211864(M2C_UNK, M2C_UNK);
extern void *data_ov031_0224e590;

s32 func_ov031_022111e0(void) {
    if (data_ov031_0224e590 == NULL) {
        func_ov031_02211864(9, -2);
        return 0;
    }
    if (func_ov031_022113c0() != 0) {
        return 0;
    }
    if ((M2C_FIELD(data_ov031_0224e590, s32 *, 4) == 0) && (M2C_FIELD(data_ov031_0224e590, s32 *, 0x3C) == 0)) {
        func_ov031_02211864(9, -2);
        return 0;
    }
    func_ov031_0220f4a0();
    func_ov031_022101c4();
    M2C_FIELD(data_ov031_0224e590, s32 *, 0) = 2;
    return 1;
}
