#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader17GetNumQueuedTasksEv();
M2C_UNK func_0203b4e8(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_021a2fa0();

s32 func_ov017_021b2b14(void *arg0) {
    s32 temp_r4;

    _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader17GetNumQueuedTasksEv() > 0) {
        return M2C_FIELD(arg0, s32 *, 8);
    }
    temp_r4 = func_ov017_0218b5b0();
    func_ov017_021a2fa0();
    func_0203b4e8(temp_r4, 8);
    func_0203b4e8(temp_r4, 0x10);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) & ~2);
    return 3;
}
