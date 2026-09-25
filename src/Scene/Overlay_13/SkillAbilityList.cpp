#include "Scene/Overlay_13/SkillUpScreen.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "System/Cache.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include <globaldefs.h>
#include <std_library_functions.h>

#define BLDCNT (*(volatile unsigned short*)0x04000050)
#define BLDCNTSUB (*(volatile unsigned short*)0x04001050)

// What func_0204af14 returns: one of a background's layers
struct BackgroundLayer
{
    char unk_0[0xc];
    void* characters_;
};

// An ability and its skill points, which func_020749ac sorts
struct SortedAbility
{
    int id_;
    float points_;
};

extern "C"
{
    // Returns a party member
    void* func_0200ff1c(GameState* gameState, int member);
    // Returns the width of a text
    int func_020420e8(const char* text, bool large);
    // The text system
    void* func_020421a0();
    // Writes a message to the buffer
    void func_02046608(void* messages, int, int message, char* buffer, unsigned int size, int, int);
    void* func_020467f0(void* pac, int index, void** outName, unsigned int* outSize);
    int func_02046900(void* pac);
    void func_0204ae44(BackgroundLayer* layer, int);
    BackgroundLayer* func_0204af14(BackgroundGraphics* graphics, int layer);
    void func_0204af38(BackgroundGraphics* graphics, int, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b0e8(BackgroundGraphics* graphics, void* characters);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b12c(BackgroundGraphics* graphics, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* graphics, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204b988(BackgroundGraphics* graphics, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    // Draws a text to a canvas
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, unsigned char size, unsigned char color,
                       short* outX, short* outY, bool large);
    // A party member's data
    PartyMemberData* func_02053c6c(void* member);
    void func_0205a198(Sprite* sprite);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* data, unsigned int size, SafeAllocator* allocator);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_020727d8(SkillNameTable* names);
    void func_020728ac(SkillNameTable* names, SafeAllocator* allocator, void* file, unsigned int size, int, int, int);
    const char* func_02072a68(SkillNameTable* names, int skill);
    // Sorts the abilities by their skill points
    void func_020749ac(SortedAbility* abilities, int first, int last, int);
    void func_02074af4(void*);
    void func_02074b64(void*);
    void func_02074bd0(void*);
    void func_02074bf4(void*);
    void func_0208df10(SkillAbilityTable* abilities);
    void func_0208df20(SkillAbilityTable* abilities, SafeAllocator* allocator, void* file, unsigned int size,
                       short* skills, int numSkills);
    SkillAbility* func_0208e024(SkillAbilityTable* abilities, int skill, int index);
    SkillAbility* func_0208e06c(SkillAbilityTable* abilities, short id);
    // The music player
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b38(void* music, int);
    void func_020dc7e8(int, int);
    // The skill of a vocation
    signed char func_020dd11c(unsigned char vocation, unsigned char index);
    void func_020e4864(const char* text, char* buffer, int, int, int, int);
}


void SkillAbilityList::Setup(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    allocators_ = (SafeAllocator*)allocator->Allocate(5 * sizeof(SafeAllocator));
    for (unsigned char i = 0; i < 5; i++)
    {
        SafeAllocator* allocators = allocators_;
        allocators[i].ResetAllocatorPointer();
        unsigned int size = sAllocatorSizes[i];
        allocators[i].CreateTypeA(allocator->Allocate(size), size);
    }
}

void SkillAbilityList::Initialize(unsigned char screen)
{
    allocators_ = NULL;
    func_0208df10(&abilities_);
    func_020727d8(&names_);
    unk_24 = 0;
    unk_25 = 0;
    func_0204af64(&background_);
    task_ = -1;
    screen_ = screen;
    loaded_ = false;
    step_ = 0;
    member_ = -1;
    skill_ = 0;
    flags_ = 0;
    spriteRenderer_ = NULL;
    sprites_ = NULL;
    markerX_ = NULL;
    markerY_ = NULL;
    markerPalettes_ = NULL;
    markerSprite_ = -1;
    if (screen_ == 0)
    {
        func_02074af4(unk_14);
        planes_ = (DISPCNT & 0x1f00) >> 8;
    }
    else
    {
        func_02074b64(unk_14);
        planes_ = (DISPCNTSUB & 0x1f00) >> 8;
    }
}

void SkillAbilityList::Finish()
{
    void* music = func_02094a00();
    func_02094b38(music, 0x68);
    func_02094ab0(music);
    if (screen_ == 0)
    {
        BackgroundLayer* layer = func_0204af14(&background_, 0);
        void* characters;
        if (layer != NULL && (characters = layer->characters_) != NULL)
        {
            memset(characters, 0, 0x600);
            CleanInvalidateCacheRange(characters, 0x20);
            LoadToMainBG1CharacterData(characters, 0, 0x20);
            func_0204b0e8(&background_, characters);
        }
        func_02074bd0(unk_14);
        DISPCNT = (DISPCNT & ~0x1f00) | (planes_ << 8);
    }
    else
    {
        func_02074bf4(unk_14);
        DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | (planes_ << 8);
    }
    if (task_ >= 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(task_);
        task_ = -1;
    }
    if (allocators_ == NULL)
        return;
    for (unsigned char i = 0; i < 5; i++)
    {
        allocators_[i].Destroy();
    }
}

void SkillAbilityList::Update()
{
    if (flags_ & 1)
        Reload();
    if (screen_ == 1)
        DrawMarkers();
}

bool SkillAbilityList::Load()
{
    SafeAllocator* allocators;
    if (loaded_)
        return true;
    bool result = true;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        SafeAllocator* allocators = allocators_;
        allocators[4].Reset();
        spriteRenderer_ = (SpriteRenderer*)allocators[4].Allocate(sizeof(SpriteRenderer));
        sprites_ = (Sprite*)allocators[4].Allocate(13 * sizeof(Sprite));
        markerX_ = (short*)allocators[4].Allocate(13 * sizeof(short));
        markerY_ = (short*)allocators[4].Allocate(13 * sizeof(short));
        markerPalettes_ = (unsigned char*)allocators[4].Allocate(13);
        func_0205a444(spriteRenderer_);
        spriteRenderer_->unk_50 = screen_;
        spriteRenderer_->SetSprites(sprites_, 13);
        for (int i = 0; i < 13; i++)
        {
            func_0205a198(&sprites_[i]);
        }
        for (int i = 0; i < 10; i++)
        {
            markerX_[i] = -1;
            markerY_[i] = -1;
            markerPalettes_[i] = 2;
        }
        task_ = loader->QueueLoadFile("data/ani/obj_sklup_i.pac", NULL);
        result = false;
        step_++;
    }
    else if (step_ == 1)
    {
        if (loader->GetTaskStatus(task_))
        {
            SafeAllocator* allocators = allocators_;
            void* name;
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            int numFiles = func_02046900(file);
            for (int i = 0; i < numFiles; i++)
            {
                unsigned int dataSize;
                void* data = func_020467f0(file, i, &name, &dataSize);
                func_0205a528(spriteRenderer_, data, dataSize, &allocators[4]);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
        result = false;
    }
    else if (step_ == 2)
    {
        loader->MaybeFreeAllocations();
        task_ = loader->QueueLoadFileInGP2("data/bin/str_sklc.gp2", "str_sklc_<LG>.bin", NULL);
        result = false;
        step_++;
    }
    else if (step_ == 3)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            SafeAllocator* allocators = allocators_;
            allocators[3].Reset();
            func_020728ac(&names_, &allocators[3], file, size, 0, 0, 0);
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
        result = false;
    }
    else if (step_ == 4)
    {
        func_0208df10(&abilities_);
        loader->MaybeFreeAllocations();
        task_ = loader->QueueLoadFileInGP2("data/prm/sklname.gp2", "sklname_<LG>.bin", NULL);
        result = false;
        step_++;
    }
    else if (step_ == 5)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            SafeAllocator* allocators = allocators_;
            allocators[2].Reset();
            short* skills = NULL;
            short vocationSkills[5] = {};
            void* member = func_0200ff1c(GameState::GetInstance(), member_);
            if (member != NULL)
            {
                PartyMemberData* data = func_02053c6c(member);
                if (data != NULL)
                {
                    for (unsigned char i = 0; i < 5; i++)
                    {
                        vocationSkills[i] = func_020dd11c(data->vocation_, i);
                    }
                    skills = vocationSkills;
                }
            }
            func_0208df20(&abilities_, &allocators[2], file, size, skills, 5);
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
        result = false;
    }
    else if (step_ == 6)
    {
        SafeAllocator* allocator = allocators_;
        allocator->Reset();
        unsigned char palettes[2] = {1, 0};
        func_0204af64(&background_);
        background_.unk_1c_0_ = screen_;
        background_.unk_1c_4_ = palettes[screen_];
        func_0204b5b4(&background_, 0);
        func_0204b11c(&background_, 0);
        func_0204b5e8(&background_, 0, 0);
        func_0204b12c(&background_, allocator);
        func_0204af38(&background_, 1, allocator);
        if (screen_ == 0)
        {
            DISPCNT = (DISPCNT & ~0x1f00) | 0x1200;
            BLDCNT = 0;
        }
        else
        {
            BG0CNTSUB = (BG0CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0xf << 8);
            BLDCNTSUB = 0;
        }
        result = false;
        step_++;
    }
    else if (step_ == 7)
    {
        loader->MaybeFreeAllocations();
        task_ = loader->QueueLoadFile("data/ani/bg_skn.pac", NULL);
        result = false;
        step_++;
    }
    else if (step_ == 8)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            void* name;
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            int numFiles = func_02046900(file);
            allocators = allocators_;
            allocators[1].Reset();
            for (int i = 0; i < numFiles; i++)
            {
                unsigned int dataSize;
                data = func_020467f0(file, i, &name, &dataSize);
                if (data != NULL)
                {
                    if (i == 0)
                    {
                        Canvas canvas;
                        func_0204c684(&canvas);
                        canvas.unk_b4 = 0xa;
                        canvas.unk_b6 = 0xb;
                        canvas.width_ = 0x20;
                        canvas.height_ = 0x18;
                        canvas.pixels_ = (char*)data + 0x10;
                        Draw(&canvas);
                    }
                    func_0204b174(&background_, data, &allocators[1], dataSize);
                }
            }
            loader->RemoveTask(task_);
            task_ = -1;
            BackgroundLayer* layer = func_0204af14(&background_, 0);
            if (layer != NULL)
                func_0204ae44(layer, member_);
            func_0204b988(&background_, 0, 0, 0, 0xffff);
            func_0204b0e8(&background_, NULL);
            loaded_ = true;
            step_ = 0;
            if (screen_ == 0)
                func_020dc7e8(4, -1);
            else
                func_020dc7e8(3, -1);
        }
        result = false;
    }
    return result;
}

