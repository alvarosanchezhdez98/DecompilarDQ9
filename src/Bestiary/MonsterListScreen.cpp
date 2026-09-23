#include "Bestiary/MonsterListScreen.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include <globaldefs.h>
#include <std_library_functions.h>

extern "C"
{
    // Returns the game's resources
    GameResources* func_0200fb8c(GameState* gameState);
    // Returns the language
    int func_0200fb08(GameState* gameState);
    // Returns whether the buttons were just pressed
    bool func_02012444(void* pad, int buttons);
    // Returns the position that's touched
    void func_02012a84(void* touch, int* x, int* y);
    // Initializes a sprite
    void func_0205a198(Sprite* sprite);
    // Initializes a sprite renderer
    void func_0205a444(SpriteRenderer* renderer);
    // Adds the sprite cells of a file to a sprite renderer
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    // Draws the sprites of a sprite renderer
    void func_0205ae8c(SpriteRenderer* renderer);
    // SpriteAnimationList functions
    void func_0205a234(SpriteAnimationList* list);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    // Plays a sound effect
    void func_0205eaa0(void* sound, int id, int);
    // Converts a string
    void func_0206819c(const char* input, char* output, int);
    // Returns the number of files in a .pac file
    int func_02046900(void* pac);
    // Returns a file of a .pac file
    void* func_020467f0(void* pac, int index, void** outName, unsigned int* outSize);
    // MonsterList functions
    void func_020972b0(MonsterList* list);
    void func_020972c8(MonsterList* list);
    void func_020972e0(MonsterList* list, SafeAllocator* allocator, void* file, unsigned int size);
    MonsterListEntry* func_02097418(MonsterList* list);
    int func_02097420(MonsterList* list);
    // Links the monsters of a family (all of them with -1), in the order that's chosen, and returns the first one
    MonsterListEntry* func_020974b0(MonsterList* list, int family, int, bool sort, int, short* outCount);
    void func_020abf60(MonsterList* list);
    // Reads the records of the monsters
    void func_020abf38(MonsterRecord* records);
    // TextTable functions
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, int id);
    // Returns the music player
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b30(void* music, int id, int);
    void func_02094b40(void* music);
    bool func_02094b4c(void* music);

    // BackgroundGraphics functions
    void func_0204af38(BackgroundGraphics* graphics, int, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b010(BackgroundGraphics* graphics, int);
    void func_0204b0e8(BackgroundGraphics* graphics, int);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b12c(BackgroundGraphics* graphics, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* graphics, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204b8d0(BackgroundGraphics* graphics, int, int, int, int, int, int, int, int);
    void func_0204b988(BackgroundGraphics* graphics, int, int, int, int);
    // Canvas functions
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* buffer, unsigned int size);
    bool func_0204c7e0(Canvas* canvas);

    // Menu functions
    void func_0207f7f0(Menu* menu, Canvas* canvases, int numCanvases);
    void func_0207f84c(Menu* menu);
    void func_0207f914(Menu* menu, SafeAllocator* allocator, const char* archive, const char* file);
    int func_0207f9f4(Menu* menu);
    void func_0207fc6c(Menu* menu, int ticks);
    void func_0207fcb8(Menu* menu);
    void func_0207fd00(Menu* menu);
    void func_0207fd44(Menu* menu);
    void func_0207fd88(Menu* menu);
    void func_0207fdcc(Menu* menu, short group);
    void func_0207fe80(Menu* menu, int, int, int);
    int func_020800fc(Menu* menu, short* cursor, short prevCursor, unsigned short buttons, unsigned char, bool);
    // Returns the first item of a group
    short func_02080468(Menu* menu, short group);
    void func_020804fc(Menu* menu, short group);
    void func_0208065c(Menu* menu, short group);
    void func_020806b0(Menu* menu, short item);
    void func_020806d8(Menu* menu, int, int, int, int);
    void func_02080798(Menu* menu, short item, int);
    void func_020809c4(Menu* menu, short group, short item, short* x, short* y);
    void func_02080b2c(Menu* menu, short item);
    void func_02080bac(Menu* menu, short group);
    void func_02080c68(Menu* menu, short group, int);
    bool func_02080d54(Menu* menu, short group, short x, short y);
    int func_02080dd4(Menu* menu, short group, short x, short y, bool* outConfirmed, int);
    // Sets the text of an item
    void func_02080f8c(Menu* menu, short item, const char* text);
    // Sets the number shown by an item
    void func_02080fa8(Menu* menu, short item, short value);
    void func_0208103c(Menu* menu, short item, short text);
    void func_0208108c(Menu* menu, short item);
    void func_02081130(Menu* menu, short group, bool);
    void func_02081164(Menu* menu, short group, int);
    void func_020813ec(Menu* menu, short group);
    Canvas* func_02081da8(Menu* menu, short group);
    void func_02081ee4(void* repeat, unsigned short* outButtons);
    void func_02081f20(void* repeat, int ticks);
    void func_0208203c(void* repeat);

    void func_0203b4d8(void*, int);
    void func_020c54a4(int, int, int, int);
    void func_020c5588(int, int, int, int, int);
    bool func_ov017_021959b4();

    extern char data_02108760[];
    extern char data_02114e30[];
    extern unsigned char data_02114e54[];
}

