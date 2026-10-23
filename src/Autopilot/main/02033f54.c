#include <m2c.h>


void *func_02033f44(void *arg0) {
    if (((u32) (M2C_FIELD(arg0, u8 *, 0xE0) << 0x19) >> 0x1F) != 0) {
        return arg0 + 0xE4;
    }
    return NULL;
}
