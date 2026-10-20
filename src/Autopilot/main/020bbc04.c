#include <m2c.h>

M2C_UNK LoadToSubBGExtendedPalette(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapSubBGExtendedPalette();
M2C_UNK MemoryUnmapSubBGExtendedPalette();

void func_020bbbf4(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    MemoryMapSubBGExtendedPalette();
    LoadToSubBGExtendedPalette(arg0, arg1, arg2);
    MemoryUnmapSubBGExtendedPalette();
}
