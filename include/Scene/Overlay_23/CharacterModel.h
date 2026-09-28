#pragma once

#include "GameState/PartyMemberData.h"
#include "Graphics/VRAMManagerState.h"
#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"
#include "System/Matrix.h"
#include "World/Object3D.h"

// The objects that CharacterModel::Draw() draws at the bones of the body: at the chest, and at the head
struct CharacterModelExtras
{
    Object3D* chest_;
    Object3D* head_;
};

// A party member's 3D model (0xc20 bytes), made of the models of its body, look and equipment, which it loads from
// data/pack_lv5/chara_pd.gp2. Overlay 9 shows it in the creation of a character, overlay 11's menus and overlay 23 in
// other screens
class CharacterModel
{
public:
    enum Part
    {
        Part_Body,
        Part_1,
        Part_2,
        Part_3,
        Part_4,
        Part_5,
        Part_6,
        Part_7,
        Part_8,
        Part_9,
        Part_Count,
    };

    // The body is parts_[0]; parts 1, 5 and 6 are animated with it
    Object3D parts_[Part_Count];
    SafeAllocator allocators_[Part_Count];
    SafeAllocator animationAllocator_;
    // What func_0207de48, func_0207df50, func_0207df90 and func_0207dfac take, for each part
    VRAMManagerState vramStates_[Part_Count];
    // The BackgroundLoader tasks of the parts' models, then of the animations (.nsbca) and of their script (.bcfg)
    short tasks_[Part_Count + 2];
    PartNameTable* names_;
    // The body holds an item with the arms (arm2R and arm2L instead of weaponR)
    unsigned char holdsWithArms_;
    unsigned char unk_c11;
    // The files are loading
    unsigned char loading_;
    // The body's model changed, so the animation is set again
    unsigned char bodyChanged_;
    unsigned char visible_;
    unsigned char vocation_;
    char unk_c16[2];
    PartyMemberData* member_;
    // The body's angle
    short angle_;
    // The colors are in VRAM
    unsigned char colored_;
    char unk_c1f;

    CharacterModel()
    {
        Initialize();
    }

    void Initialize();
    void Finish();
    void CreateAllocators(SafeAllocator* allocator);
    void InitializeVRAMStates();
    void Update();
    void UpdateColors();
    void Draw(CharacterModelExtras* extras);
    void Load(PartyMemberData* member, int vocation, int, int reload);
    void SetScale(int width, int height);
    static void GetModels(int vocation, short* models, const PartyMemberAppearance* appearance);
    void SetRotation(const Vector3fix& rotation);
    void SetAngle(int angle);
    Vector3fix GetRotation();
    void SetUnk_c11(unsigned char value);
    void Hide(int part);
    void HideAll();
    Object3D* GetBody();
    void SetNames(PartNameTable* names);
    void CancelTasks();
};
