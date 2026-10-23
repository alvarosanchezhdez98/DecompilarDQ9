#include <m2c.h>


void func_ov003_02166164(void *arg0, s32 arg1, s32 arg2) {
    s32 var_r1;

    if (arg1 != 0) {
        var_r1 = M2C_FIELD(arg0, s32 *, 0x464) | arg2;
    } else {
        var_r1 = M2C_FIELD(arg0, s32 *, 0x464) & ~arg2;
    }
    M2C_FIELD(arg0, s32 *, 0x464) = var_r1;
}
