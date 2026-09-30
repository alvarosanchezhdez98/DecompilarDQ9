// The objects of type 0x14 of the menus (see MenuObjects.h): a 3D object whose CHR archive is under data/, alone or
// in the NARC of the script
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Scene/Overlay_11/MenuScript.h"
#include <std_library_functions.h>

extern "C"
{
    void* func_020467c0(void* archive, const char* name, unsigned int* size);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
}

int GetFileInNarc(const void* archive, const char* name, const void** file, unsigned int* size, unsigned int);

int MenuObjectClass14::Initialize(MenuScript* script, int id, int heap, int vramState, const char* file)
{
    MenuObjectClass::Initialize();
    type_ = 0x14;
    id_ = id;
    heap_ = heap;
    vramState_ = vramState;
    file_ = file;
    object_.Initialize();
    Load(script);
    return 1;
}

void MenuObjectClass14::Finish(MenuObjectList* list)
{
    object_.Initialize();
}

void MenuObjectClass14::Update(MenuScript* script)
{
    int (MenuObjectClass14::*states[4])(MenuScript*) = {&MenuObjectClass14::State_Load, &MenuObjectClass14::State_Wait,
                                                          &MenuObjectClass14::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClass14::State_Load(MenuScript* script)
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

int MenuObjectClass14::State_Wait(MenuScript* script)
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

int MenuObjectClass14::State_Loaded(MenuScript* script)
{
    object_.AdvanceEffects();
    return state_;
}

void MenuObjectClass14::Draw1()
{
    if (flags_ & 8)
        return;
    object_.Draw(true);
}

void MenuObjectClass14::Draw2()
{
}

void MenuObjectClass14::SetPosition(Vector3fix* position)
{
    object_.position_.x = position->x;
    object_.position_.y = position->y;
    object_.position_.z = position->z;
}

Vector3fix MenuObjectClass14::GetPosition()
{
    return object_.position_;
}

void MenuObjectClass14::Load(MenuScript* script)
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
        LoadFile(script, (void*)file, size);
        state_ = 2;
        return;
    }
    file = func_020467c0(archive, file_, &size);
    if (file != NULL)
    {
        LoadFile(script, (void*)file, size);
        state_ = 2;
    }
}

void MenuObjectClass14::LoadFile(MenuScript* script, void* file, unsigned int size)
{
    if (file == NULL || size == 0)
        return;
    MenuHeap* heap = script->FindHeap(heap_);
    MenuVRAMState* vramState = script->FindVRAMState(vramState_);
    if (heap == NULL || vramState == NULL)
        return;
    SafeAllocator* allocator = &heap->allocator_;
    allocator->GetSizeWithLargestBlockRemoved();
    func_0207df90(&vramState->state_);
    object_.Initialize();
    ObjectArchiveLoadInfo info;
    info.fileData = file;
    info.unk_8 = size;
    info.allocator = allocator;
    object_.LoadFromCHRArchive(&info);
    object_.MaybeSetBCFGAnimation(0, 0);
    object_.SetScale(0x10a, 0x10a, 0x10a);
    func_0207dfac(&vramState->state_);
    allocator->GetSizeWithLargestBlockRemoved();
}
