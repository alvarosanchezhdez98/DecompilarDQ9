#include <m2c.h>


void func_ov017_021a85d4(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
    if (arg1 == 5) {
        M2C_FIELD(arg0, s16 *, 0x38) = 0x3C;
    }
}
