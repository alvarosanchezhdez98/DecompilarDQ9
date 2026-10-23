#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader17GetNumQueuedTasksEv();
M2C_UNK func_ov017_0218b5b0();
M2C_UNK func_ov017_0219b624();

s32 func_ov017_021b2b68(void *arg0) {
    _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader17GetNumQueuedTasksEv() > 0) {
        return M2C_FIELD(arg0, s32 *, 8);
    }
    func_ov017_0218b5b0();
    func_ov017_0219b624();
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) & ~4);
    return 3;
}
