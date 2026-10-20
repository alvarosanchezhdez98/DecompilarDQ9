#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(void *, void *);
s32 _ZN9GameState11GetInstanceEv();
void *func_0200fd0c(s32);
void *func_0200ffc0(s32);
void *func_02012fe4();
s32 func_0202ae18();
s32 func_0202c508(s32);
M2C_UNK func_02070378(void *);
M2C_UNK func_ov017_021d1a18(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov017_02199360(void *arg0) {
    s32 temp_r4;
    s32 temp_r7;
    void *temp_r4_2;
    void *temp_r5;
    void *temp_r6;
    void *temp_r8;

    if (M2C_FIELD(arg0, u8 *, 0x36B8) == 0) {
        return;
    }
    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r7 = func_0202ae18();
    temp_r6 = func_02012fe4();
    temp_r8 = M2C_FIELD(arg0, void **, 0x36BC);
    temp_r5 = func_0200fd0c(temp_r4);
    temp_r4_2 = func_0200ffc0(temp_r4);
    if (func_0202c508(temp_r7) != 0) {
        _ZN8Vector3iaSERKS_(temp_r6 + 0x2774, temp_r8 + 0x40);
        M2C_FIELD(temp_r6, s32 *, 0x2780) = (s32) M2C_FIELD(temp_r8, s16 *, 0x4C);
        func_02070378(temp_r5);
        M2C_FIELD(temp_r5, s16 *, 0) = 0x2710;
        M2C_FIELD(temp_r5, s8 *, 2) = 1;
        M2C_FIELD(temp_r5, s8 *, 7) = 1;
        _ZN8Vector3iaSERKS_(temp_r5 + 0x10, temp_r4_2 + 0x44);
        M2C_FIELD(temp_r5, s16 *, 0x1C) = (s16) M2C_FIELD(temp_r4_2, s32 *, 0x54);
        M2C_FIELD(temp_r6, s8 *, 0x2788) = 1;
        func_ov017_021d1a18(1, -1, 1, 0);
        return;
    }
    func_02070378(temp_r5);
    M2C_FIELD(temp_r5, s16 *, 0) = 0x170C;
    M2C_FIELD(temp_r5, s8 *, 2) = 1;
    M2C_FIELD(temp_r5, s8 *, 7) = 1;
    M2C_FIELD(temp_r5, s32 *, 0x10) = -0x7000;
    M2C_FIELD(temp_r5, s32 *, 0x14) = 0x2E1;
    M2C_FIELD(temp_r5, s32 *, 0x18) = 0x5E66;
    M2C_FIELD(temp_r5, s16 *, 0x1C) = 0x3244;
}
