#include <m2c.h>

M2C_UNK VectorizedMemset(M2C_UNK, M2C_UNK, M2C_UNK);
s32 _ZN13HPXEAllocator16CreateAtLocationEPvjt(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020c9be0();
extern s32 data_ov031_02290d3c;

void ov13_022411DC(M2C_UNK arg0) {
    s32 temp_r0;

    VectorizedMemset(arg0, 0, 0x40000);
    temp_r0 = _ZN13HPXEAllocator16CreateAtLocationEPvjt(arg0, 0x40000, 0);
    data_ov031_02290d3c = temp_r0;
    if (temp_r0 != 0) {
        return;
    }
    func_020c9be0();
}
