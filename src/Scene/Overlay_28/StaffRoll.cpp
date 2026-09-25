#include "Scene/Overlay_28/StaffRoll.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Graphics/Background.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "Resource/ResourceMutex.h"
#include "System/Cache.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include "System/Timing.h"
#include "System/VCountAlarm.h"
#include <globaldefs.h>
#include <std_library_functions.h>

#define BG1OFS (*(volatile unsigned int*)0x04000014)
#define BG1OFSSUB (*(volatile unsigned int*)0x04001014)

extern "C"
{
    // The pad
    extern char data_02114e30[];

    // The game's resources
    GameResources* func_0200fb8c(GameState* gameState);
    // Returns whether the buttons are held
    bool func_02012430(void* pad, int buttons);
    int func_0203b498(GameResources* resources);
    void func_0203b4a0(GameResources* resources, int);
    void func_0203b4b0(GameResources* resources, int);
    int func_0203b4d0(GameResources* resources);
    void func_0203b4d8(GameResources* resources, int);
    void func_0203b4e8(GameResources* resources, int);
    int func_0203b508(GameResources* resources);
    void func_0203b510(GameResources* resources, int);
    void func_0203b520(GameResources* resources, int);
    // Returns the width of a text
    int func_020420e8(const char* text, bool large);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b2e0(BackgroundGraphics* graphics, void* file);
    void func_0204b3a0(BackgroundGraphics* graphics, void* file);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204c684(Canvas* canvas);
    // Draws a text to a canvas
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, unsigned char size, unsigned char color,
                       short* outX, short* outY, bool large);
    void func_02074af4(void*);
    void func_02074bd0(void*);
    // The music player
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b34(void* music, int, int, int, int);
    bool func_02094b4c(void* music);
    void func_020979c0(void*);
    void func_02097b34(void*);
    void func_02097bc4(void*, int);
    void func_02097c18(void*, int, int, int, int, int, int, int);
    void func_020dc2bc();
}

// In this order, the compiler's sort lays them out like the original (see tools/data_order.py)
const unsigned int StaffRoll::sCharacterDataSize2 = 0x8000;
const unsigned int StaffRoll::sScriptBufferSize = 0x5000;
const unsigned int StaffRoll::sScreenDataSize = 0x800;
const unsigned int StaffRoll::sBufferSize = 0xa000;
const unsigned int StaffRoll::sCharacterDataSize = 0x8000;
const unsigned int StaffRoll::sScreenEntries = 0x400;
const unsigned int StaffRoll::sCharacterDataSize3 = 0x8000;

static void InitializeCanvas(Canvas* canvas, void* pixels)
{
    func_0204c684(canvas);
    canvas->pixels_ = pixels;
    canvas->x_ = 0;
    canvas->y_ = 0;
    canvas->width_ = 0x20;
    canvas->height_ = 0x20;
    canvas->unk_a0 = 0;
}

void StaffRollScroll::Advance(float pixels)
{
    position_ += (int)(4096.0f * (2.0f * pixels));
    pending_ += (int)(4096.0f * (2.0f * pixels));
}

void StaffRollScroll::ClearPassedRows(void* characters)
{
    if ((pending_ >> 12) >= 0x20u)
    {
        Canvas canvas;
        InitializeCanvas(&canvas, characters);
        memset((char*)characters + ((unsigned char)((position_ - pending_) >> 12) >> 3 << 10), 0x11111111, 0x1000);
        pending_ -= 0x20 << 12;
        dirty_ = true;
    }
}

void StaffRoll::Setup(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    buffer_ = (char*)allocator->AllocateReversed(sBufferSize) + 0x1000;
    allocator_.ResetAllocatorPointer();
    allocator_.CreateTypeA(allocator->AllocateReversed(sScriptBufferSize), sScriptBufferSize);
}

void StaffRoll::Initialize()
{
    lines_.Initialize();
    unk_1c = 0;
    unk_1d = 0;
    func_020979c0(unk_20);
    buffer_ = NULL;
    allocator_.ResetAllocatorPointer();
    mainPlanes_ = (DISPCNT & 0x1f00) >> 8;
    subPlanes_ = (DISPCNTSUB & 0x1f00) >> 8;
    scroll_.position_ = 0;
    scroll_.nextGroup_ = 0;
    scroll_.nextLine_ = 0;
    scroll_.pending_ = 0;
    scroll_.dirty_ = false;
    taskID_ = -1;
    unk_74 = 0;
    unk_78 = 0;
    unk_7c = 0;
    state_ = State_Load;
    step_ = 0;
}

