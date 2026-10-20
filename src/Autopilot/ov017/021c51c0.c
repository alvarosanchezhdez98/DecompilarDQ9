#include <m2c.h>

M2C_UNK _ZN15LightingManager11GetInstanceEv();
void *func_0200fd0c(M2C_UNK);
M2C_UNK func_020103c8(M2C_UNK, s32);
s32 func_0202c1a4(s32);
s32 func_0202c540(s32);
s32 func_0205ec34();
s32 func_0206dfb0(s32, s32, s32);

void func_ov017_021c51c0(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3, s32 arg4) {
    s32 temp_r0_2;
    u8 temp_r0;
    void *temp_r4;
    void *temp_r5;

    temp_r5 = M2C_FIELD(arg3, void **, 0x370C);
    temp_r4 = func_0200fd0c(arg2);
    if (M2C_FIELD(arg1, u8 *, 4) != func_0202c1a4(arg4)) {
        return;
    }
    M2C_FIELD(temp_r5, s8 *, 0xB) = 1;
    temp_r0 = M2C_FIELD(arg1, u8 *, 5);
    if (temp_r0 == 1) {
        temp_r0_2 = func_0205ec34();
        if (func_0206dfb0(temp_r0_2, temp_r0_2 + 0x8C, M2C_FIELD(arg1, u16 *, 8) + 0x38E) == 0) {
            M2C_FIELD(temp_r4, s32 *, 0x24) = (s32) M2C_FIELD(arg1, u16 *, 6);
        }
    } else if (temp_r0 == 2) {
        M2C_FIELD(temp_r4, s32 *, 0x28) = (s32) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_r4, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, u16 *, 8);
    }
    if ((func_0202c540(arg4) != 0) && (arg0 == 0)) {
        func_020103c8(arg2, M2C_FIELD(arg1, s32 *, 0xC));
        _ZN15LightingManager11GetInstanceEv();
    }
    M2C_FIELD(temp_r5, u16 *, 0xE) = (u16) M2C_FIELD(arg1, u16 *, 0x10);
    M2C_FIELD(temp_r5, u16 *, 0x10) = (u16) M2C_FIELD(arg1, u16 *, 0x12);
}
