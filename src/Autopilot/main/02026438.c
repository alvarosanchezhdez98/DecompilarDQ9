#include <m2c.h>

s32 func_020420e8(s32, M2C_UNK);
M2C_UNK strcpy();
extern M2C_UNK data_020ef6bc;

void func_02026428(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        strcpy(arg0 + 0x5B4, &data_020ef6bc);
    } else {
        strcpy(arg0 + 0x5B4);
    }
    M2C_FIELD(arg0, s32 *, 0xBE4) = func_020420e8(arg0 + 0x5B4, 0);
}
