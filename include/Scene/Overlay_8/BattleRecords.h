#pragma once

#include "GameState/PlayRecords.h"
#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"
#include "Scene/Overlay_23/GuideWindow.h"
#include "Text/TextTable.h"
#include "World/Object3D.h"

struct TitleScript;

// The records of another player, which tag mode received (see BattleRecords::guest_)
struct GuestRecords
{
    unsigned int hours1_ : 14;
    unsigned int unk_0_14 : 17;
    unsigned int unk_0_31 : 1;
    unsigned int hours2_ : 14;
    unsigned int unk_4_14 : 17;
    unsigned int unk_4_31 : 1;
    unsigned int minutes1_ : 7;
    unsigned int minutes2_ : 7;
    unsigned int unk_8_14 : 7;
    unsigned int unk_8_21 : 7;
    unsigned int unk_8_28 : 4;
    unsigned int unk_c_0 : 10;
    unsigned int unk_c_10 : 14;
    unsigned int unk_c_24 : 7;
    unsigned int unk_c_31 : 1;
    unsigned int unk_10_0 : 9;
    unsigned int unk_10_9 : 14;
    unsigned int unk_10_23 : 7;
    unsigned int unk_10_30 : 2;
    short title_;
    unsigned char female_ : 1;
    unsigned char unk_16_1 : 4;
    unsigned char unk_16_5 : 3;
    unsigned char unk_17;
};

// The flags of BattleRecords::flags_
#define RECORDS_TITLES 1
#define RECORDS_CLEARED 2
#define RECORDS_CLEAR_ITEM 4
#define RECORDS_CURSOR 8
#define RECORDS_SCROLL 0x10
#define RECORDS_MENU 0x20
#define RECORDS_TURN_BACK 0x40
#define RECORDS_NO_MODEL 0x80
#define RECORDS_COMMENT 0x100
#define RECORDS_SHOWN 0x200
#define RECORDS_COMMENTS 0x400
#define RECORDS_TIME1_CHANGED 0x800
#define RECORDS_TIME2_CHANGED 0x1000
#define RECORDS_ITEM_4 0x2000
#define RECORDS_DODGING 0x4000
#define RECORDS_FIRST_GUIDE 0x8000
#define RECORDS_ICON 0x10000
#define RECORDS_FADE 0x20000
#define RECORDS_TITLE_SHOWN 0x40000
#define RECORDS_SPRITES 0x80000
#define RECORDS_CLOSE 0x100000
#define RECORDS_BUSY 0x200000

// The battle records ("Kampfarchiv" in German, str_jr.gp2): the play time, the counts of the records and the titles,
// with the protagonist's 3D model and a menu of the records' kinds (0xb48 bytes). Overlay 17's scripts run it, and the
// guests' profiles of overlay 8 show another player's (see guest_)
struct BattleRecords
{
    typedef void (BattleRecords::*StateFunction)(unsigned int ticks);

    SafeAllocator allocator_;
    SafeAllocator backgroundAllocator_;
    SafeAllocator textAllocator_;
    SafeAllocator spriteAllocator_;
    SafeAllocator iconAllocator_;
    SafeAllocator modelAllocator_;
    SafeAllocator titleAllocator_;
    SafeAllocator guideAllocator_;
    // The texts of the screen (str_jr_<LG>.nat)
    TextTable texts_;
    // 0x960 bytes where the texts are written
    char* text_;
    // The titles of the guides (func_020a13c4 initializes it)
    char titleTable_[0x14];
    BackgroundGraphics backgrounds_[3];
    TextWindow window_;
    Canvas canvases_[6];
    // The pixels of the canvases
    void* pixels_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    SpriteAnimationList* animations_;
    // The icon of the last clear's title
    SpriteRenderer* iconRenderer_;
    Sprite* iconSprite_;
    // The kinds of the menu's items (0xff when empty)
    unsigned char items_[8];
    unsigned char itemCount_;
    WindowCursor cursor_;
    Object3D model_;
    // The camera (func_020a2010 initializes it)
    char camera_[0x2c8];
    TitleScript* titles_;
    GuideWindow* guide_;
    GuidePage* page_;
    // The state (see StateFunction) and its step
    signed char state_;
    unsigned char step_;
    // The step of LoadBackgrounds() and LoadIcon()
    unsigned char loadStep_;
    // What closed the records (0 to 7)
    unsigned char exit_;
    short title_;
    // The text of cmtFileTbl.bin
    short comment_;
    // RECORDS_*
    int flags_;
    int unk_b1c;
    int task_;
    // 1 when another player's records are shown
    int mode_;
    // The kind of item selected
    unsigned char kind_;
    // The first item shown
    unsigned char top_;
    unsigned char closed_;
    int titleX_;
    // Another player's: the name, the records, the texts of profstr and the titles
    const void* guest_;
    GuestRecords* guestRecords_;
    TextList* guestTexts_;
    TextTable* guestTitles_;
    PlayTime times_[2];

    void CreateAllocators(SafeAllocator* allocator);
    void Initialize();
    void Finish();
    int Update();
    void Draw1();
    void Draw3D();
    void Draw2();
    void Close();
    void SetState(signed char state);
    void State_Load(unsigned int ticks);
    void State_Setup(unsigned int ticks);
    void State_Guide(unsigned int ticks);
    void State_Main(unsigned int ticks);
    void State_FadeOut(unsigned int ticks);
    void State_Exit1(unsigned int ticks);
    void State_Exit2(unsigned int ticks);
    void State_Exit5(unsigned int ticks);
    void State_Exit7(unsigned int ticks);
    void State_Exit4(unsigned int ticks);
    void State_Exit3(unsigned int ticks);
    void State_Exit6(unsigned int ticks);
    void State_LastClear(unsigned int ticks);
    void State_Close(unsigned int ticks);
    void InitializeMenu();
    int UpdateMenu(int ticks);
    int GetTouchedItem(int x, int y);
    void InitializeItems();
    void TurnModel(unsigned int ticks);
    void UpdateAnimation(unsigned int ticks);
    void WriteTimes(ClearRecords* records);
    void WriteTime(char* text, int index, ClearRecords* records);
    void RefreshTime(int index);
    void UpdateTime(int index);
    void WriteTitle(ClearRecords* records);
    void WriteName(char* text, ClearRecords* records);
    void WriteCounts(ClearRecords* records);
    void WriteCountTexts(char* text, ClearRecords* records);
    void WriteMenu(ClearRecords* records);
    void WriteMenuTexts(char* text, int kind, ClearRecords* records);
    void DrawItems();
    void DrawCursor();
    void DrawArrows();
    void DrawBackButton();
    int LoadBackgrounds(int lastClear);
    int LoadIcon();
    void CheckClose();

    int IsFlagSet(int flag)
    {
        return flags_ & flag ? 1 : 0;
    }
};

typedef char BattleRecordsSizeCheck[sizeof(BattleRecords) == 0xb48 ? 1 : -1];
