#include <m2c.h>

s32 func_0202c508(s32);
M2C_UNK func_ov017_02192654(s32, u16, u8);
M2C_UNK func_ov017_021a23b0(M2C_UNK, u16);

void func_ov017_021d0ae4(s32 arg0, void *arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    if (func_0202c508(arg4) != 0) {
        func_ov017_02192654(arg0, M2C_FIELD(arg1, u16 *, 4), M2C_FIELD(arg1, u8 *, 6));
        return;
    }
    if (arg0 != 0) {
        return;
    }
    func_ov017_021a23b0(arg3, M2C_FIELD(arg1, u16 *, 4));
}
