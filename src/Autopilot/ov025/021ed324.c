#include <m2c.h>

M2C_UNK strcpy(void *);

void func_ov025_021ed324(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        M2C_FIELD(arg0, s8 *, 0x16C) = 0;
        return;
    }
    strcpy(arg0 + 0x16C);
}
