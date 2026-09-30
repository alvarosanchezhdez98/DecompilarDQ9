#pragma once

#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"
#include "Scene/Overlay_23/Layout.h"
#include "Text/TextTable.h"

struct Unknown_02075cdc;

// ItemInfoWindow::flags_
// Load the item's layout and texts (see ItemInfoWindow::UpdateLoad())
#define ITEM_INFO_WINDOW_LOAD 1
// The item's sprite is loaded
#define ITEM_INFO_WINDOW_SPRITE 2
// The item changes: its layout and its sprite are loaded again
#define ITEM_INFO_WINDOW_CHANGE 4
// The item's sprite isn't loaded yet
#define ITEM_INFO_WINDOW_NO_SPRITE 8
// Don't stop the music when the window closes
#define ITEM_INFO_WINDOW_KEEP_MUSIC 0x10
// Fade in the window when it's loaded
#define ITEM_INFO_WINDOW_FADE_IN 0x20
// Fade the window in and out
#define ITEM_INFO_WINDOW_FADE 0x40
// Keep the screens' brightness when the window closes
#define ITEM_INFO_WINDOW_KEEP_BRIGHTNESS 0x200
// Don't show where the item is found
#define ITEM_INFO_WINDOW_NO_PLACES 0x400
// The window shows the names of the party members (see ItemInfoWindow::SetName())
#define ITEM_INFO_WINDOW_NAMES 0x800
// A quest's item: its sprite is al_qu.spr and it has no description
#define ITEM_INFO_WINDOW_QUEST 0x1000
// The layout is loaded
#define ITEM_INFO_WINDOW_LAYOUT 0x2000
// ItemInfoWindow::State_Update() doesn't load the item's layout: MenuObjectClass10 does it in Draw3()
#define ITEM_INFO_WINDOW_NO_UPDATE 0x4000

// A sparkle on the sprite of a rare item (8 bytes)
struct ItemSparkle
{
    // Until it ends, and how long it lasts
    short timer_;
    short duration_;
    // Where it is on the sprite
    short x_;
    short y_;
};

// The sparkles on the sprite of a rare item (0x28 bytes)
struct ItemSparkles
{
    ItemSparkle sparkles_[3];
    // In milliseconds, when they last changed
    unsigned long long time_;
    // 0 to 39, which changes the colors of the stars of the item's rank
    short counter_;
    // Until another sparkle starts
    short delay_;
    unsigned char enabled_;

    void Initialize(int enabled);
    void Update();
};

// An entry of an ItemInfoTable (8 bytes): a place where the item is, or a monster that drops it
struct ItemInfoEntry
{
    unsigned char unk_0;
    unsigned char enabled_;
    short unk_2;
    const char* text_;
};

struct ItemInfoList
{
    short unk_0;
    short count_;
    ItemInfoEntry* entries_;
};

// The places where an item is found (itemplace2.nat), or the monsters that drop it (itemdrop2.nat), of
// data/prm/iteminfo_<LG>.gp2: func_020df828 initializes it, func_020df850 loads it and func_020df83c destroys it
struct ItemInfoTable
{
    char unk_0[8];
    ItemInfoList* list_;
    char unk_c[4];
};

// What can be found where an item is found: the text and what it is (8 bytes)
struct ItemPlace
{
    const char* text_;
    unsigned char kind_;

    ItemPlace& operator=(const ItemPlace& other);
};

