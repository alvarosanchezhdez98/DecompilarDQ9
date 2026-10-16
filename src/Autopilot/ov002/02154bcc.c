#include <m2c.h>

M2C_UNK func_0205ac40(void *, void *);

void func_ov002_02154bcc(s32 arg0, s32 arg1, void *arg2, u32 arg3, u8 arg4, u8 arg5) {
    s32 temp_lr;
    s32 var_r4;

    temp_lr = M2C_FIELD(arg2, s32 *, 0x40);
    var_r4 = 0;
    if ((temp_lr != 0) && (arg3 < (u32) M2C_FIELD(arg2, u16 *, 0x4E))) {
        var_r4 = (arg3 * 0x28) + temp_lr;
    }
    if (var_r4 == 0) {
        return;
    }
    M2C_FIELD(var_r4, s32 *, 0x14) = (s32) (arg0 << 0xC);
    M2C_FIELD(var_r4, s32 *, 0x18) = (s32) (arg1 << 0xC);
    if (arg5 != 0xFF) {
        M2C_FIELD(var_r4, u8 *, 0x25) = arg5;
    }
    if (arg4 != 0xFF) {
        M2C_FIELD(var_r4, u8 *, 0x22) = arg4;
    }
    func_0205ac40(arg2, (void *) var_r4);
}
