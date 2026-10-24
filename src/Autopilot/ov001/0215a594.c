#include <m2c.h>

M2C_UNK strcpy(void *, M2C_UNK);
void *func_ov001_02159f94();

void func_ov001_0215a594(s32 arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    void *temp_r0;

    temp_r0 = func_ov001_02159f94();
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s32 *, 0) = 0xB;
    strcpy(temp_r0 + 0x1C, arg1);
    M2C_FIELD(temp_r0, s32 *, 0x10) = arg2;
    M2C_FIELD(temp_r0, s32 *, 0x14) = arg3;
    M2C_FIELD(temp_r0, s32 *, 0x18) = 0;
}
