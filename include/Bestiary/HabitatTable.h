#pragma once

#include "Bestiary/NatTable.h"
#include "Memory/SafeAllocator.h"

// Where a monster can be encountered, from enchab_<LG>.nat ("encounter habitat").
// Each entry is a monster, and each of its groups is an area: its pointer is the area's name,
// and its indices are the zone IDs that belong to it. The table is loaded in the background,
// keeping only the entry of one monster.
struct HabitatTable : public NatTable
{
    enum State
    {
        State_Idle,
        State_Queue,
        State_Loading,
        State_Build,
    };

    short monsterID_;
    short state_;
    int taskID_;
    SafeAllocator* allocator_;

    void Init();
    bool Load(SafeAllocator* allocator, short monsterID);
    bool Update();
    bool Unload();
    // Builds the table from the loaded file. With a negative monsterID, it copies the whole table.
    bool Build(SafeAllocator* allocator, void* file, unsigned int fileSize, short monsterID);
};
