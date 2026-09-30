#pragma once

#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"
#include "Text/TextTable.h"

// A page of a GuideWindow (0x244 bytes): a title and a text
struct GuidePage
{
    unsigned int unk_0_0 : 9;
    unsigned int unk_0_9 : 9;
    unsigned int unk_0_18 : 9;
    unsigned int unk_0_27 : 3;
    // How the title is laid out (0 to 2)
    unsigned int layout_ : 2;
    // The text, which the message system formats
    const char* text_;
    int unk_8;
    char title_[0x38];
    // What text_ points to, when the page has its own text
    char buffer_[0x200];
};

// The flags of GuideWindow
#define GUIDE_WINDOW_REDRAW_TITLE 1
#define GUIDE_WINDOW_TITLE_CHANGED 2
#define GUIDE_WINDOW_MESSAGE_WINDOW 4
#define GUIDE_WINDOW_MAIN_SCREEN 8
#define GUIDE_WINDOW_PAUSE_MUSIC 0x10
#define GUIDE_WINDOW_NO_DIMMING 0x20
#define GUIDE_WINDOW_OPENING 0x40
#define GUIDE_WINDOW_TITLE_SCROLLING 0x80
#define GUIDE_WINDOW_SHOWN 0x100
#define GUIDE_WINDOW_SKIPPED 0x200
#define GUIDE_WINDOW_UNK_400 0x400
#define GUIDE_WINDOW_UNK_800 0x800

// A window of pages of titled texts that several overlays show over their screens (str_tg.gp2, bg_tm.pac): the
// guides of the game (0x44c bytes). The caller runs CreateAllocators(), Initialize(), SetPages(), then Update(),
// Draw1() and Draw2() each frame, and Finish()
struct GuideWindow
{
    // The states: loading, showing the pages and closing
    typedef void (GuideWindow::*StateFunction)();

    // 4 allocators: the main screen's backgrounds, the sub screen's, the texts and the sprites
    SafeAllocator* allocators_;
    // The texts of the window (str_tg_<LG>.nat)
    TextTable texts_;
    // The text that the window writes (MessageSystem::unk_5c)
    char* text_;
    GuidePage* pages_;
    int count_;
    // The page shown
    unsigned char page_;
    char unk_29;
    // func_02074af4 (main screen) and func_02074b64 (sub screen) initialize it
    char unk_2a[0x10];
    unsigned char unk_3a;
    unsigned char unk_3b;
    // What the screens showed before, which Finish() restores
    unsigned int mainLayers_;
    unsigned int subLayers_;
    BackgroundGraphics backgrounds_[2];
    BackgroundGraphics subBackgrounds_[2];
    TextWindow window_;
    Canvas canvases_[3];
    // The pixels of the canvases
    void* pixels_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    SpriteAnimationList* animations_;
    // Which screens it uses (0, 1, 2, 6 or 7)
    unsigned char type_;
    unsigned char state_;
    unsigned char step_;
    // The step of the title's animations
    unsigned char titleStep_;
    int task_;
    // GUIDE_WINDOW_*
    unsigned short flags_;
    short titleY_;
    unsigned char ticks_;
    unsigned char titleBackground_;
    short titleScroll_;
    short titleX_;
    short titleTop_;
    short titleWidth_;
    short titleHeight_;
    // The x of the arrow that crosses the title
    short arrowX_;
    // Close() was called
    unsigned char closing_;
    char unk_44b;

    void CreateAllocators(SafeAllocator* allocator);
    void Initialize(unsigned char type);
    void Finish();
    void Close();
    void Update();
    void Draw1();
    void Draw2();
    void SetPages(GuidePage* pages, int count);
    void State_Load();
    void State_Main();
    void State_Close();
    void StartTitle();
    void UpdateTitle();
    void DrawTitleBackground();
    void UpdateArrow();
    void DrawArrow();
    int WasButtonPressed();
    int Skip();
    void OpenTitle();
    void WriteTitle(char* text);
    void OpenText();
    void RefreshTitle();
    void OpenName();
    void OpenEnd();
    int SetShown(const short* ids, int count);

    static int IsFlagSet(int flag);
};
