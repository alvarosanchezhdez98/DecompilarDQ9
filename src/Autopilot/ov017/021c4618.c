#include <m2c.h>

void *func_0200ff1c(M2C_UNK, u8);
M2C_UNK func_02052958(void *, void *, M2C_UNK);
M2C_UNK strcpy(s32, s32);

void func_ov017_021c4618(s32 arg0, void *arg1, M2C_UNK arg2, s32 arg3) {
    u8 temp_r5;
    void *temp_r0;

    temp_r5 = M2C_FIELD(arg1, u8 *, 4);
    temp_r0 = func_0200ff1c(arg2, temp_r5);
    if (temp_r0 == NULL) {
        return;
    }
    func_02052958(temp_r0, arg1 + 5, 1);
    strcpy((temp_r5 * 0x30) + (arg3 + 0x435C), M2C_FIELD(temp_r0, s32 *, 0x134));
}
