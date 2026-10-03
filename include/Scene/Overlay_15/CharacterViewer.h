#pragma once

#include "Graphics/VRAMManagerState.h"
#include "Memory/SafeAllocator.h"
#include "Resource/MonsterEntry.h"
#include "Resource/PartNameTable.h"
#include "World/Object3D.h"

struct CharacterViewer;

// An entry of a menu of data/bin/charaview4.bin: an object to load, or a link to another page
struct ViewerEntry
{
    char* name_;
    char* file_;
    // The ID of the part, monster or object
    unsigned short id_;
    // The page of the menu where the entry is
    unsigned char page_;
    // The page that the entry opens, if not 0
    unsigned char link_;
};

// An object of a preset of data/bin/charaview4.bin
struct ViewerPresetItem
{
    char* file_;
    unsigned short id_;
    // The kind of object (see ViewObject::SetupFromKind()), or 8-11 for a motion of the previous one
    unsigned char kind_;
    ViewerPresetItem* next_;
};

// A preset of data/bin/charaview4.bin: objects that are loaded together
struct ViewerPreset
{
    char* name_;
    ViewerPresetItem* items_;
};

// The menus of the character viewer, which data/bin/charaview4.bin's script fills (0x10 bytes)
struct ViewerConfig
{
    ViewerEntry* entries_;
    ViewerPreset* presets_;
    int entryCount_;
    int presetCount_;

    void Clear();
    void Free();
    void SetEntryCount(int count);
    void SetPresetCount(int count);
    void AddEntry(ViewerEntry* entry);
    void AddPreset(ViewerPreset* preset);
    void Load(const char* path);
    ViewerEntry* GetEntry(int index);
    ViewerPreset* GetPreset(int index);
};

// The VRAM states of an object (see CharacterViewer::FindPlayerSlot())
struct ViewerSlot
{
    VRAMManagerState* states_;
    unsigned char used_;
    char unk_5[3];

    void Initialize();
};

// The effect of an effect object (0x1c bytes, func_0205563c initializes it)
struct ViewerEffect
{
    char unk_0[4];
    void* unk_4;
    char unk_8[4];
    void* unk_c;
    char unk_10[0xc];
};

// An item of a DebugMenu (0x40 bytes): func_0202949c initializes it, func_020294cc sets its text, func_02029560 returns it
struct DebugMenuItem
{
    char unk_0[0x40];
};

// A menu of the debug screens (0x80 bytes), which main() draws: func_02029568 initializes it, func_0202a944 adds an item
// and func_0202a9ac returns one
struct DebugMenu
{
    DebugMenuItem title_;
    int unk_40;
    char unk_44[0x5a - 0x44];
    unsigned short count_;
    short first_;
    short last_;
    short cursor_;
    // The number of items that fit in the menu
    unsigned short rows_;
    // The first item shown
    unsigned short top_;
    char unk_66[0x6c - 0x66];
    unsigned char unk_6c;
    unsigned char flags_;
    char unk_6e[2];
    unsigned char unk_70;
    char unk_71[0x80 - 0x71];

    int GetIndex();
    void SetRange(int first, int last);
    void SetIndex(int index);
};

// An object of the character viewer (0x5c bytes)
struct ViewObject
{
    enum Kind
    {
        Kind_Player,
        Kind_Doll,
        Kind_Npc,
        Kind_Monster,
        Kind_Effect,
        Kind_EventCamera,
        Kind_SkillCamera,
    };

    CharacterViewer* viewer_;
    ViewerSlot* slot_;
    // One for each part for the characters, else one
    SafeAllocator* allocators_;
    const char* name_;
    MonsterEntry* monster_;
    void* buffer_;
    unsigned int bufferSize_;
    unsigned char kind_;
    char unk_1d[3];
    // The characters' parts
    int* parts_;
    // One for each part for the characters, else one
    Object3D* objects_;
    ViewerEffect* effect_;
    // 1 when the parts changed, 2 when all of them have to be loaded again
    unsigned char reload_;
    char unk_2d[3];
    int unk_30;
    // The counts of triangles and quads that the info shows (pT and pQ)
    unsigned short triangles_;
    unsigned short quads_;
    // The chosen motion
    short motion_;
    unsigned char playing_;
    unsigned char female_;
    // The colors of the hair, the skin and the eyes (the menu's pages "Eye Colour" and "Skin Colour" set the skin and the
    // eyes)
    unsigned char hairColor_;
    unsigned char skinColor_;
    unsigned char eyeColor_;
    char unk_3f;
    short height_;
    short width_;
    int loop_;
    // Whether the character holds its weapon as in battles
    int battle_;
    // The step of the chosen motion, which the motion menu changes
    int step_;
    // The bone of the body that holds the weapon
    signed char weaponBone_;
    char unk_51[3];
    int unk_54;
    int unk_58;

