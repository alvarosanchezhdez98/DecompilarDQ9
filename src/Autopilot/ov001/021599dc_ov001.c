#include <m2c.h>


s32 func_ov001_021599dc(void *arg0, void *arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg1, s32 *, 0x50);
    if (temp_r2 >= (s32) M2C_FIELD(arg0, s32 *, 0x10)) {
        M2C_FIELD(arg1, s32 *, 0x50) = 0;
        return 0;
    }
    M2C_FIELD(arg1, s32 *, 0x50) = (s32) (temp_r2 + 1);
    return 1;
}
