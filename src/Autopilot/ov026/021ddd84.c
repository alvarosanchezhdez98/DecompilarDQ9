#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_0202ae18();
M2C_UNK func_0207d78c();
s32 func_ov017_02195658(M2C_UNK);
M2C_UNK func_ov026_021dbd1c(M2C_UNK, s32, u8);

s32 func_ov026_021ddd84(M2C_UNK arg0, M2C_UNK arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    s32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    func_0202ae18();
    func_0207d78c();
    temp_r0 = func_ov017_02195658(arg0);
    if (temp_r0 <= -1) {
        return 0;
    }
    func_ov026_021dbd1c(arg1, temp_r0, arg6);
    return 1;
}
