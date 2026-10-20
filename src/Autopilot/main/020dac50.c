#include <m2c.h>

M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_020dac68(s32);

void func_020dac40(void *arg0) {
    func_020dac68(M2C_FIELD(arg0, s32 *, 0x3BC4));
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, s32 *, 0x3BC4));
}
