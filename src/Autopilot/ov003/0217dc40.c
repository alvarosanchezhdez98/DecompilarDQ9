#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
s32 func_020421a0();
M2C_UNK func_02043204(s32);
M2C_UNK func_0205d6a0(s32, M2C_UNK);
M2C_UNK func_ov003_0217db88(void *);

void func_ov003_0217dc40(void *arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r4 = func_020421a0();
    _ZN16BackgroundLoader13AddLockGlobalEv();
    _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
    temp_r5 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_r5 != -1) {
        _ZN16BackgroundLoader10RemoveTaskEi(_ZN16BackgroundLoader11GetInstanceEv(), temp_r5);
    }
    func_0205d6a0(M2C_FIELD(arg0, s32 *, 0x90), 0);
    func_02043204(temp_r4);
    func_ov003_0217db88(arg0);
}
