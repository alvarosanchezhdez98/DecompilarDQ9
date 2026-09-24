#pragma once

#include "Bestiary/MonsterInfoScreen.h"
#include "Text/TextTable.h"

// The loaded mon_list_<LG>.nat, with every monster of the bestiary
struct MonsterList
{
    char unk_0[0x10];
};

// A menu loaded from a .gp2 file (bm_sml.gp2 for the bestiary). Its items are numbered across all its groups.
struct Menu
{
    char unk_0[0x2c];
    BackgroundGraphics* backgrounds_;
    char unk_30[6];
    // The item the cursor is on
    short cursor_;
    unsigned char unk_38;
    char unk_39;
    unsigned char unk_3a;
    char unk_3b[5];

    void SetBackgrounds(BackgroundGraphics* backgrounds)
    {
        backgrounds_ = backgrounds;
        unk_38 = 2;
    }
};

// The bestiary: menus to choose between all the monsters or one family, and a list of the monsters, 16 per page.
// The details of the monster the cursor is on are shown by the base class.
class MonsterListScreen : public MonsterInfoScreen
{
public:
    enum ListState
    {
        ListState_Setup,
        ListState_FadeIn,
        // Choose between all the monsters and one family
        ListState_SelectMode,
        ListState_SelectFamily,
        ListState_SelectMonster,
        ListState_FadeOut,
        ListState_Count,
    };

    MonsterList list_;
    SafeAllocator* listAllocators_;
    // The monsters that are listed, linked by MonsterListEntry::next_
    MonsterListEntry* entries_;
    // The first monster of the page that's shown
    MonsterListEntry* pageEntry_;
    Menu* menu_;
    BackgroundGraphics* backgrounds_;
    Canvas* canvases_;
    void* canvasBuffer_;
    // The cursor of the menu group that's being used
    short* cursor_;
    Sprite* listSprites_;
    SpriteAnimationList* animations_;
    MonsterRecord* records_;
    // str_sml_<LG>.nat
    TextTable textTable_;
    SpriteRenderer spriteRenderer_;
    char repeat_[0xc];
    unsigned short repeatButtons_;
    unsigned char unk_15a;
    char unk_15b;
    int unk_15c;
    // MENU_EVENT_* flags
    int menuEvents_;
    int ticks_;
    int listTaskID_;
    int listBackgroundTaskID_;
    // The menu group that's being used
    short group_;
    short modeCursor_;
    short familyCursor_;
    short monsterCursor_;
    // The item the cursor was on before the menu was updated
    short prevCursor_;
    unsigned char listState_;
    unsigned char listStep_;
    unsigned char listBackgroundStep_;
    // The family that's listed, or -1 for all the monsters
    signed char family_;
    unsigned char listFlags_;
    bool closing_;
    short numMonsters_;
    short variantIDs_[8];

    void Allocate(SafeAllocator* allocator);
    void Init();
    void Release();
    // Returns true when the screen is closed
    bool Update(int ticks);
    void Draw();
    void DrawMenu();
    void UpdateText();
    void Close();
    void DrawCursor();
    bool IsConfirmed();
    bool IsCanceled();
    bool ToggleOrder();
    void SelectEntry(MonsterListEntry* entry);
    void ScrollPages(int pages);
    MonsterListEntry* GetPageEntry(short page);
    MonsterListEntry* GetSelectedEntry();
    MonsterRecord* GetRecord(MonsterListEntry* entry);
    void MarkKnownMonsters();
    short CountEntries();
    short GetPage();
    void Setup();
    void FadeIn();
    void SelectMode();
    void SelectFamily();
    void SelectMonster();
    void FadeOut();
    void UpdateMenu();
    void ShowTitle();
    void ShowOrder();
    void UpdateList();
    void UpdateBackground();
    void FindVariants(short number);

    short GetNumPages()
    {
        return (CountEntries() + 15) / 16;
    }
};
