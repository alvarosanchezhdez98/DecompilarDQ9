#include <m2c.h>

M2C_UNK func_02049550(s32);

void func_02049520(void *arg0) {
    void *temp_r0;
    void *temp_r1;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 == NULL) {
        return;
    }
    func_02049550(temp_r0 + 0x4E);
    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    M2C_FIELD(temp_r1, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1, s32 *, 0x20) & ~4);
}
