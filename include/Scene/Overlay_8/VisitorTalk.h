#pragma once

#include "GameState/Profile.h"
#include "Grotto/Main/TreasureMapMetadata.h"
#include "Scene/Overlay_8/BattleRecords.h"

// What tag mode received from another player (see VisitorTalk::guest_): the name, the records, a treasure map and
// the profile
struct GuestData
{
    // The name, in the codes of the message system
    char name_[0xb];
    unsigned char unk_b_0 : 7;
    // The guest gives a treasure map
    unsigned char hasMap_ : 1;
    unsigned int vocation_ : 4;
    unsigned int unk_c_4 : 4;
    unsigned int level_ : 7;
    unsigned int unk_c_15 : 17;
    unsigned int unk_10_0 : 2;
    unsigned int unk_10_2 : 30;
    char unk_14[0x2e - 0x14];
    unsigned char female_ : 1;
    unsigned char unk_2e_1 : 7;
    char unk_2f[0x38 - 0x2f];
    GuestRecords records_;
    TreasureMapMetadata map_;
    ProfileData profile_;
};

// A visitor met in the inn, in GameState (0x2c bytes, 16 of them at 0x7200)
struct GuestEntry
{
    unsigned char id_[6];
    char name_[0xb];
    unsigned char unk_11;
    unsigned short unk_12_0 : 14;
    // The entry is used
    unsigned short used_ : 1;
    unsigned short unk_12_15 : 1;
    GuestRecords records_;
};

// The visitors met in the inn (GameState + 0x71fc)
struct VisitorList
{
    unsigned char count_;
    char unk_1[3];
    GuestEntry entries_[16];
};

// Talking to a visitor of the inn: another player that tag mode received (guest_) or a party member, whose card,
// profile and battle records it shows (tlkpcstr.gp2, obj_tlkpc.pac; 0xecc bytes). Overlay 17's scripts run it
struct VisitorTalk
{
    // func_02074af4 initializes it
    char unk_0[0x10];
    unsigned char unk_10;
    unsigned char unk_11;
    // What the main screen showed before, which Finish() restores
    unsigned int layers_;
    TextWindow window_;
    BackgroundGraphics backgrounds_[2];
    Canvas canvas_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    SpriteAnimationList* animations_;
    SafeAllocator allocator_;
    SafeAllocator textAllocator_;
    SafeAllocator recordsAllocator_;
    SafeAllocator spriteAllocator_;
    SafeAllocator profileAllocator_;
    SafeAllocator titleAllocator_;
    // The texts of the screen (tlkpcstr_<LG>.bin), of the profiles (profstr_<LG>.bin) and the titles (ttlname)
    TextList texts_;
    TextList profileTexts_;
    TextTable titles_;
    // 0x960 bytes where the texts are written (MessageSystem::unk_5c)
    char* text_;
    // The pixels of the canvas
    void* pixels_;
    BattleRecords records_;
    // The visitor's entry, saved in GameState
    GuestEntry entry_;
    ProfileData profile_;
    unsigned char unk_e98;
    // 0 while loading, 1 while talking, 2 when done
    signed char state_;
    signed char step_;
    // What the battle records do: 0 open them, 1 show them, 2 close them
    signed char recordsState_;
    signed char recordsStep_;
    int textTask_;
    int backgroundTask_;
    int spriteTask_;
    int profileTask_;
    int sentencesTask_;
    int titleTask_;
    unsigned char done_;
    signed char member_;
    unsigned char saved_;
    unsigned char full_;
    GuestData* guest_;
    // The screen is shown, the texts of the profiles and the titles are loaded, Abort() was called
    unsigned char active_ : 1;
    unsigned char profileLoaded_ : 1;
    unsigned char titlesLoaded_ : 1;
    unsigned char aborted_ : 1;
    unsigned char unk_ec0_4 : 4;
    // The sentences of the profiles (profsen_<LG>.bin)
    void* sentences_;
    unsigned int sentencesSize_;

    void Initialize(signed char member, GuestData* guest);
    void CreateAllocators(SafeAllocator* allocator);
    unsigned char Update();
    void Draw1();
    void Draw2();
    void Finish();
    void State_Load();
    void State_Talk();
    void WriteCard();
    void DrawCorners();
    void OpenRecords();
    void CloseRecords();
    void AddVisitor();
    void Abort();
};

typedef char VisitorTalkSizeCheck[sizeof(VisitorTalk) == 0xecc ? 1 : -1];
