#include <m2c.h>

s32 _Z13GetFileInNarcPKvPKcPS0_Pjj(s32, M2C_UNK *, s32 *, s32 *, s32);
M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13GetTaskStatusEi(s32, s32);
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, s32 *);
s32 func_020797dc();
void *func_02079e2c(s32, s16);
s16 *func_ov000_02160f20();
s32 func_ov000_02169a58(s32, u32);
M2C_UNK func_ov000_0216d1c4(s32, s32, s32, s32 *);
M2C_UNK func_ov025_021db8d8(void *);
M2C_UNK func_ov025_021e88d8(void *);
M2C_UNK func_ov025_021e8a40(void *, void *, void *);
M2C_UNK func_ov025_021e8a4c(void *, s32);
M2C_UNK func_ov025_021e8d20(void *, s32);
M2C_UNK sprintf(M2C_UNK *, M2C_UNK *, u32);
extern s32 data_ov025_021ef404;
extern M2C_UNK data_ov025_021ef454;
extern M2C_UNK data_ov025_021ef974;

void func_ov025_021dc694(void *arg0) {
    M2C_UNK sp18[20];
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 sp4;
    s16 *temp_r7;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    u32 var_r1;
    void *temp_r5;

    temp_r7 = func_ov000_02160f20();
    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader13GetTaskStatusEi(temp_r0, data_ov025_021ef404) != 0) {
        sp14 = 0;
        sp10 = 0;
        _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, data_ov025_021ef404, &sp14, &sp10);
        temp_r5 = func_02079e2c(func_020797dc(), *temp_r7);
        if ((sp14 != 0) && (sp10 != 0) && (temp_r5 != NULL)) {
            sprintf(sp18, &data_ov025_021ef454, (u32) (M2C_FIELD(temp_r5, s32 *, 4) << 0x14) >> 0x14);
            spC = 0;
            sp8 = 0;
            if (_Z13GetFileInNarcPKvPKcPS0_Pjj(sp14, sp18, &spC, &sp8, 0) != 0) {
                sp4 = 0;
                func_ov000_0216d1c4(arg0 + 0x30, spC, sp8, &sp4);
                if (sp4 != 0) {
                    func_ov025_021e88d8(arg0 + 0x2A8);
                    func_ov025_021e8a40(arg0 + 0x2A8, arg0 + 0x30, arg0 + 0x14C);
                    func_ov025_021e8a4c(arg0 + 0x2A8, M2C_FIELD(arg0, s32 *, 0x29C));
                    func_ov025_021e8d20(arg0 + 0x2A8, sp4);
                    func_ov025_021db8d8(arg0);
                }
            }
        }
        temp_r0_2 = M2C_FIELD(arg0, s32 *, 0xEAC);
        if ((temp_r0_2 != 3) && (temp_r0_2 != 2) && (temp_r0_2 != 6)) {
            var_r1 = (u32) (M2C_FIELD(temp_r5, s32 *, 4) << 0x14) >> 0x14;
            if (((u32) (M2C_FIELD(temp_r5, s32 *, 0x18) << 0x14) >> 0x19) == 0xC) {
                var_r1 = 0x158;
            }
            temp_r0_3 = func_ov000_02169a58(M2C_FIELD(arg0, s32 *, 0x5724), var_r1);
            if (temp_r0_3 != 0) {
                func_ov025_021e88d8(arg0 + 0x2A8);
                func_ov025_021e8a40(arg0 + 0x2A8, arg0 + 0x30, arg0 + 0x14C);
                func_ov025_021e8a4c(arg0 + 0x2A8, M2C_FIELD(arg0, s32 *, 0x29C));
                func_ov025_021e8d20(arg0 + 0x2A8, temp_r0_3);
                func_ov025_021db8d8(arg0);
            } else {
                M2C_FIELD(arg0, s32 *, 0xEAC) = 5;
                M2C_FIELD(&data_ov025_021ef974, s32 *, 0x10) = 0;
                M2C_FIELD(&data_ov025_021ef974, s32 *, 8) = 0;
            }
        }
        _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, data_ov025_021ef404);
        data_ov025_021ef404 = -1;
    }
}
