#include <m2c.h>
#pragma optimization_level 4

M2C_UNK VectorizedInvertedMemcpy(M2C_UNK *, s32, M2C_UNK);
M2C_UNK _ZN19TreasureMapMetadata10SetMapTypeE16eTreasureMapType(M2C_UNK *, M2C_UNK);

void func_02011a40(s32 arg0) {
    M2C_UNK sp0[7];

    _ZN19TreasureMapMetadata10SetMapTypeE16eTreasureMapType(sp0, 0);
    VectorizedInvertedMemcpy(sp0, arg0 + 0x6482, 0x1C);
}
