#include <m2c.h>

M2C_UNK func_ov000_0217616c();

void func_ov000_02176134(void *arg0, s16 arg1) {
    if (arg1 == M2C_FIELD(arg0, s16 *, 0xC)) {
        return;
    }
    M2C_FIELD(arg0, s16 *, 0xC) = arg1;
    func_ov000_0217616c();
}
