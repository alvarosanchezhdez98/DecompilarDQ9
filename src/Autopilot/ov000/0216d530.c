#include <m2c.h>

M2C_UNK func_0202ecec();
M2C_UNK func_ov000_0216d370(void *, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov000_0216d530(void *arg0, s32 arg1) {
    if (arg1 < 0) {
        func_ov000_0216d370(arg0, 1, 1, 1);
    } else {
        func_0202ecec();
    }
    M2C_FIELD(arg0, s32 *, 0x224) = arg1;
}
