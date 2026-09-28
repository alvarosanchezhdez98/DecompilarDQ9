// The order of the items (data/.../itemsort), and the sorted lists of the items that the menus show
#include "Scene/Overlay_23/ItemSortList.h"
#include "Resource/Script.h"

extern "C"
{
    // Prepares the table of the items
    void func_020deb08(PartNameTable* items);
    const PartEntry* func_020dedd0(PartNameTable* items, short id);
    // The saved flags, and whether one of them is set
    void* func_0205ec34();
    int func_0206dfb0(void* flags, void* values, int flag);
}

// What the script's commands take: the items to add (all of them without a filter), and the list
struct ItemSortLoading
{
    short filterCount_;
    const short* filter_;
    SafeAllocator* allocator_;
    ItemSortList* list_;
};

static ItemSortLoading sLoading;

// Command 0x66: the count of the items
static int Command_Count(Script::Parameter* params, int)
{
    short capacity = params[0].ToInt();
    if (sLoading.filter_ != NULL && sLoading.filterCount_ != 0)
        sLoading.list_->Create(sLoading.allocator_, sLoading.filterCount_);
    else
        sLoading.list_->Create(sLoading.allocator_, capacity);
    return 1;
}

// Command 0x67: an item, its orders, its category and its kind
static int Command_Item(Script::Parameter* params, int)
{
    short id = params[0].ToInt();
    if (sLoading.filter_ != NULL && sLoading.filterCount_ != 0)
    {
        int found = 0;
        for (short i = 0; i < sLoading.filterCount_; i++)
        {
            if (id == sLoading.filter_[i])
            {
                found = 1;
                break;
            }
        }
        if (!found)
            return 1;
    }
    ItemSortEntry entry;
    entry.Initialize();
    entry.id_ = id;
    entry.order_ = params[1].ToInt();
    entry.order2_ = params[2].ToInt();
    entry.category_ = params[3].ToInt();
    entry.kind_ = params[4].ToInt();
    sLoading.list_->Add(&entry);
    return 1;
}

void ItemSortEntry::Initialize()
{
    next_ = NULL;
    item_ = NULL;
    id_ = -1;
    order_ = 0xffff;
    order2_ = 0xffff;
    listed_ = 0;
    owned_ = 0;
    category_ = 0;
    kind_ = 0;
}

void ItemSortList::Initialize()
{
    first_ = NULL;
    entries_ = NULL;
    count_ = 0;
    capacity_ = 0;
}

void ItemSortList::Finish()
{
    Initialize();
}

static Script::OpcodeLookupEntry sOpcodes[] = {{0x66, Command_Count}, {0x67, Command_Item}, {0, NULL}};

void ItemSortList::Load(SafeAllocator* allocator, const void* file, unsigned int size, const short* filter,
                        short filterCount)
{
    Script script;
    if (file != NULL && size != 0)
    {
        sLoading.list_ = this;
        sLoading.allocator_ = allocator;
        sLoading.filter_ = filter;
        sLoading.filterCount_ = filterCount;
        script.Initialize();
        script.SetOpcodeLookup(sOpcodes);
        script.Load(file, size);
        script.Execute();
    }
}

void ItemSortList::Create(SafeAllocator* allocator, short capacity)
{
    if (allocator != NULL && capacity != 0)
    {
        entries_ = (ItemSortEntry*)allocator->Allocate(capacity * sizeof(ItemSortEntry));
        count_ = 0;
        capacity_ = capacity;
        for (short i = 0; i < capacity_; i++)
            entries_[i].Initialize();
    }
}

void ItemSortList::Add(const ItemSortEntry* entry)
{
    if (capacity_ <= count_)
        return;
    ItemSortEntry* copy = &entries_[count_];
    copy->next_ = entry->next_;
    copy->item_ = entry->item_;
    copy->id_ = entry->id_;
    copy->order_ = entry->order_;
    copy->order2_ = entry->order2_;
    copy->flags_ = entry->flags_;
    copy->kind_ = entry->kind_;
    count_++;
}

