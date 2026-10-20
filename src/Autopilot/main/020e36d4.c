#include <m2c.h>

M2C_UNK func_0202ae18();
s32 func_0202b7d8();

void func_020e36c4(u8 *arg0, s32 arg1) {
    func_0202ae18();
    if (func_0202b7d8() != 0) {
        *arg0 |= 1 << arg1;
    }
}
