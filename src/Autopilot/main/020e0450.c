#include <m2c.h>

M2C_UNK func_020dfbd4();
void *func_020e0310(s32, M2C_UNK, M2C_UNK (*)());

s32 func_020e0440(s32 arg0, M2C_UNK arg1) {
    void *temp_r0;

    if (arg0 == 0) {
        return 0;
    }
    temp_r0 = func_020e0310(arg0, arg1, func_020dfbd4);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s32 *, 4);
    }
    return 0;
}