void ItemSortList::SetItems(PartNameTable* items)
{
    ItemSortEntry* entry;
    ItemSortEntry* entries;
    short count;
    short i;
    if (items == NULL)
        return;
    func_020deb08(items);
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        const PartEntry* item = func_020dedd0(items, entry->id_);
        entry->item_ = item;
        if (item != NULL)
        {
            int flag = (unsigned short)item->flag_;
            if (flag > 0)
            {
                void* flags = func_0205ec34();
                if (func_0206dfb0(flags, (char*)flags + 0x8c, flag + 0xc76))
                    entry->owned_ = 1;
            }
        }
    }
    first_ = NULL;
}

void ItemSortList::Reset()
{
    ItemSortEntry* entries = entries_;
    short count = count_;
    for (short i = 0; i < count; i++)
    {
        ItemSortEntry* entry = &entries[i];
        entry->next_ = NULL;
        entry->listed_ = 0;
    }
    first_ = NULL;
}

void ItemSortList::Sort(int all, int category, int kind)
{
    ItemSortEntry* entry = FindNext(all, category, kind);
    if (entry == NULL)
        return;
    first_ = entry;
    while (entry != NULL)
    {
        ItemSortEntry* next = FindNext(all, category, kind);
        entry->next_ = next;
        entry = next;
    }
}

void ItemSortList::Sort2(int all, int category, int kind)
{
    ItemSortEntry* entry = FindNext2(all, category, kind);
    if (entry == NULL)
        return;
    first_ = entry;
    while (entry != NULL)
    {
        ItemSortEntry* next = FindNext2(all, category, kind);
        entry->next_ = next;
        entry = next;
    }
}

ItemSortEntry* ItemSortList::FindNext(int all, int category, int kind)
{
    unsigned int lowest;
    ItemSortEntry* entry;
    ItemSortEntry* found;
    ItemSortEntry* entries;
    short count;
    short i;
    found = NULL;
    lowest = 0xffff;
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        if (entry->listed_)
            continue;
        unsigned short order = entry->order_;
        if (lowest < order)
            continue;
        if (!entry->owned_)
            continue;
        if (all == 0)
        {
            int equipment;
            if (entry->category_ <= 7)
                equipment = 1;
            else
                equipment = 0;
            if (!equipment)
                continue;
        }
        else if (category >= 0 && kind >= 0)
        {
            if (entry->kind_ != kind)
                continue;
            if (category != entry->category_)
                continue;
        }
        else if (category >= 0)
        {
            if (category != entry->category_)
                continue;
        }
        else if (kind >= 0 && entry->kind_ != kind)
        {
            continue;
        }
        lowest = order;
        found = entry;
    }
    if (found != NULL)
        found->listed_ = 1;
    return found;
}

ItemSortEntry* ItemSortList::FindNext2(int all, int category, int kind)
{
    unsigned int lowest;
    ItemSortEntry* entry;
    ItemSortEntry* found;
    ItemSortEntry* entries;
    short count;
    short i;
    found = NULL;
    lowest = 0xffff;
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        if (entry->listed_)
            continue;
        unsigned short order = entry->order2_;
        if (lowest < order)
            continue;
        if (!entry->owned_)
            continue;
        if (all == 0)
        {
            int equipment;
            if (entry->category_ <= 7)
                equipment = 1;
            else
                equipment = 0;
            if (!equipment)
                continue;
        }
        else if (category >= 0 && kind >= 0)
        {
            if (entry->kind_ != kind)
                continue;
            if (category != entry->category_)
                continue;
        }
        else if (category >= 0)
        {
            if (category != entry->category_)
                continue;
        }
        else if (kind >= 0 && entry->kind_ != kind)
        {
            continue;
        }
        lowest = order;
        found = entry;
    }
    if (found != NULL)
        found->listed_ = 1;
    return found;
}

