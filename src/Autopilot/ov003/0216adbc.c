#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader20MaybeFreeAllocationsEv();
M2C_UNK func_ov003_02168324(void *);

void func_ov003_0216adbc(void *arg0) {
    s32 temp_r4;

    if (M2C_FIELD(arg0, u8 *, 0x5A4) != 0) {
        return;
    }
    temp_r4 = _ZN16BackgroundLoader11GetInstanceEv();
    _ZN16BackgroundLoader20MaybeFreeAllocationsEv();
    _ZN16BackgroundLoader10RemoveTaskEi(temp_r4, M2C_FIELD(arg0, s32 *, 0x4E0));
    M2C_FIELD(arg0, s32 *, 0x4E0) = -1;
    func_ov003_02168324(arg0);
    M2C_FIELD(arg0, s8 *, 0x4EC) = 6;
    M2C_FIELD(arg0, s8 *, 0x4E8) = 0;
}
