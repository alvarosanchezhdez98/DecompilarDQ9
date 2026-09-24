#pragma once

#include "Memory/SafeAllocator.h"

// A list of texts loaded from a .bin file of a .gp2 archive, found by their IDs. sizeof == 8
struct TextList
{
    void* entries_;
    short count_;
    short unk_6;
};

// The only code of overlay 10, named after its files: str_pit.gp2 (its texts) and ana.chr ("ana" is a hole in
// Japanese). It shows a message about a party member chosen from a menu and, if the zone allows it, creates a hole
// effect at their position and calls func_ov017_021d360c with the zone and that position. What it is in the game
// isn't known yet. Overlay 17 allocates it (sizeof == 0x28) and calls Update() every frame until it returns true.
struct PitEvent
{
    enum State
    {
        State_LoadTexts,
        State_ShowMessage,
        State_WaitForAnswer,
        State_WaitForEnd,
        State_LoadEffect,
        State_CreateEffect,
    };

    unsigned char state_;
    // Whether the hole effect is created
    bool createEffect_;
    // Frames waited after the effect was loaded
    unsigned short ticks_;
    int taskID_;
    // The game object of the effect
    int effectIndex_;
    // str_pit_<LG>.bin
    TextList texts_;
    SafeAllocator allocator_;

    void Initialize();
    void Finish();
    bool Update();
};