void ItemSortList::SortTools(int all, int category, int kind, int owned)
{
    ItemSortEntry* entry = FindNextTool(all, category, kind, owned);
    if (entry == NULL)
        return;
    first_ = entry;
    while (entry != NULL)
    {
        ItemSortEntry* next = FindNextTool(all, category, kind, owned);
        entry->next_ = next;
        entry = next;
    }
}

void ItemSortList::SortTools2(int all, int category, int kind, int owned)
{
    ItemSortEntry* entry = FindNextTool2(all, category, kind, owned);
    if (entry == NULL)
        return;
    first_ = entry;
    while (entry != NULL)
    {
        ItemSortEntry* next = FindNextTool2(all, category, kind, owned);
        entry->next_ = next;
        entry = next;
    }
}

ItemSortEntry* ItemSortList::FindNextTool(int all, int category, int kind, int owned)
{
    unsigned int lowest;
    ItemSortEntry* entry;
    ItemSortEntry* found;
    ItemSortEntry* entries;
    short count;
    short i;
    int tool;
    unsigned short order;
    found = NULL;
    lowest = 0xffff;
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        if (entry->listed_)
            continue;
        order = entry->order_;
        if (lowest < order)
            continue;
        if (owned && !entry->owned_)
            continue;
        if (all == 0)
        {
            tool = 0;
            if (entry->category_ >= 8 && entry->category_ <= 9)
                tool = 1;
            if (!tool)
                continue;
        }
        else if (category >= 0 && kind >= 0)
        {
            if (entry->kind_ != kind)
                continue;
            if (category != entry->category_)
                continue;
        }
        else if (category >= 0)
        {
            if (category != entry->category_)
                continue;
        }
        else if (kind >= 0 && entry->kind_ != kind)
        {
            continue;
        }
        lowest = order;
        found = entry;
    }
    if (found != NULL)
        found->listed_ = 1;
    return found;
}

ItemSortEntry* ItemSortList::FindNextTool2(int all, int category, int kind, int owned)
{
    unsigned int lowest;
    ItemSortEntry* entry;
    ItemSortEntry* found;
    ItemSortEntry* entries;
    short count;
    short i;
    int tool;
    unsigned short order;
    found = NULL;
    lowest = 0xffff;
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        if (entry->listed_)
            continue;
        order = entry->order2_;
        if (lowest < order)
            continue;
        if (owned && !entry->owned_)
            continue;
        if (all == 0)
        {
            tool = 0;
            if (entry->category_ >= 8 && entry->category_ <= 9)
                tool = 1;
            if (!tool)
                continue;
        }
        else if (category >= 0 && kind >= 0)
        {
            if (entry->kind_ != kind)
                continue;
            if (category != entry->category_)
                continue;
        }
        else if (category >= 0)
        {
            if (category != entry->category_)
                continue;
        }
        else if (kind >= 0 && entry->kind_ != kind)
        {
            continue;
        }
        lowest = order;
        found = entry;
    }
    if (found != NULL)
        found->listed_ = 1;
    return found;
}

void ItemSortList::SortAll(int all, int category, int kind)
{
    ItemSortEntry* entry = FindNextOfAll(all, category, kind);
    if (entry == NULL)
        return;
    first_ = entry;
    while (entry != NULL)
    {
        ItemSortEntry* next = FindNextOfAll(all, category, kind);
        entry->next_ = next;
        entry = next;
    }
}

void ItemSortList::SortAll2(int all, int category, int kind)
{
    ItemSortEntry* entry = FindNextOfAll2(all, category, kind);
    if (entry == NULL)
        return;
    first_ = entry;
    while (entry != NULL)
    {
        ItemSortEntry* next = FindNextOfAll2(all, category, kind);
        entry->next_ = next;
        entry = next;
    }
}

