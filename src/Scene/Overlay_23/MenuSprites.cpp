// The objects of type 0xa of the menus (see MenuObjects.h): sprites whose files are in a NARC under data/
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

extern "C"
{
    MessageSystem* func_020421a0();
    void* func_020467c0(void* archive, const char* name, unsigned int* size);
    int func_0204684c(void* archive, const char* name, void** file, int, unsigned int* size, int);
    void func_0205a234(SpriteAnimationList* animations);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a494(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    // The bit of the sprite's VRAM
    unsigned int func_0205af18(SpriteRenderer* renderer, Sprite* sprite);
}

static int FindFile(void* archive, const char* type, void** file, unsigned int* size);

int MenuObjectClassA::Initialize(MenuScript* script, int id, int heap, const char* archive, const char* file,
                                 int screen)
{
    MenuObjectClass::Initialize();
    type_ = 0xa;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    archive_ = archive;
    file_ = file;
    func_0205a444(&renderer_);
    memset(&range_, 0, sizeof(range_));
    renderer_.unk_50 = screen;
    Load(script);
    return 1;
}

void MenuObjectClassA::Finish(MenuObjectList* list)
{
    list->RemoveRange(&range_);
    for (unsigned int i = 0; i < renderer_.capacity_; i++)
    {
        Sprite* sprite = renderer_.GetSprite(i);
        if (sprite != NULL)
            list->ClearMask(renderer_.unk_50, func_0205af18(&renderer_, sprite));
    }
    func_0205a494(&renderer_);
    MessageSystem* messages = func_020421a0();
    messages->unk_2d8 = NULL;
    messages->unk_2e6 = 1;
}

void MenuObjectClassA::Update(MenuScript* script)
{
    int (MenuObjectClassA::*states[4])(MenuScript*) = {&MenuObjectClassA::State_Load, &MenuObjectClassA::State_Wait,
                                                         &MenuObjectClassA::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClassA::State_Load(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    if (objects->GetTask() < 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        char path[0x50];
        if (archive_ != NULL)
            sprintf(path, "data/%s", archive_);
        else
            sprintf(path, "data/%s", file_);
        int task;
        if (archive_ != NULL)
            task = loader->QueueLoadFileInGP2(path, file_, NULL);
        else
            task = loader->QueueLoadFile(path, NULL);
        objects->SetTask(task);
        return 1;
    }
    return state_;
}

int MenuObjectClassA::State_Wait(MenuScript* script)
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
            LoadFiles(script, file, size);
        }
        loader->RemoveTask(task);
        objects->SetTask(-1);
        return 2;
    }
    return state_;
}

int MenuObjectClassA::State_Loaded(MenuScript* script)
{
    return state_;
}

void MenuObjectClassA::Draw1()
{
}

void MenuObjectClassA::Draw2()
{
}

void MenuObjectClassA::Load(MenuScript* script)
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
        LoadFiles(script, archive, archiveSize);
        state_ = 2;
        return;
    }
    file = func_020467c0(archive, file_, &size);
    if (file != NULL)
    {
        LoadFiles(script, archive, archiveSize);
        state_ = 2;
    }
}

void MenuObjectClassA::LoadFiles(MenuScript* script, void* archive, unsigned int size)
{
    if (archive == NULL || size == 0)
        return;
    MenuHeap* heap = script->FindHeap(heap_);
    if (heap == NULL)
        return;
    heap->allocator_.GetSizeWithLargestBlockRemoved();
    void* file;
    unsigned int fileSize;
    if (FindFile(archive, "NCER", &file, &fileSize))
        func_0205a528(&renderer_, file, fileSize, &heap->allocator_);
    if (FindFile(archive, "NCGR", &file, &fileSize))
        func_0205a528(&renderer_, file, fileSize, &heap->allocator_);
    if (FindFile(archive, "NCLR", &file, &fileSize))
        func_0205a528(&renderer_, file, fileSize, &heap->allocator_);
    if (FindFile(archive, "NANR", &file, &fileSize))
    {
        SpriteAnimationList* animations = (SpriteAnimationList*)heap->allocator_.Allocate(sizeof(SpriteAnimationList));
        if (animations != NULL)
        {
            func_0205a234(animations);
            renderer_.animations_ = animations;
            func_0205a528(&renderer_, file, fileSize, &heap->allocator_);
        }
    }
    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObjectList* objects;
    unsigned int end = renderer_.unk_48;
    objects = script->GetObjects();
    range_.start_ = 0;
    range_.end_ = end;
    objects->AddRange(&range_);
    for (unsigned int i = 0; i < renderer_.capacity_; i++)
    {
        Sprite* sprite = renderer_.GetSprite(i);
        if (sprite != NULL)
            objects->SetMask(renderer_.unk_50, func_0205af18(&renderer_, sprite));
    }
    MessageSystem* messages = func_020421a0();
    messages->unk_2d8 = &renderer_;
    messages->unk_2dc = renderer_.sprites_;
    messages->unk_2e4 = 0;
    messages->unk_2e0 = renderer_.animations_;
    messages->unk_2e6 = 1;
}

SpriteRenderer* MenuObjectClassA::GetRenderer()
{
    return &renderer_;
}

static int FindFile(void* archive, const char* type, void** file, unsigned int* size)
{
    if (FindFilesInNarcBySubstring(archive, type, (const void**)file, size, 1))
        return 1;
    if (func_0204684c(archive, type, file, 1, size, 0))
        return 1;
    return 0;
}
