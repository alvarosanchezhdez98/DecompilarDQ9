#include <m2c.h>

M2C_UNK func_0202ae18();
s32 func_0202b7d8();

void func_020e3778(void *arg0) {
    func_0202ae18();
    if (func_0202b7d8() != 0) {
        M2C_FIELD(arg0, s8 *, 2) = 1;
    }
}
