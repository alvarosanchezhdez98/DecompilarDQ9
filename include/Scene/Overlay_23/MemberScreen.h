#pragma once

#include "GameState/PartyMember.h"
#include "Graphics/Sprite.h"
#include "Graphics/VRAMManagerState.h"
#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"
#include "Scene/Overlay_23/CharacterModel.h"
#include "Scene/Overlay_23/Layout.h"

struct EquipmentMenu;

// The flags of MemberScreen
#define MEMBER_SCREEN_TURNING 1
#define MEMBER_SCREEN_TURN_BACK 2
#define MEMBER_SCREEN_LOAD_MODEL 4
#define MEMBER_SCREEN_SWAP_MODELS 8
#define MEMBER_SCREEN_LOAD_ANIMATIONS 0x10
#define MEMBER_SCREEN_DRAW_MODEL 0x20
#define MEMBER_SCREEN_KEEP_ANGLE 0x40
#define MEMBER_SCREEN_CHANGE_MEMBER 0x80
#define MEMBER_SCREEN_LEFT 0x100
#define MEMBER_SCREEN_RIGHT 0x200
#define MEMBER_SCREEN_NEXT_PRESSED 0x400
#define MEMBER_SCREEN_BACK_PRESSED 0x800
#define MEMBER_SCREEN_CLOSE 0x1000
#define MEMBER_SCREEN_LOADING 0x2000

// The screen of the party members (clmm, lay_mm.lia): a member's 3D model, which the L and R buttons turn, their name,
// vocation and level, and the menu of overlay 5 (the equipment) when it's opened from it (0x648 bytes). Overlay 17
// runs it
struct MemberScreen
{
    // Overlay 5's equipment menu (0x428c bytes)
    EquipmentMenu* equipment_;
    SafeAllocator* allocator_;
    VRAMManagerState* vramState_;
    int unk_c;
    SafeAllocator* allocator2_;
    SafeAllocator* allocator3_;
    char unk_18[0x14];
    SafeAllocator allocators_[6];
    PartNameTable items_;
    unsigned short itemCount_;
    unsigned short itemCount2_;
    // The loaded clmm file
    void* spritesFile_;
    unsigned int spritesFileSize_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    SpriteAnimationList* animations_;
    Layout layout_;
    CharacterModel* models_[2];
    // The model shown, and the one that loads the next member's model
    CharacterModel* model_;
    CharacterModel* nextModel_;
    char unk_130[4];
    // Ticks left before the models swap
    int timer_;
    void* previousCamera_;
    // The camera (func_020a2010 initializes it)
    char camera_[0x2c8];
    VRAMManagerState vramStates_[2];
    unsigned char step_;
    signed char mode_;
    signed char state_;
    signed char previousState_;
    int memberCount_;
    int members_[4];
    // The member shown
    int member_;
    // The encoded texts of the members' names, vocations and levels
    unsigned short names_[4][16];
    int nameX_[4];
    unsigned short vocations_[4][10];
    unsigned short levelLabel_[8];
    unsigned short levels_[4][8];
    int task_;
    // MEMBER_SCREEN_*
    unsigned short flags_;
    unsigned char closed_;
    char unk_637;
    void* buffer_;
    void* buffer2_;
    // The texts shown for a member who is down, for a man and a woman
    char* downTexts_[2];

    void Initialize();
    void Finish();
    void Update();
    void Draw3D();
    void Draw2D();
    void DrawSub();
    void SetMembers(const unsigned char* members, int count);
    void DrawArrows1(int x, int y, int x2, short y2);
    void DrawArrows2(int x, int y, int x2, short y2);
    void DrawArrow3(int x, int y);
    void DrawCursor(short x, short y);
    void Close();
    void SetState(signed char state);
    void State_Load();
    void State_Main();
    void UpdateBack();
    void State_Exit();
    void DrawTexts();
    void DrawLeftRight();
    void DrawNext();
    void DrawBack();
    void UpdateModels();
    void UpdateModelLoad();
    void UpdateTurn(unsigned int ticks);
    void LoadTexts();
    void UpdateMember();
    // Does nothing (overlay 5 calls it)
    void DoNothing();
    Object3D* GetBody();
    void UpdateClose();

    static void HideElement(Layout* layout, short id, int flags);
    static unsigned int GetStars(PartyMember* member);
    static void LoadVocationIcon(int member, SpriteRenderer* renderer);
};
