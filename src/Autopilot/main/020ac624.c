#include <m2c.h>


void func_020ac614(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) + arg1);
    if ((u32) M2C_FIELD(arg0, u16 *, 0) > 0x270FU) {
        M2C_FIELD(arg0, u16 *, 0) = 0x270FU;
        M2C_FIELD(arg0, s8 *, 2) = 0x3B;
        M2C_FIELD(arg0, s8 *, 3) = 0x3B;
    }
}