    int Allocate();
    bool GetModelName(char* name, unsigned int part, int file);
    void GetAnimationName(char* name, int field);
    void LoadPalette(int part);
    void LoadPlayerAnimations(const char* event);
    void LoadDollAnimations(const char* event);
    void LoadEventAnimation(const char* event);
    int LoadPlayer();
    int LoadDoll();
    int LoadMonster(ViewerEntry* entry);
    int LoadNpc(ViewerEntry* entry);
    int LoadEffect(ViewerEntry* entry);
    int LoadCamera(ViewerEntry* entry);
    void UpdatePlayer();
    void UpdateDoll();
    void UpdateMonster();
    void UpdateNpc();
    void UpdateEffect();
    void UpdateCamera();
    void DrawPlayer();
    void DrawDoll();
    void DrawMonster();
    void DrawNpc();
    void DrawEffect();
    void Initialize();
    int SetupFromEntry(CharacterViewer* viewer, ViewerEntry* entry);
    int SetupFromKind(CharacterViewer* viewer, unsigned int kind);
    void Finish();
    void Update();
    void Draw();
    int Load(ViewerEntry* entry);
    void LoadMotion(const char* event);
    AnimationPackage* GetAnimationPackages();
    void SetAnimation(const char* name);
    BCFG::AnimationRecord* GetAnimationRecord(const char* name);
    float GetTime();
    float GetProgress();
    void Move(Vector3fix offset);
    void Turn(int angle);
    void DrawMemory();
    void SetPart(unsigned char part, int id);
    void SetGender(unsigned char female);
    void SetSkinColor(unsigned char color);
    void SetEyeColor(unsigned char color);
    void SetHairColor(unsigned char color);
    void SetBuild(short width, short height);
    void ToggleBattle();
    void SaveStep();
    void SetStep(int step);
    void AddStep(int step);
};

// A node of CharacterViewer::objects_
struct ViewObjectNode
{
    ViewObject* object_;
    ViewObjectNode* next_;
};

// The only code of overlay 15: a debug mode of main() that shows the models of the characters, monsters and effects,
// with their motions (data/bin/charaview4.bin has its menus). main() allocates it (sizeof == 0x358), and calls
// Initialize(), Run() and Finish(). While it runs, it's the game's resources (see func_0200fb84), so it starts with the
// brightness state of GameResources, which the brightness functions (Resource/Brightness.h) update
struct CharacterViewer
{
    enum Menu
    {
        Menu_Top,
        Menu_Motion,
        Menu_Option,
    };

    // The number of categories of parts whose names it loads
    static const int sCategoryCount;

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

    ViewObjectNode* objects_;
    // The object of the menus
    ViewObject* current_;
    // The object that the Move page moves
    ViewObject* selected_;
    // The kind of the last deleted object that was the current one
    signed char lastKind_;
    char unk_39[3];
    ViewerConfig config_;
    PartNameTable parts_;
    // The monsters' names (func_0206efc4 initializes it, func_0206f4f0 returns one)
    char monsters_[0xc];
    // The monsters' sounds (func_020709d8 initializes it, func_02070fd0 returns one)
    char monsterSounds_[0x14];
    void* buffer_;
    SafeAllocator partsAllocator_;
    SafeAllocator monstersAllocator_;
    SafeAllocator soundsAllocator_;
    ViewerSlot playerSlots_[4];
    ViewerSlot dollSlots_[4];
    ViewerSlot slots_[4];
    // What func_0207de48, func_0207df50, func_0207df90 and func_0207dfac take
    VRAMManagerState vramState_;
    int menu_;
    int otherMenu_;
    unsigned char aspect_;
    unsigned char floor_;
    unsigned char monsterBox_;
    unsigned char syncMotion_;
    unsigned char viewMemory_;
    // The monsters are loaded in their field version
    unsigned char field_;
    char unk_1a2[2];
    // The current page of the menu
    int page_;
    // The pages to go back to
    int history_[0x20];
    int historyCount_;
    // The milliseconds since fps_ was computed
    unsigned long long elapsed_;
    // When the work of the frame started and ended, in microseconds
    unsigned long long workStart_;
    unsigned long long workEnd_;
    // The average microseconds of the frames' work
    unsigned long long averageWork_;
    float fps_;
    int unk_250[6];
    // The cursor of each page
    short cursors_[0x29];
    char unk_2ba[2];
    int repeatDelay_;
    int repeatTimer_;
    DebugMenu menuList_;
    // The texts of menuList_'s items
    DebugMenuItem* items_;
    int scrollBarSize_;
    float scrollBarStep_;
    // The menu has to be drawn again
    unsigned char redraw_;
    char unk_351[3];
    int unk_354;

    void Draw();
    void DrawObjects();
    void DrawMenu();
    void DrawInfo();
    void DrawHelp();
    bool IsLookPage();
    bool IsMenuChanged();
    bool IsPartPage();
    void Update();
    void UpdateTopMenu();
    void UpdateMotionMenu();
    void UpdateOptionMenu();
    void MoveSelected();
    ViewObject* AddObject(ViewerEntry* entry);
    void DeleteObject(int index);
    void SelectObject(int index);
    void LoadPreset(int index);
    void PickObject(int index);
    void ToggleOption();
    void MoveMenu(int choice);
    void SetLook(int index);
    void ResetCamera();
    bool IsCameraMoving();
    void InitializeVRAM();
    void OpenMenu(int unk);
    ViewerEntry* FindEntry(int page, int* index);
    void PushPage(int page);
    int PopPage();
    ViewerSlot* FindPlayerSlot();
    ViewerSlot* FindDollSlot();
    ViewerSlot* FindSlot();
    void Initialize();
    void Finish();
    void Run();
};
