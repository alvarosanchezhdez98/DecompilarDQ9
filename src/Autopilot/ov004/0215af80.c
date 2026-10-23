#include <m2c.h>

void **func_ov004_02156f38(M2C_UNK, s32);
extern M2C_UNK data_ov004_021707d8;

s32 func_ov004_0215af80(M2C_UNK arg0) {
    void **temp_r0;
    void **temp_r0_2;

    temp_r0 = func_ov004_02156f38(arg0, 0x25A);
    if (temp_r0 != NULL) {
        M2C_FIELD(*temp_r0, M2C_UNK (**)(void **, u8), 0xE0)(temp_r0, M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x6E));
    }
    temp_r0_2 = func_ov004_02156f38(arg0, 0x2BD);
    if (temp_r0_2 != NULL) {
        M2C_FIELD(*temp_r0_2, M2C_UNK (**)(void **, s32), 0xE0)(temp_r0_2, M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), s32 *, 0x78));
    }
    return 0;
}
