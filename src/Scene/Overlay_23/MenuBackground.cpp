// The objects of type 2 of the menus (see MenuObjects.h): a background whose file is under data/, alone or in a GP2
// archive, and whose cells (.bnsc) are in the file
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Scene/Overlay_11/MenuScript.h"
#include <std_library_functions.h>

extern "C"
{
    void* func_020467c0(void* archive, const char* name, unsigned int* size);
    void* func_020467f0(void* archive, int index, char** name, unsigned int* size);
    int func_02046900(void* archive);
    void func_0204af38(BackgroundGraphics* background, unsigned char count, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204afb4(BackgroundGraphics* background);
    void func_0204b010(BackgroundGraphics* background, int);
    void func_0204b04c(BackgroundGraphics* background, int);
    void func_0204b088(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* background, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b2e0(BackgroundGraphics* background, void* file);
    void func_0204b3a0(BackgroundGraphics* background, void* file);
    void func_0204b5b4(BackgroundGraphics* background, int priority);
    void func_0204b5e8(BackgroundGraphics* background, int x, int y);
    void func_0204b988(BackgroundGraphics* background, int red, int green, int blue, int);
}

int MenuObjectClass2::Initialize(MenuScript* script, int id, int heap, const char* archive, const char* file,
                                 int screen, int layer, int priority)
{
    MenuObjectClass::Initialize();
    type_ = 2;
    script_ = script;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    archive_ = archive;
    file_ = file;
    colored_ = 0;
    func_0204af64(&background_);
    func_0204b11c(&background_, 0);
    background_.unk_1c_0_ = screen;
    background_.unk_1c_4_ = layer;
    func_0204b5b4(&background_, priority);
    func_0204b5e8(&background_, 0, 0);
    MenuHeap* menuHeap = script->FindHeap(heap_);
    if (menuHeap == NULL)
        return 0;
    func_0204b12c(&background_, &menuHeap->allocator_);
    Load(script);
    x_ = 0;
    y_ = 0;
    return 1;
}

void MenuObjectClass2::Update(MenuScript* script)
{
    int (MenuObjectClass2::*states[4])(MenuScript*) = {&MenuObjectClass2::State_Load, &MenuObjectClass2::State_Wait,
                                                         &MenuObjectClass2::State_Loaded, NULL};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClass2::State_Load(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    if (file_ == NULL)
        return 1;
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

int MenuObjectClass2::State_Wait(MenuScript* script)
{
    if (file_ == NULL)
    {
        LoadData(script);
        return 2;
    }
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
            {
                if (flags_ & 2)
                    LoadCells(script, 1, file, size);
                else
                    LoadFiles(script, file, size);
            }
        }
        loader->RemoveTask(task);
        objects->SetTask(-1);
        return 2;
    }
    return state_;
}

int MenuObjectClass2::State_Loaded(MenuScript* script)
{
    // Unused: the compiler emits its initial value, which is in the original's .rodata
    int unused[1] = {0x100000};
    if (flags_ & 0x80)
    {
        unsigned short ticks = GameState::GetInstance()->GetTickCount();
        Vector3fix position = GetPosition();
        position.x -= ticks << 11;
        position.y += ticks << 11;
        if (position.x < -0x100000)
            position.x += 0x100000;
        if (position.y > 0x100000)
            position.y -= 0x100000;
        SetPosition(&position);
    }
    if (flags_ & 1)
        return state_;
    if (colored_)
        SetColor(red_, green_, blue_);
    return state_;
}

void MenuObjectClass2::V0c(MenuScript* script)
{
    if (flags_ & 1)
        return;
    func_0204b010(&background_, 0);
}

void MenuObjectClass2::V10(MenuScript* script)
{
    if (flags_ & 1)
        return;
    func_0204b04c(&background_, 0);
}

void MenuObjectClass2::Draw3()
{
    if (flags_ & 2)
    {
        MenuScript* script = script_;
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
                    LoadCells(script, 0, file, size);
            }
            loader->RemoveTask(task);
            objects->SetTask(-1);
            state_ = 2;
        }
    }
    if (flags_ & 1)
        return;
    func_0204b088(&background_, 0);
}

void MenuObjectClass2::Finish(MenuObjectList* list)
{
    MenuObjectClass* object = list->first_;
    while (object != NULL)
    {
        MenuObjectClass* next = object->GetNext();
        if (object->GetType() == 6)
        {
            Canvas* canvas = &((MenuObjectClass6*)object)->canvas_;
            if (canvas != NULL && &background_ == canvas->background_)
                canvas->background_ = NULL;
        }
        object = next;
    }
    func_0204afb4(&background_);
}

BackgroundGraphics* MenuObjectClass2::GetBackground()
{
    return &background_;
}

