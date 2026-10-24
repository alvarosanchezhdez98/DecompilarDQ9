#include <m2c.h>

M2C_UNK LoadClearDepthBuffer(M2C_UNK, M2C_UNK);
M2C_UNK MemoryMapClearTexture();
M2C_UNK MemoryUnmapClearTexture();

void func_020bba14(M2C_UNK arg0, s32 arg1, M2C_UNK arg2) {
    MemoryMapClearTexture();
    LoadClearDepthBuffer(arg0, arg2);
    MemoryUnmapClearTexture();
}
