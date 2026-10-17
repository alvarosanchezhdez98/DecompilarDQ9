#include <m2c.h>

M2C_UNK func_0205a330(s32, s32);
M2C_UNK func_0205a370(s32, M2C_UNK);
void *func_0205a3d0(s32, M2C_UNK);
M2C_UNK func_0205a42c(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0205ae8c(void *);
M2C_UNK func_020e27ec(s32, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov003_0215c464(void *arg0) {
    s32 temp_r0_2;
    s32 temp_r4;
    void *temp_r0;
    void *temp_r0_3;

    if (M2C_FIELD(arg0, u8 *, 0x59F) & 2) {
        temp_r4 = M2C_FIELD(arg0, s32 *, 0xD4);
        if (temp_r4 != 0) {
            func_0205a370(temp_r4, 1);
            temp_r0 = func_0205a3d0(temp_r4, 1);
            if (temp_r0 != NULL) {
                M2C_FIELD(temp_r0, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x15) | 8);
            }
            func_0205a330(temp_r4, M2C_FIELD(arg0, s32 *, 0x574));
            func_020e27ec(temp_r4, 1, 0xD7, 0x96);
            func_0205a42c(temp_r4, 1, 6);
        }
        func_0205ae8c(arg0 + 0x98);
        return;
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 0xD4);
    if (temp_r0_2 == 0) {
        return;
    }
    temp_r0_3 = func_0205a3d0(temp_r0_2, 1);
    if (temp_r0_3 != NULL) {
        M2C_FIELD(temp_r0_3, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0x15) & ~8);
    }
}
