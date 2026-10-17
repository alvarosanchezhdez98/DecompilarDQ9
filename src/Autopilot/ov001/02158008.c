#include <m2c.h>


s32 func_ov001_02158008(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x64) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
    return 0;
}
