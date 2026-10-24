#include <m2c.h>

M2C_UNK func_020813ec(s32, M2C_UNK);
void *func_02081da8(s32);

void func_ov003_02166f80(void *arg0, M2C_UNK arg1, s32 arg2) {
    u8 temp_r1;
    s32 var_r1;
    void *temp_r0;

    temp_r0 = func_02081da8(M2C_FIELD(arg0, s32 *, 0x324));
    if (temp_r0 == NULL) {
        return;
    }
    temp_r1 = M2C_FIELD(temp_r0, u8 *, 0xC5);
    if (arg2 != 0) {
        var_r1 = temp_r1 | 0x40;
    } else {
        var_r1 = temp_r1 & ~0x40;
    }
    M2C_FIELD(temp_r0, u8 *, 0xC5) = var_r1;
    func_020813ec(M2C_FIELD(arg0, s32 *, 0x324), arg1);
}
