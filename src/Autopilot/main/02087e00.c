#include <m2c.h>


void func_02087df0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x10000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0x1C0000);
    M2C_FIELD(arg0, s8 *, 0x74) = 0;
    M2C_FIELD(arg0, s8 *, 0x97) = 0;
}
