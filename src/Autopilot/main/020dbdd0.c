#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13GetTaskStatusEi(s32, s32);
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, s32 *);
s32 func_02057924();
M2C_UNK func_02057de0(s32, s32, s32, s32, s32);
s32 func_02058680(s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0207df90(s32);
M2C_UNK func_0207dfac(s32);
M2C_UNK memcpy(s32, s32, s32);
M2C_UNK func_020dbf70(void *);

void func_020dbdc0(void *arg0) {
    s32 sp8;
    s32 sp4;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r6;

    if ((s32) M2C_FIELD(arg0, s32 *, 0xC) >= 0) {
        temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
        if (_ZN16BackgroundLoader13GetTaskStatusEi(temp_r0, M2C_FIELD(arg0, s32 *, 0xC)) != 0) {
            temp_r6 = func_02057924();
            sp8 = 0;
            sp4 = 0;
            _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, M2C_FIELD(arg0, s32 *, 0xC), &sp8, &sp4);
            temp_r0_2 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(arg0, s32 *, 0), sp4);
            if (temp_r0_2 == 0) {
                func_020dbf70(arg0);
                return;
            }
            memcpy(temp_r0_2, sp8, sp4);
            func_0207df90(M2C_FIELD(arg0, s32 *, 4));
            func_02057de0(temp_r6, M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0), temp_r0_2, sp4);
            func_0207dfac(M2C_FIELD(arg0, s32 *, 4));
            func_020dbf70(arg0);
            M2C_FIELD(arg0, s32 *, 0x10) = 2;
            goto block_5;
        }
    }
block_5:
    if (M2C_FIELD(arg0, u8 *, 0x14) != 0) {
        temp_r0_3 = func_02057924();
        if ((temp_r0_3 != 0) && (func_02058680(temp_r0_3, M2C_FIELD(arg0, s32 *, 8), 0, 0) <= 0)) {
            M2C_FIELD(arg0, u8 *, 0x14) = 0U;
        }
    }
}
