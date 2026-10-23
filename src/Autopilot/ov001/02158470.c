#include <m2c.h>


s32 func_ov001_02158470(void *arg0, void *arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg1, s32 *, 0x44);
    if (temp_r2 >= (s32) M2C_FIELD(arg0, s32 *, 0x1C)) {
        M2C_FIELD(arg1, s32 *, 0x44) = 0;
        return 0;
    }
    M2C_FIELD(arg1, s32 *, 0x44) = (s32) (temp_r2 + 1);
    return 1;
}
