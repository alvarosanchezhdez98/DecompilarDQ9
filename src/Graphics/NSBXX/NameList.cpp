#include "Graphics/NSBXX/NSBXX.h"

#pragma optimize_for_size off
// This NitroSystem file was compiled with -O4, unlike the game's -O2: at -O2, the loops aren't strength-reduced and are
// compiled with their condition at the bottom instead of a check before a do-while loop
#pragma optimization_level 4

// Names are 16-byte arrays, compared as four 32-bit integers.
// The name lists are const, like in NitroSystem: otherwise, the tree searches load the number of entries again instead
// of reusing the first load.
static inline const uint32_t* GetNameByIndex(const NSBXXNameList* nameList, unsigned int index)
{
    if (nameList != NULL && index < nameList->numEntries_)
    {
        const uint16_t* dataStart = (const uint16_t*)((const uint8_t*)nameList + nameList->offsetToDataStart_);
        // dataStart[1] is the distance between dataStart and the names
        return (const uint32_t*)((const uint8_t*)dataStart + dataStart[1] + 16 * index);
    }
    return NULL;
}

static inline void* GetDataByIndex(const NSBXXNameList* nameList, unsigned int index)
{
    if (nameList != NULL && index < nameList->numEntries_)
    {
        const uint16_t* dataStart = (const uint16_t*)((const uint8_t*)nameList + nameList->offsetToDataStart_);
        // dataStart[0] is the size of an entry, and the entries follow the 4-byte header
        return (void*)((const uint8_t*)dataStart + 4 + dataStart[0] * index);
    }
    return NULL;
}

extern "C" void* NSBXXNameList_Search(const NSBXXNameList* nameList, const char* nameChars)
{
    const uint32_t* name = (const uint32_t*)nameChars;
    if (name == NULL)
        return NULL;

    if (nameList->numEntries_ < 16) // list is short, do linear search
    {
        unsigned int index;
        const uint32_t* source;
        uint32_t target0 = name[0];
        uint32_t target1 = name[1];
        uint32_t target2 = name[2];
        uint32_t target3 = name[3];

        for (index = 0; index < nameList->numEntries_; ++index)
        {
            source = GetNameByIndex(nameList, index);
            if (source[0] == target0 && source[1] == target1 && source[2] == target2 && source[3] == target3)
                return GetDataByIndex(nameList, index);
        }
    }
    else // list is long, use the binary search tree
    {
        const uint32_t* source;
        const NSBXXNameList::SearchTreeEntry* entryArray;
        const NSBXXNameList::SearchTreeEntry *parent, *cursor;

        entryArray = &nameList->treeRoot_8_;
        parent = entryArray;

        if (parent->children_[0] != 0)
        {
            // Go down the tree until reaching a bit index that isn't lower than the parent's
            cursor = entryArray + parent->children_[0];
            while (parent->bitIndex_ > cursor->bitIndex_)
            {
                parent = cursor;
                cursor = entryArray + cursor->children_[(name[cursor->bitIndex_ >> 5] >> (cursor->bitIndex_ & 0x1f)) & 1];
            }

            source = GetNameByIndex(nameList, cursor->resourceIndex_);
            if (source[0] == name[0] && source[1] == name[1] && source[2] == name[2] && source[3] == name[3])
                return GetDataByIndex(nameList, cursor->resourceIndex_);
        }
    }

    return NULL;
}

extern "C" int NSBXXNameList_SearchIndex(const NSBXXNameList* nameList, const char* nameChars)
{
    const uint32_t* name = (const uint32_t*)nameChars;
    if (name == NULL)
        return -1;

    if (nameList->numEntries_ < 16) // list is short, do linear search
    {
        unsigned int index;
        const uint32_t* source;
        uint32_t target0 = name[0];
        uint32_t target1 = name[1];
        uint32_t target2 = name[2];
        uint32_t target3 = name[3];

        for (index = 0; index < nameList->numEntries_; ++index)
        {
            source = GetNameByIndex(nameList, index);
            if (source[0] == target0 && source[1] == target1 && source[2] == target2 && source[3] == target3)
                return index;
        }
    }
    else // list is long, use the binary search tree
    {
        const uint32_t* source;
        const NSBXXNameList::SearchTreeEntry* entryArray;
        const NSBXXNameList::SearchTreeEntry *parent, *cursor;

        entryArray = &nameList->treeRoot_8_;
        parent = entryArray;

        if (parent->children_[0] != 0)
        {
            // Go down the tree until reaching a bit index that isn't lower than the parent's
            cursor = entryArray + parent->children_[0];
            while (parent->bitIndex_ > cursor->bitIndex_)
            {
                parent = cursor;
                cursor = entryArray + cursor->children_[(name[cursor->bitIndex_ >> 5] >> (cursor->bitIndex_ & 0x1f)) & 1];
            }

            source = GetNameByIndex(nameList, cursor->resourceIndex_);
            if (source[0] == name[0] && source[1] == name[1] && source[2] == name[2] && source[3] == name[3])
                return cursor->resourceIndex_;
        }
    }

    return -1;
}