#define PAD_BUTTON_A 1
#define PAD_BUTTON_B 2
#define PAD_BUTTON_SELECT 4
#define PAD_BUTTON_X 0x400
#define PAD_BUTTON_Y 0x800

// Whether the touch screen is touched
#define TOUCHING (data_02114e54[0x55])

#define BLDCNTSUB 0x04001050

// Flags of MonsterListScreen::menuEvents_
#define MENU_EVENT_NEXT_PAGE 0x10
#define MENU_EVENT_PREVIOUS_PAGE 0x20

// Flags of MonsterListScreen::listFlags_
// The monsters are sorted by name instead of by number
#define LIST_FLAG_SORT 8
#define LIST_FLAG_LOADING_BACKGROUND 0x10
#define LIST_FLAG_40 0x40

// Groups of the menu
#define GROUP_MODES 1
#define GROUP_FAMILIES 2
#define GROUP_TITLE 3
#define GROUP_ORDER 4
#define GROUP_MONSTERS 5

// Items of the mode group
#define ITEM_ALL_MONSTERS 8
#define ITEM_FAMILIES 9
// The first item of the family group
#define ITEM_FIRST_FAMILY 0xb

#define MONSTERS_PER_PAGE 16
#define NUM_MONSTERS 0x134

// Sizes of the allocators in listAllocators_
static const unsigned int s_allocatorSizes[5] = { 0x6400, 0x2c00, 0x1400, 0x400, 0x400 };

void MonsterListScreen::Allocate(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;

    canvasBuffer_ = allocator->Allocate(0x4000);
    listSprites_ = (Sprite*)allocator->Allocate(8 * sizeof(Sprite));
    animations_ = (SpriteAnimationList*)allocator->Allocate(sizeof(SpriteAnimationList));
    listAllocators_ = (SafeAllocator*)allocator->Allocate(5 * sizeof(SafeAllocator));
    records_ = (MonsterRecord*)allocator->Allocate(NUM_MONSTERS * sizeof(MonsterRecord));
    for (unsigned char i = 0; i < 8; i++)
        func_0205a198(&listSprites_[i]);
    func_0205a234(animations_);
    for (int i = 0; i < 5; i++)
    {
        unsigned int size = s_allocatorSizes[i];
        listAllocators_[i].CreateTypeA(allocator->Allocate(size), size);
        listAllocators_[i].Reset();
    }
    for (unsigned short i = 0; i < NUM_MONSTERS; i++)
    {
        MonsterRecord* record = &records_[i];
        record->defeatCount_ = 0;
        record->complete_ = false;
        record->dropCount0_ = 0;
        record->dropCount1_ = 0;
    }
    menu_ = (Menu*)allocator->Allocate(sizeof(Menu));
    backgrounds_ = (BackgroundGraphics*)allocator->Allocate(2 * sizeof(BackgroundGraphics));
    canvases_ = (Canvas*)allocator->Allocate(4 * sizeof(Canvas));
    func_0207f84c(menu_);
    for (unsigned char i = 0; i < 2; i++)
        func_0204af64(&backgrounds_[i]);
    for (unsigned char i = 0; i < 4; i++)
        func_0204c684(&canvases_[i]);
    MonsterInfoScreen::Allocate(allocator);
}

void MonsterListScreen::Init()
{
    MonsterInfoScreen::Init();
    func_020972b0(&list_);
    listAllocators_ = NULL;
    entries_ = NULL;
    pageEntry_ = NULL;
    menu_ = NULL;
    backgrounds_ = NULL;
    canvases_ = NULL;
    canvasBuffer_ = NULL;
    cursor_ = NULL;
    listSprites_ = NULL;
    animations_ = NULL;
    records_ = NULL;
    func_020dfc40(&textTable_);
    func_0205a444(&spriteRenderer_);
    func_02081ee4(repeat_, &repeatButtons_);
    unk_15c = 0;
    menuEvents_ = 0;
    ticks_ = 0;
    listTaskID_ = -1;
    group_ = -1;
    modeCursor_ = -1;
    familyCursor_ = -1;
    monsterCursor_ = -1;
    prevCursor_ = -1;
    listState_ = ListState_Setup;
    listStep_ = 0;
    listBackgroundStep_ = 0;
    family_ = -1;
    listFlags_ = 0;
    closing_ = false;
    numMonsters_ = 0;
    memset(variantIDs_, 0, sizeof(variantIDs_));
}

void MonsterListScreen::Release()
{
    if (listTaskID_ >= 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(listTaskID_);
        listTaskID_ = -1;
    }
    void* music = func_02094a00();
    func_02094b40(music);
    func_02094ab0(music);
    func_020972c8(&list_);
    MonsterInfoScreen::Release();
    if (listAllocators_ == NULL)
        return;
    for (int i = 0; i < 5; i++)
    {
        if (listAllocators_[i].GetSignedAllocator() != NULL)
            listAllocators_[i].Destroy();
    }
}

