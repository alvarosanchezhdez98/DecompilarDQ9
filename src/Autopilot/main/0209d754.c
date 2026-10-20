#include <m2c.h>

s32 func_ov017_021d60f4(M2C_UNK);
void *func_0209dccc();

s32 func_0209d744(M2C_UNK arg0) {
    void *temp_r0;

    temp_r0 = func_0209dccc();
    if (temp_r0 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r0, s32 *, 0x6C) = func_ov017_021d60f4(arg0);
    return 1;
}
