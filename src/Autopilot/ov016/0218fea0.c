#include <m2c.h>


void func_ov016_0218fea0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, u8 *, 0);
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(arg1, s16 *, 2);
}