void StaffRoll::Finish()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    SetBrightness(resources, -16, 0);
    BG1OFS = 0;
    BG1OFSSUB = 0;
    if (allocator_.GetSignedAllocator() != NULL)
        allocator_.Destroy();
    func_02097b34(unk_20);
    func_02074bd0(unk_c);
    if (buffer_ != NULL)
    {
        memset(buffer_, 0, 0x20);
        CleanInvalidateCacheRange(buffer_, 0x20);
        LoadToMainBG1CharacterData(buffer_, 0, 0x20);
    }
    lines_.Clear();
    func_0203b4b0(resources, -1);
    func_0203b4e8(resources, -1);
    func_0203b520(resources, -1);
    func_0203b4a0(resources, unk_74);
    func_0203b4d8(resources, unk_78);
    func_0203b510(resources, unk_7c);
    DISPCNT = (DISPCNT & ~0x1f00) | (mainPlanes_ << 8);
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | (subPlanes_ << 8);
    Initialize();
}

bool StaffRoll::Update(int frames)
{
    void (StaffRoll::*states[])(int) = {&StaffRoll::Load, &StaffRoll::Scroll, &StaffRoll::ScrollOut, NULL};
    if (states[state_] == NULL)
        return true;
    (this->*states[state_])(frames);
    return false;
}

