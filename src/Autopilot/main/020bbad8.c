#include <m2c.h>

M2C_UNK LoadToMainObjExtendedPalette(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapMainObjExtendedPalette();
M2C_UNK MemoryUnmapMainObjExtendedPalette();

void func_020bbac8(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    MemoryMapMainObjExtendedPalette();
    LoadToMainObjExtendedPalette(arg0, arg1, arg2);
    MemoryUnmapMainObjExtendedPalette();
}
