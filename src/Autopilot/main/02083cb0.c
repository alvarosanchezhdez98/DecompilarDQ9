#include <m2c.h>


void func_02083ca0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u16 *, 0x954) = (u16) (M2C_FIELD(arg0, u16 *, 0x954) | (1 << arg1));
    M2C_FIELD(arg0, s32 *, 0x950) = arg1;
}
