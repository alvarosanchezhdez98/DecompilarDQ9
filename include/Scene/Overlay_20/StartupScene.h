#pragma once

#include "Graphics/Background.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"

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
