#include <m2c.h>

M2C_UNK LoadToTexturePalette(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapTexturePalette();
M2C_UNK MemoryUnmapTexturePalette();

void func_020bb9c4(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    MemoryMapTexturePalette();
    LoadToTexturePalette(arg0, arg1, arg2);
    MemoryUnmapTexturePalette();
}
