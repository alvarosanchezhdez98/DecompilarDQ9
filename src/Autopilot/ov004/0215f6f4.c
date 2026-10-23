#include <m2c.h>

void *func_ov004_0215e4c0(void *, M2C_UNK);
void _ZN16MenuObjectClass68SetUnkC2EP10MenuScripthi(void *, void *, u8, s32);

void func_ov004_0215f6f4(void *arg0, s16 arg1, s16 arg2, s32 arg3) {
    s8 var_ip;
    u8 var_r2;
    void *temp_r0;

    temp_r0 = func_ov004_0215e4c0(arg0, 3);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s16 *, 0x104) = arg1;
    M2C_FIELD(temp_r0, s16 *, 0x106) = arg2;
    var_r2 = 0;
    var_ip = 0xF;
    if (arg3 != 0) {
        var_ip = 3;
        var_r2 = 1;
    }
    M2C_FIELD(temp_r0, s8 *, 0x10A) = var_ip;
    _ZN16MenuObjectClass68SetUnkC2EP10MenuScripthi(temp_r0, arg0, var_r2, 0);
}
