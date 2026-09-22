#pragma once

#include <globaldefs.h>

inline unsigned int AlignTo4(unsigned int size)
{
    return (size + 3) & ~3;
}

// An entry of a .nat table, found by its key with a binary search
struct NatEntry
{
    unsigned short key_;
    unsigned short groupIndex_ : 12; // first of this entry's groups
    unsigned short numGroups_ : 4;
};

// A group of an entry, with a run of indices and one pointer
struct NatGroup
{
    unsigned short pointerIndex_;
    unsigned short flag_ : 1;
    unsigned short firstIndex_ : 11;
    unsigned short numIndices_ : 4;
};

// Runtime view of a .nat file, used for text tables such as the bestiary's (e.g. enchab_<LG>.nat).
// The file starts with the first 0xc bytes of this struct, followed by four tables and then the data
// that the pointers table points into:
//   numEntries_ NatEntry, numGroups_ NatGroup, numIndices_ unsigned short (aligned to 4), numPointers_ offsets
struct NatTable
{
    unsigned short numEntries_;
    unsigned short numGroups_;
    unsigned short numIndices_;
    unsigned short numPointers_;
    unsigned int dataSize_ : 31;
    unsigned int relocated_ : 1;
    NatEntry* entries_;
    char* data_;

    // The pointers in a .nat file are offsets into its data until they're relocated
    char* GetDataPointer(char* pointer, char* defaultValue);
    bool ForEach(void (*func)(NatTable* table, NatEntry* entry));
    bool Attach(void* file, bool* alreadyRelocated, void (*func)(NatTable* table, NatEntry* entry));
    NatEntry* BinarySearch(int key, int (*getKey)(NatEntry* entry));
    unsigned int GetTablesSize();
    unsigned short* GetIndices();
    char** GetPointers();
    NatEntry* FindEntry(int key);
    NatGroup* GetGroups(NatEntry* entry);
    NatGroup* GetGroup(int index, NatEntry* entry);
    char** GetGroupPointer(int index, NatEntry* entry);
};

int GetNatEntryKey(NatEntry* entry);
bool RelocateNatPointers(NatTable* table, bool alreadyRelocated);
