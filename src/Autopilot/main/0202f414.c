#include <m2c.h>

M2C_UNK func_0202f45c(void *, s32, s32, s32, s32, s32, s32);

void func_0202f404(void *arg0, s32 arg1, s32 arg2) {
    void *temp_lr;

    temp_lr = M2C_FIELD(arg0, void **, 0x440);
    if ((temp_lr != NULL) && (M2C_FIELD(temp_lr, s32 *, 8) != 0)) {
        func_0202f45c(arg0, M2C_FIELD(temp_lr, s16 *, 0) << 0xC, M2C_FIELD(temp_lr, s16 *, 2) << 0xC, M2C_FIELD(temp_lr, s16 *, 4) * M2C_FIELD(temp_lr, s32 *, 0x10), M2C_FIELD(temp_lr, s16 *, 6) * M2C_FIELD(temp_lr, s32 *, 0x14), arg1, arg2);
    }
}
