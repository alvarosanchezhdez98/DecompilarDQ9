#include <m2c.h>

M2C_UNK _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(M2C_UNK, s32, u32, M2C_UNK, s32, s32);
M2C_UNK _Z21FreeVRAMStagingMemoryPKv(s32);
s32 _Z25AllocateVRAMStagingMemoryj(M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0204394c(void *arg0) {
    s32 temp_r0;
    u32 temp_r5;

    temp_r0 = _Z25AllocateVRAMStagingMemoryj(0x3000);
    if (temp_r0 != 0) {
        temp_r5 = (u32) (M2C_FIELD(arg0, s32 *, 0x50) << 0x10) >> 0xD;
        memset(temp_r0, 0, 0x3000);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(1, temp_r0, temp_r5, 0x3000, 1, 0);
        _Z21FreeVRAMStagingMemoryPKv(temp_r0);
    }
}
