#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, s32);
M2C_UNK ov00_021EC24C(M2C_UNK, s32);
extern M2C_UNK data_ov031_0224a244;
extern void *data_ov031_0224e69c;

s32 ov00_021EB7CC(void *(*arg0)(M2C_UNK *, s32), s32 arg1) {
    void *temp_r0;

    if (data_ov031_0224e69c != NULL) {
        ov00_021EC24C(9, 0xFFFFA1DC);
        return 0;
    }
    temp_r0 = arg0(&data_ov031_0224a244, 0x1C20);
    data_ov031_0224e69c = temp_r0;
    if (temp_r0 == NULL) {
        ov00_021EC24C(9, 0xFFFFA1DC);
        return 0;
    }
    VectorizedMemset(temp_r0, 0, 0x1C20);
    M2C_FIELD(data_ov031_0224e69c, void *(**)(M2C_UNK *, s32), 0) = arg0;
    M2C_FIELD(data_ov031_0224e69c, s32 *, 4) = arg1;
    return 1;
}
