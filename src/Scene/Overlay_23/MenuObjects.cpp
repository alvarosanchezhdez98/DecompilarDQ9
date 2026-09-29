// What overlay 23's objects of the menus have in common (see MenuObjects.h): the functions that overlay 4 changes them
// with, their list, and the objects of type 0
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "System/Memory.h"
#include "System/TouchScreen.h"
#include <std_library_functions.h>

extern "C"
{
    extern TouchState data_02114e54;

    void func_02012a84(TouchState* touch, int* x, int* y);
    void func_0204719c(void* model);
    void func_02047230(void* model);
    void func_02047554(void* model, int, int);
    void func_02047b30(void* model, void* file, unsigned int size, SafeAllocator* allocator);
    void* func_020467c0(void* archive, const char* name, unsigned int* size);
    const char* func_02072a68(TextTable* texts, short id);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
}

int GetFileInNarc(const void* archive, const char* name, const void** file, unsigned int* size, unsigned int);

unsigned short GetMenuObject8TextId(MenuScript* script, unsigned short id)
{
    MenuObjectClass8* object = (MenuObjectClass8*)script->GetObjects()->Find(id);
    if (object == NULL)
        return 0;
    if (object->GetType() != 8)
        return 0;
    return object->textId_;
}

const char* GetMenuObject4Text(MenuScript* script, unsigned short id, int text)
{
    MenuObjectClass4* object = (MenuObjectClass4*)script->GetObjects()->Find(id);
    if (object == NULL)
        return 0;
    if (object->GetType() != 4)
        return 0;
    return func_02072a68(object->GetTexts(), text);
}

void SetMenuObject8Text(MenuScript* script, unsigned short id, const char* text, unsigned char color)
{
    MenuObjectClass8* object = (MenuObjectClass8*)script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    if (object->GetType() != 8)
        return;
    object->text_ = text;
    object->Vd8(color);
}

void SetMenuObject8TextId(MenuScript* script, unsigned short id, unsigned short text, unsigned char color)
{
    MenuObjectClass8* object = (MenuObjectClass8*)script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    if (object->GetType() != 8)
        return;
    object->textId_ = text;
    object->Vd8(color);
}

void SetMenuObjectFValue(MenuScript* script, unsigned short id, int value, unsigned char color)
{
    MenuObjectClassF* object = (MenuObjectClassF*)script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    if (object->GetType() != 15)
        return;
    object->SetValue(value);
    object->Vd8(color);
}

MenuObjectClass7* GetMenuObject7(MenuScript* script, unsigned short id)
{
    MenuObjectClass7* object = (MenuObjectClass7*)script->GetObjects()->Find(id);
    if (object == NULL)
        return NULL;
    if (object->GetType() != 7)
        object = NULL;
    return object;
}

int GetMenuObject7Selection(MenuScript* script, unsigned short id)
{
    MenuObjectClass7* object = GetMenuObject7(script, id);
    if (object == NULL)
        return -1;
    int unk = object->GetUnk9bc0();
    return object->GetSelection(object->GetUnk9bb0(), unk);
}

MenuObjectClass* GetMenuObject7Selected(MenuScript* script, unsigned short id)
{
    int selection = GetMenuObject7Selection(script, id);
    return script->GetObjects()->Find(selection);
}

void SetMenuObject7Unk5c(MenuScript* script, unsigned short id, short a, short b)
{
    MenuObjectClass7* object = GetMenuObject7(script, id);
    if (object != NULL)
    {
        object->unk_5c = a;
        object->unk_5e = b;
    }
}

void SetMenuObjectFlags(MenuScript* script, unsigned short id, unsigned char flags)
{
    MenuObjectClass* object = script->GetObjects()->Find(id);
    if (object != NULL)
        object->flags_ |= flags;
}

void ClearMenuObjectFlags(MenuScript* script, unsigned short id, unsigned char flags)
{
    MenuObjectClass* object = script->GetObjects()->Find(id);
    if (object != NULL)
        object->flags_ &= ~flags;
}

void SetMenuObject6Pages(MenuScript* script, unsigned short id, short page, short pages)
{
    MenuObjectClass6* object = (MenuObjectClass6*)script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    if (object->GetType() != 6)
        return;
    object->page_ = page;
    object->pages_ = pages;
    object->Refresh(script);
}

