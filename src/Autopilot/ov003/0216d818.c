#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
M2C_UNK func_020421a0();
M2C_UNK func_02043204();
M2C_UNK func_0205d6a0(s32, M2C_UNK);
M2C_UNK func_ov003_0216d77c(void *);

void func_ov003_0216d818(void *arg0) {
    _ZN16BackgroundLoader13AddLockGlobalEv();
    _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
    func_020421a0();
    func_02043204();
    func_0205d6a0(M2C_FIELD(arg0, s32 *, 0x12C0), 0);
    func_ov003_0216d77c(arg0);
}