void StaffRoll::Load(int frames)
{
    void* music = func_02094a00();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (step_ == 0)
    {
        func_02094ab0(music);
        func_02094b34(music, 0x7a, 0x20b, 0, 0);
        step_++;
    }
    else if (step_ == 1)
    {
        if (func_02094b4c(music))
            step_++;
    }
    else if (step_ == 2)
    {
        func_020dc2bc();
        func_02074af4(unk_c);
        unk_74 = func_0203b498(resources);
        unk_78 = func_0203b4d0(resources);
        unk_7c = func_0203b508(resources);
        func_0203b4d8(resources, 0x90);
        char* buffer = buffer_;
        func_02097bc4(unk_20, 2);
        func_02097c18(unk_20, 2, 0, 0, 0, 0, 0x180, 0);
        BG1CNTSUB = (BG1CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1000;
        BackgroundGraphics graphics;
        func_0204af64(&graphics);
        graphics.unk_1c_0_ = 1;
        graphics.unk_1c_4_ = 1;
        func_0204b11c(&graphics, 0);
        func_0204b5e8(&graphics, 0, 0);
        void* font = (void*)resources->unknown_2c;
        func_0204b2e0(&graphics, font);
        func_0204b3a0(&graphics, font);
        unsigned short color = 0x67f5;
        memcpy(buffer, &color, sizeof(color));
        CleanInvalidateCacheRange(buffer, sizeof(color));
        LoadToSubBGStandardPalette(buffer, 0xa, sizeof(color));
        for (unsigned short i = 0; i < sScreenEntries; i++)
            ((unsigned short*)buffer)[i] = i;
        CleanInvalidateCacheRange(buffer, sScreenDataSize);
        LoadToSubBG1ScreenData(buffer, 0, sScreenDataSize);
        memset(buffer, 0x11111111, sCharacterDataSize);
        CleanInvalidateCacheRange(buffer, sCharacterDataSize);
        LoadToSubBG1CharacterData(buffer, 0, sCharacterDataSize);
        memset(buffer_, 0x11111111, sCharacterDataSize);
        CleanInvalidateCacheRange(buffer_, sCharacterDataSize);
        BG0CNTSUB = (BG0CNTSUB & ~BGCNT_MASK_PRIORITY) | 1;
        BG1CNTSUB = BG1CNTSUB & ~BGCNT_MASK_PRIORITY;
        BG2CNTSUB = (BG2CNTSUB & ~BGCNT_MASK_PRIORITY) | 2;
        BG3CNTSUB = (BG3CNTSUB & ~BGCNT_MASK_PRIORITY) | 3;
        DISPCNT = (DISPCNT & ~0x1f00) | 0x1100;
        DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x200;
        step_++;
    }
    else if (step_ == 3)
    {
        taskID_ = loader->QueueLoadFile("data/evspt_lv5/staffroll.bin", NULL);
        step_++;
    }
    else if (step_ == 4)
    {
        if (loader->GetTaskStatus(taskID_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(taskID_, &file, &size);
            if (file != NULL && size != 0)
            {
                allocator_.Reset();
                lines_.Load(&allocator_, file, size);
            }
            loader->RemoveTask(taskID_);
            taskID_ = -1;
            step_++;
        }
    }
    else if (step_ == 5)
    {
        step_++;
        SetBrightness(resources, 0, 30);
    }
    else if (step_ == 6)
    {
        if (!IsBrightnessTransitionActive(resources))
        {
            state_ = State_Scroll;
            step_ = 0;
        }
    }
}

void StaffRoll::Draw()
{
    if (state_ != State_Load && buffer_ != NULL)
    {
        BG1OFSSUB = 0x1ff0000 & ((unsigned int)((scroll_.position_ >> 12) << 24) >> 8);
        if (scroll_.dirty_)
        {
            CleanInvalidateCacheRange(buffer_, sCharacterDataSize);
            LoadToSubBG1CharacterData(buffer_, 0, sCharacterDataSize);
            CleanCacheRange(buffer_, sCharacterDataSize);
        }
        scroll_.dirty_ = false;
    }
}

void StaffRoll::Scroll(int frames)
{
    // Declared in this order, the variables get the original's registers
    float speed;
    char* characters;
    short group;
    short x;
    int width;
    bool done;
    bool large;
    unsigned char y;
    StaffRollLine* line;
    short position[2];
    Canvas canvas;
    speed = lines_.speed_;
    scroll_.Advance(0.5f * ((float)frames * speed));
    scroll_.ClearPassedRows(buffer_);
    characters = buffer_;
    group = -1;
    while (true)
    {
        line = lines_.Get(scroll_.nextLine_);
        if (line == NULL)
        {
            // The original places the other exit's code after the loop, which only a goto gives
            done = true;
            goto end;
        }
        if (group != line->group_)
        {
            if ((scroll_.position_ >> 12) + 0xc0u < line->height_ + (scroll_.nextGroup_ >> 12))
                break;
            scroll_.nextGroup_ += line->height_ << 12;
        }
        y = scroll_.nextGroup_ >> 12;
        large = false;
        if (line->size_ == 12)
            large = true;
        x = 0;
        if (line->alignment_ != 0)
        {
            width = func_020420e8(line->text_, large);
            x = 0x88;
            switch (line->alignment_)
            {
            case 1:
                x = (0x100 - width) >> 1;
                break;
            case 2:
                x = 0x78 - width;
                break;
            }
        }
        InitializeCanvas(&canvas, characters);
        int size = line->size_;
        canvas.unk_b4 = size;
        canvas.unk_b6 = size + 1;
        func_0204f41c(&canvas, x, y, line->text_, line->size_, line->color_, &position[0], &position[1], large);
        if (y + line->size_ > 0x100)
            func_0204f41c(&canvas, x, y - 0x100, line->text_, line->size_, line->color_, &position[0], &position[1], large);
        scroll_.nextLine_++;
        scroll_.dirty_ = true;
        group = line->group_;
    }
    done = false;
end:
    func_02012430(data_02114e30, 0x2000);
    if (done)
    {
        state_ = State_ScrollOut;
        step_ = 0;
    }
}

void StaffRoll::ScrollOut(int frames)
{
    float speed = lines_.speed_;
    scroll_.Advance(0.5f * ((float)frames * speed));
    scroll_.ClearPassedRows(buffer_);
    if ((scroll_.nextGroup_ >> 12) + 0x10u <= (scroll_.position_ >> 12))
    {
        state_ = State_End;
        step_ = 0;
    }
}

void TimedStaffRoll::Initialize()
{
    StaffRoll::Initialize();
    start_ = now_ = 0;
    previousFrames_ = frames_ = 0;
    setupTime_ = elapsed_ = 0;
    draw_ = false;
}

void TimedStaffRoll::Finish()
{
    draw_ = false;
    previousFrames_ = frames_ = 0;
    start_ = now_ = 0;
    setupTime_ = elapsed_ = 0;
    StaffRoll::Finish();
}

void TimedStaffRoll::Setup(SafeAllocator* allocator)
{
    StaffRoll::Setup(allocator);
    start_ = now_ = 0;
    previousFrames_ = frames_ = 0;
    draw_ = false;
    setupTime_ = GetCurrentTimestamp();
}

void TimedStaffRoll::Update()
{
    if (state_ == State_Load)
        return;
    previousFrames_ = frames_;
    now_ = GetCurrentTimestamp();
    frames_ = (now_ - start_) * 60 / 523656;
    if (frames_ == previousFrames_)
        return;
    StaffRoll::Update(frames_ - previousFrames_);
    draw_ = !draw_;
    elapsed_ = now_ - setupTime_;
}

void TimedStaffRoll::Load()
{
    unsigned char state = state_;
    if (state != State_Load)
        return;
    StaffRoll::Update(2);
    if (state == State_Load && state_ == State_Scroll)
    {
        start_ = GetCurrentTimestamp();
        frames_ = 0;
    }
}

static void OnVCount(void* arg)
{
    TimedStaffRoll* staffRoll = (TimedStaffRoll*)arg;
    if (staffRoll == NULL)
        return;
    bool operational = SetResourceMutexOperational(false);
    if (!staffRoll->draw_)
    {
        staffRoll->Update();
    }
    else
    {
        staffRoll->Draw();
        staffRoll->draw_ = !staffRoll->draw_;
    }
    SetResourceMutexOperational(operational);
}

void StartStaffRoll(SafeAllocator* allocator)
{
    gStaffRoll.Initialize();
    gStaffRoll.Setup(allocator);
    func_020c93bc(&gStaffRollAlarm);
    func_020c93d0(&gStaffRollAlarm, 0xd7, 0x1e, OnVCount, &gStaffRoll);
}

void StopStaffRoll()
{
    func_020c949c(&gStaffRollAlarm);
    gStaffRoll.Finish();
}

void LoadStaffRoll()
{
    gStaffRoll.Load();
}

unsigned int GetStaffRollMilliseconds()
{
    return gStaffRoll.elapsed_ * 64 / TIMER_TICKS_PER_MILLISECOND;
}