void RefreshMenuObject6(MenuScript* script, unsigned short id)
{
    MenuObjectClass6* object = (MenuObjectClass6*)script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    if (object->GetType() != 6)
        return;
    object->Refresh(script);
}

void CallMenuObjectVf0(MenuScript* script, unsigned short id, int value)
{
    MenuObjectClass* object = script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    object->Vf0(value);
}

void CallMenuObjectVf4(MenuScript* script, unsigned short id, int value)
{
    MenuObjectClass* object = script->GetObjects()->Find(id);
    if (object == NULL)
        return;
    object->Vf4(value);
}

void MenuObjectList::Initialize()
{
    first_ = NULL;
    task_ = -1;
    memset(slots_, 0, sizeof(slots_));
    ranges_ = NULL;
    masks_[0] = 0;
    masks_[1] = 1;
    for (int i = 0; i < 3; i++)
        groups_[i].Clear();
}

void MenuObjectGroup::Clear()
{
    VectorizedMemset(this, 0, sizeof(MenuObjectGroup));
    entry_ = -1;
    callback_ = -1;
}

void MenuObjectList::Add(MenuObjectClass* object)
{
    if (object->id_ == 0)
        return;
    MenuObjectClass* last = first_;
    if (last != NULL)
    {
        while (last->next_ != NULL)
            last = last->next_;
        last->next_ = object;
        object->prev_ = last;
        return;
    }
    first_ = object;
}

void MenuObjectList::Remove(MenuObjectClass* object)
{
    if (object == NULL)
        return;
    MenuObjectClass* prev = object->prev_;
    MenuObjectClass* next = object->next_;
    if (prev != NULL)
        prev->next_ = next;
    if (next != NULL)
        next->prev_ = prev;
    if (first_ == object)
        first_ = next;
    object->prev_ = NULL;
    object->next_ = NULL;
    object->Finish(this);
}

void MenuObjectList::RemoveHeap(int heap)
{
    MenuObjectClass* object = first_;
    while (object != NULL)
    {
        MenuObjectClass* next = object->next_;
        if (object->heap_ == heap)
            Remove(object);
        object = next;
    }
}

MenuObjectClass* MenuObjectList::Find(int id)
{
    for (MenuObjectClass* object = first_; object != NULL; object = object->next_)
    {
        if (id == object->GetId())
            return object;
    }
    return NULL;
}

MenuObjectClass* MenuObjectList::GetAt(int index)
{
    MenuObjectClass* object = first_;
    while (object != NULL && index > 0)
    {
        object = object->next_;
        index--;
    }
    return object;
}

void MenuObjectList::Update(MenuScript* script)
{
    MenuObjectClass* object;
    for (object = first_; object != NULL; object = object->next_)
        object->V0c(script);
    for (object = first_; object != NULL; object = object->next_)
        object->Update(script);
    for (object = first_; object != NULL; object = object->next_)
        object->V10(script);
    if (CheckGroups(script))
        return;
    CheckTouch(script);
}

void MenuObjectList::Draw1()
{
    for (MenuObjectClass* object = first_; object != NULL; object = object->next_)
        object->Draw1();
}

void MenuObjectList::Draw2()
{
    for (MenuObjectClass* object = first_; object != NULL; object = object->next_)
        object->Draw2();
}

void MenuObjectList::Draw3()
{
    for (MenuObjectClass* object = first_; object != NULL; object = object->next_)
        object->Draw3();
}

void MenuObjectList::CheckTouch(MenuScript* script)
{
    int x;
    int y;
    if (!data_02114e54.touching_)
        return;
    func_02012a84(&data_02114e54, &x, &y);
    for (MenuObjectClass* object = first_; object != NULL; object = object->next_)
    {
        if (object->IsTouched() && object->GetTouchCallback() > 0)
        {
            script->RunCallback(object->GetTouchCallback());
            return;
        }
    }
}

