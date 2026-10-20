#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, s32 *);
M2C_UNK func_0203bd08();
s32 *func_0203bd14();
s32 func_0203be4c();
M2C_UNK func_0205a498(s32, s32, s32, M2C_UNK);
M2C_UNK func_0205af38(s32, s32, M2C_UNK, M2C_UNK);

void func_02020aec(s32 arg0, s32 *arg1, M2C_UNK arg2) {
    s32 sp4;
    s32 sp0;
    s32 temp_r0;
    s32 temp_r4;

    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    sp4 = 0;
    sp0 = 0;
    _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, *arg1, &sp4, &sp0);
    M2C_FIELD(func_0203bd14(), s32 *, 0x508) = 0x2000;
    func_0203bd08();
    temp_r4 = func_0203be4c() + 0x2C0;
    *func_0203bd14() = temp_r4;
    func_0205a498(arg0 + 0x94, sp4, sp0, arg2);
    _ZN16BackgroundLoader10RemoveTaskEi(_ZN16BackgroundLoader11GetInstanceEv(), *arg1);
    *arg1 = -1;
    func_0205af38(arg0 + 0x94, arg0 + 0x250, 1, 1);
    func_0205af38(arg0 + 0x94, arg0 + 0x2A0, 1, 1);
}
