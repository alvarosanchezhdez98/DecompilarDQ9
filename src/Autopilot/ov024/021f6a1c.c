#include <m2c.h>

void func_ov024_021f6a4c(void *arg0, void *arg1);

void func_ov024_021f6a1c(void *arg0, void *arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0xC0);
    if (temp_r2 >= 0x10) {
        return;
    }
    func_ov024_021f6a4c((void *) ((temp_r2 * 0xC) + (s32) arg0), arg1);
    M2C_FIELD(arg0, s32 *, 0xC0) = (s32) (M2C_FIELD(arg0, s32 *, 0xC0) + 1);
}
