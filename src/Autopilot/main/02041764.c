#include <m2c.h>

M2C_UNK _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(M2C_UNK, s32, s32, M2C_UNK, s32, s32);

u32 func_02041754(void *arg0) {
    s32 temp_r1;
    s32 var_r0;
    u32 temp_r0;

    var_r0 = M2C_FIELD(arg0, s32 *, 8);
    if (var_r0 >= 0) {
        temp_r0 = (u32) (M2C_FIELD(arg0, u8 *, 0x16) << 0x1F) >> 0x1F;
        if (temp_r0 != 0) {
            temp_r1 = M2C_FIELD(arg0, s32 *, 0);
            if (temp_r1 != 0) {
                _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(1, temp_r1, M2C_FIELD(arg0, s32 *, 4), 0x80, 1, 1);
                var_r0 = M2C_FIELD(arg0, u8 *, 0x16) & ~1;
                M2C_FIELD(arg0, u8 *, 0x16) = (u8) var_r0;
                /* Duplicate return node #6. Try simplifying control flow for better match */
                return (u32) var_r0;
            }
        }
        return temp_r0;
    }
    return (u32) var_r0;
}
