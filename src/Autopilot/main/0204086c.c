#include <m2c.h>

M2C_UNK func_0203cda8(void *, s32);
M2C_UNK func_0203db34();

void func_0204085c(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0x10) = arg1;
        M2C_FIELD(temp_r0, s32 *, 0x14) = arg2;
        M2C_FIELD(temp_r0, s32 *, 0x18) = arg3;
        func_0203cda8(M2C_FIELD(arg0, void **, 0x14), arg2);
        return;
    }
    if (M2C_FIELD(arg0, void **, 0x18) != NULL) {
        func_0203db34();
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s32 *, 0xB0) = arg2;
        return;
    }
    if (M2C_FIELD(arg0, void **, 0x1C) == NULL) {
        return;
    }
    func_0203db34();
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), s32 *, 0x2D4) = arg2;
}
