#pragma once

#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"
#include "Text/TextTable.h"

// A party member's data, which func_02053c6c returns
struct PartyMemberData
{
    char unk_0[0x16c];
    // The level of each vocation
    unsigned short levels_[0xd];
    // For each vocation
    unsigned char unk_186[0xd];
    char unk_193[0x464 - 0x193];
    // The points spent on each skill
    unsigned char skillPoints_[0x100];
    // The skill points that aren't spent yet
    unsigned short unspentSkillPoints_;
    char unk_566[0x950 - 0x566];
    int vocation_;
};

// An ability that a skill teaches, from sklname_<LG>.bin
struct SkillAbility
{
    short id_;
    unsigned short unk_2_0 : 2;
    // The skill points that it needs
    unsigned short points_ : 7;
    unsigned short icon_ : 6;
    // The ability has a marker on the list
    unsigned short marked_ : 1;
    // The message of its name
    int message_;
};

// The abilities that each skill teaches (sklname_<LG>.bin): func_0208df10 initializes it, func_0208df20 loads it,
// func_0208e024 returns a skill's abilities and func_0208e06c an ability by its ID
struct SkillAbilityTable
{
    char unk_0[8];
};

// The names of the skills (str_sklc_<LG>.bin): func_020727d8 initializes it, func_020728ac loads it and func_02072a68
// returns a name
struct SkillNameTable
{
    char unk_0[8];
};

// The second class of overlay 13, *likely* the panel of the skill up screen that lists the abilities of the selected
// skill and the points that they need. The caller (overlays 2 and 23) runs Setup(), Initialize(), Load() until it
// returns true, Select() when the skill changes, Update() each frame and Finish()
struct SkillAbilityList
{
    // What each file is loaded to: the background's screen, its characters, the abilities, the names and the sprites
    SafeAllocator* allocators_;
    SkillNameTable names_;
    SkillAbilityTable abilities_;
    // func_02074af4 (main screen) and func_02074b64 (sub screen) initialize it
    char unk_14[0x10];
    unsigned char unk_24;
    unsigned char unk_25;
    char unk_26[2];
    BackgroundGraphics background_;
    // The markers of the abilities (obj_sklup_i.pac), on the sub screen
    SpriteRenderer* spriteRenderer_;
    Sprite* sprites_;
    short* markerX_;
    short* markerY_;
    unsigned char* markerPalettes_;
    // The BackgroundLoader's task
    int task_;
    // The displayed backgrounds, to restore
    unsigned int planes_;
    // 0: the main screen, 1: the sub screen
    unsigned char screen_;
    bool loaded_;
    unsigned char step_;
    // The party member and which of their vocation's skills is shown
    signed char member_;
    unsigned char skill_;
    // 1: the list is loaded again
    unsigned char flags_;
    // The marker's sprite
    signed char markerSprite_;

    // Where the texts are drawn, in pixels: the skill's name, and the abilities' lines
    static const int sTitleY;
    static const int sLineHeight;
    static const int sAbilityX;
    static const unsigned int sAllocatorSizes[5];

    void Setup(SafeAllocator* allocator);
    void Initialize(unsigned char screen);
    void Finish();
    void Update();
    bool Load();
    void DrawMarkers();
    void Select(int member, unsigned int skill);
    void Reload();
    void Draw(Canvas* canvas);
};

// A party member's name and status
struct PartyMemberStatus
{
    char name_[0x30];
    unsigned short unk_30;
    unsigned short unk_32;
    unsigned short unk_34;
    unsigned short unk_36;
    unsigned short unk_38;
};

// A party member, which func_0200ff1c returns: func_02053c6c returns their data
struct PartyMember
{
    char unk_0[0x130];
    unsigned short* unk_130;
    PartyMemberStatus* status_;
    unsigned short* unk_138;
};

// What the caller of SkillPointMenu::Initialize() has: its window, which the menu copies on the sub screen
struct SkillPointMenuParent
{
    char unk_0[0x178];
    void* unk_178;
    char unk_17c[0xc];
    TextWindow window_;
};