int MenuObjectList::CheckGroups(MenuScript* script)
{
    if (data_02114e54.touching_)
    {
        for (int i = 0; i < 3; i++)
        {
            MenuObjectGroup* group = &groups_[i];
            if (group->count_ == 0)
                continue;
            int busy = 0;
            for (int j = 0; j < group->count_ && !busy; j++)
            {
                MenuObjectClass* object = Find(group->ids_[j]);
                if (object != NULL && object->ContainsTouch())
                    busy = 1;
            }
            if (busy)
                continue;
            if (group->entry_ > 0)
                script->StartEntry(group->entry_);
            if (group->callback_ > 0)
                script->RunCallback(group->callback_);
            return 1;
        }
    }
    return 0;
}

void MenuObjectList::SetTask(int task)
{
    task_ = task;
}

int MenuObjectList::GetTask()
{
    return task_;
}

int MenuObjectList::IsLoading()
{
    for (MenuObjectClass* object = first_; object != NULL; object = object->next_)
    {
        if (object->state_ != 2)
            return 1;
    }
    return 0;
}

void MenuObjectList::SetSlots(int set, unsigned int start, unsigned int count)
{
    if (start >= 0x80)
        return;
    unsigned int* slots = slots_[set];
    for (unsigned short i = 0; i < count; i++)
    {
        int index = start >> 2;
        int bit = start & 3;
        slots[index] |= 1 << bit;
        start++;
    }
}

void MenuObjectList::ClearSlots(int set, unsigned int start, unsigned int count)
{
    if (start >= 0x80)
        return;
    for (unsigned short i = 0; i < count; i++)
    {
        int index = start >> 2;
        int bit = start & 3;
        slots_[set][index] &= ~(1 << bit);
        start++;
    }
}

int MenuObjectList::FindSlots(int set, unsigned int count)
{
    for (int start = 0; start < 0x80; start++)
    {
        int free = 1;
        unsigned int slot = start;
        for (unsigned short i = 0; i < count; i++)
        {
            int index = slot >> 2;
            int bit = slot & 3;
            if (slots_[set][index] & (1 << bit))
            {
                free = 0;
                break;
            }
            slot++;
        }
        if (free)
            return start;
    }
    return -1;
}

void MenuObjectList::AddRange(MenuObjectRange* range)
{
    if (range == NULL)
        return;
    range->prev_ = NULL;
    range->next_ = NULL;
    MenuObjectRange* other = ranges_;
    if (other == NULL)
    {
        ranges_ = range;
        return;
    }
    while (other != NULL)
    {
        if (range->start_ < other->start_)
        {
            if (other->prev_ != NULL)
                other->prev_->next_ = range;
            range->next_ = other;
            range->prev_ = other->prev_;
            other->prev_ = range;
            if (other == ranges_)
                ranges_ = range;
            return;
        }
        if (other->next_ == NULL)
        {
            other->next_ = range;
            range->prev_ = other;
            return;
        }
        other = other->next_;
    }
}

void MenuObjectList::RemoveRange(MenuObjectRange* range)
{
    if (range == NULL)
        return;
    if (range == ranges_)
        ranges_ = range->next_;
    if (range->prev_ != NULL)
        range->prev_->next_ = range->next_;
    if (range->next_ != NULL)
        range->next_->prev_ = range->prev_;
}

unsigned int MenuObjectList::FindRange(unsigned int size)
{
    MenuObjectRange* range = ranges_;
    while (range != NULL)
    {
        unsigned int end = range->end_;
        range = range->next_;
        unsigned int limit = end + size;
        if (range == NULL)
            return end;
        if (limit <= range->start_)
            return end;
    }
    return 0;
}

void MenuObjectList::SetMask(int set, unsigned int bit)
{
    if (bit >= 16)
        return;
    masks_[set] |= 1 << bit;
}

void MenuObjectList::ClearMask(int set, unsigned int bit)
{
    if (bit >= 16)
        return;
    masks_[set] &= ~(1 << bit);
}

int MenuObjectList::FindMask(int set)
{
    for (int bit = 0; bit < 16; bit++)
    {
        if (!(masks_[set] & (1 << bit)))
            return bit;
    }
    return -1;
}

void MenuObjectList::SetGroup(int index, const MenuObjectGroup* group)
{
    if (index >= 3)
        return;
    VectorizedInvertedMemcpy(group, &groups_[index], sizeof(MenuObjectGroup));
}

void MenuObjectList::ClearGroup(int index)
{
    if (index >= 3)
        return;
    groups_[index].Clear();
}