// The window of the information on an item, which overlays 2, 3, 4, 5 and 6 show (and MenuObjectClass10): its
// sprite, its description, its stats, where it's found and which monsters drop it (0x79c bytes)
struct ItemInfoWindow
{
    // The layout's file
    SafeAllocator allocator_;
    // The texts' file (str_ii)
    SafeAllocator textAllocator_;
    // The places, the monsters and their names
    SafeAllocator infoAllocator_;
    // The sprites of the item: the one that it shows and the next one
    SafeAllocator* spriteAllocator_;
    SafeAllocator* nextSpriteAllocator_;
    // The sprites of the window (oiij or oiir)
    SafeAllocator* windowSpriteAllocator_;
    PartNameTable* names_;
    PartEntry* item_;
    PartEntry* nextItem_;
    TextTable texts_;
    ItemInfoTable places_;
    ItemInfoTable drops_;
    // The names of the fields (fldstr) and of the monsters (itm_mob)
    TextTable fieldNames_;
    TextTable monsterNames_;
    // The monsters that drop the item
    short monsters_[3];
    short numMonsters_;
    Unknown_02075cdc* sprite_;
    Unknown_02075cdc* nextSprite_;
    Layout layout_;
    // What func_02074af4 (main screen) or func_02074b64 (sub screen) saves, and func_02074bd0 or func_02074bf4
    // restores
    char screenState_[0x10];
    unsigned char unk_128;
    unsigned char unk_129;
    SpriteRenderer renderer_;
    Sprite sprites_[30];
    char description_[0x100];
    // The screen's layers before the window changed them
    int layers_;
    int task_;
    // The tasks of the item's sprite, of the layout, of the description, of the places, of the names of the fields,
    // of the monsters and of their names
    int tasks_[7];
    // The step of ItemInfoWindow::UpdateLoad(), or -1
    int loadStep_;
    int unk_758;
    // Where the next canvas goes in the VRAM of the screen's background
    unsigned int vramOffset_;
    unsigned int namesOffset_;
    unsigned int namesSize_;
    unsigned int statsOffset_;
    unsigned int statsSize_;
    short itemId_;
    short nextItemId_;
    // ITEM_INFO_WINDOW_*
    unsigned short flags_;
    // 0 while it opens, 1 while it's open, 2 while it closes, 3 when it's closed
    unsigned char state_;
    unsigned char step_;
    // The background when the item isn't equipment: none, bg_iidc or bg_iilist
    unsigned char background_;
    // The kind of the background that's loaded (see GetBackgroundKind())
    signed char backgroundKind_;
    // The party member that the stats are compared with, or -1
    signed char member_;
    // 1 when it's a window of a menu's script (MenuObjectClass10)
    signed char mode_;
    // 0 for the main screen, 1 for the sub one
    signed char screen_;
    // The window's sprites that are loaded (1: oiir, 2: oiij), and the ones that are loading
    signed char windowSprites_;
    signed char nextWindowSprites_;
    int windowSpriteTask_;
    // The names of the party members, with their numbers of items and the maximum
    const char* memberNames_[3];
    unsigned char memberCounts_[3];
    unsigned char memberMaxima_[3];
    unsigned char memberUnk_[3];
    unsigned char multiplier_;
    // Whether the layout is the equipment's
    signed char equipmentLayout_;
    // Its canvas buffer isn't the window's
    unsigned char externalBuffer_ : 1;
    // The window is on the same screen as a menu that it's shown in
    unsigned char inMenu_ : 1;

    void SetBuffer(void* buffer);
    void CreateAllocators(SafeAllocator* allocator);
    void Initialize(short item, signed char mode);
    void Finish();
    int Update();
    void DrawSprites();
    void Reset(SafeAllocator* allocator, short item, PartNameTable* names, unsigned short flags);
    void Close();
    void SetItem(short item);
    void ChangeItem(short item);
    void SetUpSubScreen();
    void RestoreScreen();
    static void ClearBackground();
    void SetInMenu(unsigned char inMenu);
    void ResetItem();
    void ClearNames();
    void SetName(int index, const char* name, unsigned char count, unsigned char maximum, unsigned char unk);
    void SetMultiplier(unsigned char multiplier);
    void DrawNames(Canvas* canvas);
    unsigned int DrawNameBox();
    void DrawArrow();
    void LoadWindowSprites(signed char sprites);
    void State_Open();
    void State_Update();
    void State_Close();
    void UpdateWindowSprites();
    void SetBrightness(int brightness, int frames);
    int IsFading();
    void DrawItemName();
    void DrawStats();
    void DrawResistances();
    void DrawDescription();
    void Draw();
    void UpdateLoad();
    int Load_Background();
    int Load_BackgroundWait();
    int Load_Sprite();
    int Load_SpriteWait();
    int Load_Layout();
    int Load_LayoutWait();
    int Load_Description();
    int Load_DescriptionWait();
    int Load_Places();
    int Load_PlacesWait();
    int Load_FieldNames();
    int Load_FieldNamesWait();
    int Load_Drops();
    int Load_DropsWait();
    int Load_MonsterNames();
    int Load_MonsterNamesWait();
    void DrawFields();
    void DrawMonsters();

    static void CancelTask(int* task);
};