void MenuObjectClass2::SetFile(const char* file)
{
    file_ = file;
    state_ = 0;
    flags_ |= 3;
}

void MenuObjectClass2::Load(MenuScript* script)
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
        LoadFiles(script, file, size);
}

void MenuObjectClass2::LoadFiles(MenuScript* script, void* archive, unsigned int size)
{
    if (archive == NULL || size == 0)
        return;
    MenuHeap* heap = script->FindHeap(heap_);
    if (heap == NULL)
        return;
    int count = func_02046900(archive);
    int cells = 0;
    for (int i = 0; i < count; i++)
    {
        unsigned int fileSize;
        char* name;
        func_020467f0(archive, i, &name, &fileSize);
        if (strstr(name, ".bnsc") != NULL)
            cells++;
    }
    if (cells > 0)
        func_0204af38(&background_, cells, &heap->allocator_);
    for (int i = 0; i < count; i++)
    {
        unsigned int fileSize;
        char* name;
        void* file = func_020467f0(archive, i, &name, &fileSize);
        if (file != NULL)
            func_0204b174(&background_, file, &heap->allocator_, fileSize);
    }
}

// NONMATCHING: the C matches 75.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The copy of the background's two nibbles gets other registers: the original extracts the screen to a third one
#ifdef NONMATCHING
void MenuObjectClass2::LoadCells(MenuScript* script, int add, void* archive, unsigned int size)
{
    if (archive == NULL || size == 0)
        return;
    int count = func_02046900(archive);
    for (int i = 0; i < count; i++)
    {
        unsigned int fileSize;
        char* name;
        void* file = func_020467f0(archive, i, &name, &fileSize);
        if (file == NULL)
            continue;
        BackgroundGraphics background;
        func_0204af64(&background);
        background.unk_1c_0_ = background_.unk_1c_0_;
        background.unk_1c_4_ = background_.unk_1c_4_;
        if (add)
            func_0204b2e0(&background, file);
        else
            func_0204b3a0(&background, file);
    }
}
#else
asm void MenuObjectClass2::LoadCells(MenuScript* script, int add, void* archive, unsigned int size)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x28
    movs r8, r3
    mov r10, r0
    ldrne r0, [sp, #0x50]
    mov r9, r2
    cmpne r0, #0x0
    beq @L021f7c60
    mov r0, r8
    bl func_02046900
    mov r6, r0
    mov r7, #0x0
    add r5, sp, #0x0
    add r11, sp, #0x4
    b @L021f7c58
@L021f7bd4:
    mov r0, r8
    mov r1, r7
    mov r2, r5
    mov r3, r11
    bl func_020467f0
    movs r4, r0
    beq @L021f7c54
    add r0, sp, #0x8
    bl func_0204af64
    ldrb r1, [r10, #0x44]
    ldrb r0, [sp, #0x24]
    cmp r9, #0x0
    mov r1, r1, lsl #0x1c
    mov r2, r1, lsr #0x1c
    bic r1, r0, #0xf
    and r0, r2, #0xf
    orr r0, r1, r0
    strb r0, [sp, #0x24]
    and r0, r0, #0xff
    ldrb r2, [r10, #0x44]
    bic r1, r0, #0xf0
    mov r0, r2, lsl #0x18
    mov r0, r0, lsr #0x1c
    mov r0, r0, lsl #0x1c
    orr r0, r1, r0, lsr #0x18
    strb r0, [sp, #0x24]
    add r0, sp, #0x8
    mov r1, r4
    beq @L021f7c50
    bl func_0204b2e0
    b @L021f7c54
@L021f7c50:
    bl func_0204b3a0
@L021f7c54:
    add r7, r7, #0x1
@L021f7c58:
    cmp r7, r6
    blt @L021f7bd4
@L021f7c60:
    add sp, sp, #0x28
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void MenuObjectClass2::SetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    red_ = red;
    green_ = green;
    blue_ = blue;
    colored_ = 1;
    func_0204b988(&background_, red_, green_, blue_, 0xffff);
}

void MenuObjectClass2::LoadData(MenuScript* script)
{
    void* data = script->GetData();
    unsigned int size = script->GetDataSize();
    if (data == NULL || size == 0)
        return;
    if (flags_ & 2)
        LoadCells(script, 1, data, size);
    else
        LoadFiles(script, data, size);
}

void MenuObjectClass2::SetPosition(Vector3fix* position)
{
    x_ = position->x >> 12;
    y_ = position->y >> 12;
    func_0204b5e8(&background_, x_, y_);
}

Vector3fix MenuObjectClass2::GetPosition()
{
    Vector3fix position;
    position.x = x_ << 12;
    position.y = y_ << 12;
    position.z = 0;
    return position;
}
