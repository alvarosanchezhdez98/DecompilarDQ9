#pragma once

#include "GameState/Profile.h"
#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"
#include "Text/ForbiddenWordChecker.h"
#include "Text/TextTable.h"

// A loaded .bin file of texts: func_020727d8 initializes it, func_020728ac loads it and func_02072a68 returns a text
struct BinTextTable
{
    char unk_0[8];
};

// What func_ov023_021e7220 initializes: the windows of the profile editor, which overlay 23 runs
struct Unknown_021e7220
{
    char unk_0[0x5f4];
    BinTextTable* strings_;
    TextTable* texts_;
    void* unk_5fc;
    // The message being edited
    char* message_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    // The page of the card, and the card has two
    unsigned char unk_60c;
    unsigned char unk_60d;
    char unk_60e[0x614 - 0x60e];
};

// A key of a keyboard's layout (0x14 bytes)
struct KeyboardKey
{
    short x_;
    short y_;
    const char* text_;
    const char* shiftedText_;
    unsigned char flags_;
    unsigned char unk_d;
    unsigned char size_;
    unsigned char unk_f;
    char unk_10[4];
};

// A keyboard's layout (keyboard_pr.bin), which overlay 3 has: func_ov003_0215e6d8 initializes it
struct KeyboardLayout
{
    KeyboardKey* keys_;
    char unk_4[2];
    short count_;
    char unk_8[8];
};

// The keyboard of overlay 3: func_ov003_0215efb8 initializes it and func_ov003_0215f000 updates it
struct Keyboard
{
    // The selected key
    KeyboardKey* key_;
    KeyboardLayout* layout_;
    // The text that it edits
    char* text_;
    int unk_c;
    int size_;
    int unk_14;
    int unk_18;
    short unk_1c;
    unsigned char unk_1e;
    unsigned char unk_1f;
    unsigned char unk_20;
    unsigned char unk_21;
    unsigned char unk_22;
    unsigned char unk_23;
    unsigned char unk_24;
    char unk_25[3];

    void SetText(char* text, int size)
    {
        text_ = text;
        size_ = size;
    }
};

// Overlay 12, the editor of the player's profile (for tag mode): its message, title and accolade, which overlay 17
// runs. Overlay 17 calls Initialize(), Load() and Update() until it returns nonzero, then Finish()
struct ProfileEditor
{
    void* unk_0;
    void* unk_4;
    // func_02074af4 initializes it
    char unk_8[0x10];
    unsigned char unk_18;
    unsigned char unk_19;
    char unk_1a[2];
    // The main screen's enabled backgrounds (bits 8 to 12 of DISPCNT) before the editor
    int planes_;
    SafeAllocator allocators_[7];
    TextWindow window_;
    BackgroundGraphics backgrounds_[3];
    Canvas canvases_[13];
    Unknown_021e7220 windows_;
    BinTextTable strings_;
    TextTable texts_;
    SpriteRenderer* renderer_;
    void* unk_1360;
    Sprite* sprites_;
    SpriteRenderer* renderer2_;
    Sprite* sprites2_;
    unsigned char step_;
    unsigned char state_;
    char unk_1372[2];
    char* text_;
    const char* unk_1378;
    void* pixels_;
    // The BackgroundLoader tasks of the files
    int tasks_[6];
    int unk_1398;
    int result_;
    unsigned char unk_13a0;
    char unk_13a1[3];
    int unk_13a4;
    signed char unk_13a8;
    signed char unk_13a9;
    unsigned char unk_13aa;
    unsigned char unk_13ab;
    void* unk_13ac;
    char* name_;
    void* unk_13b4;
    unsigned int unk_13b8;
    void* unk_13bc;
    signed char* unk_13c0;
    unsigned short unk_13c4_0 : 5;
    unsigned short unk_13c4_5 : 11;
    char unk_13c6[2];
    unsigned short* unk_13c8;
    unsigned int* unk_13cc;
    char* message_;
    unsigned int selection_;
    int selections_[6];
    int unk_13f0;
    unsigned int design_;
    unsigned int unk_13f8;
    // The birthday being edited
    unsigned short year_;
    unsigned char month_;
    unsigned char day_;
    char accoladeText_[0x40];
    char titleText_[0x40];
    ForbiddenWordChecker checker_;
    unsigned char finished_;
    unsigned char unk_14bd;
    char unk_14be[2];

    void SetCanvasColors(int canvas, int color, int shadow);
    void Initialize();
    void LoadProfile();
    void Load(SafeAllocator* allocator);
    int Update(int input);
    void Draw1();
    void Draw2();
    void Finish();
    void DrawItemText(unsigned char item, int selected);
    void UpdateText();
    void LoadStrings();
    void LoadSentences();
    void LoadTexts();
    void LoadBackgrounds();
    void LoadSprites();
    void LoadSprites2();
    void State_Load();
    void State_Menu();
    void State_TitleCategory();
    void State_Title0();
    void State_Title1();
    void State_Title2();
    void State_06();
    void State_07();
    void State_08();
    void State_09();
    void State_0a();
    void State_0b();
    void State_0c();
    void State_0d();
    void State_0e();
    void State_Finish();
    void RefreshCard(int animate, int design, int keepPage);
    int FormatCard(ProfileData* profile);
    void SelectItem(int cancel);
    void SetItemWindow(unsigned char item, short x, short y);
    void OpenMenu();
    void OpenTitleCategories();
    void OpenTitles0();
    void OpenTitles1();
    void OpenTitles2();
    void OpenQuestion();
    void OpenBirthday();
    void OpenAccoladeKinds();
    void OpenAccolades0();
    void OpenAccolades1();
    void OpenDesigns();
    void OpenMessage();
    void Text_01(char* text, int hidden);
    void Text_02(char* text, int hidden);
    void Text_03(char* text, int hidden);
    void Text_04(char* text, int hidden);
    void Text_05(char* text, int hidden);
    void Text_06(char* text, int hidden);
    void Text_07(char* text, int hidden);
    void Text_08(char* text, int hidden);
    void Text_09(char* text, int hidden);
    void Text_0a(char* text, int hidden);
    void Text_0b(char* text, int hidden);
    void Text_0c(char* text, int hidden);
    void Text_0d(char* text, int hidden);
    void Text_0e(char* text, int hidden);

    // In overlay 23 (ProfileEditorDisplay.cpp)
    void UpdateDateArrows();
    void ShowDateItems(unsigned char state, unsigned char year, unsigned char month, unsigned char day);
    int GetTouchedDateArrow();
    int UpdateTouchedPage();
    void RefreshAccoladeTexts();
    void ResetAccoladeTexts();
    void DrawCursorAnimation();
    void DrawDateArrows();
    void DrawDateMarker();
    void DrawMarker();
    void DrawKey();
    void DrawKeyText();
    int IsConfirmed();
    int IsCancelled();
    void SetItemGrid();
};
