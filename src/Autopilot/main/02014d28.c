#include <m2c.h>

M2C_UNK sprintf(M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK strcat(M2C_UNK, M2C_UNK *);
M2C_UNK strcpy(s32, M2C_UNK *);
s32 strrchr(M2C_UNK, M2C_UNK);
extern M2C_UNK data_020ef1de;
extern M2C_UNK data_020ef1e6;

void func_02014d18(M2C_UNK arg0, M2C_UNK *arg1, M2C_UNK arg2) {
    s32 temp_r0;

    sprintf(arg2, &data_020ef1de, arg0);
    temp_r0 = strrchr(arg2, 0x2E);
    if (temp_r0 != 0) {
        strcpy(temp_r0 + 1, arg1);
        return;
    }
    strcat(arg2, &data_020ef1e6);
    strcat(arg2, arg1);
}
