#pragma once

#include "GameState/PartyMemberData.h"
#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Graphics/TextWindow.h"
#include "Memory/SafeAllocator.h"
#include "Scene/Overlay_12/ProfileEditor.h"
#include "Scene/Overlay_23/CharacterModel.h"
#include "System/TouchScreen.h"
#include "Text/ForbiddenWordChecker.h"
#include "Text/TextTable.h"
#include "World/Object3D.h"

// A loaded data/prm/level<vocation>.bin (func_0208247c initializes it, func_02082490 loads it)
struct LevelTable
{
    char unk_0[0x3c];
};

// What func_02083cbc writes
struct LevelStatistics
{
    char unk_0[0x18];
};

// What func_0209a804 initializes
struct Unknown_0209a804
{
    char unk_0[4];
};

// The statistics of a new party member, which func_02086404 initializes
struct MemberStatistics
{
    char unk_0[0x14c];
    unsigned int unk_14c_0 : 10;
    unsigned int unk_14c_10 : 10;
    unsigned int unk_14c_20 : 10;
    unsigned int unk_150_0 : 10;
    unsigned int unk_150_10 : 10;
    unsigned int unk_150_20 : 10;
    unsigned int unk_154_0 : 10;
    unsigned int unk_154_10 : 10;
    unsigned int unk_154_20 : 10;
    unsigned int unk_158_0 : 10;
    unsigned int unk_158_10 : 10;
    unsigned int unk_158_20 : 10;
    unsigned int unk_15c_0 : 10;
    unsigned int unk_15c_10 : 10;
    char unk_160[0x23c - 0x160];
};

// A skill that a vocation learns at a level
struct LevelSkill
{
    unsigned short skill_;
    unsigned short level_;
};

// What func_0209a810 writes
struct VocationSkills
{
    char unk_0[0x10c];
    LevelSkill skills_[13][20];
    char unk_51c[0x550 - 0x51c];
};

// The area of the choices of a state (0x20 bytes, sGrids has them): the position of the first, the size of each, the
// distance between them, and how many columns and rows they're in. Overlays 2 and 23 call its Reset() too, whose only
// copy is in overlay 9
struct ChoiceGrid
{
    int x_;
    int y_;
    int width_;
    int height_;
    int stepX_;
    int stepY_;
    int columns_;
    int rows_;

    void Reset();
};

// What func_0204af14 returns: a part of a background's graphics
struct BackgroundPart
{
    char unk_0[0xc];
    void* unk_c;
};

// Overlay 9, the creation of a character: of the protagonist at the start of the game (overlay 21 runs it, mode 0),
// or of a party member at the Quester's Rest (overlay 3, mode 1). Overlay 23 has more of its code, which takes it too.
// Its states choose the sex, then each part of the character's look, then the name, then the confirmation
struct CharacterCreation
{
    SafeAllocator allocators_[9];
    // For the models: the protagonist's model, and the two models of the preview
    SafeAllocator* modelAllocator_;
    SafeAllocator* previewAllocators_;
    // The key that the keyboard had when the list of the states was opened
    KeyboardKey* savedKey_;
    Keyboard* keyboard_;
    KeyboardLayout* layout_;
    PartNameTable partNames_;
    TextTable texts_;
    void* unk_f8;
    ForbiddenWordChecker checker_;
    BackgroundGraphics backgrounds_[6];
    TextWindow windows_[2];
    Canvas canvases_[1];
    Canvas canvases2_[4];
    void* pixels_;
    void* pixels2_;
    SpriteRenderer* renderer_;
    Sprite* sprites_;
    void* unk_7e0;
    SpriteRenderer* renderer2_;
    Sprite* sprites2_;
    void* unk_7ec;
    // The two characters of overlay 23 that show the choices: the current one and the next one
    CharacterModel* characters_[2];
    CharacterModel* character_;
    CharacterModel* nextCharacter_;
    int unk_800;
    // The angle that the character turns to
    int targetAngle_;
    // What func_0207de48, func_0207df50, func_0207df90 and func_0207dfac take
    char unk_808[0x70];
    Object3D object_;
    // The camera (func_020a2010 initializes it)
    char camera_[0x2c8];
    WindowCursor cursor_;
    ChoiceGrid grid_;
    // The rectangle of the cursor, and the position of the last choice
    short cursorX_;
    short cursorY_;
    short cursorWidth_;
    short cursorHeight_;
    short lastX_;
    short lastY_;
    // The state (the index in the table of Update()), and the step in it
    signed char state_;
    unsigned char step_;
    char unk_c5a[2];
    // The BackgroundLoader tasks of the models of the confirmation
    int modelTasks_[3];
    // What func_0207de48, func_0207df50, func_0207df90 and func_0207dfac take
    char unk_c68[0x70];
    Object3D object2_;
    unsigned char selection_;
    unsigned char unk_d85;
    char unk_d86[2];
    PartyMemberData* member_;
    int touchedChoice_;
    // The BackgroundLoader task of the backgrounds of a state, and the step of their loading
    int task_;
    unsigned char loadStep_;
    // 0: the protagonist, 1: a party member
    unsigned char mode_;
    short timer_;
    short unk_d98;
    char unk_d9a[2];
    unsigned int flags_;
    // The last state that can be chosen, for each sex
    signed char lastStates_[2];
    // The vocation of a party member (0 for the protagonist)
    unsigned char vocation_;
    // 0: a man, 1: a woman
    unsigned char sex_;
    // The choice of each state, for each sex
    unsigned char bodyType_[2];
    unsigned char hairStyle_[2];
    unsigned char skinColor_[2];
    unsigned char eyeColor_[2];
    unsigned char face_[2];
    unsigned char hairColor_[2];
    // The names being written, for each sex
    char** names_;
    unsigned char unk_db4;
    unsigned char keyboardResult_;
    unsigned char unk_db6;
    char unk_db7;

    void Load(SafeAllocator* allocator);
    void Initialize(int vocation, int mode);
    void Finish();
    int Update();
    void Draw2D();
    void Draw3D();
    void UpdateGraphics();
    void QueueBackgrounds();
    void LoadBackgrounds();
    void SetState(unsigned char state);
    void State_Load();
    void State_Sex();
    void State_BodyType();
    void State_HairStyle();
    void State_Face();
    void State_HairColor();
    void State_EyeColor();
    void State_SkinColor();
    void State_Name();
    void State_Confirm();
    void State_Finish();
    void State_Exit();
    void SwapCharacters();
    void UpdateCharacter();
    void Turn(unsigned int ticks);
    void SetChoice(int choice);
    int GetModel(int state, int choice);
    void GetBodyScale(int bodyType, short* width, short* height);
    void ResetCursor();
    void SetGrid();
    void SetCursor(int choice);
    int UpdateChoice();
    int GetTouchedChoice(int x, int y);
    void CheckName();
    void SetRandomName();
    int UpdateTimer(int ticks);

    // In overlay 23 (CharacterCreationDisplay.cpp)
    void OpenStateWindow();
    void UpdateStateWindow();
    void OpenChoiceWindow();
    void ClearChoiceWindow();
    void OpenNameWindow();
    void UpdateNameWindow();
    void OpenConfirmWindow();
    void WriteConfirmText(char* text, int highlighted);
    void UpdateConfirmWindow();
    void UpdateBackgrounds();
    void UpdateSprites();
    void UpdateAnimations();
    void SetCursorSprites(int x, int y, int width, int height);
    void UpdateFade(unsigned int ticks);
    void DrawFade(int color, int alpha);
};
