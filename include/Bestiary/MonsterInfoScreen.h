#pragma once

#include "Bestiary/HabitatTable.h"
#include "Memory/SafeAllocator.h"
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

// A layout (.lia file) of the menus in overlay 23
struct LayoutElement
{
    short id_;
    char unk_2[0x14];
    // LAYOUT_ELEMENT_FLAG_*
    unsigned char flags_;
    char unk_17;
};

#define LAYOUT_ELEMENT_FLAG_VISIBLE 1
#define LAYOUT_ELEMENT_FLAG_4 0x10

// A surface that text is drawn to
struct Canvas
{
    char unk_0[4];
    struct BackgroundGraphics* background_;
    void* pixels_;
    char unk_c[0x9c];
    // In tiles
    short width_;
    short height_;
    short x_;
    short y_;
    char unk_b0[4];
    short unk_b4;
    short unk_b6;
    char unk_b8[0x28];
};

// Loads the graphics of a background
struct BackgroundGraphics
{
    char unk_0[0x1c];
    unsigned char unk_1c_0_ : 4;
    unsigned char unk_1c_4_ : 4;
    char unk_1d[3];
};

struct Layout
{
    char unk_0[4];
    Canvas* canvas_;
    LayoutElement* elements_;
    char unk_c[6];
    short unk_12;
    unsigned short numElements_;
    char unk_16[0x36];

    void SetCanvas(Canvas* canvas)
    {
        canvas_ = canvas;
        unk_12 = 1;
    }
};

struct Sprite
{
    char unk_0[0x14];
    fix32_t x_;
    fix32_t y_;
    char unk_1c[6];
    unsigned char unk_22;
    char unk_23[3];
    unsigned char unk_26;
    char unk_27;
};

// The animated sprites of a SpriteRenderer
struct SpriteAnimation
{
    char unk_0[4];
    short x_;
    short y_;
    char unk_8[0xd];
    unsigned char flags_;
};

struct SpriteAnimationList
{
    char unk_0[8];
};

struct SpriteRenderer
{
    char unk_0[0x3c];
    SpriteAnimationList* animations_;
    Sprite* sprites_;
    char unk_44[8];
    short numSprites_;
    char unk_4e[2];
    unsigned char unk_50;
    char unk_51[3];

    void SetSprites(Sprite* sprites, short numSprites)
    {
        sprites_ = sprites;
        numSprites_ = numSprites;
    }
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
