#include "Bestiary/HabitatTable.h"
#include "Filesystem/BackgroundLoader.h"
#include <globaldefs.h>
#include <std_library_functions.h>

// The NatTable functions in this file are probably inline functions from a header, since other modules have their own
// copies of them. They're defined here while the rest of the bestiary isn't decompiled.

extern "C"
{
    // Returns the 'zone struct'
    void* func_02012fe4();
    // Returns true for the zone IDs of grottos
    bool func_0201b588(unsigned short zoneID);
    // Probably returns whether a zone has been visited
    bool func_0201bb78(void* zoneStruct, unsigned short zoneID);
    char* func_0205ec34();
    // Checks a story flag
    bool func_0206dfb0(void*, void*, int flag);
    // Copies a string into memory from the allocator
    char* func_020da150(SafeAllocator* allocator, const char* string);

    // { "enchab_<LG>.nat", "data/prm/enchab.gp2" }
    extern const char* data_ov014_021897c4[2];
}

int GetNatEntryKey(NatEntry* entry)
{
    return entry->key_;
}

bool RelocateNatPointers(NatTable* table, bool alreadyRelocated)
{
    if (table == NULL || alreadyRelocated)
        return false;

    NatEntry* entries = table->entries_;
    unsigned short* indicesEnd = (unsigned short*)((NatGroup*)(entries + table->numEntries_) + table->numGroups_) + table->numIndices_;
    char** pointers = (char**)((char*)entries + (((char*)indicesEnd - (char*)entries + 3) & ~3));
    int numPointers = table->numPointers_;
    for (int i = 0; i < numPointers; i++, pointers++)
    {
        *pointers = table->GetDataPointer(*pointers, NULL);
    }
    return true;
}

char* NatTable::GetDataPointer(char* pointer, char* defaultValue)
{
    bool invalid = true;
    int offset = pointer - (char*)NULL;
    if (offset != -1 && data_ != NULL)
        invalid = false;
    if (!invalid)
        defaultValue = data_ + offset;
    return defaultValue;
}

void HabitatTable::Init()
{
    memset(this, 0, sizeof(NatTable));
    monsterID_ = -1;
    taskID_ = -1;
    Unload();
}

bool HabitatTable::Load(SafeAllocator* allocator, short monsterID)
{
    Unload();
    Init();
    monsterID_ = monsterID;
    allocator_ = allocator;
    state_ = State_Queue;
    return Update();
}

bool HabitatTable::Update()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    switch (state_)
    {
    case State_Queue:
        taskID_ = loader->QueueLoadFileInGP2(data_ov014_021897c4[1], data_ov014_021897c4[0], NULL);
        state_ = State_Loading;
        return Update();
    case State_Loading:
        if (loader->GetTaskStatus(taskID_) == 0)
            return false;
        state_ = State_Build;
        return Update();
    case State_Build:
    {
        void* file = NULL;
        unsigned int fileSize = 0;
        loader->GetLoadedFileByID(taskID_, &file, &fileSize);
        Build(allocator_, file, fileSize, monsterID_);
        Unload();
        return true;
    }
    }
    return true;
}

bool HabitatTable::Unload()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (taskID_ >= 0)
    {
        loader->RemoveTask(taskID_);
        taskID_ = -1;
    }
    state_ = State_Idle;
    allocator_ = NULL;
    return true;
}

