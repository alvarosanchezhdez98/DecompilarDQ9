#include "Scene/Overlay_11/MenuScript.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "System/Cache.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include "System/VRAM.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>
#include <std_library_functions.h>

extern "C"
{
    // Returns the game's mode (6 is the title)
    int func_0200fb9c(GameState* gameState);
    int func_02012034(GameState* gameState);
    void func_0202ae18();
    void func_0203b4d8(GameResources* resources, int);
    void func_0203b4e8(GameResources* resources, int);
    MessageSystem* func_020421a0();
    // The answer to the question of the message window: 0 (yes) or 1 (no)
    int func_020457e0(MessageSystem* messages);
    void func_02074af4(void*);
    void func_02074b64(void*);
    void func_02074bd0(void*);
    void func_02074bf4(void*);
    void func_0207df50(VRAMManagerState* state);
    void func_0207dfc8(VRAMManagerState* state, VRAMManagerState* copy);
    // OS_Terminate
    void func_020c9be0();

    // Whether the menu is finishing
    int func_ov017_021959b4();
    void func_ov017_021d4c04(ScriptEngine* engine, void* file, void* stack, int stackSize, void* frames, int frameCount);
    void func_ov017_021d4ccc(ScriptEngine* engine);
    void func_ov017_021d4ce4(ScriptEngine* engine, int entry);
    int func_ov017_021d4df8(ScriptEngine* engine, int entry);

    void func_ov023_021f672c(MenuObjectList* objects);
    void func_ov023_021f6844(MenuObjectList* objects, int heap);
    void func_ov023_021f68dc(MenuObjectList* objects, MenuScript* script);
    void func_ov023_021f698c(MenuObjectList* objects);
    void func_ov023_021f69bc(MenuObjectList* objects);
    void func_ov023_021f69ec(MenuObjectList* objects);
    // The BackgroundLoader's task of the objects
    int func_ov023_021f6bb8(MenuObjectList* objects);
}

void MenuHeap::Initialize()
{
    id_ = 0;
    allocator_.ResetAllocatorPointer();
    next_ = 0;
    child_ = 0;
}

MenuHeap* MenuHeap::Find(int id)
{
    if (id_ == id)
        return this;

    MenuHeap* heap = 0;
    if (next_ != 0)
        heap = next_->Find(id);
    if (heap != 0)
        return heap;

    if (child_ != 0)
        heap = child_->Find(id);
    return heap;
}

void MenuHeap::AddNext(MenuHeap* heap)
{
    if (next_ != 0)
    {
        MenuHeap* last = next_;
        while (last->next_ != 0)
            last = last->next_;
        last->next_ = heap;
    }
    else
    {
        next_ = heap;
    }
}

void MenuHeap::AddChild(MenuHeap* heap)
{
    if (child_ == 0)
        child_ = heap;
    else
        child_->AddNext(heap);
}

void MenuVRAMState::Initialize()
{
    id_ = 0;
    unk_2 = 0;
    unk_74 = 0;
    next_ = 0;
}

void MenuScript::Initialize()
{
    heap_.Initialize();
    file_ = 0;
    fileSize_ = 0;
    buffer_ = 0;
    bufferSize_ = 0;
    bufferHeap_ = -1;
    data_ = 0;
    dataSize_ = 0;
    memset(&engine_, 0, sizeof(engine_));
    entry_ = -1;
    nextEntry_ = 0;
    flags_ = 0;
    func_ov023_021f672c(&objects_);
    loadTask_ = -1;
    func_0203b4d8(func_ov017_0218b5b0(), 0xc0);
    screensSwapped_ = (POWCNT & 0x8000) >> 15;
    unk_1a4 = 0;
    unk_1a5 = 0;
    func_02074af4(unk_194);
    func_02074b64(unk_194);
    mainLayers_ = (DISPCNT & 0x1f00) >> 8;
    subLayers_ = (DISPCNTSUB & 0x1f00) >> 8;
    unk_1b0 = 0;
    unk_1b2 = 0;
    callbacks_ = 0;
    callbackCount_ = 0;
    callback_ = 0;
    frameCallback_ = 0;
    yesCallback_ = 0;
    noCallback_ = 0;
    yesEntry_ = 0;
    noEntry_ = 0;
    unk_1c8 = 0;
    idleTime_ = 0;
    mainBanks_ = 0;
    subBanks_ = 0;
    finishCallback_ = 0;
    finished_ = false;
    finishing_ = false;
}

