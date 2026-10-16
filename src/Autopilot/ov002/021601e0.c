#include <m2c.h>

M2C_UNK func_02041a28(s32, M2C_UNK);
M2C_UNK func_02041a90(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_02041cc0(s32, M2C_UNK);
M2C_UNK func_02042084(s32, s32, M2C_UNK, M2C_UNK);
s32 func_020e0434(s32, s16);

void func_ov002_021601e0(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        return;
    }
    func_02041a28(arg1, 0);
    func_02042084(arg1, func_020e0434(arg0 + 0x20, 0x1130), 0x48, 0);
    func_02041cc0(arg1, 0x10);
    func_02041a90(arg1, 0, 0x3A);
    func_02042084(arg1, func_020e0434(arg0 + 0x20, (s16) (M2C_FIELD(arg0, s16 *, 0x1C06) + 0x1131)), 0x48, 0);
}
