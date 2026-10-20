#include <m2c.h>

M2C_UNK _ZN13SafeAllocator5ResetEv(s32);
s32 func_ov017_0218b5b0();

void func_0208e4f8(void *arg0) {
    _ZN13SafeAllocator5ResetEv(func_ov017_0218b5b0() + 0x1A0);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}
