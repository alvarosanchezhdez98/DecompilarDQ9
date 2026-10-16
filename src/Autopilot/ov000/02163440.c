#include <m2c.h>


void func_ov000_02163440(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x6E44) = arg1;
    M2C_FIELD(arg0, s16 *, 0x6E46) = arg2;
    M2C_FIELD(arg0, s16 *, 0x6E48) = arg3;
}
