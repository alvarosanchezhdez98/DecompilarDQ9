#include <m2c.h>

M2C_UNK func_0203ac10(void *, void *, M2C_UNK);

void func_0209c7fc(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s16 *, 0xCE) < 0) {
        return;
    }
    func_0203ac10(arg0, arg0 + 0xC4, 0);
    M2C_FIELD(arg0, s16 *, 0xCE) = -1;
    M2C_FIELD(arg0, s16 *, 0xCA) = 0;
}
