#include <m2c.h>

M2C_UNK func_02046a8c(s32, s32);
s32 func_02046b60(s32, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_020d9ab0(M2C_UNK);

void func_020d9a58(M2C_UNK arg0) {
    s32 temp_r5;
    void *temp_r0;

    temp_r0 = func_ov017_0218b5b0();
    temp_r5 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    if (func_02046b60(temp_r5, 0x1C) != 0) {
        func_02046a8c(temp_r5, M2C_FIELD(temp_r0, s32 *, 0x3B14));
        func_02046a8c(temp_r5, M2C_FIELD(temp_r0, s32 *, 0x370C));
    }
    func_020d9ab0(arg0);
}
