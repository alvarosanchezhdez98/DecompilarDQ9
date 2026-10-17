#include <m2c.h>
#pragma optimization_level 4


void func_ov017_021bd35c(void *arg0, void *arg1) {
    M2C_FIELD(arg0, u16 *, 0x150) = (u16) M2C_FIELD(arg1, u16 *, 0);
    M2C_FIELD(arg0, u16 *, 0x152) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0x154) = (u16) M2C_FIELD(arg1, u16 *, 4);
    M2C_FIELD(arg0, u16 *, 0x156) = (u16) M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 0x158) = (u16) M2C_FIELD(arg1, u16 *, 8);
}