bool MonsterListScreen::Update(int ticks)
{
    if (ticks == 0)
        ticks = 1;
    ticks_ = ticks;
    if (func_ov017_021959b4())
        Close();
    if (listState_ != ListState_Setup)
    {
        func_0207fc6c(menu_, ticks_);
        if (cursor_ != NULL)
        {
            func_02081f20(repeat_, ticks_);
            prevCursor_ = *cursor_;
            bool scrolls = false;
            if (listState_ == ListState_SelectMonster)
                scrolls = CountEntries() > MONSTERS_PER_PAGE;
            menuEvents_ = func_020800fc(menu_, cursor_, prevCursor_, repeatButtons_, unk_15a, scrolls);
            menu_->cursor_ = *cursor_;
            if (menuEvents_ != 0)
                func_020804fc(menu_, group_);
            if (prevCursor_ != *cursor_)
                func_020813ec(menu_, group_);
        }
    }
    MonsterInfoScreen::Update();
    UpdateBackground();

    // What Update() runs in each state
    static void (MonsterListScreen::*states[ListState_Count + 1])() = {
        &MonsterListScreen::Setup,
        &MonsterListScreen::FadeIn,
        &MonsterListScreen::SelectMode,
        &MonsterListScreen::SelectFamily,
        &MonsterListScreen::SelectMonster,
        &MonsterListScreen::FadeOut,
        NULL,
    };
    if (states[listState_] == NULL)
        return true;
    (this->*states[listState_])();
    return false;
}

void MonsterListScreen::Draw()
{
    if (listState_ != ListState_SelectMonster)
        return;
    MonsterInfoScreen::Draw();
}

void MonsterListScreen::DrawMenu()
{
    if (listState_ == ListState_Setup)
        return;
    func_0207fcb8(menu_);
    func_0207fd00(menu_);
    func_0207fe80(menu_, 1, 0, 1);
    func_0207fd44(menu_);
    DrawCursor();
}

void MonsterListScreen::UpdateText()
{
    if (listState_ != ListState_Setup)
        func_0207fd88(menu_);
    MonsterInfoScreen::UpdateText();
}

void MonsterListScreen::Close()
{
    if (closing_)
        return;
    closing_ = true;
    if (cursor_ != NULL)
        *cursor_ = -1;
    cursor_ = NULL;
    listState_ = ListState_FadeOut;
    listStep_ = 0;
}

void MonsterListScreen::DrawCursor()
{
    if (cursor_ == NULL || group_ < 0)
        return;
    Canvas* canvas = func_02081da8(menu_, group_);
    if (canvas == NULL || !func_0204c7e0(canvas))
        return;

    short x;
    short y;
    func_020809c4(menu_, group_, *cursor_, &x, &y);
    x -= 0x10;
    y -= 3;
    func_0205a370(animations_, 0);
    SpriteAnimation* animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
        animation->flags_ |= 8;
    func_0205a330(animations_, ticks_);
    short animationX;
    short animationY;
    animationY = y;
    animationX = x;
    animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
    {
        animation->x_ = animationX;
        animation->y_ = animationY;
    }
    func_0205ae8c(&spriteRenderer_);
}

bool MonsterListScreen::IsConfirmed()
{
    int x;
    int y;
    bool confirmed = false;
    if (func_02012444(data_02114e30, PAD_BUTTON_A | PAD_BUTTON_X))
        confirmed = true;
    if (TOUCHING && cursor_ != NULL)
    {
        func_02012a84(data_02114e54, &x, &y);
        int item = func_02080dd4(menu_, group_, x, y, &confirmed, 1);
        if (item < 0)
            return false;
        *cursor_ = item;
        if (prevCursor_ != *cursor_)
        {
            menu_->cursor_ = *cursor_;
            func_020813ec(menu_, group_);
        }
    }
    return confirmed;
}

bool MonsterListScreen::IsCanceled()
{
    bool canceled = false;
    if (func_02012444(data_02114e30, PAD_BUTTON_B))
        canceled = true;
    if (TOUCHING)
    {
        int x;
        int y;
        func_02012a84(data_02114e54, &x, &y);
        if (!func_02080d54(menu_, group_, x, y))
            canceled = true;
    }
    return canceled;
}

inline short TilesToPixels(short tiles)
{
    return tiles * 8;
}

