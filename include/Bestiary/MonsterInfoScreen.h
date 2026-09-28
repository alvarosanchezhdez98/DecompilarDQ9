#pragma once

#include "Bestiary/HabitatTable.h"
#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Memory/SafeAllocator.h"
#include "Scene/Overlay_23/Layout.h"
#include "World/Object3D.h"

// A monster of the bestiary list, from mon_list_<LG>.nat
struct MonsterListEntry
{
    // The next monster shown in the list (see MonsterListScreen)
    MonsterListEntry* next_;
    const char* modelName_;
    const char* name_;
    short monsterID_;
    char unk_e[4];
    // Text of the monster's family, in str_sml_<LG>.nat
    signed char familyTextID_;
    unsigned char unk_13_0_ : 1;
    // Set when the player has defeated it at least once, so its information is shown
    unsigned char known_ : 1;
    unsigned char unk_13_2_ : 6;
    char unk_14[6];
    // The monster's number in the bestiary
    short number_;
    char unk_1c[4];
};

// What the player knows about a monster
struct MonsterRecord
{
    unsigned int defeatCount_ : 10;
    // All its information is shown, with a second page of description
    unsigned int complete_ : 1;
    unsigned int dropCount0_ : 7;
    unsigned int dropCount1_ : 7;
    unsigned int unk_0_25_ : 7;
};

// A monster's drops and how its model is shown, from mons_info2.nat
struct MonsterInfo
{
    char unk_0[8];
    short dropItemIDs_[2];
    unsigned char numAnimations_;
    char unk_d[3];
    float position_[3];
    float rotationY_;
    float scale_[3];
    const char** animations_;
};

struct MonsterRecordCount
{
    unsigned int value_;
    char unk_4[2];
    unsigned short count_;
};

// The loaded mons_info2.nat
struct MonsterInfoTable
{
    char unk_0[0x10];
};

// The monster that's shown with the best record
struct MonsterBest
{
    unsigned int value_;
    short monsterID_;
    unsigned short count_;

    void Init();
};

// The screen with the details of a monster in the bestiary: its model, which can be rotated with the L and R buttons,
// its description, drops and habitat.
class MonsterInfoScreen
{
public:
    enum State
    {
        State_Setup,
        State_Run,
        State_Count,
    };

    void** buffers_;
    SpriteRenderer* spriteRenderer_;
    Sprite* sprites_;
    MonsterInfoTable infos_;
    HabitatTable habitats_;
    SafeAllocator* allocators_;
    Object3D* model_;
    void* camera_;
    MonsterListEntry* monster_;
    MonsterListEntry* prevMonster_;
    MonsterRecord* record_;
    MonsterRecord* prevRecord_;
    Layout* layout_;
    // str_sml_<LG>.nat
    void* texts_;
    char* dropNames_[2];
    char* description_;
    int taskID_;
    int backgroundTaskID_;
    int animationIndex_;
    int unk_78;
    unsigned char state_;
    unsigned char initStep_;
    unsigned char backgroundStep_;
    unsigned char loadStep_;
    unsigned char page_;
    unsigned char flags_;
    unsigned char rotating_ : 1;
    unsigned char unk_82_1_ : 1;
    unsigned char loadModel_ : 1;
    unsigned char unk_82_3_ : 1;
    unsigned char unk_82_4_ : 4;
    short unk_84;
    short taskIDs_[5];
    // The L, R and page buttons are drawn pressed while these are set
    unsigned char buttonPressed_[3];
    unsigned char unk_93;
    unsigned char unk_94;
    short* variants_;
    MonsterBest best_;

    void Allocate(SafeAllocator* allocator);
    void Init();
    void Release();
    void Update();
    void Draw();
    void PlaceModel();
    void CancelLoading();
    void TogglePage();
    void NextAnimation();
    void SetMonster(MonsterListEntry* monster, MonsterRecord* record);
    void LoadMonster(MonsterListEntry* monster, MonsterRecord* record, bool loadModel);
    void UpdateLoading();
    void Setup();
    void Run();
    void UpdateBackground();
    void UpdateText();
};
