#include <m2c.h>

M2C_UNK func_0202ae18();
s32 func_0202b7d8();

void func_020e3748(void *arg0, s32 arg1) {
    func_0202ae18();
    if (func_0202b7d8() != 0) {
        M2C_FIELD(arg0, u8 *, 1) = (u8) (M2C_FIELD(arg0, u8 *, 1) & ~(1 << arg1));
    }
}
