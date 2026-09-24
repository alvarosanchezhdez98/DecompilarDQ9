#pragma once

#include "Graphics/Background.h"
#include "Memory/SafeAllocator.h"

// A menu of text items, which main's code runs (func_0205c790 initializes it, func_0205cb74 adds an item)
struct TextMenu
{
    char unk_0[4];
    char unk_4[0x1c];
    char unk_20[0x50];
    char unk_70[0x40];
    unsigned char unk_b0;
    unsigned char unk_b1;
    char unk_b2[2];
    short x_;
    short y_;
    short width_;
    short height_;
    char unk_bc[0x233 - 0xbc];
    unsigned char unk_233;
    unsigned char unk_234;
    char unk_235[3];

    // Sets the number of columns and rows of the items
    void SetGrid(int columns, int rows);

    void SetPosition(short x, short y)
    {
        x_ = x;
        y_ = y;
    }
};

// What func_0205cfd4 initializes, *likely* a text window: StartupScene draws the library versions with it
struct TextWindow
{
    char unk_0[0x98];
    BackgroundGraphics* background_;
    char unk_9c[4];
    // In tiles
    short width_;
    short height_;
    short unk_a4;
    short unk_a6;
    short unk_a8;
    short unk_aa;
    short unk_ac;
    short unk_ae;
    char unk_b0;
    unsigned char unk_b1;
    unsigned char unk_b2;
    char unk_b3[2];
    unsigned char unk_b5;
    unsigned char unk_b6;
    char unk_b7[5];
};

// The only code of overlay 20, *likely* what the game starts with: main() runs it in mode 6 (the title), where it shows
// the logos (nintendo.pac, bg_mobi_2.pac, bg_lv5.pac) and then starts the game, and in the other modes, where it
// shows the versions of the game and its libraries and then a debug menu (bg_title.pac) that chooses the next mode.
// main() allocates it (sizeof == 0x504) and calls Initialize(), Run() and Finish()
struct StartupScene
{
    // State_Menu while the debug menu runs, State_End when an item is chosen
    int state_;
    // The frames since the debug menu started
    int frame_;
    int unk_8;
    TextMenu menu_;
    // What func_0207de48, func_0207df50, func_0207df90 and func_0207dfac take
    char unk_244[0x70];
    TextWindow window_;
    BackgroundGraphics windowBackground_;
    Canvas canvas_;
    SafeAllocator allocator_;
    // Initialize() resets it, and nothing else in the overlay uses it
    SafeAllocator unk_484;
    // The canvas' pixels
    void* canvasBuffer_;
    BackgroundGraphics mainBackground_;
    BackgroundGraphics subBackground_;
    char unk_4dc[8];
    // In milliseconds
    int timer_;
    float mainBrightness_;
    int mainBrightnessTarget_;
    int mainBrightnessTimeRemaining_;
    float subBrightness_;
    int subBrightnessTarget_;
    int subBrightnessTimeRemaining_;
    int unk_500;

    enum State
    {
        State_End = -1,
        State_Menu = 100,
    };

    void Initialize();
    void Finish();
    void Run();
    void UpdateMenu();
    void LoadMenuBackgrounds();
    void LoadNintendoLogo();
    void LoadMobiLogo();
    void LoadCompanyLogo(int company);
    void UpdateBrightness();
    void SetMainBrightness(int brightness, int duration);
    void SetSubBrightness(int brightness, int duration);
    void UpdateTimer();
    bool IsBrightnessTransitionActive();
    void Cleanup();

    int IsMainBrightnessTransitionActive() { return mainBrightnessTimeRemaining_ > 0; }
    int IsSubBrightnessTransitionActive() { return subBrightnessTimeRemaining_ > 0; }
    int IsTimerActive() { return timer_ > 0; }
};
