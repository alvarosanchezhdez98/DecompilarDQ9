#include <m2c.h>
#pragma optimization_level 4


void func_0203409c(void *arg0) {
    M2C_FIELD(arg0, u16 *, 0xC4) = (u16) (M2C_FIELD(arg0, u16 *, 0xC4) & ~0x7FFF);
}
