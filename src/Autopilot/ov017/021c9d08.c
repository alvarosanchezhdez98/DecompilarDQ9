#include <m2c.h>

void *func_ov017_021b8468(s32);

void func_ov017_021c9d08(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    void *temp_r0;

    temp_r0 = func_ov017_021b8468(M2C_FIELD(arg3, s32 *, 0x3718));
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0xEB4) = (u8) M2C_FIELD(arg1, u8 *, 4);
    }
}
