#pragma once

#include "Graphics/Sprite.h"
#include "Text/TextTable.h"

// The only code of overlay 19, *likely* the screen of the save data's errors: main() runs it when func_02011570 says
// so, and GameState::saveError_ (which func_020a94f8 sets when a save fails its checks) chooses its first message
// from str_err_<LG>.nat. Some errors only show a message; others ask a question and, if answered, *likely* delete the
// save data while the quill pen of pen.pac is drawn. main() allocates it (sizeof == 0x2e0) and calls Initialize(),
// Run() and Finish(). While it runs, it's the game's resources (see func_0200fb84), so it starts with the brightness
// state of GameResources, which the brightness functions (Resource/Brightness.h) update
struct SaveErrorScreen
{
    enum State
    {
        // Only the message is shown
        State_Idle,
        State_Ask,
        State_AskAgain,
        State_Delete,
        State_Deleted,
        State_EndAfterMessage,
        State_DeleteFailed,
        State_DeleteFailedEnd,
        State_WaitForButton,
        State_End,
    };

    unsigned int brightnessFlags_0;
    unsigned int brightnessFlags_4;
    unsigned int brightnessFlags_8;
    float mainBrightness;
    int mainBrightnessTarget;
    int mainBrightnessTimeRemaining;
    float subBrightness;
    int subBrightnessTarget;
    int subBrightnessTimeRemaining;
    bool mainBrightnessLocked;
    bool subBrightnessLocked;
    bool mainBrightnessDirty;
    bool subBrightnessDirty;
    bool allowBrightnessApply;
    char unk_29[3];

    // What func_020a9ea4 and func_020ab7a8 take: *likely* the task that deletes the save data
    char unk_2c[8];
    // str_err_<LG>.nat
    TextTable texts_;
    // Bit 0: the pen is shown
    unsigned int flags_;
    // 0 until pen.pac is loaded
    int penStep_;
    SpriteRenderer spriteRenderer_;
    Sprite sprites_[14];
    SpriteAnimationList animations_;

    // The size of the buffer of Run()'s allocator, for the texts and the pen's sprites
    static const unsigned int sBufferSize;

    void Initialize();
    void Finish();
    void Run();
    void DrawPen();
    bool WasButtonPressed();
};