int MenuScript::AllocateBuffer(int heap, unsigned int size)
{
    MenuHeap* found = heap_.Find(heap);
    if (found == 0)
        return 1;

    buffer_ = found->allocator_.Allocate(size);
    if (buffer_ == 0)
        return 1;

    bufferHeap_ = heap;
    bufferSize_ = size;
    return 0;
}

void* MenuScript::GetBuffer()
{
    return buffer_;
}

bool MenuScript::AllocateData(int heap, unsigned int size)
{
    MenuHeap* found = heap_.Find(heap);
    if (found == 0)
        return false;

    data_ = found->allocator_.Allocate(size);
    if (data_ == 0)
        return false;

    dataSize_ = size;
    return true;
}

void MenuScript::SetData(void* data, unsigned int size)
{
    data_ = data;
    dataSize_ = size;
}

void* MenuScript::GetData()
{
    return data_;
}

unsigned int MenuScript::GetDataSize()
{
    return dataSize_;
}

void MenuScript::Load(SafeAllocator* allocator, void* file, unsigned int fileSize)
{
    file_ = file;
    fileSize_ = fileSize;
    void* stack = allocator->Allocate(0x400);
    void* frames = allocator->Allocate(0x1800);
    if (stack == 0 || frames == 0)
        func_020c9be0();

    func_ov017_021d4c04(&engine_, file_, stack, 0x80, frames, 0x200);
    SetMenuScriptCommands(&engine_);
}

void MenuScript::CreateHeap(void* buffer, unsigned int size)
{
    heap_.Initialize();
    heap_.allocator_.CreateTypeB(buffer, size, 4);
}

MenuHeap* MenuScript::GetHeap()
{
    return &heap_;
}

MenuHeap* MenuScript::FindHeap(int id)
{
    return heap_.Find(id);
}

void MenuScript::DestroyHeap(MenuHeap* heap)
{
    if (heap == 0)
        return;

    DestroyHeap(heap->next_);
    DestroyHeap(heap->child_);
    func_ov023_021f6844(&objects_, heap->id_);
    heap->allocator_.Destroy();
}

void MenuScript::SaveVRAMState(VRAMManagerState* state)
{
    vramState_.Initialize();
    func_0207df50(state);
    func_0207dfc8(state, &vramState_.state_);
}

MenuVRAMState* MenuScript::FindVRAMState(int id)
{
    for (MenuVRAMState* state = &vramState_; state != 0; state = state->next_)
    {
        if (state->id_ == id)
            return state;
    }
    return 0;
}

bool MenuScript::Update()
{
    GameResources* resources = func_ov017_0218b5b0();
    func_0202ae18();
    if (!finishing_)
    {
        if (func_ov017_021959b4())
        {
            finishing_ = true;
            if (resources != 0)
                SetBrightness(resources, -16, 10);
        }

        RunScript();
        UpdateCallbacks();
        UpdateQuestion();
        func_ov023_021f68dc(&objects_, this);
    }
    else if (resources != 0 && !IsBrightnessTransitionActive(resources))
    {
        Finish();
        finished_ = true;
    }
    return !finished_;
}

void MenuScript::Draw1()
{
    func_ov023_021f698c(&objects_);
}

void MenuScript::Draw2()
{
    func_ov023_021f69bc(&objects_);
}

void MenuScript::Draw3()
{
    func_ov023_021f69ec(&objects_);
}

void MenuScript::Finish()
{
    if (func_ov017_021959b4() && finishCallback_ != 0)
        finishCallback_(this);
    finishCallback_ = 0;

    DestroyHeap(&heap_);
    DISPCNT = (DISPCNT & ~0x1f00) | 0x100;
    func_02074bd0(unk_194);
    func_02074bf4(unk_194);
    POWCNT = (screensSwapped_ << 15) | (POWCNT & ~0x8000);

    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    void* buffer = data_0211e33c;
    memset(buffer, 0, 0x600);
    CleanInvalidateCacheRange(buffer, 0x20);
    LoadToMainBG1CharacterData(buffer, 0, 0x20);
    CleanInvalidateCacheRange(buffer, 0x600);
    LoadToMainBG1ScreenData(buffer, 0, 0x600);
    DISPCNT = (mainLayers_ << 8) | (DISPCNT & ~0x1f00);
    DISPCNTSUB = (subLayers_ << 8) | (DISPCNTSUB & ~0x1f00);
    BackgroundLoader::GetInstance()->RemoveTask(func_ov023_021f6bb8(&objects_));
    BackgroundLoader::RemoveLockGlobal();
    func_0203b4e8(func_ov017_0218b5b0(), 0xc0);
}

void MenuScript::StartEntry(int entry)
{
    nextEntry_ = entry;
}

