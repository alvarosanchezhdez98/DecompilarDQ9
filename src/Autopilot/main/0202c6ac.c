#include <m2c.h>

s32 func_0202bcbc(void *, M2C_UNK);
s32 func_0202c540();

void func_0202c69c(void *arg0, M2C_UNK arg1) {
    if (func_0202c540() != 0) {
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x100F) = (u8) (M2C_FIELD(arg0, u8 *, 0x100F) & ~(1 << func_0202bcbc(arg0, arg1)));
}
