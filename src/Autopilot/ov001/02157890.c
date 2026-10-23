#include <m2c.h>

s32 func_ov001_021570b4(void *);
M2C_UNK func_ov001_02157570(void *, M2C_UNK);

void func_ov001_02157890(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_r7;
    s32 var_r8;

    if (M2C_FIELD(arg0, s32 *, 0x8C0) == 0) {
        return;
    }
    var_r7 = 0;
    var_r8 = 0;
    if (func_ov001_021570b4(arg0 + 0x188) != 0) {
        var_r7 = 1;
    }
    if (func_ov001_021570b4(arg0 + 0x524) != 0) {
        var_r8 = 1;
    }
    if ((var_r7 != 0) && (var_r8 != 0)) {
        M2C_FIELD(arg0, s32 *, 0x8C0) = 0;
    }
    func_ov001_02157570(arg0 + 0x188, arg1);
    func_ov001_02157570(arg0 + 0x524, arg2);
}
