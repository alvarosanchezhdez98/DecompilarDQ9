#include <m2c.h>


void *func_0209bd80(void *arg0, s32 arg1) {
    if ((s32) M2C_FIELD(arg0, s32 *, 0xC0) <= arg1) {
        return NULL;
    }
    return arg0 + (arg1 << 5);
}
