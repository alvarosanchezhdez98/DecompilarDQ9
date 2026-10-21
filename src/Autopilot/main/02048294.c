#include <m2c.h>


s32 func_02048284(void *arg0, s32 arg1) {
    s32 temp_r0;
    u16 temp_r2;
    u16 temp_r3;
    void *temp_ip;

    temp_ip = M2C_FIELD(arg0, void **, 0x130);
    temp_r3 = M2C_FIELD(temp_ip, u16 *, 6);
    temp_r2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), u16 *, 0x32);
    temp_r0 = temp_r2 - temp_r3;
    if (temp_r0 <= 0) {
        return 0;
    }
    if (temp_r0 <= arg1) {
        M2C_FIELD(temp_ip, u16 *, 6) = temp_r2;
        return temp_r0;
    }
    M2C_FIELD(temp_ip, u16 *, 6) = (u16) (temp_r3 + arg1);
    return arg1;
}
