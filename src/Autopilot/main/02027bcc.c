#include <m2c.h>


void func_02027bbc(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0xA97) = (u8) (M2C_FIELD(arg0, u8 *, 0xA97) & ~arg1);
}
