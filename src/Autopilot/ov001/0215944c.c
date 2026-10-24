#include <m2c.h>

M2C_UNK func_ov001_021579ac(void *);
M2C_UNK func_ov001_02157acc(void *);
M2C_UNK func_ov001_02157ae0(void *, void *, void *);

s32 func_ov001_0215944c(s32 arg0, void *arg1) {
    u32 var_r0;

    if ((s32) M2C_FIELD(arg1, s32 *, 0x48) <= 0) {
        func_ov001_021579ac(arg1 + 0x11C);
        func_ov001_02157acc(arg1 + 0x11C);
        M2C_FIELD(arg1, s32 *, 0x48) = 1;
    }
    func_ov001_02157ae0(arg1 + 0x11C, arg1 + 0x74, arg1 + 0x84);
    if (M2C_FIELD(arg1, s32 *, 0x580) == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        M2C_FIELD(arg1, s32 *, 0x48) = 0;
        return 0;
    }
    return 1;
}
