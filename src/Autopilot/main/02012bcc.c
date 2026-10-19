#include <m2c.h>

extern void *data_020fb3cc;

void func_02012bbc(s32 arg0) {
    if (arg0 == 0x10) {
        M2C_FIELD(data_020fb3cc, s8 *, 0x62) = 0;
    }
}
