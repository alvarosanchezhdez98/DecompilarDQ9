#pragma once

#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"

// An item in the order of the items (0x10 bytes)
struct ItemSortEntry
{
    // The next item in the sorted list
    ItemSortEntry* next_;
    const PartEntry* item_;
    short id_;
    // The two orders that the list sorts by
    unsigned short order_;
    unsigned short order2_;
    union
    {
        struct
        {
            // It's in the sorted list already
            unsigned char listed_ : 1;
            // The player has the item
            unsigned char owned_ : 1;
            unsigned char category_ : 6;
        };
        unsigned char flags_;
    };
    unsigned char kind_;

    void Initialize();
};

// The order of the items, which a script (itemsort) fills, and the lists of items sorted by it that it builds. The
// menus of the items use it: overlay 2's, the equipment's (overlay 5), overlay 4's
struct ItemSortList
{
    ItemSortEntry* first_;
    ItemSortEntry* entries_;
    short count_;
    short capacity_;

    void Initialize();
    void Finish();
    // Runs the script of the order, which adds the items of the filter (all of them without one)
    void Load(SafeAllocator* allocator, const void* file, unsigned int size, const short* filter, short filterCount);
    void Create(SafeAllocator* allocator, short capacity);
    void Add(const ItemSortEntry* entry);
    void SetItems(PartNameTable* items);
    void Reset();
    void Sort(int all, int category, int kind);
    void Sort2(int all, int category, int kind);
    ItemSortEntry* FindNext(int all, int category, int kind);
    ItemSortEntry* FindNext2(int all, int category, int kind);
    void SortTools(int all, int category, int kind, int owned);
    void SortTools2(int all, int category, int kind, int owned);
    ItemSortEntry* FindNextTool(int all, int category, int kind, int owned);
    ItemSortEntry* FindNextTool2(int all, int category, int kind, int owned);
    void SortAll(int all, int category, int kind);
    void SortAll2(int all, int category, int kind);
    ItemSortEntry* FindNextOfAll(int all, int category, int kind);
    ItemSortEntry* FindNextOfAll2(int all, int category, int kind);
    short IndexOf(int id);
    short Count(int all, int category, int type);
    short CountTools(int all, int category, int type);

};
