#include <m2c.h>

M2C_UNK _ZN9StaffRoll4DrawEv();
M2C_UNK func_0208be90();
s32 func_020a18f4(M2C_UNK);
M2C_UNK func_ov001_0215686c();

void func_ov017_021bb8f0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x160) != 0) {
        _ZN9StaffRoll4DrawEv();
    }
    if (M2C_FIELD(arg0, s32 *, 0x120) != 0) {
        func_0208be90();
    }
    if (func_020a18f4(1) == 0) {
        return;
    }
    func_ov001_0215686c();
}
