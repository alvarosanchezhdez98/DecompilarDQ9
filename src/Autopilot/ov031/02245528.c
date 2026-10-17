#include <m2c.h>


void func_ov031_02245528(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x34) = arg1;
    M2C_FIELD(arg0, s8 *, 0x35) = 0;
    M2C_FIELD(arg0, s8 *, 0x37) = 0;
    if (arg1 == 0) {
        M2C_FIELD(arg0, s8 *, 0x36) = 1;
    }
}
