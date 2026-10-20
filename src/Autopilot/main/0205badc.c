#include <m2c.h>

M2C_UNK func_0205bb04(s32 *, s32);
s32 func_0205bb84();

void func_0205bacc(s32 *arg0, s32 arg1) {
    if (arg1 < 0) {
        return;
    }
    *arg0 = arg1;
    if (func_0205bb84() < arg1) {
        return;
    }
    func_0205bb04(arg0, arg1 - 1);
}
