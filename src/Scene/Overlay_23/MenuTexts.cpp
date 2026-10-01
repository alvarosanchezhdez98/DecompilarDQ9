// The objects of type 4 of the menus (see MenuObjects.h): a list of texts, loaded from a .bin or .mes file under
// data/, that the other objects show
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "GameState/PartyMemberData.h"
#include "Scene/Overlay_11/MenuScript.h"
#include <std_library_functions.h>

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    // The index of the hero in the party
    int func_020100a8(GameState* gameState);
    void* func_020467c0(void* archive, const char* name, unsigned int* size);
    void func_020727d8(TextList* texts);
    void func_020728ac(TextList* texts, SafeAllocator* allocator, void* file, unsigned int size, int, int,
                       unsigned char variant);
    void func_020dfc2c(TextTable* texts);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    // Whether the file is a table of texts (.mes)
    int func_020e03b8(TextTable* texts, void* file, unsigned int size);
    // Makes a list of the table's texts
    void func_020e03f0(TextTable* texts, TextList* list);
}

int MenuObjectClass4::Initialize(MenuScript* script, int id, int heap, const char* archive, const char* file,
                                 int variant)
{
    MenuObjectClass::Initialize();
    type_ = 4;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    archive_ = archive;
    file_ = file;
    variant_ = variant;
    Load(script);
    return 1;
}

void MenuObjectClass4::Update(MenuScript* script)
{
    static int (MenuObjectClass4::*states[4])(MenuScript*) = {&MenuObjectClass4::State_Load,
                                                              &MenuObjectClass4::State_Wait,
                                                              &MenuObjectClass4::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClass4::State_Load(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    if (objects->GetTask() < 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        int variant = 0;
        if (variant_ == 1)
        {
            GameState* gameState = GameState::GetInstance();
            GameObject* hero = gameState->GetPartyMemberByIndex(func_020100a8(gameState));
            if (hero != NULL)
                variant = hero->partyData_->appearance_.female_;
        }
        else if (variant_ == 2)
        {
        }
        else if (variant_ == 3)
            variant = 1;
        char name[0x20];
        if (archive_ != NULL)
            sprintf(name, archive_, variant);
        else
            sprintf(name, file_, variant);
        char path[0x40] = {0};
        if (strncmp(path, "data/", 5) != 0)
            strcpy(path, "data/");
        strcat(path, name);
        int task;
        if (archive_ != NULL)
        {
            memset(name, 0, sizeof(name));
            sprintf(name, file_, variant);
            task = loader->QueueLoadFileInGP2(path, name, NULL);
        }
        else
            task = loader->QueueLoadFile(path, NULL);
        objects->SetTask(task);
        return 1;
    }
    return state_;
}

int MenuObjectClass4::State_Wait(MenuScript* script)
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
            if (file != NULL && size != 0)
                LoadFile(script, file, size);
        }
        loader->RemoveTask(task);
        objects->SetTask(-1);
        return 2;
    }
    return state_;
}

int MenuObjectClass4::State_Loaded(MenuScript* script)
{
    return state_;
}

void MenuObjectClass4::Finish(MenuObjectList* list)
{
    func_020727d8(&texts_);
}

TextList* MenuObjectClass4::GetTexts()
{
    return &texts_;
}

void MenuObjectClass4::Load(MenuScript* script)
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int task = script->GetLoadTask();
    if (task < 0 || !loader->GetTaskStatus(task) || loader->GetDetailedTaskStatus(task) != 2)
        return;
    void* archive;
    unsigned int archiveSize;
    loader->GetLoadedFileByID(task, &archive, &archiveSize);
    if (archive == NULL || archiveSize == 0)
        return;
    unsigned int size;
    void* file = func_020467c0(archive, file_, &size);
    if (file != NULL)
        LoadFile(script, file, size);
}

void MenuObjectClass4::LoadFile(MenuScript* script, void* file, unsigned int size)
{
    if (file == NULL || size == 0)
        return;
    MenuHeap* heap = script->FindHeap(heap_);
    MenuVRAMState* vramState = script->FindVRAMState(vramState_);
    if (heap == NULL || vramState == NULL)
        return;
    TextTable table;
    func_020dfc2c(&table);
    if (func_020e03b8(&table, file, size))
    {
        func_020dfc40(&table);
        func_020dfec0(&table, &heap->allocator_, file, size);
        func_020e03f0(&table, &texts_);
        return;
    }
    int variant = 0;
    if (variant_ == 1)
    {
        GameState* gameState = GameState::GetInstance();
        GameObject* hero = gameState->GetPartyMemberByIndex(func_020100a8(gameState));
        if (hero != NULL)
            variant = hero->partyData_->appearance_.female_;
    }
    else if (variant_ == 2)
    {
    }
    else if (variant_ == 3)
        variant = 1;
    func_020727d8(&texts_);
    func_020728ac(&texts_, &heap->allocator_, file, size, 0, 0, variant);
}