bool MonsterListScreen::ToggleOrder()
{
    bool toggle = false;
    Canvas* canvas = func_02081da8(menu_, GROUP_ORDER);
    if (canvas != NULL && func_0204c7e0(canvas))
    {
        // The button starts a tile above its canvas
        short y = canvas->y_;
        short height = canvas->height_;
        y--;
        height++;
        short left = TilesToPixels(canvas->x_);
        short top = TilesToPixels(y);
        short right = left + TilesToPixels(canvas->width_);
        short bottom = top + TilesToPixels(height);
        if (TOUCHING)
        {
            int x;
            int y;
            func_02012a84(data_02114e54, &x, &y);
            if (left <= x && x < right && top <= y && y < bottom)
                toggle = true;
        }
    }
    if (func_02012444(data_02114e30, PAD_BUTTON_SELECT))
        toggle = true;
    if (toggle)
    {
        MonsterListEntry* entry = GetSelectedEntry();
        if (entry == NULL)
            return false;
        if (!entry->known_)
        {
            monsterCursor_ = -1;
            prevCursor_ = -1;
            entry = NULL;
        }
        if (listFlags_ & LIST_FLAG_SORT)
            listFlags_ &= ~LIST_FLAG_SORT;
        else
            listFlags_ |= LIST_FLAG_SORT;
        short count = 0;
        entries_ = func_020974b0(&list_, family_, -1, (listFlags_ & LIST_FLAG_SORT) != 0, 0x10, &count);
        SelectEntry(entry);
        func_0205eaa0(data_02108760, 1, 0);
        func_020804fc(menu_, GROUP_MONSTERS);
        ShowOrder();
        UpdateList();
    }
    return toggle;
}

void MonsterListScreen::SelectEntry(MonsterListEntry* entry)
{
    pageEntry_ = entries_;
    monsterCursor_ = 0x1b;
    if (menu_ != NULL)
        monsterCursor_ = func_02080468(menu_, GROUP_MONSTERS);
    if (entry == NULL)
        return;

    MonsterListEntry* current;
    MonsterListEntry* page;
    short index;
    MonsterListEntry* first;
    first = entries_;
    index = 0;
    current = first;
    page = first;
    for (; current != NULL; current = current->next_)
    {
        if (index % MONSTERS_PER_PAGE == 0)
        {
            page = current;
            index = 0;
        }
        if (current == entry)
            break;
        index++;
    }
    if (current == NULL)
    {
        index = 0;
        page = first;
    }
    monsterCursor_ += index;
    pageEntry_ = page;
}

void MonsterListScreen::ScrollPages(int pages)
{
    short numPages = GetNumPages();
    short page = GetPage();
    page += pages;
    if (page < 0)
        page = numPages + page;
    if (numPages <= page)
        page -= numPages;
    pageEntry_ = GetPageEntry(page);
}

MonsterListEntry* MonsterListScreen::GetPageEntry(short page)
{
    MonsterListEntry* entry = entries_;
    int index = 0;
    MonsterListEntry* pageEntry = entry;
    short pageIndex = 0;
    for (; entry != NULL; entry = entry->next_)
    {
        if (index == 0)
        {
            pageEntry = entry;
            if (pageIndex == page)
                break;
            pageIndex++;
        }
        index = (short)(index + 1) % MONSTERS_PER_PAGE;
    }
    return pageEntry;
}

MonsterListEntry* MonsterListScreen::GetSelectedEntry()
{
    Menu* menu = menu_;
    short selected = monsterCursor_ - func_02080468(menu, GROUP_MONSTERS);
    MonsterListEntry* entry = pageEntry_;
    short index = 0;
    while (entry != NULL)
    {
        if (selected == index || entry->next_ == NULL)
            break;
        index++;
        entry = entry->next_;
    }
    if (entry == NULL)
    {
        pageEntry_ = entries_;
        index = 0;
    }
    monsterCursor_ = func_02080468(menu, GROUP_MONSTERS) + index;
    if (entry != NULL)
    {
        FindVariants(entry->number_);
        variants_ = variantIDs_;
    }
    return entry;
}

MonsterRecord* MonsterListScreen::GetRecord(MonsterListEntry* entry)
{
    if (entry == NULL)
        return NULL;
    short index = entry->number_ - 1;
    if (index >= 0 && index < NUM_MONSTERS)
        return &records_[index];
    return NULL;
}

void MonsterListScreen::MarkKnownMonsters()
{
    MonsterListEntry* entries = func_02097418(&list_);
    unsigned short count = func_02097420(&list_);
    for (unsigned short i = 0; i < count; i++)
    {
        MonsterListEntry* entry = &entries[i];
        MonsterRecord* record = GetRecord(entry);
        if (record != NULL && record->defeatCount_ != 0)
            entry->known_ = true;
    }
}

short MonsterListScreen::CountEntries()
{
    short count = 0;
    for (MonsterListEntry* entry = entries_; entry != NULL; entry = entry->next_)
        count++;
    return count;
}

short MonsterListScreen::GetPage()
{
    MonsterListEntry* entry = entries_;
    short index = 0;
    for (; entry != NULL; entry = entry->next_)
    {
        if (entry == pageEntry_)
            return index / MONSTERS_PER_PAGE;
        index++;
    }
    return -1;
}