bool HabitatTable::Build(SafeAllocator* allocator, void* file, unsigned int fileSize, short monsterID)
{
    if (allocator == NULL || file == NULL || fileSize == 0)
        return false;

    if (monsterID < 0)
    {
        if (allocator != NULL && file != NULL)
        {
            memcpy(this, file, 0xc);
            unsigned int tablesSize = GetTablesSize();
            unsigned int dataSize = dataSize_;
            entries_ = tablesSize != 0 ? (NatEntry*)allocator->Allocate(tablesSize) : NULL;
            data_ = dataSize != 0 ? (char*)allocator->Allocate(dataSize) : NULL;
            if (entries_ != NULL)
                memcpy(entries_, (char*)file + 0xc, tablesSize);
            if (data_ != NULL)
                memcpy(data_, (char*)file + (GetTablesSize() + 0xc), dataSize);
            relocated_ = true;
        }
        RelocateNatPointers(this, false);
    }
    else
    {
        NatTable source;
        memset(&source, 0, sizeof(source));
        bool alreadyRelocated;
        source.Attach(file, &alreadyRelocated, NULL);
        NatEntry* entry = source.BinarySearch(monsterID, GetNatEntryKey);
        if (entry != NULL)
        {
            char* flags = func_0205ec34();
            bool grottosKnown = func_0206dfb0(flags, flags + 0x8c, 0x79d) != false;
            void* zoneStruct = func_02012fe4();

            NatGroup* groups = (NatGroup*)(source.entries_ + source.numEntries_);
            NatGroup* entryGroups = groups + entry->groupIndex_;
            unsigned short* indices = (unsigned short*)(groups + source.numGroups_);
            char** pointers = (char**)((char*)source.entries_ + (((char*)(indices + source.numIndices_) - (char*)source.entries_ + 3) & ~3));
            int numGroups = entry->numGroups_;
            int numIndices = 0;
            NatGroup* entryGroup = entryGroups;
            for (int i = 0; i < numGroups; i++, entryGroup++)
                numIndices += entryGroup->numIndices_;

            NatTable table;
            table.numEntries_ = 1;
            table.numGroups_ = numGroups;
            table.numIndices_ = numIndices;
            table.numPointers_ = numGroups;
            table.dataSize_ = 0;
            char* buffer = (char*)allocator->Allocate(table.GetTablesSize());
            table.entries_ = (NatEntry*)buffer;
            table.data_ = NULL;
            if (buffer != NULL)
            {
                NatGroup* newGroups = (NatGroup*)(buffer + sizeof(NatEntry));
                unsigned short* newIndices = (unsigned short*)(newGroups + numGroups);
                char** newPointers = (char**)(buffer + (((char*)(newIndices + numIndices) - buffer + 3) & ~3));
                memcpy(buffer, entry, sizeof(NatEntry));
                memcpy(newGroups, entryGroups, numGroups * sizeof(NatGroup));
                NatGroup* group = newGroups;
                ((NatEntry*)buffer)->groupIndex_ = 0;

                int indexTotal = 0;
                int pointerIndex = 0;
                for (int i = 0; i < numGroups; i++)
                {
                    int count = group->numIndices_;
                    memcpy(newIndices, indices + group->firstIndex_, count * sizeof(unsigned short));
                    memcpy(newPointers, pointers + group->pointerIndex_, sizeof(char*));
                    group->pointerIndex_ = pointerIndex;
                    group->firstIndex_ = indexTotal;
                    *newPointers = func_020da150(allocator, source.GetDataPointer(*newPointers, NULL));

                    bool known = count == 0;
                    unsigned short* zoneID = newIndices;
                    for (int j = 0; j < count; j++, zoneID++)
                    {
                        known = (func_0201b588(*zoneID) && grottosKnown) || func_0201bb78(zoneStruct, *zoneID);
                        if (known)
                            break;
                    }
                    group->flag_ = known;

                    newIndices += count;
                    newPointers++;
                    indexTotal += count;
                    group++;
                    pointerIndex++;
                }

                // Sort the areas that the player knows first
                bool swapped;
                do
                {
                    swapped = false;
                    group = newGroups;
                    for (int i = 0; i < numGroups - 1; i++, group++)
                    {
                        if (!group[0].flag_ && group[1].flag_)
                        {
                            NatGroup temp;
                            memcpy(&temp, &group[0], sizeof(NatGroup));
                            memcpy(&group[0], &group[1], sizeof(NatGroup));
                            memcpy(&group[1], &temp, sizeof(NatGroup));
                            swapped = true;
                        }
                    }
                } while (swapped);
            }
            else
            {
                table.numEntries_ = 0;
                table.numGroups_ = 0;
                table.numIndices_ = 0;
                table.numPointers_ = 0;
            }
            memcpy(this, &table, sizeof(NatTable));
        }
    }
    return true;
}

bool NatTable::ForEach(void (*func)(NatTable* table, NatEntry* entry))
{
    int count;
    NatEntry* entry = entries_;
    if (entry == NULL || (count = numEntries_) == 0 || func == NULL)
        return false;
    for (int i = 0; i < count; i++, entry++)
        func(this, entry);
    return true;
}

bool NatTable::Attach(void* file, bool* alreadyRelocated, void (*func)(NatTable* table, NatEntry* entry))
{
    *alreadyRelocated = false;
    if (file == NULL)
        return false;

    memcpy(this, file, 0xc);
    entries_ = (NatEntry*)((char*)file + 0xc);
    data_ = (char*)file + (GetTablesSize() + 0xc);
    if (relocated_)
    {
        *alreadyRelocated = true;
        return true;
    }
    ForEach(func);
    relocated_ = true;
    ((NatTable*)file)->relocated_ = true;
    return true;
}

NatEntry* NatTable::BinarySearch(int key, int (*getKey)(NatEntry* entry))
{
    NatEntry* entries = entries_;
    if (entries == NULL || getKey == NULL)
        return NULL;
    if (numEntries_ == 0)
        return NULL;

    int low = 0;
    int high = numEntries_ - 1;
    while (low <= high)
    {
        int middle = low + ((high - low + 1) >> 1);
        NatEntry* entry = &entries[middle];
        int entryKey = getKey(entry);
        if (entryKey == key)
            return entry;
        if (entryKey > key)
            high = middle - 1;
        else
            low = middle + 1;
    }
    return NULL;
}

unsigned int NatTable::GetTablesSize()
{
    unsigned int entriesSize = numEntries_ * sizeof(NatEntry);
    unsigned int size = numGroups_ * sizeof(NatGroup) + numIndices_ * sizeof(unsigned short) + entriesSize;
    return AlignTo4(size) - entriesSize + numPointers_ * sizeof(char*) + entriesSize;
}

unsigned short* NatTable::GetIndices()
{
    return (unsigned short*)((NatGroup*)(entries_ + numEntries_) + numGroups_);
}

char** NatTable::GetPointers()
{
    NatEntry* entries = entries_;
    unsigned short* indicesEnd = GetIndices() + numIndices_;
    return (char**)((char*)entries + (((char*)indicesEnd - (char*)entries + 3) & ~3));
}

NatEntry* NatTable::FindEntry(int key)
{
    if (key < 0)
        return entries_;
    return BinarySearch(key, GetNatEntryKey);
}

NatGroup* NatTable::GetGroups(NatEntry* entry)
{
    if (entry == NULL)
        return NULL;
    return (NatGroup*)(entries_ + numEntries_) + entry->groupIndex_;
}

NatGroup* NatTable::GetGroup(int index, NatEntry* entry)
{
    if (entry == NULL)
        return NULL;
    return GetGroups(entry) + index;
}

char** NatTable::GetGroupPointer(int index, NatEntry* entry)
{
    if (entry == NULL)
        return NULL;
    NatGroup* group = GetGroup(index, entry);
    if (group == NULL)
        return NULL;
    return GetPointers() + group->pointerIndex_;
}
