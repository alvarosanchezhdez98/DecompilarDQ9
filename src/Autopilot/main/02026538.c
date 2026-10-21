#include <m2c.h>

M2C_UNK func_02042764(s8 *, s32, M2C_UNK);
M2C_UNK strcpy(s32, M2C_UNK *);
extern M2C_UNK data_020ef6ca;

void func_02026528(s32 arg0, s8 *arg1) {
    if ((arg1 != NULL) && (*arg1 != 0)) {
        func_02042764(arg1, arg0 + 0x724, 1);
        return;
    }
    strcpy(arg0 + 0x724, &data_020ef6ca);
}
