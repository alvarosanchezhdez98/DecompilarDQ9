#include <m2c.h>

M2C_UNK LoadToSubObjExtendedPalette(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapSubObjExtendedPalette();
M2C_UNK MemoryUnmapSubObjExtendedPalette();

void func_020bbbc8(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    MemoryMapSubObjExtendedPalette();
    LoadToSubObjExtendedPalette(arg0, arg1, arg2);
    MemoryUnmapSubObjExtendedPalette();
}
