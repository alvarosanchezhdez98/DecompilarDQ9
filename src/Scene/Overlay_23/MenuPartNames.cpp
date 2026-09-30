// The objects of type 0x11 of the menus (see MenuObjects.h), which load the names of the items and of the parts of
// the characters' models
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Scene/Overlay_11/MenuScript.h"

extern "C"
{
    // The GP2 archive of the names and their file in it
    extern const char* data_020f2a30;
    extern const char* data_020f2a38;

    void func_020de848(PartNameTable* names);
    void func_020de888(PartNameTable* names, SafeAllocator* allocator, void* file, unsigned int size);
    void func_020dea64(PartNameTable* names, SafeAllocator* allocator, void* file, unsigned int size,
                       const unsigned char* categories, int count);
}

int MenuObjectClass11::Initialize(MenuScript* script, int id, int heap, int categories)
{
    MenuObjectClass::Initialize();
    type_ = 0x11;
    id_ = id;
    heap_ = heap;
    func_020de848(&names_);
    categories_ = categories;
    allocator_.ResetAllocatorPointer();
    return 1;
}

void MenuObjectClass11::Finish(MenuObjectList* list)
{
    if (allocator_.GetSignedAllocator() == NULL)
        return;
    allocator_.Destroy();
}

void MenuObjectClass11::Update(MenuScript* script)
{
    int (MenuObjectClass11::*states[4])(MenuScript*) = {&MenuObjectClass11::State_Load, &MenuObjectClass11::State_Wait,
                                                          &MenuObjectClass11::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClass11::State_Load(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    if (objects->GetTask() >= 0)
        return state_;
    objects->SetTask(BackgroundLoader::GetInstance()->QueueLoadFileInGP2(data_020f2a38, data_020f2a30, NULL));
    return 1;
}

int MenuObjectClass11::State_Wait(MenuScript* script)
{
    MenuHeap* heap;
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
            heap = script->FindHeap(heap_);
            if (heap == NULL)
            {
                loader->RemoveTask(task);
                objects->SetTask(-1);
                return 2;
            }
            if (categories_ == 0)
            {
                allocator_.CreateTypeA(heap->allocator_.Allocate(0x1a000), 0x1a000);
                allocator_.Reset();
                func_020de888(&names_, &allocator_, file, size);
            }
            else
            {
                unsigned int bytes = 0;
                short count = 0;
                unsigned char categories[12] = {0};
                if (categories_ & 1)
                {
                    bytes += 79872.0;
                    for (short i = 0; i <= 7; i++)
                        categories[count++] = i;
                }
                if (categories_ & 2)
                {
                    bytes += 7987.2;
                    categories[count++] = 8;
                }
                if (categories_ & 4)
                {
                    bytes += 4915.2;
                    categories[count++] = 9;
                }
                if (categories_ & 8)
                {
                    bytes += 15872.0;
                    categories[count++] = 11;
                }
                if (bytes > 0x1a000)
                    bytes = 0x1a000;
                allocator_.CreateTypeA(heap->allocator_.Allocate(bytes), bytes);
                allocator_.Reset();
                func_020dea64(&names_, &allocator_, file, size, categories, count);
            }
        }
        loader->RemoveTask(task);
        objects->SetTask(-1);
        return 2;
    }
    return state_;
}

int MenuObjectClass11::State_Loaded(MenuScript* script)
{
    return state_;
}

void* MenuObjectClass11::Ve8()
{
    return &names_;
}
