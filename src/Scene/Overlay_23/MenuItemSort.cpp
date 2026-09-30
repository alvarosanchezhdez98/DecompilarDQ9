// The objects of type 0x12 of the menus (see MenuObjects.h), which load the order of the items
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Scene/Overlay_11/MenuScript.h"

int MenuObjectClass12::Initialize(MenuScript* script, int id, int heap)
{
    MenuObjectClass::Initialize();
    type_ = 0x12;
    id_ = id;
    heap_ = heap;
    list_.Initialize();
    return 1;
}

void MenuObjectClass12::Finish(MenuObjectList* list)
{
    list_.Finish();
}

void MenuObjectClass12::Update(MenuScript* script)
{
    int (MenuObjectClass12::*states[4])(MenuScript*) = {&MenuObjectClass12::State_Load, &MenuObjectClass12::State_Wait,
                                                          &MenuObjectClass12::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClass12::State_Load(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    if (objects->GetTask() >= 0)
        return state_;
    objects->SetTask(
        BackgroundLoader::GetInstance()->QueueLoadFileInGP2("data/prm/itemsort.gp2", "itemsort_<LG>.bin", NULL));
    return 1;
}

int MenuObjectClass12::State_Wait(MenuScript* script)
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
            list_.Load(&heap->allocator_, file, size, NULL, 0);
        }
        loader->RemoveTask(task);
        objects->SetTask(-1);
        return 2;
    }
    return state_;
}

int MenuObjectClass12::State_Loaded(MenuScript* script)
{
    return state_;
}

void* MenuObjectClass12::Vec()
{
    return &list_;
}
