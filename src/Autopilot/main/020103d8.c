#include <m2c.h>


void func_020103c8(void *arg0, f32 arg1) {
    if (!(arg1 < 0.0f)) {
        M2C_FIELD(arg0, f32 *, 0x3E0) = arg1;
    }
}
