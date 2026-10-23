#include <m2c.h>

u16 *func_02012fe4();
void *func_0201b600(u16 *, M2C_UNK, M2C_UNK);
s32 func_020ae4c8();
M2C_UNK func_020ae4ec(M2C_UNK, M2C_UNK);

void func_020ae880(s32 arg0) {
    M2C_UNK var_r1;
    u16 *temp_r0;
    u16 temp_r0_2;
    void *temp_r4;
    void *temp_r5;
    void *temp_r6;
    void *temp_r7;

    temp_r0 = func_02012fe4();
    if (*temp_r0 != 0x232F) {
        return;
    }
    temp_r7 = func_0201b600(temp_r0, 0, 5);
    temp_r6 = func_0201b600(temp_r0, 0, 3);
    temp_r5 = func_0201b600(temp_r0, 0, 0xF);
    temp_r4 = func_0201b600(temp_r0, 0, 0x11);
    if ((temp_r7 != NULL) && (temp_r6 != NULL) && (temp_r5 != NULL) && (temp_r4 != NULL)) {
        if (func_020ae4c8() == 0) {
            temp_r0_2 = M2C_FIELD(temp_r6, u16 *, 2);
            if (arg0 == 0) {
                M2C_FIELD(temp_r6, u16 *, 2) = (u16) (temp_r0_2 & ~4);
                M2C_FIELD(temp_r4, u16 *, 2) = (u16) (M2C_FIELD(temp_r4, u16 *, 2) & ~4);
                M2C_FIELD(temp_r5, u16 *, 2) = (u16) (M2C_FIELD(temp_r5, u16 *, 2) | 4);
                M2C_FIELD(temp_r7, u16 *, 2) = (u16) (M2C_FIELD(temp_r7, u16 *, 2) | 4);
            } else {
                M2C_FIELD(temp_r6, u16 *, 2) = (u16) (temp_r0_2 | 4);
                M2C_FIELD(temp_r4, u16 *, 2) = (u16) (M2C_FIELD(temp_r4, u16 *, 2) | 4);
                M2C_FIELD(temp_r5, u16 *, 2) = (u16) (M2C_FIELD(temp_r5, u16 *, 2) & ~4);
                M2C_FIELD(temp_r7, u16 *, 2) = (u16) (M2C_FIELD(temp_r7, u16 *, 2) & ~4);
            }
        }
        if (arg0 != 0) {
            var_r1 = 1;
        } else {
            var_r1 = 0;
        }
        func_020ae4ec(0xC, var_r1);
    }
}
