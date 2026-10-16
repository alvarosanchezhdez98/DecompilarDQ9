#include <m2c.h>


void func_ov003_0215917c(void *arg0, s32 arg1) {
    u8 temp_ip;
    u8 temp_ip_2;
    u8 temp_ip_3;
    u8 temp_ip_4;
    u8 temp_r3;
    u8 temp_r3_2;

    M2C_FIELD(arg0, u8 *, 0x589) = 0U;
    if (arg1 & 1) {
        temp_r3 = M2C_FIELD(arg0, u8 *, 0x589);
        M2C_FIELD(arg0, u8 *, 0x589) = (u8) (temp_r3 + 1);
        M2C_FIELD((arg0 + temp_r3), s8 *, 0x58A) = 0;
    }
    if (arg1 & 2) {
        temp_ip = M2C_FIELD(arg0, u8 *, 0x589);
        M2C_FIELD(arg0, u8 *, 0x589) = (u8) (temp_ip + 1);
        M2C_FIELD((arg0 + temp_ip), s8 *, 0x58A) = 1;
    }
    if (arg1 & 4) {
        temp_ip_2 = M2C_FIELD(arg0, u8 *, 0x589);
        M2C_FIELD(arg0, u8 *, 0x589) = (u8) (temp_ip_2 + 1);
        M2C_FIELD((arg0 + temp_ip_2), s8 *, 0x58A) = 2;
    }
    if (arg1 & 8) {
        temp_ip_3 = M2C_FIELD(arg0, u8 *, 0x589);
        M2C_FIELD(arg0, u8 *, 0x589) = (u8) (temp_ip_3 + 1);
        M2C_FIELD((arg0 + temp_ip_3), s8 *, 0x58A) = 3;
    }
    if (arg1 & 0x10) {
        temp_ip_4 = M2C_FIELD(arg0, u8 *, 0x589);
        M2C_FIELD(arg0, u8 *, 0x589) = (u8) (temp_ip_4 + 1);
        M2C_FIELD((arg0 + temp_ip_4), s8 *, 0x58A) = 4;
    }
    if (!(arg1 & 0x20)) {
        return;
    }
    temp_r3_2 = M2C_FIELD(arg0, u8 *, 0x589);
    M2C_FIELD(arg0, u8 *, 0x589) = (u8) (temp_r3_2 + 1);
    M2C_FIELD((arg0 + temp_r3_2), s8 *, 0x58A) = 5;
}
