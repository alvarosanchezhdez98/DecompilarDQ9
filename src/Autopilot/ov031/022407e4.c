#include <m2c.h>


s32 ov38_0222250C(void *arg0, u32 arg1) {
    if ((u32) M2C_FIELD(arg0, u32 *, 0xC) <= arg1) {
        return 1;
    }
    return 0;
}
