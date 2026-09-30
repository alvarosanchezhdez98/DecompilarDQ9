#pragma once

#include "Memory/SafeAllocator.h"

// An entry of ExperienceTable: the multiplier up to an experience
struct ExperienceEntry
{
    unsigned int limit_ : 26;
    unsigned int multiplier_ : 6;
};

// The multipliers of the experience by level (data/bin/expadj.nat), 0x18 bytes
struct ExperienceTable
{
    unsigned int count_ : 12;
    unsigned int size_ : 19;
    unsigned int loaded_ : 1;
    ExperienceEntry* entries_;
    void* unk_8;
    // 0: nothing, 1: load, 2: loading, 3: loaded
    short step_;
    char unk_e[2];
    int task_;
    SafeAllocator* allocator_;

    static const char* sFile;

    void Initialize();
    void Finish();
    void Load(SafeAllocator* allocator);
    int Update();
    int CancelTask();
    int Parse(SafeAllocator* allocator, void* file, unsigned int size);
    unsigned int GetEntriesSize();
    ExperienceEntry* FindEntry(int value);
    unsigned int GetMultiplier(int value, unsigned int multiplier);
};
