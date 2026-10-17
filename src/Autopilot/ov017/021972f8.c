#include <m2c.h>


void func_ov017_021972f8(void *arg0, s16 arg1) {
    u8 temp_ip;

    temp_ip = M2C_FIELD(arg0, u8 *, 0x44C0);
    M2C_FIELD(arg0, u8 *, 0x44C0) = (u8) (temp_ip + 1);
    M2C_FIELD((arg0 + (temp_ip * 2)), s16 *, 0x44B8) = arg1;
    M2C_FIELD(arg0, u8 *, 0x44C0) = (u8) (M2C_FIELD(arg0, u8 *, 0x44C0) & 3);
}
