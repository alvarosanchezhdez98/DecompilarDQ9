#include <m2c.h>


s32 func_020db9a8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x54) == 0) {
        return (s32) (*(u16 *)0x04000304 & 0x8000) >> 0xF;
    }
    return 0;
}
