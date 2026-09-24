#pragma once

#include "Memory/SafeAllocator.h"

// The character being created, returned by func_02010954
struct CreatedCharacter
{
    char unk_0[0x568];
    short unk_568;
};

// Overlay 9's code, *likely* the character creation (keyboard_cm.bin, str_cm). sizeof == 0xdb8
struct CharacterCreation
{
    char unk_0[0xd88];
    CreatedCharacter* character_;
    char unk_d8c[0xdb8 - 0xd8c];
};

// The only code of overlay 21: a mode of main() with its own main loop, that runs overlay 9's character creation
// until it's done. main() allocates it (sizeof == 0xbc), and calls Initialize(), Run() and Finish().
// While it runs, it's the game's resources (see func_0200fb84), so it starts with the brightness state of
// GameResources, which the brightness functions (Resource/Brightness.h) update
struct CharacterCreationScene
{
    unsigned int brightnessFlags_0;
    unsigned int brightnessFlags_4;
    unsigned int brightnessFlags_8;
    float mainBrightness;
    int mainBrightnessTarget;
    int mainBrightnessTimeRemaining;
    float subBrightness;
    int subBrightnessTarget;
    int subBrightnessTimeRemaining;
    bool mainBrightnessLocked;
    bool subBrightnessLocked;
    bool mainBrightnessDirty;
    bool subBrightnessDirty;
    bool allowBrightnessApply;

    SafeAllocator allocator_;
    CharacterCreation* creation_;
    // What func_0207de48, func_0207df50, func_0207df90 and func_0207dfac take
    char unk_44[0x70];
    CreatedCharacter* character_;
    // Set when the character creation is done
    int done_;

    void Initialize();
    void Finish();
    void Run();
    void Update();
    void Draw();
};
