#include <m2c.h>

s32 func_0202bcbc(void *, M2C_UNK);
s32 func_0202c540();

void func_0202c6dc(void *arg0, M2C_UNK arg1) {
    if (func_0202c540() != 0) {
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x1010) = (u8) (M2C_FIELD(arg0, u8 *, 0x1010) | (1 << func_0202bcbc(arg0, arg1)));
}