// The first class of overlay 13, *likely* the skill up screen's menu that spends a party member's skill points on
// the skills of their vocation. It runs on the main screen, or on the sub screen when Initialize() gets the window of
// the caller (overlays 2 and 23), which runs Setup(), Initialize(), SetMember(), Update() until it returns State_End,
// Apply() and Finish(); overlay 0 runs Draw() and UpdateMessage()
struct SkillPointMenu
{
    enum State
    {
        State_Load,
        // Spending the points
        State_Allocate,
        // The message that the points were spent, or on the sub screen that they weren't
        State_Message,
        // Whether to finish: without spending the points (State_Confirm), or spending them (State_ConfirmApply)
        State_Confirm,
        State_ConfirmApply,
        State_Finish,
        State_End,
    };

    // The buttons that choose an item, and the size of the vocation's icon
    static const int sConfirmButtons;
    static const unsigned int sIconSize;

    SafeAllocator allocator_;
    // The time since the previous frame
    int elapsed_;
    SpriteRenderer* spriteRenderer_;
    unsigned short cursorAnimation_;
    // Where the member's name ends
    short nameEnd_;
    // func_02074af4 (main screen) and func_02074b64 (sub screen) initialize it
    char unk_20[0x10];
    unsigned char unk_30;
    unsigned char unk_31;
    // The displayed backgrounds, to restore
    unsigned int planes_;
    TextWindow window_;
    BackgroundGraphics backgrounds_[2];
    Canvas canvases_[3];
    TextMenu menu_;
    SafeAllocator textAllocator_;
    // str_su_<LG>.nat
    TextTable texts_;
    unsigned char unk_638[4];
    unsigned char state_;
    unsigned char previousState_;
    unsigned char step_;
    bool stateChanged_;
    // The menu runs on the sub screen
    bool subScreen_;
    unsigned int ticks_;
    // What the window returns: 2 when it's touched
    int windowInput_;
    int previousWindowInput_;
    // The BackgroundLoader's task
    int task_;
    // The canvases' pixels
    void* canvasPixels_;
    // The message system's buffer, which the windows' texts are written to
    char* text_;
    // The selected skill, and 5 for the end of the list
    int selection_;
    // 0: the points are spent, 1: they aren't
    int confirmSelection_;
    // The points are spent when the menu finishes
    bool apply_;
    unsigned char unk_665;
    // The member's skill points that aren't spent yet, before and after this menu
    int availablePoints_;
    int remainingPoints_;
    // The most points of a skill
    int maxPoints_;
    // The points of each skill, and those added to it
    int points_[5];
    int addedPoints_[5];
    // The points of the skill can't change
    unsigned char locked_[5];
    PartyMemberStatus* status_;
    unsigned char vocation_;
    unsigned char skills_[5];
    unsigned int level_;
    unsigned char unk_6b4;
    unsigned int unk_6b8;
    // 1: the cursor is drawn
    unsigned char flags_;
    unsigned short unk_6be;
    unsigned short unk_6c0;
    unsigned short unk_6c2;
    unsigned short unk_6c4;
    unsigned short unk_6c6;
    unsigned short unk_6c8;
    unsigned short unk_6ca;

    void Initialize(SkillPointMenuParent* parent);
    void Finish();
    unsigned char Update(int elapsed);
    void Draw();
    void UpdateMessage();
    void SetMember(PartyMember* member);
    void Apply(PartyMember* member);
    void Setup(SafeAllocator* allocator);
    void Load();
    void OpenPointsWindow();
    void WritePoints(char* text);
    void ShowMessage();
    void OpenMessageWindow();
    void WriteMessage(char* text);
    void OpenMenu();
    void OpenConfirmWindow();
    void WriteConfirm(char* text);
    void OpenMemberWindow();
    void WriteMember(char* text);
    void UpdateAllocate();
    void UpdateMessageMain();
    void UpdateConfirmMain();
    void UpdateMessageSub();
    void UpdateConfirmSub();
    void RefreshPoints();
    void RefreshConfirm();
    // Hides a canvas of the window, or shows it: the first one's text is written again
    void SetCanvasHidden(int index, int hidden);
    void DrawCursor();
    void DrawIcon();
};
