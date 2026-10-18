#include <m2c.h>

M2C_UNK func_0202e9a4();

void func_0202f0c4(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x1F0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x1F4) = arg2;
    if (arg2 != 0) {
        return;
    }
    func_0202e9a4();
}
