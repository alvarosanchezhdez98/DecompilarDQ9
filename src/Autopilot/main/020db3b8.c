#include <m2c.h>

void *func_ov017_0218b5b0();

s32 func_020db3a8(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x54) == 1) && (((s32) (*(u16 *)0x04000304 & 0x8000) >> 0xF) == 1)) {
        return 1;
    }
    if (M2C_FIELD(M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3718), u8 *, 3) != 0) {
        return 1;
    }
    return 0;
}
