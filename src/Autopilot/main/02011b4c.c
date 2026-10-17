#include <m2c.h>


void func_02011b3c(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x63DC) = (u8) (M2C_FIELD(arg0, u8 *, 0x63DC) | arg1);
}
