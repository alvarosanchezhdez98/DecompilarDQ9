#include <m2c.h>

M2C_UNK func_020a620c(s32);

void func_ov003_02173788(void *arg0) {
    func_020a620c(arg0 + 0xD8);
    if (M2C_FIELD(arg0, u8 *, 0xEF) != 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0xCB) != 0) {
        M2C_FIELD(arg0, u8 *, 0xCB) = 0U;
        M2C_FIELD(arg0, s8 *, 0xED) = 3;
        M2C_FIELD(arg0, u8 *, 0xEF) = 0U;
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0xCA) != 0) {
        M2C_FIELD(arg0, s8 *, 0xED) = 4;
        M2C_FIELD(arg0, u8 *, 0xEF) = 0U;
    }
}
