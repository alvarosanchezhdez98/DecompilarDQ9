#include <m2c.h>

M2C_UNK strcpy(M2C_UNK, M2C_UNK *);
s32 strlen(M2C_UNK *);
s32 strstr(M2C_UNK, M2C_UNK *);
extern M2C_UNK data_ov025_021ef778;
extern M2C_UNK data_ov025_021ef781;
extern M2C_UNK data_ov025_021ef78a;
extern M2C_UNK data_ov025_021ef791;
extern M2C_UNK data_ov025_021ef7ac;
extern M2C_UNK data_ov025_021ef7b5;
extern M2C_UNK data_ov025_021ef7be;

s32 func_ov025_021e24d0(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = strstr(arg0, &data_ov025_021ef778);
    if (temp_r0 == 0) {
        strstr(arg0, &data_ov025_021ef781);
    }
    if (temp_r0 != 0) {
        strcpy(arg2, temp_r0 + strlen(&data_ov025_021ef78a));
        strcpy(arg1, &data_ov025_021ef791);
        return 1;
    }
    temp_r0_2 = strstr(arg0, &data_ov025_021ef7ac);
    if (temp_r0_2 == 0) {
        strstr(arg0, &data_ov025_021ef7b5);
    }
    if (temp_r0_2 == 0) {
        return 0;
    }
    strcpy(arg2, temp_r0_2 + strlen(&data_ov025_021ef78a));
    strcpy(arg1, &data_ov025_021ef7be);
    return 1;
}
