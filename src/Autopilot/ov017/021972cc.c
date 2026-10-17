#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov017_021972cc(void *arg0) {
    memset(arg0 + 0x44B8, 0, 8);
    M2C_FIELD(arg0, s8 *, 0x44C0) = 0;
}
