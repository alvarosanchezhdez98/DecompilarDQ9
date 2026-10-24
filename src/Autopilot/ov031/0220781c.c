#include <m2c.h>


void SOC_U32to4U8(u32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0) = (s8) (arg0 >> 0x18);
    M2C_FIELD(arg1, s8 *, 1) = (s8) (arg0 >> 0x10);
    M2C_FIELD(arg1, s8 *, 2) = (s8) (arg0 >> 8);
    M2C_FIELD(arg1, u8 *, 3) = arg0;
}
