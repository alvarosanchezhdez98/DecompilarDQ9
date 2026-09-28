#pragma once

#include "GameState/PartyMemberData.h"
#include "Memory/SafeAllocator.h"
#include "Scene/Overlay_9/CharacterCreation.h"

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
    PartyMemberData* character_;
    // Set when the character creation is done
    int done_;

    void Initialize();
    void Finish();
    void Run();
    void Update();
    void Draw();
};
