#include <m2c.h>


void func_020968a4(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(arg0, s16 *, 0x228);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(arg0, s16 *, 0x22A);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s16 *, 0x22C);
}
