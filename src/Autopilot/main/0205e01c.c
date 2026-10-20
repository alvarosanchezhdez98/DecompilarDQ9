#include <m2c.h>

s32 func_0205d81c();

s32 func_0205e00c(void *arg0) {
    if (func_0205d81c() != 0) {
        return 0;
    }
    return (M2C_FIELD(arg0, u8 *, 0xB4) * 0xE0) + M2C_FIELD(arg0, s32 *, 0x9C);
}
