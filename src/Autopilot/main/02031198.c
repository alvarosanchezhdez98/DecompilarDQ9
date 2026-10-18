#include <m2c.h>

M2C_UNK func_020311e8(s32, s16, s16, s16);

void func_02031188(s32 arg0, void *arg1) {
    func_020311e8(arg0 + 0x24, M2C_FIELD(arg1, s16 *, 0x12), M2C_FIELD(arg1, s16 *, 0x14), M2C_FIELD(arg1, s16 *, 0x16));
    func_020311e8(arg0, M2C_FIELD(arg1, s16 *, 0), M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 4));
    func_020311e8(arg0 + 0xC, M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg1, s16 *, 8), M2C_FIELD(arg1, s16 *, 0xA));
    func_020311e8(arg0 + 0x18, M2C_FIELD(arg1, s16 *, 0xC), M2C_FIELD(arg1, s16 *, 0xE), M2C_FIELD(arg1, s16 *, 0x10));
}
