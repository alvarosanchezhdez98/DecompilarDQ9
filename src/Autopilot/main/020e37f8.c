#include <m2c.h>

M2C_UNK func_0202ae18();
s32 func_0202b7d8();

u8 func_020e37e8(void *arg0) {
    func_0202ae18();
    if (func_0202b7d8() != 0) {
        return M2C_FIELD(arg0, u8 *, 2);
    }
    return 1U;
}
