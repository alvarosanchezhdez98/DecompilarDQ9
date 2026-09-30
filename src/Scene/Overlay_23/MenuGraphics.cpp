// The objects of type 0xc of the menus (see MenuObjects.h): graphics whose file is under data/, alone or in the NARC
// of the script
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Scene/Overlay_11/MenuScript.h"
#include <std_library_functions.h>

struct Unknown_0203bd08;

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    Unknown_0203bd08* func_0203bd08();
    unsigned int func_0203be40(Unknown_0203bd08*);
    unsigned int func_0203be4c(Unknown_0203bd08*);
    void* func_020467c0(void* archive, const char* name, unsigned int* size);
    void func_02075cdc(Unknown_02075cdc* graphics);
    void func_02075db0(Unknown_02075cdc* graphics, int x, int y);
    void func_02076080(Unknown_02075cdc* graphics, SafeAllocator* allocator, void* file, unsigned int size);
    unsigned int func_02076738(Unknown_02075cdc* graphics, void* file, unsigned int size);
    void func_02076928(Unknown_02075cdc* graphics, int);
}

int GetFileInNarc(const void* archive, const char* name, const void** file, unsigned int* size, unsigned int);

int MenuObjectClassC::Initialize(MenuScript* script, int id, int heap, const char* file, int screen)
{
    MenuObjectClass::Initialize();
    type_ = 0xc;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = file;
    MenuObjectList* objects = script->GetObjects();
    unsigned int slot = objects->FindSlots(screen, 1);
    objects->SetSlots(screen, slot, 1);
    func_02075cdc(&graphics_);
    unsigned int oam;
    if (screen == 0)
        oam = func_0203be40(func_0203bd08());
    else
        oam = func_0203be4c(func_0203bd08());
    graphics_.unk_14 = oam + slot * 8;
    graphics_.unk_38 = 0;
    unsigned int mask = objects->FindMask(screen);
    objects->SetMask(screen, mask);
    graphics_.unk_3c = mask & 0xf;
    graphics_.unk_40 = 0;
    graphics_.unk_5e = screen;
    unk_a4 = 0;
    memset(&range_, 0, sizeof(range_));
    x_ = 0;
    y_ = 0;
    pressedRight_ = 0;
    pressedLeft_ = 0;
    Load(script);
    return 1;
}

void MenuObjectClassC::Finish(MenuObjectList* list)
{
    list->ClearSlots(graphics_.unk_5e, graphics_.unk_70, 1);
    list->RemoveRange(&range_);
    list->ClearMask(graphics_.unk_5e, graphics_.unk_3c);
}

void MenuObjectClassC::Update(MenuScript* script)
{
    int (MenuObjectClassC::*states[4])(MenuScript*) = {&MenuObjectClassC::State_Load, &MenuObjectClassC::State_Wait,
                                                         &MenuObjectClassC::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClassC::State_Load(MenuScript* script)
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

int MenuObjectClassC::State_Wait(MenuScript* script)
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

int MenuObjectClassC::State_Loaded(MenuScript* script)
{
    int dx = 0;
    int dy = 0;
    if (pressedRight_)
    {
        dx = 1;
        dy = 1;
    }
    else if (pressedLeft_)
    {
        dx = -1;
        dy = 1;
    }
    func_02075db0(&graphics_, x_ + dx, y_ + dy);
    pressedRight_ = 0;
    pressedLeft_ = 0;
    return state_;
}

void MenuObjectClassC::SetPosition(Vector3fix* position)
{
    x_ = position->x;
    y_ = position->y;
}

Vector3fix MenuObjectClassC::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_;
    // Not y: a bug of the game
    position.z = y_;
    return position;
}

void MenuObjectClassC::V3c(short value)
{
    unk_a4 = value;
}

int MenuObjectClassC::V40()
{
    return unk_a4;
}

void MenuObjectClassC::Load(MenuScript* script)
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

void MenuObjectClassC::LoadFile(MenuScript* script, void* file, unsigned int size)
{
    if (file == NULL || size == 0)
        return;
    MenuHeap* heap = script->FindHeap(heap_);
    if (heap == NULL)
        return;
    unsigned int vramSize = func_02076738(&graphics_, file, size);
    MenuObjectList* objects = script->GetObjects();
    unsigned int start = objects->FindRange(vramSize);
    range_.start_ = start;
    range_.end_ = start + vramSize;
    objects->AddRange(&range_);
    graphics_.unk_38 = start;
    heap->allocator_.GetSizeWithLargestBlockRemoved();
    func_02076080(&graphics_, &heap->allocator_, file, size);
    func_02076928(&graphics_, 1);
    heap->allocator_.GetSizeWithLargestBlockRemoved();
}
