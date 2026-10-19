#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
extern s32 data_020fe9a4;

void func_02029060(void) {
    if (data_020fe9a4 == 0) {
        return;
    }
    memset(data_020fe9a4, 0, 0x6000);
}