void MonsterListScreen::Setup()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (listStep_ == 0)
    {
        func_0203b4d8(func_ov017_0218b5b0(), 0x609fe);
        func_020c54a4(0, 0, 0, 0);
        func_020c5588(0, 0, 0x7fff, 0, 0);
        void* music = func_02094a00();
        func_02094ab0(music);
        func_02094b40(music);
        func_02094b30(music, 0x6a, 0);
        listStep_++;
    }
    else if (listStep_ == 1)
    {
        if (func_02094b4c(func_02094a00()))
            listStep_++;
    }
    else if (listStep_ == 2)
    {
        listTaskID_ = loader->QueueLoadFileInGP2("data/prm/mon_list.gp2", "mon_list_<LG>.nat", NULL);
        listStep_++;
    }
    else if (listStep_ == 3)
    {
        if (loader->GetTaskStatus(listTaskID_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(listTaskID_, &file, &size);
            if (file != NULL)
            {
                listAllocators_[0].Reset();
                func_020972e0(&list_, &listAllocators_[0], file, size);
            }
            loader->RemoveTask(listTaskID_);
            listTaskID_ = -1;
            listStep_++;
        }
    }
    else if (listStep_ == 4)
    {
        int count = func_02097420(&list_);
        MonsterListEntry* entry = func_02097418(&list_);
        for (int i = 0; i < count; i++, entry++)
        {
            char name[0x80] = {};
            func_0206819c(entry->name_, name, 0);
            sprintf((char*)entry->name_, name);
        }
        BG0CNTSUB = (BG0CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0x1d << 8);
        BG1CNTSUB = (BG1CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0x1e << 8);
        BG2CNTSUB = (BG2CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0x1f << 8) | (2 << 2);
        listFlags_ |= LIST_FLAG_LOADING_BACKGROUND;
        listStep_++;
    }
    else if (listStep_ == 5)
    {
        if (!(listFlags_ & LIST_FLAG_LOADING_BACKGROUND))
        {
            SafeAllocator* allocators = listAllocators_;
            allocators[2].Reset();
            func_0207f914(menu_, &allocators[2], "data/bin/menu/bm_sml.gp2", "bm_sml");
            listStep_++;
        }
    }
    else if (listStep_ == 6)
    {
        int status = func_0207f9f4(menu_);
        if (status == 0)
            listStep_++;
        if (status < 0)
            listState_ = ListState_Count;
    }
    else if (listStep_ == 7)
    {
        func_02080798(menu_, 6, 1);
        spriteRenderer_.unk_50 = 1;
        spriteRenderer_.SetSprites(listSprites_, 8);
        spriteRenderer_.animations_ = animations_;
        listTaskID_ = loader->QueueLoadFile("data/ani/obj_sml2.pac", NULL);
        listStep_++;
    }
    else if (listStep_ == 8)
    {
        if (loader->GetTaskStatus(listTaskID_))
        {
            void* name;
            void* file;
            unsigned int size;
            unsigned int cellsSize;
            SafeAllocator* allocators;
            int numFiles;
            loader->GetLoadedFileByID(listTaskID_, &file, &size);
            numFiles = func_02046900(file);
            allocators = listAllocators_;
            allocators[3].Reset();
            for (int i = 0; i < numFiles; i++)
            {
                void* cells = func_020467f0(file, i, &name, &cellsSize);
                if (cells != NULL)
                    func_0205a528(&spriteRenderer_, cells, cellsSize, &allocators[3]);
            }
            loader->RemoveTask(listTaskID_);
            listTaskID_ = -1;
            listStep_++;
        }
    }
    else if (listStep_ == 9)
    {
        func_020dfc40(&textTable_);
        listTaskID_ = loader->QueueLoadFileInGP2("data/bin/menu/str_sml.gp2", "str_sml_<LG>.nat", NULL);
        listStep_++;
    }
    else if (listStep_ == 10)
    {
        if (loader->GetTaskStatus(listTaskID_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(listTaskID_, &file, &size);
            if (file != NULL)
            {
                SafeAllocator* allocators = listAllocators_;
                allocators[4].Reset();
                func_020dfec0(&textTable_, &allocators[4], file, size);
            }
            loader->RemoveTask(listTaskID_);
            listTaskID_ = -1;
            listStep_ += 3;
        }
    }
    else if (listStep_ == 11)
        listStep_++;
    else if (listStep_ == 12)
        listStep_++;
    else if (listStep_ == 13)
    {
        func_020abf60(&list_);
        func_020abf38(records_);
        MarkKnownMonsters();
        BG0CNTSUB = (BG0CNTSUB & ~BGCNT_MASK_PRIORITY);
        BG1CNTSUB = (BG1CNTSUB & ~BGCNT_MASK_PRIORITY) | 1;
        BG2CNTSUB = (BG2CNTSUB & ~BGCNT_MASK_PRIORITY) | 2;
        BG3CNTSUB = (BG3CNTSUB & ~BGCNT_MASK_PRIORITY) | 3;
        DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | (0x17 << 8);
        ColorEffect_ConfigureAlphaBlend(BLDCNTSUB, BLEND_TARGET_BG1, BLEND_TARGET_BG2, 10, 6);
        menu_->SetBackgrounds(backgrounds_);
        func_0207f7f0(menu_, canvases_, 4);
        menu_->unk_3a = 0;
        func_020974b0(&list_, -1, -1, false, 0, &numMonsters_);
        short count = 0;
        entries_ = func_020974b0(&list_, family_, -1, (listFlags_ & LIST_FLAG_SORT) != 0, 0x10, &count);
        pageEntry_ = entries_;
        listState_ = ListState_FadeIn;
        listStep_ = 0;
    }
}

void MonsterListScreen::FadeIn()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (listStep_ == 0)
    {
        texts_ = &textTable_;
        UpdateMenu();
        group_ = GROUP_MODES;
        if (modeCursor_ < 0)
            modeCursor_ = func_02080468(menu_, group_);
        menu_->cursor_ = modeCursor_;
        func_020813ec(menu_, group_);
        listStep_++;
    }
    else if (listStep_ == 1)
    {
        SetBrightness(resources, 0, 8);
        listStep_++;
    }
    else if (listStep_ == 2)
    {
        if (!IsBrightnessTransitionActive(resources))
        {
            listState_ = ListState_SelectMode;
            listStep_ = 0;
        }
    }
}