void MenuScript::RunScript()
{
    GameState* gameState = GameState::GetInstance();
    if (func_0200fb9c(gameState) == 6)
    {
        if (func_02012034(gameState) == 1)
        {
            idleTime_ += gameState->GetTickCount();
            if (idleTime_ > 3600)
            {
                idleTime_ = 0;
                nextEntry_ = Entry_TitleDemo;
                gameState->titleDemo_ = (unsigned char)(gameState->titleDemo_ + 1) % 3;
            }
        }
        else
        {
            idleTime_ = 0;
        }
    }

    if (nextEntry_ >= 0)
    {
        if (!func_ov017_021d4df8(&engine_, nextEntry_))
        {
            nextEntry_ = -1;
            return;
        }

        entry_ = nextEntry_;
        nextEntry_ = -1;
        func_ov017_021d4ce4(&engine_, entry_);
        if (engine_.stopped_ != 0)
            entry_ = -1;
        return;
    }

    if (entry_ < 0)
        return;

    func_ov017_021d4ccc(&engine_);
    if (engine_.stopped_ != 0)
        entry_ = -1;
}

void MenuScript::SetFlags(unsigned int flags)
{
    flags_ |= flags;
}

unsigned int MenuScript::GetFlags(unsigned int flags)
{
    return flags_ & flags;
}

MenuObjectList* MenuScript::GetObjects()
{
    return &objects_;
}

void MenuScript::SetLoadTask(int task)
{
    loadTask_ = task;
}

int MenuScript::GetLoadTask()
{
    return loadTask_;
}

void MenuScript::SetUnk1b0(unsigned short value)
{
    if (unk_1b0 != value)
        unk_1c8 = 1;
    unk_1b0 = value;
}

unsigned short MenuScript::GetUnk1b0()
{
    return unk_1b0;
}

void MenuScript::SetUnk1b2(unsigned short value)
{
    unk_1b2 = value;
}

unsigned short MenuScript::GetUnk1b2()
{
    return unk_1b2;
}

void MenuScript::SetCallbacks(Callback* callbacks, unsigned int count)
{
    callbacks_ = callbacks;
    callbackCount_ = count;
}

MenuScript::Callback* MenuScript::GetCallbacks(unsigned int* count)
{
    *count = callbackCount_;
    return callbacks_;
}

void MenuScript::RunCallback(unsigned int callback)
{
    if (callbacks_ == 0)
        return;
    if (callback == 0 || callbackCount_ <= callback)
        return;

    if (callbacks_[callback](this))
        callback_ = callback;
}

void MenuScript::UpdateCallbacks()
{
    if (callback_ != 0)
    {
        if (!callbacks_[callback_](this))
            callback_ = 0;
        return;
    }

    if (frameCallback_ != 0)
        callbacks_[frameCallback_](this);
}

void MenuScript::SetUnk1c8()
{
    unk_1c8 = 1;
}

void MenuScript::UpdateQuestion()
{
    if (yesEntry_ == 0 && noEntry_ == 0 && yesCallback_ == 0 && noCallback_ == 0)
        return;
    MessageSystem* messages = func_020421a0();
    if (messages->busy_ != 0)
        return;

    switch (func_020457e0(messages))
    {
        case 0:
            if (yesEntry_ != 0)
            {
                nextEntry_ = yesEntry_;
                yesEntry_ = 0;
                noEntry_ = 0;
            }
            if (yesCallback_ != 0)
            {
                RunCallback(yesCallback_);
                yesCallback_ = 0;
                noCallback_ = 0;
            }
            break;

        case 1:
            if (noEntry_ != 0)
            {
                nextEntry_ = noEntry_;
                yesEntry_ = 0;
                noEntry_ = 0;
            }
            if (noCallback_ != 0)
            {
                RunCallback(noCallback_);
                yesCallback_ = 0;
                noCallback_ = 0;
            }
            break;
    }
}

void MenuScript::ClearUnk1c8()
{
    unk_1c8 = 0;
}

int MenuScript::GetUnk1c8()
{
    return unk_1c8;
}

void MenuScript::SetAnswerCallbacks(int yes, int no)
{
    yesCallback_ = yes;
    noCallback_ = no;
}

void MenuScript::SetAnswerEntries(int yes, int no)
{
    yesEntry_ = yes;
    noEntry_ = no;
}

void MenuScript::SaveMainBanks()
{
    mainBanks_ = GetMainBGVRAMBanks();
}

void MenuScript::SaveSubBanks()
{
    subBanks_ = GetSubBGVRAMBanks();
}

void MenuScript::SetFinishCallback(void (*callback)(MenuScript* script))
{
    finishCallback_ = callback;
}