void SkillAbilityList::DrawMarkers()
{
    if (spriteRenderer_ == NULL)
        return;
    if (flags_ & 1)
        return;
    if (markerSprite_ < 0)
        return;
    Sprite* sprite = &sprites_[markerSprite_];
    for (int i = 0; i < 10; i++)
    {
        short x = markerX_[i];
        short y;
        if (x >= 0 && (y = markerY_[i]) >= 0)
        {
            sprite->x_ = x << 12;
            sprite->y_ = y << 12;
            sprite->unk_22 = i + 0x20;
            sprite->unk_26 = 0;
            sprite->unk_25 = markerPalettes_[i];
            func_0205ac40(spriteRenderer_, sprite);
        }
    }
}

void SkillAbilityList::Select(int member, unsigned int skill)
{
    if (member_ == member && skill_ == skill)
        return;
    // The party has 4 members
    bool valid;
    if (member >= 0 && member <= 3)
        valid = true;
    else
        valid = false;
    if (!valid)
        return;
    if (skill >= 5)
        return;
    member_ = member;
    skill_ = skill;
    if (task_ >= 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(task_);
        task_ = -1;
    }
    flags_ |= 1;
    step_ = 0;
}

void SkillAbilityList::Reload()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            markerX_[i] = -1;
            markerY_[i] = -1;
            markerPalettes_[i] = 2;
        }
        markerSprite_ = -1;
        loader->MaybeFreeAllocations();
        task_ = loader->QueueLoadFile("data/ani/bg_skn.pac", NULL);
        step_++;
    }
    else if (step_ == 1)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* name;
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            func_02046900(file);
            unsigned int dataSize;
            void* data = func_020467f0(file, 0, &name, &dataSize);
            if (data != NULL)
            {
                Canvas canvas;
                func_0204c684(&canvas);
                canvas.pixels_ = (char*)data + 0x10;
                canvas.unk_b4 = 0xa;
                canvas.unk_b6 = 0xb;
                canvas.width_ = 0x20;
                canvas.height_ = 0x18;
                Draw(&canvas);
                func_0204b174(&background_, data, NULL, dataSize);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            BackgroundLayer* layer = func_0204af14(&background_, 0);
            if (layer != NULL)
                func_0204ae44(layer, member_);
            func_0204b988(&background_, 0, 0, 0, 0xffff);
            func_0204b0e8(&background_, NULL);
            step_ = 0;
            flags_ &= ~1;
        }
    }
}

