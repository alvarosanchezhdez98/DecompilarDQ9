#pragma once

#include "GameState/PlayRecords.h"
#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"
#include "Text/TextTable.h"

// A loaded .bin file of texts: func_020727d8 initializes it, func_020728ac loads it and func_02072a68 returns a text
struct BinTextTable
{
    char unk_0[8];
};

// The card of the player's profile that tag mode shows on the sub screen (str_sli.gp2, bg_slime3.pac), with three
// pages: the records, the profile and the message (0x614 bytes). Overlay 12's profile editor and overlay 2 show it
struct ProfileCard
{
    // The allocators of the background, of the card's texts and of the rest
    SafeAllocator allocators_[3];
    // 0 in overlay 2, where the play time is shown, 2 in overlay 12
    int mode_;
    // What the sub screen had before, which Finish() restores
    unsigned int subBGBanks_;
    unsigned int subObjBanks_;
    unsigned int subLayers_;
    // The texts of the card (str_sli_<LG>.nat)
    TextTable cardTexts_;
    // func_02074b64 initializes it
    char unk_64[0x10];
    unsigned char unk_74;
    unsigned char unk_75;
    char unk_76[2];
    TextWindow window_;
    BackgroundGraphics backgrounds_[2];
    Canvas canvases_[5];
    // The pixels of the canvases
    void* pixels_;
    // The text that a page writes (MessageSystem::unk_5c)
    char* text_;
    // Load() finished
    int loaded_;
    int step_;
    int task_;
    // The scrolling of the background
    int scrollX_;
    int scrollY_;
    // The card's design (0 to 3)
    int design_;
    BinTextTable* strings_;
    TextTable* texts_;
    // A text that the message page shows
    const char* unk_5fc;
    // The message being edited
    char* message_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    // The page of the card, and the card has two
    unsigned char unk_60c;
    unsigned char unk_60d;
    PlayTime playTime_;
    char unk_612[2];

    void CreateAllocators(SafeAllocator* allocator);
    void Initialize(int mode);
    void Finish();
    void Update(int ticks);
    void Draw1();
    void Draw2();
    int Load();
    int SetDesign(int design);
    void OpenPage(int page, int design);
    void RefreshPage(int page, int design);
    void SetWindow(int id, short x, short y);
    void OpenRecords();
    void RefreshRecords();
    void OpenProfile();
    void RefreshProfile();
    void OpenMessage();
    void RefreshMessage();
    void RedrawMessage();
    void DrawPlayTime();
    void DrawRecords();
    void DrawUnkF74();
    void DrawProfile();
    void DrawUnk5fc();
    void DrawMessage();
    void DrawName();
    void DrawLabel();
};
