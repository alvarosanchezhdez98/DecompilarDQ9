#include <m2c.h>

M2C_UNK _Z26FindFilesInNarcBySubstringPKvPKcPS0_Pjj(s32, M2C_UNK *, s32 *, s32 *, s32);
M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13GetTaskStatusEi(s32, s32);
s32 _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(s32, M2C_UNK *, M2C_UNK);
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, M2C_UNK *);
s32 _ZN16BackgroundLoader21GetDetailedTaskStatusEi(s32, s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_020280b0(s32);
M2C_UNK func_02028104(void *, s32, s32, s32);
M2C_UNK func_02028214(void *, s32);
extern M2C_UNK data_ov017_021d7b3a;
extern M2C_UNK data_ov017_021d7b4f;

void func_ov017_021b498c(void *arg0) {
    M2C_UNK sp10;
    s32 spC;
    s32 sp8;
    s32 sp4;
    s32 temp_r0;
    void *temp_r6;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader13GetTaskStatusEi(temp_r0, M2C_FIELD(arg0, s32 *, 0xC)) != 0) {
        if (_ZN16BackgroundLoader21GetDetailedTaskStatusEi(temp_r0, M2C_FIELD(arg0, s32 *, 0xC)) == 2) {
            _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, M2C_FIELD(arg0, s32 *, 0xC), &spC, &sp10);
            if (spC != 0) {
                _Z26FindFilesInNarcBySubstringPKvPKcPS0_Pjj(spC, &data_ov017_021d7b4f, &sp4, &sp8, 1);
                if (sp4 != 0) {
                    temp_r6 = M2C_FIELD(arg0, void **, 8);
                    func_020280b0(temp_r6 + 0x18);
                    func_02028104(temp_r6 + 0x18, M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x10), sp4, sp8);
                    func_02028214(temp_r6 + 0x18, M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x10));
                    M2C_FIELD(temp_r6, s8 *, 0xC) = 1;
                }
            }
        }
        _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, M2C_FIELD(arg0, s32 *, 0xC));
        M2C_FIELD(arg0, s32 *, 0xC) = -1;
        M2C_FIELD(arg0, s32 *, 0xC) = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(temp_r0, &data_ov017_021d7b3a, 0);
        M2C_FIELD(arg0, s8 *, 0x10) = 3;
    }
}
