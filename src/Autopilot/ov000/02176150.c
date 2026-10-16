#include <m2c.h>

M2C_UNK func_ov000_0217616c();

void func_ov000_02176150(void *arg0, s16 arg1) {
    if (arg1 == M2C_FIELD(arg0, s16 *, 0xE)) {
        return;
    }
    M2C_FIELD(arg0, s16 *, 0xE) = arg1;
    func_ov000_0217616c();
}
