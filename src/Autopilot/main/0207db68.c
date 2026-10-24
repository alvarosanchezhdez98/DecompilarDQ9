#include <m2c.h>

M2C_UNK func_0202ae18();
s32 func_0202c508();
M2C_UNK func_ov017_021c9b90(M2C_UNK, s8);
void *func_0207d9bc();

s8 func_0207db58(s32 arg0, M2C_UNK arg1, s8 arg2) {
    void *temp_r0;

    temp_r0 = func_0207d9bc();
    if (temp_r0 == NULL) {
        return -1;
    }
    if ((s32) M2C_FIELD(temp_r0, s8 *, 4) < 0) {
        M2C_FIELD(temp_r0, s8 *, 4) = arg2;
        func_0202ae18();
        if (func_0202c508() != 0) {
            func_ov017_021c9b90(arg1, M2C_FIELD(temp_r0, s8 *, 4));
        }
    }
    return M2C_FIELD(temp_r0, s8 *, 4);
}
