#include <m2c.h>

M2C_UNK LoadToTextureImage(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapTextureImage();
M2C_UNK MemoryUnmapTextureImage();

void func_020bb998(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    MemoryMapTextureImage();
    LoadToTextureImage(arg0, arg1, arg2);
    MemoryUnmapTextureImage();
}