void MonsterListScreen::SelectMode()
{
    if (listStep_ == 0)
    {
        if (!(listFlags_ & LIST_FLAG_LOADING_BACKGROUND))
        {
            short count = 0;
            entries_ = func_020974b0(&list_, family_, -1, (listFlags_ & LIST_FLAG_SORT) != 0, 0x10, &count);
            pageEntry_ = entries_;
            UpdateMenu();
            group_ = GROUP_MODES;
            if (modeCursor_ < 0)
                modeCursor_ = func_02080468(menu_, group_);
            menu_->cursor_ = modeCursor_;
            func_020813ec(menu_, group_);
            func_0208203c(repeat_);
            cursor_ = NULL;
            listStep_++;
        }
    }
    else if (listStep_ == 1)
    {
        cursor_ = &modeCursor_;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(repeat_);
            switch (*cursor_)
            {
            case ITEM_ALL_MONSTERS:
                listFlags_ |= LIST_FLAG_LOADING_BACKGROUND;
                listState_ = ListState_SelectMonster;
                listStep_ = 0;
                break;
            case ITEM_FAMILIES:
                listState_ = ListState_SelectFamily;
                listStep_ = 0;
                break;
            }
            func_0207fdcc(menu_, group_);
            cursor_ = NULL;
        }
        else if (IsCanceled() || func_02012444(data_02114e30, PAD_BUTTON_Y))
        {
            listState_ = ListState_FadeOut;
            listStep_ = 0;
        }
    }
}

void MonsterListScreen::SelectFamily()
{
    if (listStep_ == 0)
    {
        if (!(listFlags_ & LIST_FLAG_LOADING_BACKGROUND))
        {
            group_ = GROUP_FAMILIES;
            if (familyCursor_ < 0)
                familyCursor_ = func_02080468(menu_, group_);
            func_020813ec(menu_, group_);
            family_ = familyCursor_ - ITEM_FIRST_FAMILY;
            short count = 0;
            entries_ = func_020974b0(&list_, family_, -1, (listFlags_ & LIST_FLAG_SORT) != 0, 0x10, &count);
            pageEntry_ = entries_;
            UpdateMenu();
            listStep_++;
        }
    }
    else if (listStep_ == 1)
    {
        cursor_ = &familyCursor_;
        family_ = familyCursor_ - ITEM_FIRST_FAMILY;
        if (menuEvents_ != 0 || prevCursor_ != *cursor_)
        {
            short count = 0;
            entries_ = func_020974b0(&list_, family_, -1, (listFlags_ & LIST_FLAG_SORT) != 0, 0x10, &count);
            pageEntry_ = entries_;
            UpdateMenu();
        }
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(repeat_);
            if (CountEntries() != 0)
            {
                func_0207fdcc(menu_, group_);
                cursor_ = NULL;
                listState_ = ListState_SelectMonster;
                listStep_ = 0;
                listFlags_ |= LIST_FLAG_LOADING_BACKGROUND;
            }
        }
        else if (IsCanceled())
        {
            func_0207fdcc(menu_, group_);
            familyCursor_ = -1;
            family_ = -1;
            listState_ = ListState_SelectMode;
            listStep_ = 0;
        }
        else if (func_02012444(data_02114e30, PAD_BUTTON_Y))
        {
            func_0207fdcc(menu_, group_);
            familyCursor_ = -1;
            family_ = -1;
            listState_ = ListState_FadeOut;
            listStep_ = 0;
        }
    }
}

