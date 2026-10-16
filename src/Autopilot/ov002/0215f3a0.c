#include <m2c.h>

M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
void *func_0205d81c(void *, u8);
M2C_UNK func_0205de24(void *, M2C_UNK, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_0215be00(void *, u8, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_0215f4e8(void *, s32, M2C_UNK);
M2C_UNK func_ov002_0215f644(void *, s32, M2C_UNK);

void func_ov002_0215f3a0(void *arg0) {
    s16 temp_r4;
    s16 temp_r5;
    s16 temp_r6;
    void *temp_r0;
    void *temp_r0_2;

    func_ov002_0215be00(arg0, 0x16U, 0x10, 0x14);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_ov002_0215f644(arg0, M2C_FIELD(arg0, s32 *, 0x1BD0), 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 0, 0, 0);
    func_0205de24(arg0 + 0xEC8, 0, 2);
    func_ov002_0215be00(arg0, (u8) M2C_FIELD(arg0, s32 *, 0x1BB8), 1, 1);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_ov002_0215f4e8(arg0, M2C_FIELD(arg0, s32 *, 0x1BD0), 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 1, 0, 0);
    temp_r0 = func_0205d81c(arg0 + 0xEC8, (u8) M2C_FIELD(arg0, s32 *, 0x1BB8));
    if (temp_r0 != NULL) {
        temp_r4 = M2C_FIELD(temp_r0, s16 *, 0xAC);
        temp_r6 = M2C_FIELD(temp_r0, s16 *, 0xA8);
        temp_r5 = M2C_FIELD(temp_r0, s16 *, 0xAE);
        temp_r0_2 = func_0205d81c(arg0 + 0xEC8, 0x16U);
        if (temp_r0_2 != NULL) {
            M2C_FIELD(temp_r0_2, s16 *, 0xAC) = (s16) (temp_r4 + temp_r6);
            M2C_FIELD(temp_r0_2, s16 *, 0xAE) = temp_r5;
        }
    }
}
