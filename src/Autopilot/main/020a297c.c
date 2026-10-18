#include <m2c.h>

M2C_UNK func_020a2928(s32);

void func_020a296c(void *arg0) {
    func_020a2928(arg0 + 0x298);
    M2C_FIELD(arg0, u8 *, 0x245) = (u8) (M2C_FIELD(arg0, u8 *, 0x245) | 4);
}
