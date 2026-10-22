#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(void *, void *);

void func_02048c90(void *arg0) {
    void *temp_r0;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r1_3;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s8 *, 0x34) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x13C), s32 *, 0x38) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x13C), s16 *, 0x3C) = 0;
    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    _ZN8Vector3iaSERKS_(temp_r1 + 0x40, temp_r1 + 0x10);
    temp_r1_2 = M2C_FIELD(arg0, void **, 0x13C);
    M2C_FIELD(temp_r1_2, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1_2, s32 *, 0x20) & ~0x10);
    temp_r1_3 = M2C_FIELD(arg0, void **, 0x13C);
    M2C_FIELD(temp_r1_3, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1_3, s32 *, 0x20) & ~0x40);
}
