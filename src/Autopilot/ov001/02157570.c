#include <m2c.h>


void func_ov001_02157570(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x38C);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x390);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x394);
}
