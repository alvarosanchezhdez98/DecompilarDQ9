#include <m2c.h>

M2C_UNK func_0203a974(void *, M2C_UNK *, M2C_UNK *, M2C_UNK, s32);
s32 func_0203aa64(void *);
M2C_UNK func_0203aa98(void *, s16);
extern M2C_UNK data_ov031_02257180;
extern M2C_UNK data_020f057c;
extern M2C_UNK data_020f0594;

void func_0205ea20(void *arg0, s16 arg1) {
    M2C_UNK *var_r1;
    s32 temp_r0;

    var_r1 = NULL;
    if (arg1 == 0x64) {
        var_r1 = &data_020f057c;
    } else if (arg1 == 0x65) {
        var_r1 = &data_020f0594;
    }
    if (var_r1 != NULL) {
        func_0203a974(arg0, var_r1, &data_ov031_02257180, 0x4B000, 0);
    }
    M2C_FIELD(arg0, s32 *, 0xB0) = func_0203aa64(arg0);
    M2C_FIELD(arg0, s16 *, 0xB4) = arg1;
    func_0203aa98(arg0, arg1);
    temp_r0 = func_0203aa64(arg0);
    M2C_FIELD(arg0, s32 *, 0xC0) = temp_r0;
    M2C_FIELD(arg0, s32 *, 0xB8) = temp_r0;
}
