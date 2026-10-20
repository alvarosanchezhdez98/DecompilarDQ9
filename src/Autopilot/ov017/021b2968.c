#include <m2c.h>

M2C_UNK _Z13SetBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z17SetMainBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(M2C_UNK, s32, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
M2C_UNK func_020397c0();
s32 func_020429d4();
s32 func_02046708(s32, M2C_UNK);
s32 func_020d6c00();
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
s32 func_ov017_0218b5b0();

s32 func_ov017_021b2968(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;

    temp_r5 = func_ov017_0218b5b0();
    if (((u32) (M2C_FIELD(arg0, s32 *, 0x38) << 0x1C) >> 0x1F) != 0) {
        temp_r0 = func_020429d4();
        memset(temp_r0, 0, 0x800);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(5, temp_r0, 0, 0x800, 1, 0);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(7, temp_r0, 0, 0x800, 1, 0);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(9, temp_r0, 0, 0x800, 1, 0);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(6, temp_r0, 0, 0x20, 1, 0);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(8, temp_r0, 0, 0x20, 1, 0);
        _Z17StageMemoryToVRAM13VRAMSubregionPKvjjbb(0xA, temp_r0, 0, 0x20, 1, 0);
        temp_r0_2 = func_020d6c00();
        if ((func_02046708(temp_r0_2, 1) == 0) && (func_02046708(temp_r0_2, 0x40) == 0)) {
            _Z17SetMainBrightnessP13GameResourcesii(temp_r5, 0, 0x28);
        } else {
            _Z13SetBrightnessP13GameResourcesii(temp_r5, 0, 0x28);
        }
    }
    _ZN9GameState11GetInstanceEv();
    if (_ZN9GameState20GetUnknownGameObjectEv() != 0) {
        func_020397c0();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    return 8;
}
