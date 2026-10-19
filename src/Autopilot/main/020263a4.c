#include <m2c.h>


void func_02026394(void *arg0, u32 arg1) {
    if (arg1 < 4U) {
        M2C_FIELD(arg0, u8 *, 0x75D) = (u8) (M2C_FIELD(arg0, u8 *, 0x75D) & ~(1 << arg1));
    }
}