ItemSortEntry* ItemSortList::FindNextOfAll(int all, int category, int kind)
{
    unsigned int lowest;
    ItemSortEntry* entry;
    ItemSortEntry* found;
    ItemSortEntry* entries;
    short count;
    short i;
    found = NULL;
    lowest = 0xffff;
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        if (entry->listed_)
            continue;
        unsigned short order = entry->order_;
        if (lowest < order)
            continue;
        if (all == 0)
        {
            int equipment;
            if (entry->category_ <= 7)
                equipment = 1;
            else
                equipment = 0;
            if (!equipment)
                continue;
        }
        else if (category >= 0 && kind >= 0)
        {
            if (entry->kind_ != kind)
                continue;
            if (category != entry->category_)
                continue;
        }
        else if (category >= 0)
        {
            if (category != entry->category_)
                continue;
        }
        else if (kind >= 0 && entry->kind_ != kind)
        {
            continue;
        }
        lowest = order;
        found = entry;
    }
    if (found != NULL)
        found->listed_ = 1;
    return found;
}

ItemSortEntry* ItemSortList::FindNextOfAll2(int all, int category, int kind)
{
    unsigned int lowest;
    ItemSortEntry* entry;
    ItemSortEntry* found;
    ItemSortEntry* entries;
    short count;
    short i;
    found = NULL;
    lowest = 0xffff;
    entries = entries_;
    count = count_;
    for (i = 0; i < count; i++)
    {
        entry = &entries[i];
        if (entry->listed_)
            continue;
        unsigned short order = entry->order2_;
        if (lowest < order)
            continue;
        if (all == 0)
        {
            int equipment;
            if (entry->category_ <= 7)
                equipment = 1;
            else
                equipment = 0;
            if (!equipment)
                continue;
        }
        else if (category >= 0 && kind >= 0)
        {
            if (entry->kind_ != kind)
                continue;
            if (category != entry->category_)
                continue;
        }
        else if (category >= 0)
        {
            if (category != entry->category_)
                continue;
        }
        else if (kind >= 0 && entry->kind_ != kind)
        {
            continue;
        }
        lowest = order;
        found = entry;
    }
    if (found != NULL)
        found->listed_ = 1;
    return found;
}

short ItemSortList::IndexOf(int id)
{
    ItemSortEntry* entry = first_;
    if (entry == NULL)
        return -1;
    for (short i = 0; entry != NULL; i++, entry = entry->next_)
    {
        if (entry->id_ == id)
            return i;
    }
    return -1;
}

short ItemSortList::Count(int all, int category, int type)
{
    short count = 0;
    short n = count_;
    switch (all)
    {
    case 0:
        for (short i = 0; i <= 7; i++)
            count += Count(-1, i, -1);
        return count;
    case 1:
    case 2:
    default:
        ItemSortEntry* entries = entries_;
        for (short i = 0; i < n; i++)
        {
            ItemSortEntry* entry = &entries[i];
            const PartEntry* item;
            if (entry->owned_ && (item = entry->item_) != NULL)
            {
                if (category >= 0 && type >= 0)
                {
                    if (category == item->category_ && type == item->type_)
                        count++;
                }
                else if (category >= 0)
                {
                    if (category == item->category_)
                        count++;
                }
                else if (type >= 0 && type == item->type_)
                {
                    count++;
                }
            }
        }
        return count;
    }
}

short ItemSortList::CountTools(int all, int category, int type)
{
    short count = 0;
    short n = count_;
    switch (all)
    {
    case 0:
        for (short i = 8; i <= 9; i++)
            count += CountTools(-1, i, -1);
        return count;
    case 1:
    case 2:
    default:
        ItemSortEntry* entries = entries_;
        for (short i = 0; i < n; i++)
        {
            ItemSortEntry* entry = &entries[i];
            const PartEntry* item;
            if (entry->owned_ && (item = entry->item_) != NULL)
            {
                if (category >= 0 && type >= 0)
                {
                    if (category == item->category_ && type == item->type_)
                        count++;
                }
                else if (category >= 0)
                {
                    if (category == item->category_)
                        count++;
                }
                else if (type >= 0 && type == item->type_)
                {
                    count++;
                }
            }
        }
        return count;
    }
}
