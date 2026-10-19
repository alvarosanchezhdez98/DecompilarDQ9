#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13GetTaskStatusEi(s32, s32);
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, s32 *);
M2C_UNK func_0201c724(u16, void *, s32, s32);
M2C_UNK func_0201403c(void *);

s32 func_02013fb4(void *arg0) {
    s32 sp4;
    s32 sp0;
    s32 temp_r0;

    if ((s32) M2C_FIELD(arg0, s32 *, 0x430) < 0) {
        return 1;
    }
    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader13GetTaskStatusEi(temp_r0, M2C_FIELD(arg0, s32 *, 0x430)) == 0) {
        return 0;
    }
    _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, M2C_FIELD(arg0, s32 *, 0x430), &sp4, &sp0);
    func_0201c724(M2C_FIELD(arg0, u16 *, 0), arg0 + 0xC, sp4, sp0);
    _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, M2C_FIELD(arg0, s32 *, 0x430));
    M2C_FIELD(arg0, s32 *, 0x430) = -1;
    func_0201403c(arg0);
    return 1;
}
