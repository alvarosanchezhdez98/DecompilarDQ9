#include <m2c.h>

M2C_UNK LoadToMainBGExtendedPalette(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapMainBGExtendedPalette();
M2C_UNK MemoryUnmapMainBGExtendedPalette();

void func_020bbaf4(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    MemoryMapMainBGExtendedPalette();
    LoadToMainBGExtendedPalette(arg0, arg1, arg2);
    MemoryUnmapMainBGExtendedPalette();
}
