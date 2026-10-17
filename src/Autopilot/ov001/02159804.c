#include <m2c.h>


s32 func_ov001_02159804(void *arg0, void *arg1) {
    M2C_FIELD(arg1, f32 *, 0x8C) = (f32) M2C_FIELD(arg0, s32 *, 0x10);
    return 0;
}