void MonsterListScreen::SelectMonster()
{
    if (listStep_ == 0)
    {
        if (listFlags_ & LIST_FLAG_LOADING_BACKGROUND)
            return;
        pageEntry_ = entries_;
        UpdateMenu();
        ShowTitle();
        ShowOrder();
        group_ = GROUP_MONSTERS;
        monsterCursor_ = func_02080468(menu_, group_);
        UpdateList();
        func_0208203c(repeat_);
        cursor_ = NULL;
        listStep_++;
        monster_ = NULL;
        prevMonster_ = NULL;
        MonsterListEntry* entry = GetSelectedEntry();
        LoadMonster(entry, GetRecord(entry), true);
        unk_82_3_ = true;
    }
    else if (listStep_ == 1)
    {
        cursor_ = &monsterCursor_;
        if (ToggleOrder())
        {
            if (prevCursor_ < 0)
            {
                MonsterListEntry* entry = GetSelectedEntry();
                if (entry->known_)
                    SetMonster(entry, GetRecord(entry));
                prevCursor_ = *cursor_;
            }
            return;
        }
        if (menuEvents_ != 0 || prevCursor_ != *cursor_)
        {
            if (menuEvents_ & MENU_EVENT_NEXT_PAGE)
                ScrollPages(1);
            else if (menuEvents_ & MENU_EVENT_PREVIOUS_PAGE)
                ScrollPages(-1);
            UpdateList();
            MonsterListEntry* entry = GetSelectedEntry();
            SetMonster(entry, GetRecord(entry));
        }
        if (IsConfirmed())
        {
            if (listFlags_ & LIST_FLAG_40)
            {
                MonsterListEntry* entry = GetSelectedEntry();
                SetMonster(entry, GetRecord(entry));
            }
            else
                NextAnimation();
        }
        else if (func_02012444(data_02114e30, PAD_BUTTON_Y))
            TogglePage();
        else if (IsCanceled())
        {
            flags_ &= ~4;
            if (family_ >= 0)
                listState_ = ListState_SelectFamily;
            if (family_ < 0)
                listState_ = ListState_SelectMode;
            monster_ = NULL;
            prevMonster_ = NULL;
            listFlags_ |= LIST_FLAG_LOADING_BACKGROUND;
            func_0207fdcc(menu_, group_);
            listStep_ = 0;
            cursor_ = NULL;
            func_0207fdcc(menu_, GROUP_ORDER);
            func_0207fdcc(menu_, GROUP_TITLE);
            CancelLoading();
        }
    }
}

void MonsterListScreen::FadeOut()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (listStep_ == 0)
    {
        SetBrightness(resources, -16, 8);
        listStep_++;
    }
    else if (listStep_ == 1)
    {
        if (!IsBrightnessTransitionActive(resources))
        {
            listState_ = ListState_Count;
            listStep_ = 0;
        }
    }
}

// Items that are hidden while choosing the mode, the monster and the family. Each list ends with -1.
static const short s_hiddenItems[3][11] = {
    { 6, 7, 0x2e, 0x2f, -1 },
    { 0, 1, 2, 3, 4, 5, 6, 0x2e, 0x2f, -1 },
    { 0, 1, 2, 4, 7, -1 },
};

void MonsterListScreen::UpdateMenu()
{
    int hidden = 0;
    if (listState_ == ListState_SelectMonster)
        hidden = 1;
    if (listState_ == ListState_SelectFamily)
        hidden = 2;
    func_020806d8(menu_, 0, 2, 1, 4);
    func_02080bac(menu_, 0);
    if (family_ >= 0)
        func_0208103c(menu_, 0x2f, family_ + 0x1e);

    short numKnown = 0;
    MonsterListEntry* entry = entries_;
    if (entry != NULL)
    {
        for (; entry != NULL; entry = entry->next_)
            numKnown += entry->known_;
    }

    short numMonsters = numMonsters_;
    short completion = 0;
    if (numMonsters != 0)
    {
        float value = (float)numKnown / (float)numMonsters;
        value *= 10000.0f;
        if (value < 100.0f)
            value = 100.0f;
        if (numKnown == 0)
            value = 0.0f;
        short percent = value;
        completion = percent / 100;
    }
    func_02080fa8(menu_, 4, completion);
    func_02080fa8(menu_, 5, numKnown);
    for (unsigned char i = 0;; i++)
    {
        short item = s_hiddenItems[hidden][i];
        if (item < 0)
            break;
        func_02080b2c(menu_, item);
    }
    func_02081164(menu_, 0, 1);
    func_020813ec(menu_, 0);
}

void MonsterListScreen::ShowTitle()
{
    short text = modeCursor_ + 0x10;
    if (modeCursor_ == ITEM_FAMILIES && familyCursor_ >= 0)
        text = familyCursor_ - 4;
    func_0208103c(menu_, 0x19, text);
    func_0208108c(menu_, 0x19);
    func_02081164(menu_, GROUP_TITLE, 1);
    func_02080c68(menu_, GROUP_TITLE, 1);
    func_020813ec(menu_, GROUP_TITLE);
}

void MonsterListScreen::ShowOrder()
{
    func_0208103c(menu_, 0x1a, ((listFlags_ & LIST_FLAG_SORT) != 0) + 0x1b);
    func_02080798(menu_, 0x1a, 1);
    func_02081164(menu_, GROUP_ORDER, 1);
    func_02080c68(menu_, GROUP_ORDER, 1);
    func_020813ec(menu_, GROUP_ORDER);
}

