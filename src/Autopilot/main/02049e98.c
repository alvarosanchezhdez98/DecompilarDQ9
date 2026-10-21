#include <m2c.h>

M2C_UNK func_02048cf0(void *, M2C_UNK);

void func_02049e88(void *arg0) {
    void *temp_r3;
    void *temp_r3_2;

    temp_r3 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r3 == NULL) {
        return;
    }
    M2C_FIELD(temp_r3, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x20) & ~3);
    temp_r3_2 = M2C_FIELD(arg0, void **, 0x13C);
    M2C_FIELD(temp_r3_2, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r3_2, s32 *, 0x20) | 0x20);
    func_02048cf0(arg0, 0);
}