const int SkillAbilityList::sTitleY = 12;
const int SkillAbilityList::sLineHeight = 15;
const int SkillAbilityList::sAbilityX = 46;

// The icons of the abilities that have a marker, in the order of the marker's sprites
static const signed char sMarkedIcons[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, -1};

// What each allocator can hold
const unsigned int SkillAbilityList::sAllocatorSizes[5] = {0xa00, 0xa00, 0xc00, 0x400, 0x800};

void SkillAbilityList::Draw(Canvas* canvas)
{
    int color;
    if (canvas == NULL)
        return;
    void* member = func_0200ff1c(GameState::GetInstance(), member_);
    if (member == NULL)
        return;
    PartyMemberData* data = func_02053c6c(member);
    if (data == NULL)
        return;
    int skill = func_020dd11c(data->vocation_, skill_);
    unsigned char points = data->skillPoints_[skill];
    int y = 0x1e;
    const char* name = func_02072a68(&names_, skill);
    short outX;
    short outY;
    func_0204f41c(canvas, (0x100 - func_020420e8(name, false)) >> 1, sTitleY, name, 0xa, 0xf, &outX, &outY, false);

    SortedAbility abilities[10];
    memset(abilities, 0, sizeof(abilities));
    for (unsigned char i = 0; i < 10; i++)
    {
        SortedAbility* sorted = &abilities[i];
        SkillAbility* ability = func_0208e024(&abilities_, skill, i);
        if (ability != NULL)
        {
            sorted->id_ = ability->id_;
            sorted->points_ = ability->points_;
        }
    }
    func_020749ac(abilities, 0, 9, 0);

    SkillAbility* first = func_0208e06c(&abilities_, abilities[0].id_);
    for (int i = 0; sMarkedIcons[i] >= 0; i++)
    {
        if (sMarkedIcons[i] == first->icon_)
        {
            markerSprite_ = i;
            break;
        }
    }

    for (unsigned char i = 0; i < 10; i++)
    {
        color = 3;
        SkillAbility* ability = func_0208e06c(&abilities_, abilities[i].id_);
        if (ability != NULL)
        {
            int needed = ability->points_;
            if (points >= needed)
                color = 0xf;
            char text[0x20] = {};
            sprintf(text, "%d", needed);
            func_0204f41c(canvas, 0x22 - func_020420e8(text, false), y, text, 0xa, color, &outX, &outY, false);
            char message[0x100] = {};
            char formatted[0x100] = {};
            func_02046608(func_020421a0(), 0xa, ability->message_, message, 0x100, 0, 0);
            func_020e4864(message, formatted, 1, 0, 0, 0);
            if (ability->marked_ && markerSprite_ >= 0)
            {
                markerX_[i] = func_020420e8(formatted, false) + sAbilityX;
                markerY_[i] = y - 2;
                if (color == 0xf)
                    markerPalettes_[i] = 1;
            }
            func_0204f41c(canvas, sAbilityX, y, formatted, 0xa, color, &outX, &outY, false);
            y += sLineHeight;
        }
    }
}
