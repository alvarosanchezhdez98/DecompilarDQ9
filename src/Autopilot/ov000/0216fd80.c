#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, s32 *);
M2C_UNK func_020e0028(void *, M2C_UNK, s32, s32, void *, s32);

void func_ov000_0216fd80(void *arg0, M2C_UNK arg1) {
    s32 spC;
    s32 sp8;
    s32 temp_r0;

    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, M2C_FIELD(arg0, s32 *, 0), &spC, &sp8);
    func_020e0028(arg0 + 0x88, arg1, spC, sp8, arg0 + 4, (s32) (u16) M2C_FIELD(arg0, s32 *, 0x84));
    _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(arg0, s32 *, 0) = -1;
    M2C_FIELD(arg0, s8 *, 0xA1) = 1;
}
