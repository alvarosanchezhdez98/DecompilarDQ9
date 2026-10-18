#include <m2c.h>

M2C_UNK func_020bdb0c(s32, s32);

void func_0203aa44(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_r0 == 0) {
        return;
    }
    func_020bdb0c(temp_r0, M2C_FIELD(arg0, s32 *, 0xA0));
}
