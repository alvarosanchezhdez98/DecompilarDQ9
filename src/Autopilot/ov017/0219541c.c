#include <m2c.h>

s32 func_0202ae18();
M2C_UNK func_0202c600(s32, s32);
M2C_UNK strcpy(void *, s32);
M2C_UNK func_ov017_02195214(s32, s32);

void func_ov017_0219541c(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_r1;
    s32 temp_r4;
    void *temp_r1_2;

    temp_r4 = func_0202ae18();
    temp_r1 = arg1 - 1;
    if (temp_r1 < 0) {
        return;
    }
    if (temp_r1 > 2) {
        return;
    }
    func_ov017_02195214(arg0 + 0x42F1 + (temp_r1 * 0xF), arg2);
    func_0202c600(temp_r4, arg1);
    temp_r1_2 = M2C_FIELD(arg0, void **, 0x441C);
    if ((M2C_FIELD(temp_r1_2, u8 *, 0) == 1) && (M2C_FIELD(temp_r1_2, u8 *, 2) == arg1)) {
        strcpy(temp_r1_2 + 4, arg2 + 2);
    }
}