void MonsterListScreen::UpdateList()
{
    Menu* menu = menu_;
    menu->cursor_ = monsterCursor_;
    func_02080bac(menu, GROUP_MONSTERS);
    func_0208065c(menu, GROUP_MONSTERS);
    MonsterListEntry* entry = pageEntry_;
    short item = 0x1b;
    for (short i = 0; i < MONSTERS_PER_PAGE; item++, i++)
    {
        if (entry != NULL)
        {
            // The names of unknown monsters are hidden
            func_02080f8c(menu, item, func_020e0434(&textTable_, 0x15));
            if (entry->known_)
                func_02080f8c(menu_, item, entry->name_);
            entry = entry->next_;
        }
        else
        {
            func_020806b0(menu, item);
            func_02080b2c(menu, item);
        }
    }
    short count = CountEntries();
    func_02080fa8(menu, 0x2b, GetPage() + 1);
    func_02080fa8(menu, 0x2d, (count + MONSTERS_PER_PAGE - 1) / MONSTERS_PER_PAGE);
    func_02081130(menu, GROUP_MONSTERS, count > MONSTERS_PER_PAGE);
    func_020813ec(menu, GROUP_MONSTERS);
}

void MonsterListScreen::UpdateBackground()
{
    SafeAllocator* allocators;
    GameState* gameState = GameState::GetInstance();
    if (!(listFlags_ & LIST_FLAG_LOADING_BACKGROUND))
        return;

    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (listBackgroundStep_ == 0)
    {
        const char* file = "data/ani/bg_smlttl.pac";
        if (listState_ == ListState_SelectMonster)
            file = "data/ani/bg_smliti.pac";
        listBackgroundTaskID_ = loader->QueueLoadFile(file, NULL);
        listBackgroundStep_++;
    }
    else if (listBackgroundStep_ == 1)
    {
        if (!loader->GetTaskStatus(listBackgroundTaskID_))
            return;

        BackgroundGraphics graphics;
        void* name;
        void* file;
        unsigned int size;
        unsigned int dataSize;
        int numFiles;
        loader->GetLoadedFileByID(listBackgroundTaskID_, &file, &size);
        numFiles = func_02046900(file);
        allocators = listAllocators_;
        allocators[1].Reset();
        func_0204af64(&graphics);
        func_0204b11c(&graphics, 0);
        graphics.unk_1c_0_ = 1;
        graphics.unk_1c_4_ = 2;
        func_0204b5b4(&graphics, 2);
        func_0204b12c(&graphics, &allocators[1]);
        func_0204b5e8(&graphics, 0, 0);
        func_0204af38(&graphics, 5, &allocators[1]);
        for (int i = 1; i < numFiles; i++)
        {
            void* data = func_020467f0(file, i, &name, &dataSize);
            if (data != NULL)
                func_0204b174(&graphics, data, &allocators[1], dataSize);
        }
        loader->RemoveTask(listBackgroundTaskID_);
        listBackgroundTaskID_ = -1;

        // The title is written in the language of the game
        int language = func_0200fb08(gameState);
        int title = 0;
        switch (language)
        {
        case 2:
            title = 1;
            break;
        case 4:
            title = 2;
            break;
        case 3:
            title = 3;
            break;
        case 5:
            title = 4;
            break;
        }
        func_0204b010(&graphics, 0);
        func_0204b988(&graphics, 0, 0, 0, 0xffff);
        if (title != 0)
            func_0204b8d0(&graphics, title, 0, 0, 0x16, 2, 9, 2, 0xffff);
        func_0204b0e8(&graphics, 0);

        allocators[1].Reset();
        for (unsigned char i = 0; i < 2; i++)
        {
            BackgroundGraphics* background = &backgrounds_[i];
            func_0204af64(background);
            background->unk_1c_0_ = 1;
            background->unk_1c_4_ = i;
            func_0204b11c(background, 0);
            func_0204b5b4(background, i);
            func_0204b12c(background, &allocators[1]);
            func_0204b5e8(background, 0, 0);
        }
        void* data = func_020467f0(file, 0, &name, &dataSize);
        if (data != NULL)
            func_0204b174(backgrounds_, data, &allocators[1], dataSize);
        for (unsigned char i = 0; i < 2; i++)
        {
            BackgroundGraphics* background = &backgrounds_[i];
            func_0204b010(background, 0);
            func_0204b0e8(background, 0);
        }
        for (unsigned char i = 0; i < 4; i++)
        {
            Canvas* canvas = &canvases_[i];
            func_0204c684(canvas);
            func_0204c7a8(canvas, &allocators[1], canvasBuffer_, 0x600);
            canvas->background_ = backgrounds_;
        }
        listBackgroundStep_ = 0;
        listFlags_ &= ~LIST_FLAG_LOADING_BACKGROUND;
    }
}

void MonsterListScreen::FindVariants(short number)
{
    MonsterListEntry* entry = func_02097418(&list_);
    if (entry == NULL)
        return;
    int count = func_02097420(&list_);
    if (count == 0)
        return;
    memset(variantIDs_, 0, sizeof(variantIDs_));
    for (int i = 0; i < count; i++, entry++)
    {
        if (entry != NULL && entry->known_ && entry->number_ == number)
        {
            variantIDs_[0] = entry->monsterID_;
            return;
        }
    }
}
