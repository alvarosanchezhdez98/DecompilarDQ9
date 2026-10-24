#include <m2c.h>

void *func_0201b600(M2C_UNK, M2C_UNK, u16);

s32 func_0201bd74(M2C_UNK arg0, s32 arg1, M2C_UNK arg2) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = func_0201b600(arg0, arg2, arg1);
    if (temp_r0 != NULL) {
        if (!(M2C_FIELD(temp_r0, u16 *, 2) & 4)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