void MenuObjectClass::Initialize()
{
    type_ = 0xffff;
    id_ = 0;
    heap_ = 0;
    file_ = NULL;
    prev_ = NULL;
    next_ = NULL;
    flags_ = 0;
    state_ = 0;
}

unsigned short MenuObjectClass::GetId()
{
    return id_;
}

unsigned short MenuObjectClass::GetType()
{
    return type_;
}

MenuObjectClass* MenuObjectClass::GetNext()
{
    return next_;
}

int MenuObjectClass0::Initialize(MenuScript* script, int id, int heap, int vramState, const char* file)
{
    MenuObjectClass::Initialize();
    type_ = 0;
    id_ = id;
    heap_ = heap;
    vramState_ = vramState;
    file_ = file;
    func_0204719c(model_);
    Load(script);
    unk_a8 = 0;
    unk_aa = 0;
    return 1;
}

void MenuObjectClass0::Finish(MenuObjectList* list)
{
    func_02047230(model_);
}

void MenuObjectClass0::Update(MenuScript* script)
{
    int (MenuObjectClass0::*states[4])(MenuScript*) = {&MenuObjectClass0::State_Load, &MenuObjectClass0::State_Wait,
                                                         &MenuObjectClass0::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClass0::State_Load(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    if (objects->GetTask() >= 0)
        return state_;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    char path[0x50];
    sprintf(path, "data/%s", file_);
    objects->SetTask(loader->QueueLoadFile(path, NULL));
    return 1;
}

int MenuObjectClass0::State_Wait(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int task = objects->GetTask();
    if (loader->GetTaskStatus(task))
    {
        if (loader->GetDetailedTaskStatus(task) == 2)
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task, &file, &size);
            LoadFile(script, file, size);
        }
        loader->RemoveTask(task);
        objects->SetTask(-1);
        return 2;
    }
    return state_;
}

int MenuObjectClass0::State_Loaded(MenuScript* script)
{
    return state_;
}

void MenuObjectClass0::Draw1()
{
}

void MenuObjectClass0::Draw2()
{
    if (flags_ & 8)
        return;
    func_02047554(model_, 0, 1);
}

void MenuObjectClass0::SetPosition(Vector3fix* position)
{
    position_.x = position->x;
    position_.y = position->y;
    position_.z = position->z;
}

Vector3fix MenuObjectClass0::GetPosition()
{
    return position_;
}

void MenuObjectClass0::V3c(short value)
{
    unk_a8 = value;
}

unsigned short MenuObjectClass0::V40()
{
    return unk_a8;
}

void MenuObjectClass0::V44(short value)
{
    unk_aa = value;
}

unsigned short MenuObjectClass0::V48()
{
    return unk_aa;
}

void MenuObjectClass0::Load(MenuScript* script)
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int task = script->GetLoadTask();
    if (task < 0 || !loader->GetTaskStatus(task) || loader->GetDetailedTaskStatus(task) != 2)
        return;
    void* archive;
    unsigned int archiveSize;
    const void* file;
    unsigned int size;
    loader->GetLoadedFileByID(task, &archive, &archiveSize);
    if (GetFileInNarc(archive, file_, &file, &size, 0))
    {
        LoadFile(script, archive, archiveSize);
        state_ = 2;
        return;
    }
    file = func_020467c0(archive, file_, &size);
    if (file != NULL)
    {
        LoadFile(script, archive, archiveSize);
        state_ = 2;
    }
}

void MenuObjectClass0::LoadFile(MenuScript* script, void* file, unsigned int size)
{
    if (file == NULL || size == 0)
        return;
    MenuHeap* heap = script->FindHeap(heap_);
    MenuVRAMState* vramState = script->FindVRAMState(vramState_);
    if (heap == NULL || vramState == NULL)
        return;
    heap->allocator_.GetSizeWithLargestBlockRemoved();
    func_0207df90(&vramState->state_);
    func_0204719c(model_);
    func_02047b30(model_, file, size, &heap->allocator_);
    func_0207dfac(&vramState->state_);
    heap->allocator_.GetSizeWithLargestBlockRemoved();
}

void* MenuObjectClass0::GetModel()
{
    return model_;
}

void MenuObjectClass0::SetLoaded()
{
    state_ = 2;
}
