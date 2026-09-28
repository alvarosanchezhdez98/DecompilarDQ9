#pragma once

// A saved state of the VRAM's managers, which func_0207de48 initializes, func_0207df50 saves and func_0207dfc8 copies
// (*likely* NitroSystem's texture and palette VRAM managers, which it calls)
struct VRAMManagerState
{
    char unk_0[0x68];
    // Its low 16 bits are the palettes' offset in VRAM, divided by 8 (overlay 23's CharacterModel writes the colors
    // there)
    unsigned int unk_68;
    char unk_6c[4];
};
