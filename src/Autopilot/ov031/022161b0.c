#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, void *);
M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
extern void *data_ov031_0224e5d8;

s32 ov00_021FDB9C(s32 arg0, void *arg1) {
    if (M2C_FIELD(data_ov031_0224e5d8, s32 *, 0x1A90) != 2) {
        return -1;
    }
    if ((arg0 < 0) || (arg0 >= (s32) M2C_FIELD(data_ov031_0224e5d8, s32 *, 0x1A88))) {
        return -1;
    }
    VectorizedMemset(arg1, 0, 0x78);
    M2C_FIELD(arg1, s32 *, 0) = 1;
    M2C_FIELD(arg1, u16 *, 4) = (u16) M2C_FIELD((data_ov031_0224e5d8 + (arg0 * 2)), u16 *, 0x1A48);
    VectorizedInvertedMemcpy((arg0 * 0x70) + (s32) (data_ov031_0224e5d8 + 0x1348), arg1 + 6);
    return 0;
}
