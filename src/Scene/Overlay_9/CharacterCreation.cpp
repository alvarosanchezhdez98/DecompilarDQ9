// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_9/CharacterCreation.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Filesystem/GPC.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>
#include "Util/Random.h"
#include <std_library_functions.h>

#define REG_BLDCNT 0x04000050
#define REG_BLDCNT_SUB 0x04001050
#define REG_MASTER_BRIGHT ((volatile unsigned short*)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((volatile unsigned short*)0x0400106c)

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    int memcmp(const void* a, const void* b, unsigned long size);

    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];

    GameResources* func_0200fb8c(GameState* gameState);
    void func_020100c4(GameState* gameState, void* camera);
    void func_0202e0a4(void* camera);
    void func_0203bd14();
    void func_0203c4c4();
    MessageSystem* func_020421a0();
    // The code of a character of a text
    signed char func_020424e4(const char* character, int);
    void func_02043124(MessageSystem* messages);
    void func_02043204(MessageSystem* messages);
    void func_02045cac();
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204afb4(BackgroundGraphics* background);
    void func_0204b010(BackgroundGraphics* background, int);
    void func_0204b04c(BackgroundGraphics* background, int);
    void func_0204b088(BackgroundGraphics* background, int);
    void func_0204c684(Canvas* canvas);
    int func_0204c7cc();
    void func_0205a494(SpriteRenderer* renderer);
    void func_0205bc24(WindowFrame* frame, int);
    void func_0205bef8(WindowCursor* cursor);
    void func_0205cfd4(TextWindow* window);
    void func_0205d048(TextWindow* window);
    int func_0205d0e0(TextWindow* window, int);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    Canvas* func_0205d8c4(TextWindow* window);
    void func_020a20d8(void* camera);
    void* func_020d6c00();
    void func_020de848(PartNameTable* names);
    void func_020dfc40(TextTable* texts);
    const char* func_020e0434(TextTable* texts, short id);

    void func_ov003_0215e6d8(KeyboardLayout* layout);
    void func_ov003_0215efb8(Keyboard* keyboard);
    int func_0200fb08(GameState* gameState);
    // The count of the files of an archive, and a file of it
    int func_02046900(void* archive);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    void* func_0204af14(BackgroundGraphics* background, unsigned char index);
    void func_0204af38(BackgroundGraphics* background, unsigned char, SafeAllocator* allocator);
    void func_0204b0e8(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* background, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b2e0(BackgroundGraphics* background, void* file);
    void func_0204b3a0(BackgroundGraphics* background, void* file);
    void func_0204b5b4(BackgroundGraphics* background, int);
    void func_0204b5e8(BackgroundGraphics* background, int, int);
    void func_0204b620(BackgroundGraphics* background, void*, void*, int, int, int, int, int, int, int);
    void func_0204b8d0(BackgroundGraphics* background, int, int, int, int, int, int, int, int);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    // The files of the names of the parts of the characters' models
    extern const char* data_020f2a30;
    extern const char* data_020f2a38;
    void func_0202e5c0(void* camera, int x, int y, int z);
    void func_0202e5c8(void* camera, int x, int y, int z);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, int size);
    void func_0205a198(Sprite* sprite);
    void func_0205a234(void*);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int count);
    void func_0205deb4(TextWindow* window, int, int);
    void func_0207de48(void*, int, int);
    void func_0207df50(void*);
    void func_0207df90(void*);
    void func_0207dfac(void*);
    void func_020a2010(void* camera);
    void func_020a27a0(void* camera);
    void func_020de9a4(PartNameTable* names, SafeAllocator* allocator, void* file, unsigned int size, const short* ids,
                       int count);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    void func_ov003_0215e6f8(KeyboardLayout* layout, SafeAllocator* allocator, void* file, unsigned int size);
    void func_ov003_0215f41c(Keyboard* keyboard, const char* text);
    KeyboardKey* func_ov003_0215f4fc(Keyboard* keyboard, const char* text);
    // "%s"
    extern const char data_020ef078[];
    // The file of the forbidden words, and the file of the texts of the checker
    extern const char* data_020f2858;
    extern const char* data_020f285c;
    void* func_02010828(GameState* gameState);
    int func_02012430(void* pad, int buttons);
    int func_02012444(void* pad, int buttons);
    void func_02012a84(TouchState* touch, int* x, int* y);
    void func_0202ee38(void* camera, const Vector3fix* position, int);
    void func_0202ee58(void* camera, const Vector3fix* target, int);
    int func_0202eeb4(void* camera);
    int func_0203b57c(GameResources* resources, int);
    void* func_020425b4(signed char code, int);
    void* func_0204254c(const char* character, int);
    void func_020426bc(const char* text, char* codes, int);
    int func_0205bafc(WindowCursor* cursor);
    unsigned char func_0205bb84(WindowCursor* cursor);
    int func_0205bf58(WindowCursor* cursor, unsigned int ticks);
    void func_0205d6a0(TextWindow* window, int);
    int func_0205d794(TextWindow* window);
    int func_0205da38(TextWindow* window, int);
    void func_0205eaa0(void* sound, int effect, int);
    void func_0205ebc0(void* sound, int, int);
    void func_0205ebec(void* sound);
    void func_0205ebfc(void* sound, int, int);
    void func_0208247c(LevelTable* levels);
    void func_02082490(LevelTable* levels, void* file, unsigned int size, int level, int);
    void func_020830cc(PartyMemberData* member, MemberStatistics* statistics);
    void func_02083b60(PartyMemberData* member, unsigned short skill);
    void func_02083ca0(PartyMemberData* member, int vocation);
    void func_02083cbc(PartyMemberData* member, LevelTable* levels, LevelStatistics* statistics);
    void func_02083e28(PartyMemberData* member, int);
    void func_020863c4(PartyMemberData* member);
    void func_02086404(MemberStatistics* statistics);
    void func_02086778(void* party, MemberStatistics* statistics, int, int);
    void func_0209a804(Unknown_0209a804* unknown);
    void func_0209a810(Unknown_0209a804* unknown, VocationSkills* skills);
    void func_0209c678(void*, int);
    // GXx_SetMasterBrightness_
    void func_020c39a0(volatile unsigned short* reg, int brightness);
    int func_020d2ff0(const char* text);
    const void* func_020dedd0(PartNameTable* names, short id);
    void func_020e038c(TextTable* texts, void* file, unsigned int size);
    void func_ov003_0215ec68(int size, short* width, short* height);
    int func_ov003_0215f000(Keyboard* keyboard, int ticks);
    KeyboardKey* func_ov003_0215f4a4(Keyboard* keyboard, int);
    void func_ov003_0215f4e4(Keyboard* keyboard, int);
    // The touch screen
    extern TouchState data_02114e54;
    int func_020e0424(TextTable* texts);
    // Methods of overlay 23, for the assembly
    void _ZN17CharacterCreation15OpenStateWindowEv();
    void _ZN17CharacterCreation16OpenChoiceWindowEv();
    void _ZN17CharacterCreation14OpenNameWindowEv();
    void _ZN17CharacterCreation17OpenConfirmWindowEv();
    void _ZN17CharacterCreation17UpdateBackgroundsEv();
    // CharacterModel's methods, for the assembly
    void _ZN14CharacterModel10InitializeEv();
    void _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator();
    void _ZN14CharacterModel20InitializeVRAMStatesEv();
    void _ZN14CharacterModel4LoadEP15PartyMemberDataiii();
    void _ZN14CharacterModel8SetScaleEii();
    void _ZN14CharacterModel8SetAngleEi();
    void _ZN14CharacterModel10SetUnk_c11Eh();
    void _ZN14CharacterModel8SetNamesEP13PartNameTable();
}

// The symbols of the patterns of the forbidden words
static const char sSymbols[15][5] __attribute__((aligned(4))) = {
    ":", "[", "]", "{", "}", "^", "-", ".", "$", "/", "@", "&", ",", "<c/>", "'"};

// What CheckName() writes for a tag (in .data, before the pool of the strings)
static char sTagCharacter[4] = "C";

// The strings of the functions, which the compiler pools in this order. Some functions are in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for them
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] = "*\0PALT\0SCRN\0data/bin/menu/str_cm.gp2\0str_cm_<LG>.nat\0data/pack_lv5/chara_pd.gp2\0"
                         "data/bin/keyboard_cm.bin\0data/bin/keyboard_cs.bin\0" "1\0 \0W\0data/prm/level%d.bin\0" "0";
#define STRING(offset, text) (sStrings + (offset))
#endif

void CharacterCreation::Load(SafeAllocator* allocator)
{
    // The sizes of the allocators: .rodata has them among the variables (the compiler sorts a function's static
    // variables with them, emitting them even though the code uses their values as immediates)
    static const unsigned int sSize1 = 0x3400;
    static const unsigned int sSize5 = 0x2000;
    static const unsigned int sSize0 = 0x3800;
    static const unsigned char sConstant1 = 7;
    static const unsigned int sSize3 = 0x2b240;
    static const unsigned int sSize4 = 0xc00;
    static const unsigned int sSize2 = 0x1000;
    static const unsigned int sSize6 = 0x400;
    static const unsigned int sSize8 = 0x1800;
    static const unsigned int sSize7 = 0x800;
    // Two more constants of this kind, *likely* the counts of sPartNameIDs and sPartNames
    static const int sConstant0 = 0x29;
    if (allocator == NULL)
        return;

    allocators_[0].CreateTypeA(allocator->Allocate(sSize0), sSize0);
    allocators_[1].CreateTypeA(allocator->Allocate(sSize1), sSize1);
    allocators_[2].CreateTypeA(allocator->Allocate(sSize2), sSize2);
    allocators_[3].CreateTypeA(allocator->Allocate(sSize3), sSize3);
    allocators_[4].CreateTypeA(allocator->Allocate(sSize4), sSize4);
    allocators_[5].CreateTypeA(allocator->Allocate(sSize5), sSize5);
    allocators_[6].CreateTypeA(allocator->Allocate(sSize6), sSize6);
    allocators_[7].CreateTypeA(allocator->Allocate(sSize7), sSize7);
    allocators_[8].CreateTypeA(allocator->Allocate(sSize8), sSize8);
    names_ = (char**)allocator->Allocate(8);
    for (int i = 0; i < 2; i++)
    {
        names_[i] = (char*)allocator->Allocate(0x48);
        memset(names_[i], 0, 0x48);
    }
    keyboard_ = (Keyboard*)allocator->Allocate(0x28);
    layout_ = (KeyboardLayout*)allocator->Allocate(0x10);
    func_ov003_0215efb8(keyboard_);
    func_ov003_0215e6d8(layout_);
    renderer_ = (SpriteRenderer*)allocator->Allocate(0x54);
    sprites_ = (Sprite*)allocator->Allocate(0xf0);
    unk_7e0 = allocator->Allocate(8);
    renderer2_ = (SpriteRenderer*)allocator->Allocate(0x54);
    sprites2_ = (Sprite*)allocator->Allocate(0x3e8);
    unk_7ec = allocator->Allocate(8);
    if (mode_ != 0)
        return;

    modelAllocator_ = (SafeAllocator*)allocator->Allocate(0x14);
    previewAllocators_ = (SafeAllocator*)allocator->Allocate(0x28);
    modelAllocator_->ResetAllocatorPointer();
    for (int i = 0; i < 2; i++)
        previewAllocators_[i].ResetAllocatorPointer();
    modelAllocator_->CreateTypeA(allocator->Allocate(0xc000), 0xc000);
    previewAllocators_[0].CreateTypeA(allocator->Allocate(0x3000), 0x3000);
    previewAllocators_[1].CreateTypeA(allocator->Allocate(0x1800), 0x1800);
}

void CharacterCreation::Initialize(int vocation, int mode)
{
    mode_ = mode;
    if (mode_ == 1)
        func_020466e4(func_020d6c00(), 0xf);
    allocators_[0].ResetAllocatorPointer();
    allocators_[1].ResetAllocatorPointer();
    allocators_[2].ResetAllocatorPointer();
    allocators_[3].ResetAllocatorPointer();
    allocators_[4].ResetAllocatorPointer();
    allocators_[5].ResetAllocatorPointer();
    allocators_[6].ResetAllocatorPointer();
    allocators_[7].ResetAllocatorPointer();
    allocators_[8].ResetAllocatorPointer();
    modelAllocator_ = NULL;
    previewAllocators_ = NULL;
    keyboard_ = NULL;
    layout_ = NULL;
    func_020de848(&partNames_);
    func_020dfc40(&texts_);
    unk_f8 = NULL;
    checker_.Initialize();
    func_0204af64(&backgrounds_[0]);
    func_0204af64(&backgrounds_[1]);
    func_0204af64(&backgrounds_[2]);
    func_0204af64(&backgrounds_[3]);
    func_0204af64(&backgrounds_[4]);
    func_0204af64(&backgrounds_[5]);
    func_0205cfd4(&windows_[0]);
    func_0205cfd4(&windows_[1]);
    for (int i = 0; i < 1; i++)
        func_0204c684(&canvases_[i]);
    for (int i = 0; i < 4; i++)
        func_0204c684(&canvases2_[i]);
    pixels_ = NULL;
    pixels2_ = NULL;
    renderer_ = NULL;
    sprites_ = NULL;
    unk_7e0 = NULL;
    renderer2_ = NULL;
    sprites2_ = NULL;
    unk_7ec = NULL;
    characters_[0] = NULL;
    characters_[1] = NULL;
    character_ = NULL;
    nextCharacter_ = NULL;
    unk_800 = 0;
    targetAngle_ = 0;
    object_.Initialize();
    object2_.Initialize();
    func_0205bef8(&cursor_);
    grid_.Reset();
    cursorX_ = -1;
    cursorY_ = -1;
    cursorWidth_ = -1;
    cursorHeight_ = -1;
    lastX_ = -1;
    lastY_ = -1;
    state_ = 0;
    step_ = 0;
    selection_ = 0;
    unk_d85 = 0;
    member_ = NULL;
    touchedChoice_ = -1;
    task_ = 0;
    loadStep_ = 0;
    timer_ = 0;
    unk_d98 = 0;
    memset(&flags_, 0, sizeof(flags_));
    for (int i = 0; i < 2; i++)
        lastStates_[i] = 1;
    vocation_ = vocation;
    sex_ = 0;
    for (int i = 0; i < 2; i++)
    {
        bodyType_[i] = 0;
        hairStyle_[i] = 0;
        skinColor_[i] = 0;
        eyeColor_[i] = 0;
        face_[i] = 0;
        hairColor_[i] = 0;
    }
    names_ = NULL;
    unk_db4 = func_020424e4(STRING(0x0, "*"), 0);
    unk_db6 = 0;
}

void ChoiceGrid::Reset()
{
    x_ = y_ = -1;
    width_ = height_ = -1;
    stepX_ = -1;
    stepY_ = -1;
    columns_ = -1;
    rows_ = -1;
}

void ForbiddenWordChecker::Initialize()
{
    memset(&file_, 0, sizeof(file_));
    unk_24 = 0;
    unk_28 = 0;
    unsigned char* symbol = symbols_;
    for (int i = 0; i < 15; i++)
        *symbol++ = func_020424e4(sSymbols[i], 1);
}

void CharacterCreation::Finish()
{
    if (mode_ == 1)
        func_020466f4(func_020d6c00(), 0xf);
    characters_[0]->Finish();
    characters_[1]->Finish();
    MessageSystem* messages = func_020421a0();
    func_02045cac();
    func_02043204(messages);
    func_02043124(messages);
    if (renderer_ != NULL)
        func_0205a494(renderer_);
    if (renderer2_ != NULL)
        func_0205a494(renderer2_);
    func_0203bd14();
    func_0203c4c4();

    BackgroundGraphics* backgrounds[] = {&backgrounds_[0], &backgrounds_[1], &backgrounds_[2],
                                         &backgrounds_[3], &backgrounds_[4], &backgrounds_[5]};
    for (int i = 0; i < 6; i++)
    {
        BackgroundGraphics* background = backgrounds[i];
        func_0204b010(background, 0);
        func_0204b04c(background, 0);
        func_0204b088(background, 0);
        func_0204afb4(background);
    }
    func_0205d048(&windows_[0]);
    func_0205d048(&windows_[1]);
    unk_f8 = NULL;
    pixels_ = NULL;
    pixels2_ = NULL;
    if (previewAllocators_ != NULL)
    {
        previewAllocators_[0].Destroy();
        previewAllocators_[1].Destroy();
    }
    if (modelAllocator_ != NULL)
        modelAllocator_->Destroy();

    SafeAllocator* allocators[10] = {&allocators_[8], &allocators_[7], &allocators_[6], &allocators_[5],
                                     &allocators_[4], &allocators_[3], &allocators_[2], &allocators_[1],
                                     &allocators_[0]};
    for (int i = 0; allocators[i] != NULL; i++)
    {
        if (allocators[i]->GetSignedAllocator() != 0)
            allocators[i]->Destroy();
    }
}

int CharacterCreation::Update()
{
    unsigned int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (state_ != 0)
        func_020a20d8(camera_);
    if (state_ == 9 && step_ == 2)
    {
        Canvas* canvas = func_0205d8c4(&windows_[1]);
        if (canvas != NULL && func_0204c7cc() != 0 && !(canvas->flags_ & 2))
            func_0205bc24(&windows_[1].base_.frame_, -1);
    }
    func_0205d0e0(&windows_[0], ticks);
    unk_d85 = func_0205d0e0(&windows_[1], ticks);
    if (flags_ & 0x200)
    {
        object_.AdvanceEffects();
        object2_.AdvanceEffects();
    }
    if (character_ != NULL)
        character_->Update();
    if (nextCharacter_ != NULL)
        nextCharacter_->Update();
    Turn(ticks);
    SwapCharacters();
    UpdateCharacter();

    void (CharacterCreation::*states[])() = {
        &CharacterCreation::State_Load,      &CharacterCreation::State_Sex,
        &CharacterCreation::State_BodyType,  &CharacterCreation::State_Face,
        &CharacterCreation::State_HairColor, &CharacterCreation::State_HairStyle,
        &CharacterCreation::State_EyeColor,  &CharacterCreation::State_SkinColor,
        &CharacterCreation::State_Name,      &CharacterCreation::State_Confirm,
        &CharacterCreation::State_Finish,    &CharacterCreation::State_Exit,
        0,
    };
    if (states[state_] == 0)
        return 0;
    (this->*states[state_])();
    QueueBackgrounds();
    return state_ == 12;
}

// The file's variables, defined here for the original's layout: the compiler sorts them by size, and the order of the ones
// with the same size depends on where they're defined (see Decompiling.md)

struct ChoiceIDs
{
    signed char ids_[10];
};

// The scale of the body of each body type, for each sex
struct BodyScale
{
    short width_;
    short height_;
};

// The parts whose names are copied to the party member: the part (an index in the models) and where its name goes
struct PartName
{
    unsigned char model_;
    unsigned char name_;
    char unk_2[5];
};

// Where the camera looks from and at when the character is created
static const Vector3fix sFinishPosition = {0, 0xf800, 0x42ccc};
static const signed char sFinishScreens[3] = {3, 1, 0};
// The same for the sub screen's backgrounds of the other states
static const unsigned char sPriorities[2] = {0, 1};
static const signed char sLoadScreens[4] = {3, 1, 0, 0};
static const signed char sScreens[2] = {2, 1};
// Which mode each palette of the files is for
static const unsigned char sPaletteModes[2] = {0, 1};
static const signed char sFinishUnk[3] = {2, 1, 0};
// For each state, the files of its two backgrounds, and -1 at the end
static const signed char sStateBackgrounds[] = {1, 2, 2, 2, 5, 5, 3, 5, 1, 4, 5, 0, 5, 5, 1,
                                                6, 5, 0, 7, 5, 0, 8, 5, 4, -1, -1, -1};
static const signed char sLoadUnk2[4] = {2, 1, 0, 0};
// The color of the skin of each choice
static const unsigned char sSkinColors[8] = {12, 13, 4, 1, 6, 7, 9, 14};
#ifndef NONMATCHING
// The models of a new character: the initializer of State_Load()'s local array, which the compiler copies from here
static const short sDefaultModels[10] = {-1, -1, 0, 0, -1, -1, -1, -1, -1, -1};
#endif
// The loading of the backgrounds of the final state: their priorities (and more) and the files that they have
static const unsigned char sFinishPriorities[3] = {1, 2, 3};
// Where the camera looks from and at, while the hair style or the skin color are chosen, and after
static const Vector3fix sHeadPosition = {0x9000, 0x12800, 0x2f000};
// The IDs of the names of the parts in the file of their names
static const short sPartNameIDs[0x29] = {
    0x3e2, 0x3e8, 0x1f41, 0x1f4a, 0x2328, 0x2329, 0x232a, 0x232b, 0x232c, 0x232d, 0x232e, 0x232f, 0x2330, 0x2331,
    0x233c, 0x233d, 0x233e, 0x233f, 0x2340, 0x2341, 0x2342, 0x2343, 0x2344, 0x2345, 0x4e24, 0x4fb3, 0x5078, 0x4e84,
    0x32cd, 0x3f55, 0x36b5, 0x32cf, 0x32d0, 0x3f57, 0x42e0, 0x36b7, 0x36b8, 0x43fe, 0x5014, 0x50dc, 0x4a6a};
static const ChoiceIDs sChoiceIDs = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
static const Vector3fix sHeadTarget = {0x9000, 0x12800, 0};
static const Vector3fix sBodyPosition = {0xd000, 0xf800, 0x42ccc};
// The same for the skin color
static const Vector3fix sSkinPosition = {0x9000, 0x12800, 0x2f000};
static const Vector3fix sSkinTarget = {0x9000, 0x12800, 0};
static const Vector3fix sSkinBodyPosition = {0xd000, 0xf800, 0x42ccc};
// How many random names there are for each sex
static const int sRandomNameCounts[2] = {101, 101};
static const Vector3fix sSkinBodyTarget = {0xd000, 0xf800, 0};
static const BodyScale sBodyScales[2][5] = {
    {{0xeb8, 0x109f}, {0xe35, 0x1028}, {0xf0a, 0xfae}, {0x1024, 0xf33}, {0xf1e, 0xeb4}},
    {{0xeb8, 0x1051}, {0xe39, 0xffb}, {0xee1, 0xf85}, {0x1024, 0xf33}, {0xeb8, 0xeb4}},
};
static const unsigned char sLoadPriorities[4] = {1, 2, 3, 2};
// The grid of the choices of each state: the state, then the grid (see ChoiceGrid), and -1 at the end
static const short sGrids[] = {
    1, 0x40, 0x30, 0x80, 0x20, 0, 0x30, 1, 2,
    2, 0x20, 0x28, 0x20, 0x48, 0x28, 0, 5, 1,
    3, 0x20, 0x28, 0x20, 0x20, 0x28, 0x28, 5, 2,
    4, 0x20, 0x28, 0x20, 0x20, 0x28, 0x28, 5, 2,
    5, 0x20, 0x28, 0x20, 0x20, 0x28, 0x28, 5, 2,
    7, 0x28, 0x28, 0x20, 0x20, 0x30, 0x28, 4, 2,
    6, 0x28, 0x28, 0x20, 0x20, 0x30, 0x28, 4, 2,
    8, 0x18, 0x38, 0x10, 0x10, 0x10, 0x10, 11, 6,
    -1,
};
static const PartName sPartNames[7] = {{0, 0}, {1, 1}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}};
static const Vector3fix sFinishTarget = {0, 0xf800, 0};
// The sizes of the pixels of the sub screen's canvases
static const unsigned short sCanvasSizes[4] = {0x200, 0x80, 0x80, 0x80};
// The backgrounds of the first states: their priorities (and more) and the files that they have
static const unsigned char sLoadUnk[4] = {0, 0, 0, 1};
static const Vector3fix sBodyTarget = {0xd000, 0xf800, 0};

void CharacterCreation::Draw2D()
{
    signed char state = state_;
    if (state != 0 && state != 12)
    {
        UpdateBackgrounds();
        UpdateSprites();
        UpdateAnimations();
        if (state_ != 10)
        {
            func_0205d1e0(&windows_[0]);
            func_0205d228(&windows_[0]);
            func_0205d274(&windows_[0]);
        }
        func_0205d1e0(&windows_[1]);
        func_0205d228(&windows_[1]);
        func_0205d274(&windows_[1]);
    }
}

void CharacterCreation::Draw3D()
{
    signed char state = state_;
    if (state != 0 && state != 12)
    {
        GXFIFO_MATRIX_PUSH = 0;
        character_->Draw(NULL);
        if (flags_ & 0x200)
        {
            object_.Draw(true);
            object2_.Draw(true);
        }
        GXFIFO_MATRIX_POP = 1;
    }
}

void CharacterCreation::UpdateGraphics()
{
    LoadBackgrounds();
    signed char state = state_;
    if (state == 0 || state == 12)
        return;
    if (flags_ & 0x80)
        return;
    func_0205d2bc(&windows_[0]);
    func_0205d2bc(&windows_[1]);
    if (flags_ & 0x1000)
    {
        func_0204b088(&backgrounds_[1], 0);
        flags_ &= ~0x1000;
    }
    if (flags_ & 0x2000)
    {
        func_0204b088(&backgrounds_[4], 0);
        if (state == 8 || state == 9)
            func_0204b088(&backgrounds_[3], 0);
        flags_ &= ~0x2000;
    }
    UpdateStateWindow();
    ClearChoiceWindow();
    UpdateNameWindow();
    UpdateConfirmWindow();
}

void CharacterCreation::QueueBackgrounds()
{
    if (!(flags_ & 0x80) || loadStep_ == 2)
        return;

    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int state = state_;
    if (loadStep_ == 0)
    {
        short id = state;
        if ((state == 3) | ((state == 2) | (state == 5)))
            id += sex_ * 100;
        const char* name = func_020e0434(&texts_, id + 50);
        task_ = loader->QueueLoadFileInGP2(func_020e0434(&texts_, id), name, NULL);
        loadStep_ = 1;
    }
    else if (loadStep_ == 1)
    {
        if (loader->GetTaskStatus(task_) != 0)
            loadStep_ = 2;
    }
}

void CharacterCreation::LoadBackgrounds()
{
    int firstEnd;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int first;
    int last;
    signed char state = state_;
    if (loadStep_ != 2)
        return;

    if (state == 10)
    {
        allocators_[0].Reset();
        BackgroundGraphics* backgrounds[] = {&backgrounds_[0], &backgrounds_[1], &backgrounds_[2]};
        for (int i = 0; i < 3; i++)
        {
            BackgroundGraphics* background = backgrounds[i];
            func_0204af64(background);
            func_0204b11c(background, 0);
            background->unk_1c_0_ = 0;
            background->unk_1c_4_ = sFinishPriorities[i];
            func_0204b5b4(background, sFinishScreens[i]);
            func_0204b5e8(background, 0, 0);
            func_0204b12c(background, &allocators_[0]);
            if (sFinishUnk[i] > 0)
                func_0204af38(background, sFinishUnk[i], &allocators_[0]);
        }
        char name[4];
        void* archive;
        unsigned int archiveSize;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        if (mode_ == 1)
            count--;
        for (int i = 0; i < count; i++)
        {
            unsigned int size;
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
            {
                if (i == 2)
                {
                    func_0204b174(&backgrounds_[1], file, &allocators_[0], size);
                    func_0204b174(&backgrounds_[2], file, &allocators_[0], size);
                }
                else
                {
                    func_0204b174(&backgrounds_[0], file, &allocators_[0], size);
                }
            }
        }
        loader->RemoveTask(task_);
        task_ = -1;
        func_0204b8d0(&backgrounds_[0], 0, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
        func_0204b0e8(&backgrounds_[0], 0);
        func_0204bc74(&backgrounds_[1], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[1], 0);
        func_0204bc74(&backgrounds_[2], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[2], 0);
        flags_ &= ~0x80;
        loadStep_ = 0;
        return;
    }

    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x1500;
    allocators_[1].Reset();
    first = 0;
    BackgroundGraphics* backgrounds[] = {&backgrounds_[3], &backgrounds_[4]};
    for (int i = 0; i < 2; i++)
    {
        BackgroundGraphics* background = backgrounds[i];
        func_0204af64(background);
        func_0204b11c(background, 0);
        background->unk_1c_0_ = 1;
        background->unk_1c_4_ = sPriorities[i];
        func_0204b5b4(background, sScreens[i]);
        func_0204b5e8(background, 0, 0);
        func_0204b12c(background, &allocators_[1]);
        unsigned char screen = 0;
        for (int j = 0; sStateBackgrounds[j] >= 0; j += 3)
        {
            if (state == sStateBackgrounds[j])
            {
                screen = sStateBackgrounds[j + i + 1];
                if (i == 0)
                    first = screen;
                break;
            }
        }
        if (screen != 0)
            func_0204af38(background, screen, &allocators_[1]);
    }

    char name[4];
    void* archive;
    unsigned int archiveSize;
    unsigned int size;
    loader->GetLoadedFileByID(task_, &archive, &archiveSize);
    int count = func_02046900(archive);
    if (state == 8)
        unk_db6 = unk_db6 == 0 ? 1 : 0;
    unsigned char palette = 0;
    last = count - 1;
    firstEnd = first + 1;
    void* file;
    for (int i = 0; i < count; i++)
    {
        file = func_020467f0(archive, i, name, &size);
        if (file == NULL)
            continue;
        char type[5] = {};
        memcpy(type, file, 4);
        if (memcmp(type, STRING(0x2, "PALT"), 4) == 0 && sPaletteModes[palette++] == mode_)
            continue;
        if (state == 8)
        {
            BackgroundGraphics* background = &backgrounds_[4];
            if (i < first)
                background = &backgrounds_[3];
            if (i == last)
                background = &backgrounds_[3];
            if (unk_db6 != 0)
            {
                if (i != last)
                    func_0204b2e0(background, file);
            }
            else
            {
                if (i != last)
                    func_0204b3a0(background, file);
                if (memcmp(type, STRING(0x7, "SCRN"), 4) == 0)
                    func_0204b174(background, file, &allocators_[1], size);
            }
        }
        else if (i < firstEnd)
        {
            func_0204b174(&backgrounds_[3], file, &allocators_[1], size);
        }
        else
        {
            func_0204b174(&backgrounds_[4], file, &allocators_[1], size);
        }
    }

    if (unk_db6 != 0)
        return;
    loader->RemoveTask(task_);
    task_ = -1;
    int unk = 0;
    if (mode_ == 0 && state == 1)
        unk = 1;
    if (state == 8 && mode_ == 1)
    {
        void* palettes = func_0204af14(&backgrounds_[3], 4);
        for (int i = 0; i < 4; i++)
        {
            BackgroundPart* part = (BackgroundPart*)func_0204af14(&backgrounds_[3], i);
            BackgroundGraphics graphics;
            func_0204af64(&graphics);
            func_0204b620(&graphics, part->unk_c, palettes, 0, 0, 0x13, 0x11, 4, 2, 1);
        }
    }
    func_0204b8d0(&backgrounds_[3], unk, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
    if (backgrounds_[3].unk_1d == 5)
    {
        int type = func_0200fb08(GameState::GetInstance());
        int unk2 = 0;
        switch (type)
        {
        case 2:
            unk2 = 1;
            break;
        case 4:
            unk2 = 2;
            break;
        case 3:
            unk2 = 3;
            break;
        case 5:
            unk2 = 4;
            break;
        }
        if (unk2 != 0)
            func_0204b8d0(&backgrounds_[3], unk2, 0, 0, 1, 1, 0xd, 3, 0xffff);
    }
    func_0204bc74(&backgrounds_[4], 0, 0, 0, 0x20, 0x19, 0);
    flags_ |= 0x2000;
    if (backgrounds_[4].unk_1d != 0)
        UpdateBackgrounds();
    flags_ &= ~0x2000;
    func_0204b0e8(&backgrounds_[3], 0);
    func_0204b0e8(&backgrounds_[4], 0);
    flags_ |= 0x4000;
    ClearChoiceWindow();
    flags_ &= ~0x4000;
    flags_ |= 0x8000;
    UpdateNameWindow();
    flags_ &= ~0x8000;
    flags_ &= ~0x80;
    loadStep_ = 0;
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x1700;
}

void CharacterCreation::SetState(unsigned char state)
{
    signed char newState = state;
    state_ = newState;
    step_ = 0;
    if (lastStates_[sex_] < state)
        lastStates_[sex_] = newState;
    flags_ |= 0x1100;
    if (state != 9 && state != 11 && state != 12)
        flags_ |= 0x80;
}

// NONMATCHING: the C matches 79.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original keeps two copies of sChoiceIDs on the stack that nothing reads, where GetModel() is inlined for the skin
// and hair colors; the compiler removes them, so the stack and the registers differ. Struct copies, dead arrays and
// other compiler versions didn't keep them.
#ifdef NONMATCHING
void CharacterCreation::State_Load()
{
    GameState* gameState = GameState::GetInstance();
    func_0200fb8c(gameState);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        BackgroundLoader::AddLockGlobal();
        BackgroundLoader::FreeAllocationsGlobal();
        unsigned int textsSize;
        void* texts = ExtractFileFromGP2(STRING(0xc, "data/bin/menu/str_cm.gp2"), STRING(0x25, "str_cm_<LG>.nat"), &textsSize);
        allocators_[5].Reset();
        func_020dfec0(&texts_, &allocators_[5], texts, textsSize);
        BackgroundLoader::RemoveLockGlobal();
        unk_f8 = func_020421a0()->unk_5c;
        func_020de848(&partNames_);
        BackgroundLoader::AddLockGlobal();
        unsigned int namesSize;
        void* names = ExtractFileFromGP2(data_020f2a38, data_020f2a30, &namesSize);
        if (names != NULL)
            func_020de9a4(&partNames_, &allocators_[4], names, namesSize, sPartNameIDs, 0x29);
        BackgroundLoader::RemoveLockGlobal();

        CharacterModel* character = (CharacterModel*)allocators_[3].Allocate(sizeof(CharacterModel));
        characters_[0] = character;
        character->Initialize();
        character->CreateAllocators(&allocators_[3]);
        character->InitializeVRAMStates();
        character->SetNames(&partNames_);
        CharacterModel* character2 = (CharacterModel*)allocators_[3].Allocate(sizeof(CharacterModel));
        characters_[1] = character2;
        character2->Initialize();
        character2->CreateAllocators(&allocators_[3]);
        character2->InitializeVRAMStates();
        character2->SetNames(&partNames_);

        if (mode_ == 0)
        {
            BackgroundLoader::AddLockGlobal();
            BackgroundLoader::FreeAllocationsGlobal();
            unsigned int length = 0;
            GPCReadPair pair;
            unsigned char* buffer = data_0211e33c;
            unsigned int capacity = 0x30000;
            ZeroInitGPCPointer(&pair.pGPCFile);
            pair.ZeroInitializeMachine();
            if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine, STRING(0x35, "data/pack_lv5/chara_pd.gp2"),
                                                           buffer, length, capacity, false, NULL))
            {
                unsigned int offset = length;
                capacity -= offset;
                if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer + offset, length, capacity,
                                                func_020e0434(&texts_, 2000)))
                {
                    func_0207de48(unk_808, 0xc00, 0x30);
                    func_0207df50(unk_808);
                    func_0207df90(unk_808);
                    object_.SetModelFromFileCopy(modelAllocator_, buffer + offset, length,
                                                 (Model3D::TextureStagingMode)0);
                    func_0207dfac(unk_808);
                }
            }
            BackgroundLoader::RemoveLockGlobal();
            func_0207de48(unk_c68, 0x1a00, 0x20);
            pair.Reset();
            ZeroDestroyGPCPointer(&pair.pGPCFile);
        }

        void* camera = camera_;
        func_020a2010(camera);
        func_0202e5c0(camera, 0xd000, 0xf800, 0x42ccc);
        func_0202e5c8(camera, 0xd000, 0xf800, 0);
        func_0202e0a4(camera);
        func_020a27a0(camera);
        func_020100c4(gameState, camera);
        sex_ = 0;
        bodyType_[0] = 2;
        bodyType_[1] = 2;
        hairStyle_[0] = 0;
        hairStyle_[1] = 0;
        skinColor_[0] = 0;
        skinColor_[1] = 5;
        eyeColor_[0] = 3;
        eyeColor_[1] = 3;
        face_[0] = 0;
        face_[1] = 0;
        hairColor_[0] = 0;
        hairColor_[1] = 3;
        if (mode_ == 1)
        {
            hairStyle_[0] = 1;
            hairStyle_[1] = 1;
            face_[1] = 1;
            skinColor_[1] = 0;
            hairColor_[1] = 0;
        }

        PartyMemberAppearance* appearance = &member_->details_.appearance_;
        appearance->female_ = sex_;
        appearance->eyeColor_ = eyeColor_[sex_];
        appearance->skinColor_ = GetModel(7, skinColor_[sex_]);
        appearance->hairColor_ = GetModel(4, hairColor_[sex_]);
        GetBodyScale(bodyType_[sex_], &appearance->width_, &appearance->height_);
        short hairStyle = GetModel(5, hairStyle_[sex_]) + 0x233c;
        short face = GetModel(3, face_[sex_]) + 0x2328;
        short models[10] = {-1, -1, hairStyle, face, -1, -1, -1, -1, -1, -1};
        memcpy(appearance->models_, models, sizeof(models));
        appearance->unk_16 = -1;
        character->SetScale(appearance->width_, appearance->height_);
        character2->SetScale(appearance->width_, appearance->height_);
        if (vocation_ != 0)
        {
            character->SetUnk_c11(1);
            character2->SetUnk_c11(1);
            switch (vocation_)
            {
            case 1:
            case 7:
            case 8:
                appearance->models_[7] = 0x4e24;
                break;
            case 2:
            case 9:
                appearance->models_[7] = 0x5014;
                break;
            case 3:
            case 10:
                appearance->models_[7] = 0x4fb3;
                break;
            case 4:
                appearance->models_[7] = 0x5078;
                break;
            case 6:
            case 11:
                appearance->models_[7] = 0x4e84;
                break;
            case 5:
                appearance->models_[7] = 0x4a6a;
                break;
            case 12:
                appearance->models_[7] = 0x50dc;
                break;
            }
            appearance->models_[0] = 0x32cd;
            appearance->unk_16 = 0x36b5;
            appearance->models_[1] = 0x3f55;
            appearance->models_[5] = 0x43fe;
        }
        if (mode_ == 0)
        {
            appearance->models_[0] = 0x32cf;
            appearance->unk_16 = 0x36b7;
            appearance->models_[1] = 0x3f57;
            appearance->models_[5] = 0x42e0;
        }

        BackgroundGraphics* backgrounds[] = {&backgrounds_[0], &backgrounds_[1], &backgrounds_[2], &backgrounds_[5]};
        for (int i = 0; i < 4; i++)
        {
            BackgroundGraphics* background = backgrounds[i];
            SafeAllocator* allocator = &allocators_[0];
            if (i == 3)
                allocator = &allocators_[2];
            func_0204af64(background);
            func_0204b11c(background, 0);
            background->unk_1c_0_ = sLoadUnk[i];
            background->unk_1c_4_ = sLoadPriorities[i];
            func_0204b5b4(background, sLoadScreens[i]);
            func_0204b5e8(background, 0, 0);
            func_0204b12c(background, allocator);
            if (sLoadUnk2[i] > 0)
                func_0204af38(background, sLoadUnk2[i], allocator);
        }
        signed char state = state_;
        const char* file = func_020e0434(&texts_, state + 50);
        task_ = loader->QueueLoadFileInGP2(func_020e0434(&texts_, state), file, NULL);
        step_++;
    }
    else if (step_ == 1)
    {
        if (loader->GetTaskStatus(task_) == 0)
            return;
        void* archive;
        unsigned int archiveSize;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        if (mode_ == 1)
            count--;
        for (int i = 0; i < count; i++)
        {
            char name[4];
            unsigned int size;
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
            {
                if (i == 0)
                {
                    func_0204b174(&backgrounds_[2], file, &allocators_[0], size);
                    func_0204b174(&backgrounds_[5], file, &allocators_[2], size);
                }
                else if (i <= 3)
                {
                    func_0204b174(&backgrounds_[0], file, &allocators_[0], size);
                }
                else
                {
                    func_0204b174(&backgrounds_[1], file, &allocators_[0], size);
                }
            }
        }
        loader->RemoveTask(task_);
        task_ = -1;
        int unk = 1;
        if (mode_ == 1)
            unk = 0;
        func_0204b8d0(&backgrounds_[0], unk, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
        func_0204b0e8(&backgrounds_[0], 0);
        func_0204bc74(&backgrounds_[1], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[1], 0);
        func_0204bc74(&backgrounds_[2], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[2], 0);
        func_0204bc74(&backgrounds_[5], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[5], 0);
        flags_ |= 0x1000;
        UpdateBackgrounds();
        func_0204b0e8(&backgrounds_[1], 0);
        flags_ &= ~0x1000;

        pixels_ = allocators_[0].Allocate(0x1000);
        for (int i = 0; i < 1; i++)
        {
            Canvas* canvas = &canvases_[i];
            func_0204c7a8(canvas, &allocators_[0], pixels_, 0x200);
            canvas->background_ = &backgrounds_[2];
        }
        windows_[0].background_ = &backgrounds_[2];
        windows_[0].unk_b2 = 1;
        func_0205cf78(&windows_[0], canvases_, 1);
        pixels2_ = allocators_[2].Allocate(0x400);
        for (int i = 0; i < 4; i++)
        {
            Canvas* canvas = &canvases2_[i];
            func_0204c7a8(canvas, &allocators_[2], pixels2_, sCanvasSizes[i]);
            canvas->background_ = &backgrounds_[5];
        }
        windows_[1].background_ = &backgrounds_[5];
        windows_[1].unk_b2 = 1;
        func_0205cf78(&windows_[1], canvases2_, 4);

        SpriteRenderer* renderer = renderer_;
        func_0205a444(renderer);
        renderer->unk_50 = 0;
        renderer->SetSprites(sprites_, 6);
        renderer->animations_ = (SpriteAnimationList*)unk_7e0;
        for (int i = 0; i < 6; i++)
            func_0205a198(&sprites_[i]);
        func_0205a234(unk_7e0);
        SpriteRenderer* renderer2 = renderer2_;
        func_0205a444(renderer2);
        renderer2->unk_50 = 1;
        renderer2->SetSprites(sprites2_, 25);
        renderer2->animations_ = (SpriteAnimationList*)unk_7ec;
        for (int i = 0; i < 25; i++)
            func_0205a198(&sprites2_[i]);
        func_0205a234(unk_7ec);
        const char* file = func_020e0434(&texts_, 0x41a);
        task_ = loader->QueueLoadFileInGP2(func_020e0434(&texts_, 1000), file, NULL);
        step_++;
    }
    else if (step_ == 2)
    {
        if (loader->GetTaskStatus(task_) == 0)
            return;
        void* archive;
        unsigned int archiveSize;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        allocators_[6].Reset();
        for (int i = 0; i < count; i++)
        {
            char name[4];
            unsigned int size;
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
            {
                if (i < 4)
                    func_0205a528(renderer_, file, size, &allocators_[6]);
                else
                    func_0205a528(renderer2_, file, size, &allocators_[6]);
            }
        }
        loader->RemoveTask(task_);
        task_ = -1;
        step_++;
    }
    else if (step_ == 3)
    {
        if (mode_ == 0)
            task_ = loader->QueueLoadFile(STRING(0x50, "data/bin/keyboard_cm.bin"), NULL);
        else
            task_ = loader->QueueLoadFile(STRING(0x69, "data/bin/keyboard_cs.bin"), NULL);
        step_++;
    }
    else if (step_ == 4)
    {
        if (loader->GetTaskStatus(task_) == 0)
            return;
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(task_, &file, &size);
        if (file != NULL && size != 0)
        {
            allocators_[8].Reset();
            func_ov003_0215e6f8(layout_, &allocators_[8], file, size);
            keyboard_->layout_ = layout_;
            func_ov003_0215f41c(keyboard_, STRING(0x82, "1"));
            KeyboardKey* key = func_ov003_0215f4fc(keyboard_, STRING(0x84, " "));
            if (key != NULL)
                key->unk_f = 1;
        }
        loader->RemoveTask(task_);
        task_ = -1;
        step_++;
    }
    else
    {
        characters_[0]->SetAngle(0x1eb);
        characters_[1]->SetAngle(0x1eb);
        characters_[0]->Load(member_, member_->details_.unk_4e0, 0, 0);
        characters_[1]->Load(member_, member_->details_.unk_4e0, 0, 0);
        character_ = characters_[0];
        nextCharacter_ = characters_[1];
        OpenStateWindow();
        OpenChoiceWindow();
        OpenNameWindow();
        func_0205deb4(&windows_[1], 2, 0);
        func_0205deb4(&windows_[1], 3, 0);
        SetState(1);
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11GPCReadPair21ZeroInitializeMachineEv(); // GPCReadPair::ZeroInitializeMachine
    void _ZN11GPCReadPair5ResetEv(); // GPCReadPair::Reset
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN17CharacterCreation12GetBodyScaleEiPsS0_(); // CharacterCreation::GetBodyScale
    void _ZN17CharacterCreation8GetModelEii(); // CharacterCreation::GetModel
    void _ZN17CharacterCreation8SetStateEh(); // CharacterCreation::SetState
    void _ZN8Object3D20SetModelFromFileCopyEP13SafeAllocatorPKvjN7Model3D18TextureStagingModeE(); // Object3D::SetModelFromFileCopy
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void CharacterCreation::State_Load()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xd0
    mov r9, r0
    bl _ZN9GameState11GetInstanceEv
    mov r11, r0
    bl func_0200fb8c
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r1, [r9, #0xc59]
    mov r5, r0
    cmp r1, #0x0
    bne @L02185d04
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    ldr r0, =sStrings+0xc
    ldr r1, =sStrings+0x25
    add r2, sp, #0x44
    bl ExtractFileFromGP2
    mov r4, r0
    add r0, r9, #0x64
    bl _ZN13SafeAllocator5ResetEv
    ldr r3, [sp, #0x44]
    mov r2, r4
    add r0, r9, #0xe0
    add r1, r9, #0x64
    bl func_020dfec0
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    bl func_020421a0
    ldr r1, [r0, #0x5c]
    add r0, r9, #0xc8
    str r1, [r9, #0xf8]
    bl func_020de848
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    ldr r0, =data_020f2a38
    ldr r1, =data_020f2a30
    ldr r0, [r0, #0x0]
    ldr r1, [r1, #0x0]
    add r2, sp, #0x40
    bl ExtractFileFromGP2
    movs r2, r0
    beq @L021856f4
    ldr r1, =sPartNameIDs
    mov r0, #0x29
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    ldr r3, [sp, #0x40]
    add r0, r9, #0xc8
    add r1, r9, #0x50
    bl func_020de9a4
@L021856f4:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r9, #0x3c
    mov r1, #0xc20
    bl _ZN13SafeAllocator8AllocateEj
    mov r6, r0
    str r0, [r9, #0x7f0]
    bl _ZN14CharacterModel10InitializeEv
    mov r0, r6
    add r1, r9, #0x3c
    bl _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator
    mov r0, r6
    bl _ZN14CharacterModel20InitializeVRAMStatesEv
    mov r0, r6
    add r1, r9, #0xc8
    bl _ZN14CharacterModel8SetNamesEP13PartNameTable
    add r0, r9, #0x3c
    mov r1, #0xc20
    bl _ZN13SafeAllocator8AllocateEj
    mov r7, r0
    str r0, [r9, #0x7f4]
    bl _ZN14CharacterModel10InitializeEv
    mov r0, r7
    add r1, r9, #0x3c
    bl _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator
    mov r0, r7
    bl _ZN14CharacterModel20InitializeVRAMStatesEv
    mov r0, r7
    add r1, r9, #0xc8
    bl _ZN14CharacterModel8SetNamesEP13PartNameTable
    ldrb r0, [r9, #0xd95]
    cmp r0, #0x0
    bne @L02185888
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    mov r0, #0x0
    add r4, sp, #0x80
    str r0, [sp, #0x3c]
    mov r0, r4
    ldr r10, =data_0211e33c
    mov r8, #0x30000
    bl ZeroInitGPCPointer
    mov r0, r4
    bl _ZN11GPCReadPair21ZeroInitializeMachineEv
    add r1, sp, #0x3c
    stmia sp, {r1, r8}
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    ldr r2, =sStrings+0x35
    mov r0, r4
    add r1, sp, #0x84
    mov r3, r10
    bl LoadAndDecompressGPCHeaderAndInnerFileInfo
    cmp r0, #0x0
    beq @L02185860
    ldr r4, [sp, #0x3c]
    add r0, r9, #0xe0
    sub r8, r8, r4
    mov r1, #0x7d0
    bl func_020e0434
    str r8, [sp, #0x0]
    str r0, [sp, #0x4]
    add r0, sp, #0x80
    add r1, sp, #0x84
    add r2, r10, r4
    add r3, sp, #0x3c
    bl DecompressFileFromGPCByName
    cmp r0, #0x0
    beq @L02185860
    add r0, r9, #0x8
    mov r1, #0xc00
    mov r2, #0x30
    add r0, r0, #0x800
    bl func_0207de48
    add r0, r9, #0x8
    add r0, r0, #0x800
    bl func_0207df50
    add r0, r9, #0x8
    add r0, r0, #0x800
    bl func_0207df90
    mov r0, #0x0
    str r0, [sp, #0x0]
    add r0, r9, #0x78
    ldr r1, [r9, #0xb4]
    ldr r3, [sp, #0x3c]
    add r2, r10, r4
    add r0, r0, #0x800
    bl _ZN8Object3D20SetModelFromFileCopyEP13SafeAllocatorPKvjN7Model3D18TextureStagingModeE
    add r0, r9, #0x8
    add r0, r0, #0x800
    bl func_0207dfac
@L02185860:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r9, #0x68
    add r0, r0, #0xc00
    mov r1, #0x1a00
    mov r2, #0x20
    bl func_0207de48
    add r0, sp, #0x80
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0x80
    bl ZeroDestroyGPCPointer
@L02185888:
    add r4, r9, #0x124
    add r0, r4, #0x800
    bl func_020a2010
    ldr r3, =0x42ccc
    add r0, r4, #0x800
    mov r1, #0xd000
    mov r2, #0xf800
    bl func_0202e5c0
    add r0, r4, #0x800
    mov r1, #0xd000
    mov r2, #0xf800
    mov r3, #0x0
    bl func_0202e5c8
    add r0, r4, #0x800
    bl func_0202e0a4
    add r0, r4, #0x800
    bl func_020a27a0
    mov r0, r11
    add r1, r4, #0x800
    bl func_020100c4
    mov r1, #0x0
    strb r1, [r9, #0xda3]
    mov r0, #0x2
    strb r0, [r9, #0xda4]
    strb r0, [r9, #0xda5]
    strb r1, [r9, #0xda6]
    strb r1, [r9, #0xda7]
    strb r1, [r9, #0xda8]
    mov r0, #0x5
    strb r0, [r9, #0xda9]
    mov r0, #0x3
    strb r0, [r9, #0xdaa]
    strb r0, [r9, #0xdab]
    strb r1, [r9, #0xdac]
    strb r1, [r9, #0xdad]
    strb r1, [r9, #0xdae]
    strb r0, [r9, #0xdaf]
    ldrb r0, [r9, #0xd95]
    cmp r0, #0x1
    bne @L02185940
    mov r0, #0x1
    strb r0, [r9, #0xda6]
    strb r0, [r9, #0xda7]
    strb r0, [r9, #0xdad]
    strb r1, [r9, #0xda9]
    strb r1, [r9, #0xdaf]
@L02185940:
    ldr r0, [r9, #0xd88]
    ldrb r1, [r9, #0xda3]
    add r0, r0, #0x88
    add r4, r0, #0x400
    ldrb r2, [r4, #0x14]
    and r0, r1, #0x1
    ldr r3, =sChoiceIDs
    bic r1, r2, #0x1
    orr r0, r1, r0
    strb r0, [r4, #0x14]
    ldrb r1, [r9, #0xda3]
    and r0, r0, #0xff
    bic r0, r0, #0xe
    add r1, r9, r1
    ldrb r8, [r1, #0xdaa]
    add r2, sp, #0x52
    mov r1, #0xa
    mov r8, r8, lsl #0x1d
    orr r0, r0, r8, lsr #0x1c
    strb r0, [r4, #0x14]
    ldrb r0, [r9, #0xda3]
    add r0, r9, r0
    ldrb r8, [r0, #0xda8]
@L0218599c:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L0218599c
    ldrb r1, [r4, #0x14]
    and r0, r8, #0xff
    mov r0, r0, lsl #0x1c
    bic r1, r1, #0xf0
    orr r0, r1, r0, lsr #0x18
    strb r0, [r4, #0x14]
    ldrb r0, [r9, #0xda3]
    ldr r3, =sChoiceIDs
    add r2, sp, #0x48
    add r0, r9, r0
    ldrb r8, [r0, #0xdae]
    mov r1, #0xa
@L021859dc:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021859dc
    ldrb r1, [r4, #0x15]
    and r0, r8, #0xff
    and r0, r0, #0xf
    bic r1, r1, #0xf
    orr r0, r1, r0
    strb r0, [r4, #0x15]
    ldrb r1, [r9, #0xda3]
    mov r0, r9
    add r2, r4, #0x18
    add r1, r9, r1
    ldrb r1, [r1, #0xda4]
    add r3, r4, #0x1a
    bl _ZN17CharacterCreation12GetBodyScaleEiPsS0_
    ldrb r2, [r9, #0xda3]
    mov r0, r9
    mov r1, #0x5
    add r2, r9, r2
    ldrb r2, [r2, #0xda6]
    bl _ZN17CharacterCreation8GetModelEii
    add r0, r0, #0x33c
    add r0, r0, #0x2000
    mov r1, r0, lsl #0x10
    ldrb r2, [r9, #0xda3]
    mov r8, r1, asr #0x10
    mov r1, #0x3
    add r0, r9, r2
    ldrb r2, [r0, #0xdac]
    mov r0, r9
    bl _ZN17CharacterCreation8GetModelEii
    add r0, r0, #0x328
    add r0, r0, #0x2000
    mov r0, r0, lsl #0x10
    ldr r10, =sDefaultModels
    mov r3, r0, asr #0x10
    add r2, sp, #0x6c
    mov r1, #0xa
@L02185a7c:
    ldrh r0, [r10], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L02185a7c
    add r1, sp, #0x6c
    mov r0, r4
    mov r2, #0x14
    strh r8, [sp, #0x70]
    strh r3, [sp, #0x72]
    bl memcpy
    mvn r0, #0x0
    strh r0, [r4, #0x16]
    ldrsh r1, [r4, #0x18]
    ldrsh r2, [r4, #0x1a]
    mov r0, r6
    bl _ZN14CharacterModel8SetScaleEii
    ldrsh r1, [r4, #0x18]
    ldrsh r2, [r4, #0x1a]
    mov r0, r7
    bl _ZN14CharacterModel8SetScaleEii
    ldrb r0, [r9, #0xda2]
    cmp r0, #0x0
    beq @L02185ba4
    mov r0, r6
    mov r1, #0x1
    bl _ZN14CharacterModel10SetUnk_c11Eh
    mov r0, r7
    mov r1, #0x1
    bl _ZN14CharacterModel10SetUnk_c11Eh
    ldrb r0, [r9, #0xda2]
    cmp r0, #0xc
    addls pc, pc, r0, lsl #0x2
    b @L02185b84
@L02185b00:
    b @L02185b84
    b @L02185b34
    b @L02185b40
    b @L02185b4c
    b @L02185b58
    b @L02185b70
    b @L02185b64
    b @L02185b34
    b @L02185b34
    b @L02185b40
    b @L02185b4c
    b @L02185b64
    b @L02185b7c
@L02185b34:
    ldr r0, =0x4e24
    strh r0, [r4, #0xe]
    b @L02185b84
@L02185b40:
    ldr r0, =0x5014
    strh r0, [r4, #0xe]
    b @L02185b84
@L02185b4c:
    ldr r0, =0x4fb3
    strh r0, [r4, #0xe]
    b @L02185b84
@L02185b58:
    ldr r0, =0x5078
    strh r0, [r4, #0xe]
    b @L02185b84
@L02185b64:
    ldr r0, =0x4e84
    strh r0, [r4, #0xe]
    b @L02185b84
@L02185b70:
    ldr r0, =0x4a6a
    strh r0, [r4, #0xe]
    b @L02185b84
@L02185b7c:
    ldr r0, =0x50dc
    strh r0, [r4, #0xe]
@L02185b84:
    ldr r0, =0x32cd
    ldr r1, =0x3f55
    strh r0, [r4, #0x0]
    add r0, r0, #0x3e8
    strh r0, [r4, #0x16]
    ldr r0, =0x43fe
    strh r1, [r4, #0x2]
    strh r0, [r4, #0xa]
@L02185ba4:
    ldrb r0, [r9, #0xd95]
    cmp r0, #0x0
    bne @L02185bd0
    ldr r0, =0x32cf
    ldr r1, =0x3f57
    strh r0, [r4, #0x0]
    add r0, r0, #0x3e8
    strh r0, [r4, #0x16]
    ldr r0, =0x42e0
    strh r1, [r4, #0x2]
    strh r0, [r4, #0xa]
@L02185bd0:
    add r3, r9, #0x138
    add r2, r9, #0x158
    add r1, r9, #0x178
    add r0, r9, #0x1d8
    str r3, [sp, #0x5c]
    str r2, [sp, #0x60]
    str r1, [sp, #0x64]
    str r0, [sp, #0x68]
    mov r7, #0x0
    add r6, sp, #0x5c
    ldr r4, =sLoadUnk
    ldr r11, =sLoadPriorities
    b @L02185ca8
@L02185c04:
    ldr r8, [r6, r7, lsl #0x2]
    mov r10, r9
    mov r0, r8
    cmp r7, #0x3
    addeq r10, r9, #0x28
    bl func_0204af64
    mov r0, r8
    mov r1, #0x0
    bl func_0204b11c
    ldrb r1, [r4, r7]
    ldrb r2, [r8, #0x1c]
    ldrb r0, [r11, r7]
    and r1, r1, #0xf
    bic r2, r2, #0xf
    orr r1, r2, r1
    strb r1, [r8, #0x1c]
    and r1, r1, #0xff
    mov r0, r0, lsl #0x1c
    bic r1, r1, #0xf0
    orr r0, r1, r0, lsr #0x18
    ldr r1, =sLoadScreens
    strb r0, [r8, #0x1c]
    ldrsb r1, [r1, r7]
    mov r0, r8
    bl func_0204b5b4
    mov r1, #0x0
    mov r0, r8
    mov r2, r1
    bl func_0204b5e8
    mov r0, r8
    mov r1, r10
    bl func_0204b12c
    ldr r0, =sLoadUnk2
    ldrsb r1, [r0, r7]
    cmp r1, #0x0
    ble @L02185ca4
    mov r0, r8
    mov r2, r10
    and r1, r1, #0xff
    bl func_0204af38
@L02185ca4:
    add r7, r7, #0x1
@L02185ca8:
    cmp r7, #0x4
    blt @L02185c04
    add r0, r9, #0xc00
    ldrsb r6, [r0, #0x58]
    add r0, r9, #0xe0
    add r1, r6, #0x32
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_020e0434
    mov r4, r0
    mov r1, r6
    add r0, r9, #0xe0
    bl func_020e0434
    mov r1, r0
    mov r0, r5
    mov r2, r4
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r9, #0xd90]
    ldrb r0, [r9, #0xc59]
    add r0, r0, #0x1
    strb r0, [r9, #0xc59]
    b @L0218633c
@L02185d04:
    cmp r1, #0x1
    bne @L021860e0
    ldr r1, [r9, #0xd90]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0218633c
    ldr r1, [r9, #0xd90]
    add r2, sp, #0x34
    add r3, sp, #0x30
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x34]
    bl func_02046900
    ldrb r1, [r9, #0xd95]
    mov r8, r0
    mov r10, #0x0
    cmp r1, #0x1
    subeq r8, r8, #0x1
    add r7, sp, #0x38
    add r6, sp, #0x2c
    b @L02185de0
@L02185d58:
    ldr r0, [sp, #0x34]
    mov r1, r10
    mov r2, r7
    mov r3, r6
    bl func_020467f0
    movs r4, r0
    beq @L02185ddc
    cmp r10, #0x0
    bne @L02185da8
    ldr r3, [sp, #0x2c]
    mov r1, r4
    mov r2, r9
    add r0, r9, #0x178
    bl func_0204b174
    ldr r3, [sp, #0x2c]
    mov r1, r4
    add r0, r9, #0x1d8
    add r2, r9, #0x28
    bl func_0204b174
    b @L02185ddc
@L02185da8:
    cmp r10, #0x3
    bgt @L02185dc8
    ldr r3, [sp, #0x2c]
    mov r1, r4
    mov r2, r9
    add r0, r9, #0x138
    bl func_0204b174
    b @L02185ddc
@L02185dc8:
    ldr r3, [sp, #0x2c]
    mov r1, r4
    mov r2, r9
    add r0, r9, #0x158
    bl func_0204b174
@L02185ddc:
    add r10, r10, #0x1
@L02185de0:
    cmp r10, r8
    blt @L02185d58
    ldr r1, [r9, #0xd90]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r9, #0xd90]
    ldrb r0, [r9, #0xd95]
    mov r2, #0x0
    mov r1, #0x1
    cmp r0, #0x1
    str r2, [sp, #0x0]
    str r2, [sp, #0x4]
    mov r0, #0x20
    str r0, [sp, #0x8]
    mov r0, #0x18
    str r0, [sp, #0xc]
    ldr r4, =0xffff
    moveq r1, #0x0
    mov r3, r2
    add r0, r9, #0x138
    str r4, [sp, #0x10]
    bl func_0204b8d0
    add r0, r9, #0x138
    mov r1, #0x0
    bl func_0204b0e8
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    mov r2, r1
    mov r3, r1
    add r0, r9, #0x158
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r9, #0x158
    mov r1, #0x0
    bl func_0204b0e8
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    add r0, r9, #0x178
    mov r2, r1
    mov r3, r1
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r9, #0x178
    mov r1, #0x0
    bl func_0204b0e8
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    add r0, r9, #0x1d8
    mov r2, r1
    mov r3, r1
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r9, #0x1d8
    mov r1, #0x0
    bl func_0204b0e8
    ldr r1, [r9, #0xd9c]
    mov r0, r9
    orr r1, r1, #0x1000
    str r1, [r9, #0xd9c]
    bl _ZN17CharacterCreation17UpdateBackgroundsEv
    add r0, r9, #0x158
    mov r1, #0x0
    bl func_0204b0e8
    ldr r1, [r9, #0xd9c]
    mov r0, r9
    bic r1, r1, #0x1000
    str r1, [r9, #0xd9c]
    mov r1, #0x1000
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r9, #0x7d0]
    mov r11, #0x200
    mov r10, #0x0
    add r7, r9, #0x370
    add r6, r9, #0x178
    mov r4, #0xe0
    b @L02185f58
@L02185f38:
    mla r8, r10, r4, r7
    ldr r2, [r9, #0x7d0]
    mov r0, r8
    mov r1, r9
    mov r3, r11
    bl func_0204c7a8
    str r6, [r8, #0x4]
    add r10, r10, #0x1
@L02185f58:
    cmp r10, #0x1
    blt @L02185f38
    add r0, r9, #0x178
    str r0, [r9, #0x290]
    mov r2, #0x1
    add r0, r9, #0x1f8
    add r1, r9, #0x370
    strb r2, [r9, #0x2aa]
    bl func_0205cf78
    add r0, r9, #0x28
    mov r1, #0x400
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r9, #0x7d4]
    mov r10, #0x0
    add r7, r9, #0x450
    add r4, r9, #0x1d8
    ldr r6, =sCanvasSizes
    mov r11, #0xe0
    b @L02185fc8
@L02185fa4:
    mla r8, r10, r11, r7
    mov r0, r10, lsl #0x1
    ldrh r3, [r6, r0]
    ldr r2, [r9, #0x7d4]
    mov r0, r8
    add r1, r9, #0x28
    bl func_0204c7a8
    str r4, [r8, #0x4]
    add r10, r10, #0x1
@L02185fc8:
    cmp r10, #0x4
    blt @L02185fa4
    add r0, r9, #0x1d8
    str r0, [r9, #0x34c]
    mov r0, #0x1
    strb r0, [r9, #0x366]
    add r0, r9, #0x2b4
    add r1, r9, #0x450
    mov r2, #0x4
    bl func_0205cf78
    ldr r6, [r9, #0x7d8]
    mov r0, r6
    bl func_0205a444
    mov r4, #0x0
    strb r4, [r6, #0x50]
    ldr r1, [r9, #0x7dc]
    mov r0, #0x6
    str r1, [r6, #0x40]
    strh r0, [r6, #0x4c]
    ldr r0, [r9, #0x7e0]
    str r0, [r6, #0x3c]
    mov r6, #0x28
    b @L02186034
@L02186024:
    ldr r0, [r9, #0x7dc]
    mla r0, r4, r6, r0
    bl func_0205a198
    add r4, r4, #0x1
@L02186034:
    cmp r4, #0x6
    blt @L02186024
    ldr r0, [r9, #0x7e0]
    bl func_0205a234
    ldr r4, [r9, #0x7e4]
    mov r0, r4
    bl func_0205a444
    mov r0, #0x1
    strb r0, [r4, #0x50]
    ldr r1, [r9, #0x7e8]
    mov r0, #0x19
    str r1, [r4, #0x40]
    strh r0, [r4, #0x4c]
    ldr r0, [r9, #0x7ec]
    mov r6, #0x0
    str r0, [r4, #0x3c]
    mov r4, #0x28
    b @L0218608c
@L0218607c:
    ldr r0, [r9, #0x7e8]
    mla r0, r6, r4, r0
    bl func_0205a198
    add r6, r6, #0x1
@L0218608c:
    cmp r6, #0x19
    blt @L0218607c
    ldr r0, [r9, #0x7ec]
    bl func_0205a234
    ldr r1, =0x41a
    add r0, r9, #0xe0
    bl func_020e0434
    mov r4, r0
    add r0, r9, #0xe0
    mov r1, #0x3e8
    bl func_020e0434
    mov r2, r4
    mov r1, r0
    mov r0, r5
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r9, #0xd90]
    ldrb r0, [r9, #0xc59]
    add r0, r0, #0x1
    strb r0, [r9, #0xc59]
    b @L0218633c
@L021860e0:
    cmp r1, #0x2
    bne @L021861a8
    ldr r1, [r9, #0xd90]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0218633c
    ldr r1, [r9, #0xd90]
    add r2, sp, #0x24
    add r3, sp, #0x20
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x24]
    bl func_02046900
    mov r7, r0
    add r0, r9, #0x78
    bl _ZN13SafeAllocator5ResetEv
    mov r8, #0x0
    add r6, sp, #0x28
    add r4, sp, #0x1c
    b @L0218617c
@L02186130:
    ldr r0, [sp, #0x24]
    mov r1, r8
    mov r2, r6
    mov r3, r4
    bl func_020467f0
    movs r1, r0
    beq @L02186178
    cmp r8, #0x4
    bge @L02186168
    ldr r0, [r9, #0x7d8]
    ldr r2, [sp, #0x1c]
    add r3, r9, #0x78
    bl func_0205a528
    b @L02186178
@L02186168:
    ldr r0, [r9, #0x7e4]
    ldr r2, [sp, #0x1c]
    add r3, r9, #0x78
    bl func_0205a528
@L02186178:
    add r8, r8, #0x1
@L0218617c:
    cmp r8, r7
    blt @L02186130
    ldr r1, [r9, #0xd90]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r9, #0xd90]
    ldrb r0, [r9, #0xc59]
    add r0, r0, #0x1
    strb r0, [r9, #0xc59]
    b @L0218633c
@L021861a8:
    cmp r1, #0x3
    bne @L021861e8
    ldrb r1, [r9, #0xd95]
    mov r2, #0x0
    cmp r1, #0x0
    bne @L021861cc
    ldr r1, =sStrings+0x50
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    b @L021861d4
@L021861cc:
    ldr r1, =sStrings+0x69
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
@L021861d4:
    str r0, [r9, #0xd90]
    ldrb r0, [r9, #0xc59]
    add r0, r0, #0x1
    strb r0, [r9, #0xc59]
    b @L0218633c
@L021861e8:
    cmp r1, #0x4
    bne @L02186298
    ldr r1, [r9, #0xd90]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0218633c
    ldr r1, [r9, #0xd90]
    add r2, sp, #0x18
    add r3, sp, #0x14
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x18]
    cmp r0, #0x0
    ldrne r0, [sp, #0x14]
    cmpne r0, #0x0
    beq @L02186274
    add r0, r9, #0xa0
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r9, #0xc4]
    ldr r2, [sp, #0x18]
    ldr r3, [sp, #0x14]
    add r1, r9, #0xa0
    bl func_ov003_0215e6f8
    ldr r2, [r9, #0xc4]
    ldr r0, [r9, #0xc0]
    ldr r1, =sStrings+0x82
    str r2, [r0, #0x4]
    ldr r0, [r9, #0xc0]
    bl func_ov003_0215f41c
    ldr r0, [r9, #0xc0]
    ldr r1, =sStrings+0x84
    bl func_ov003_0215f4fc
    cmp r0, #0x0
    movne r1, #0x1
    strneb r1, [r0, #0xf]
@L02186274:
    ldr r1, [r9, #0xd90]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r9, #0xd90]
    ldrb r0, [r9, #0xc59]
    add r0, r0, #0x1
    strb r0, [r9, #0xc59]
    b @L0218633c
@L02186298:
    ldr r0, [r9, #0x7f0]
    ldr r1, =0x1eb
    bl _ZN14CharacterModel8SetAngleEi
    ldr r0, [r9, #0x7f4]
    ldr r1, =0x1eb
    bl _ZN14CharacterModel8SetAngleEi
    mov r3, #0x0
    str r3, [sp, #0x0]
    ldr r1, [r9, #0xd88]
    ldr r0, [r9, #0x7f0]
    add r2, r1, #0x500
    ldrsh r2, [r2, #0x68]
    bl _ZN14CharacterModel4LoadEP15PartyMemberDataiii
    mov r3, #0x0
    str r3, [sp, #0x0]
    ldr r0, [r9, #0x7f4]
    ldr r1, [r9, #0xd88]
    add r2, r1, #0x500
    ldrsh r2, [r2, #0x68]
    bl _ZN14CharacterModel4LoadEP15PartyMemberDataiii
    ldr r1, [r9, #0x7f0]
    mov r0, r9
    str r1, [r9, #0x7f8]
    ldr r1, [r9, #0x7f4]
    str r1, [r9, #0x7fc]
    bl _ZN17CharacterCreation15OpenStateWindowEv
    mov r0, r9
    bl _ZN17CharacterCreation16OpenChoiceWindowEv
    mov r0, r9
    bl _ZN17CharacterCreation14OpenNameWindowEv
    add r0, r9, #0x2b4
    mov r1, #0x2
    mov r2, #0x0
    bl func_0205deb4
    add r0, r9, #0x2b4
    mov r1, #0x3
    mov r2, #0x0
    bl func_0205deb4
    mov r0, r9
    mov r1, #0x1
    bl _ZN17CharacterCreation8SetStateEh
@L0218633c:
    add sp, sp, #0xd0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void CharacterCreation::State_Sex()
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    if (step_ == 0)
    {
        if (func_0203b57c(resources, 0) == -16 && func_0203b57c(resources, 1) == -16)
        {
            if (flags_ & 0x80)
                return;
            SetBrightness(resources, 0, 15);
        }
        ResetCursor();
        SetGrid();
        SetCursor(sex_);
        step_++;
    }
    if (step_ == 1)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        flags_ |= 1;
        step_++;
    }
    else if (step_ == 2)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(sex_);
        step_++;
    }
    else if (step_ == 3)
    {
        int result = UpdateChoice();
        if (result != state_)
        {
            CharacterModel* next = nextCharacter_;
            if (next->loading_ == 0)
            {
                next->Hide(0);
                next->Hide(2);
                next->Hide(3);
                next->Hide(4);
            }
        }
        if (result == -2)
        {
            SetState(2);
            return;
        }
        if (result == -3)
        {
            if (mode_ == 1)
                flags_ &= ~0x400;
            else if (mode_ == 0)
                gameState->unk_63d4 = 0;
            SetState(11);
            return;
        }
        if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
                SetState(state);
        }
    }
}

void CharacterCreation::State_BodyType()
{
    if (step_ == 0)
    {
        ResetCursor();
        SetGrid();
        SetCursor(bodyType_[sex_]);
        flags_ |= 1;
        step_++;
    }
    else if (step_ == 1)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(bodyType_[sex_]);
        step_++;
    }
    else if (step_ == 2)
    {
        int result = UpdateChoice();
        if (result == -2)
        {
            SetState(3);
            return;
        }
        if (result == -3)
        {
            SetState(1);
            return;
        }
        if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
                SetState(state);
        }
    }
}

void CharacterCreation::State_HairStyle()
{
    if (step_ == 0)
    {
        ResetCursor();
        SetGrid();
        SetCursor(hairStyle_[sex_]);
        Vector3fix position = sHeadPosition;
        Vector3fix target = sHeadTarget;
        func_0202ee38(camera_, &position, 0x1e000);
        func_0202ee58(camera_, &target, 0x1e000);
        flags_ |= 1;
        step_++;
    }
    else if (step_ == 1)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(hairStyle_[sex_]);
        step_++;
    }
    else if (step_ == 2)
    {
        int result = UpdateChoice();
        int changed = 0;
        if (result == -2)
        {
            SetState(6);
            changed = 1;
        }
        else if (result == -3)
        {
            SetState(4);
            changed = 1;
        }
        else if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
            {
                SetState(state);
                changed = 1;
            }
        }
        if (changed)
        {
            Vector3fix position = sBodyPosition;
            Vector3fix target = sBodyTarget;
            func_0202ee38(camera_, &position, 0x1e000);
            func_0202ee58(camera_, &target, 0x1e000);
        }
    }
}

void CharacterCreation::State_Face()
{
    if (step_ == 0)
    {
        ResetCursor();
        SetGrid();
        SetCursor(face_[sex_]);
        flags_ |= 1;
        step_++;
    }
    else if (step_ == 1)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(face_[sex_]);
        step_++;
    }
    else if (step_ == 2)
    {
        int result = UpdateChoice();
        if (result == -2)
        {
            SetState(4);
            return;
        }
        if (result == -3)
        {
            SetState(2);
            return;
        }
        if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
                SetState(state);
        }
    }
}

void CharacterCreation::State_HairColor()
{
    if (step_ == 0)
    {
        ResetCursor();
        SetGrid();
        SetCursor(hairColor_[sex_]);
        flags_ |= 1;
        step_++;
    }
    else if (step_ == 1)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(hairColor_[sex_]);
        step_++;
    }
    else if (step_ == 2)
    {
        int result = UpdateChoice();
        if (result == -2)
        {
            SetState(5);
            return;
        }
        if (result == -3)
        {
            SetState(3);
            return;
        }
        if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
                SetState(state);
        }
    }
}

void CharacterCreation::State_EyeColor()
{
    if (step_ == 0)
    {
        ResetCursor();
        SetGrid();
        SetCursor(eyeColor_[sex_]);
        flags_ |= 1;
        step_++;
    }
    else if (step_ == 1)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(eyeColor_[sex_]);
        step_++;
    }
    else if (step_ == 2)
    {
        int result = UpdateChoice();
        if (result == -2)
        {
            SetState(7);
            return;
        }
        if (result == -3)
        {
            SetState(5);
            return;
        }
        if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
                SetState(state);
        }
    }
}

void CharacterCreation::State_SkinColor()
{
    if (step_ == 0)
    {
        ResetCursor();
        SetGrid();
        SetCursor(skinColor_[sex_]);
        Vector3fix position = sSkinPosition;
        Vector3fix target = sSkinTarget;
        func_0202ee38(camera_, &position, 0x1e000);
        func_0202ee58(camera_, &target, 0x1e000);
        targetAngle_ = 0x1eb;
        flags_ = (flags_ | 8) & ~1;
        step_++;
    }
    else if (step_ == 1)
    {
        if (flags_ & 0x80)
            return;
        SetChoice(skinColor_[sex_]);
        step_++;
    }
    else if (step_ == 2)
    {
        if (!(flags_ & 1) && !(flags_ & 8))
            flags_ |= 1;
        int result = UpdateChoice();
        int changed = 0;
        if (result == -2)
        {
            SetState(8);
            changed = 1;
        }
        else if (result == -3)
        {
            SetState(6);
            changed = 1;
        }
        else if (result >= 101 && result <= 108)
        {
            int state = result - 100;
            if (state <= lastStates_[sex_] && state != state_)
            {
                SetState(state);
                changed = 1;
            }
        }
        if (changed)
        {
            Vector3fix position = sSkinBodyPosition;
            Vector3fix target = sSkinBodyTarget;
            func_0202ee38(camera_, &position, 0x1e000);
            func_0202ee58(camera_, &target, 0x1e000);
        }
    }
}

void CharacterCreation::State_Name()
{
    if (step_ == 0)
    {
        keyboard_->SetText(names_[sex_], 0x48);
        keyboard_->unk_14 = 8;
        keyboard_->unk_1f = 0;
        keyboard_->unk_21 = 0;
        keyboard_->unk_24 = 1;
        func_ov003_0215f41c(keyboard_, STRING(0x82, "1"));
        savedKey_ = keyboard_->key_;
        if (savedKey_ != NULL)
            keyboard_->key_ = savedKey_;
        savedKey_ = NULL;
        CharacterInfo* info = (CharacterInfo*)func_0204254c(STRING(0x86, "W"), 0);
        if (info != NULL)
            keyboard_->unk_c = info->unk_4 * 8 + 7;
        step_++;
    }
    else if (step_ == 1)
    {
        keyboard_->unk_18 = 0;
        keyboard_->unk_1c = 0;
        flags_ |= 1;
        flags_ &= ~0x800;
        flags_ |= 0x8100;
        step_++;
    }
    else if (step_ == 2)
    {
        if (flags_ & 0x80)
            return;
        keyboardResult_ = func_ov003_0215f000(keyboard_, GameState::GetInstance()->GetTickCount());
        int result = UpdateChoice();
        if (keyboardResult_ != 0)
            result = -1;
        int checked = 0;
        if (result == -2)
        {
            checked = 1;
            CheckName();
        }
        else if (result == -3)
        {
            SetState(7);
            return;
        }
        else if (result >= 101 && result <= 108)
        {
            result -= 100;
            if (result <= lastStates_[sex_] && result != state_)
            {
                SetState(result);
                return;
            }
        }

        flags_ |= 0x2000;
        switch (keyboardResult_)
        {
        case 1:
            func_0205eaa0(data_02108760, 2, 0);
            break;
        case 9:
            if (!func_02012444(data_02114e30, 1) && data_02114e54.touching_ == 0)
                SetState(7);
            else
                func_0205eaa0(data_02108760, 1, 0);
            flags_ |= 0x8100;
            break;
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 11:
            if (!func_02012444(data_02114e30, 2))
                func_0205eaa0(data_02108760, 1, 0);
            flags_ |= 0x8100;
            break;
        case 3:
            func_0205eaa0(data_02108760, 1, 0);
            flags_ |= 0x8100;
            UpdateNameWindow();
            if (func_02012444(data_02114e30, 1))
            {
                KeyboardKey* key = func_ov003_0215f4a4(keyboard_, 6);
                if (key != NULL)
                    keyboard_->key_ = key;
            }
            break;
        case 10:
            if (*names_[sex_] == 0)
                func_0205eaa0(data_02108760, 1, 0);
            if (checked == 0)
            {
                checked = 1;
                func_0205eaa0(data_02108760, 1, 0);
                CheckName();
            }
            break;
        case 13:
            func_0205eaa0(data_02108760, 1, 0);
            break;
        case 12:
            func_0205eaa0(data_02108760, 1, 0);
            SetRandomName();
            flags_ |= 0x8100;
            return;
        default:
            flags_ &= ~0x2000;
            if (func_02012444(data_02114e30, 4) && result != -2)
            {
                if (keyboard_->key_ != NULL)
                {
                    SetRandomName();
                    flags_ |= 0x8100;
                    return;
                }
            }
            else if (func_02012444(data_02114e30, 0xc0))
            {
                flags_ |= 0x2000;
            }
            break;
        }

        if (keyboardResult_ != 0 && keyboardResult_ != 8)
        {
            WindowCursor* cursor = &cursor_;
            func_0205bef8(cursor);
            func_0205ba68(cursor, 11, 6, 1);
            func_0205bacc(cursor, 0x42);
            cursor->unk_4 = 1;
            func_0205bb04(cursor, 0);
        }
        if (func_02012444(data_02114e30, 8) && !(flags_ & 0x8100) && keyboard_->key_ != NULL && checked == 0)
            CheckName();
        if (flags_ & 0x400000)
        {
            flags_ |= 0x2000 | 0x1000000;
            step_++;
        }
        if (flags_ & 0x800)
        {
            WindowCursor* cursor = &cursor_;
            func_0205bef8(cursor);
            func_0205ba68(cursor, 11, 6, 1);
            func_0205bacc(cursor, 0x42);
            cursor->unk_4 = 1;
            func_0205bb04(cursor, 0);
            func_ov003_0215f4e4(keyboard_, 6);
            flags_ |= 0x1000000;
            sprintf(member_->name_, data_020ef078, names_[sex_]);
            SetState(9);
        }
    }
    else if (step_ == 3)
    {
        if (func_02012444(data_02114e30, 0x401) || data_02114e54.touching_ != 0)
        {
            func_0205eaa0(data_02108760, 1, 0);
            flags_ = (flags_ & ~0x1400000) | 0x2000;
            step_ = 2;
        }
        else if (func_02012444(data_02114e30, 2))
        {
            flags_ = (flags_ & ~0x1400000) | 0x2000;
            step_ = 2;
        }
    }

    KeyboardKey* key = keyboard_->key_;
    if (key != NULL)
    {
        short width;
        short height;
        func_ov003_0215ec68(key->size_, &width, &height);
        cursorX_ = key->x_;
        cursorY_ = key->y_;
        cursorWidth_ = width;
        cursorHeight_ = height;
    }
}

// NONMATCHING: the C matches 64.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original lays out the structures on the stack in another order (the skills of the vocations below the others),
// and keeps other values in registers in the loop over the names of the parts.
#ifdef NONMATCHING
void CharacterCreation::State_Confirm()
{
    GameState* gameState = GameState::GetInstance();
    func_020d6c00();
    if (step_ == 0)
    {
        OpenConfirmWindow();
        func_0205deb4(&windows_[1], 3, 2);
        func_0205eaa0(data_02108760, 5, 0);
        step_++;
    }
    else if (step_ == 1)
    {
        flags_ |= 0x2000;
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 1, -8);
        flags_ &= ~0x1000000;
        step_++;
    }
    else if (step_ == 2)
    {
        selection_ = func_0205d794(&windows_[1]);
        int cancel = 0;
        int touched = func_0205da38(&windows_[1], 0x14);
        int a = func_02012444(data_02114e30, 1);
        if (touched | (a | func_02012444(data_02114e30, 0x400)))
        {
            func_0205eaa0(data_02108760, 1, cancel);
            switch ((signed char)selection_)
            {
            case 0:
                step_++;
                break;
            case 1:
                cancel = 1;
                break;
            }
        }
        else if (func_02012444(data_02114e30, 2))
        {
            cancel = 1;
        }
        if (step_ == 3)
        {
            func_0205d6a0(&windows_[1], 0);
            func_0205deb4(&windows_[1], 3, 2);
            flags_ &= ~0x60;
        }
        else if (cancel)
        {
            func_0205d6a0(&windows_[1], 0);
            flags_ &= ~0x60;
            step_ = 0xff;
        }
    }
    else if (step_ == 3)
    {
        func_0204b010(&backgrounds_[4], 0);
        func_0204bc74(&backgrounds_[4], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b04c(&backgrounds_[4], 0);
        func_0204b088(&backgrounds_[4], 0);
        if (mode_ == 0)
        {
            member_->details_.unk_4e2 = sSkinColors[skinColor_[sex_]];
            gameState->unk_63d4 = 1;
            ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 1, 0);
            func_0205deb4(&windows_[1], 3, 0);
            func_0205d1e0(&windows_[1]);
            func_0205d228(&windows_[1]);
            func_0205d274(&windows_[1]);
            func_0205d2bc(&windows_[1]);
            SetState(10);
        }
        else if (mode_ == 1)
        {
            MemberStatistics statistics;
            LevelStatistics levelStatistics;
            LevelTable levels;
            VocationSkills skills;
            char path[0x20];
            unsigned int size;
            Unknown_0209a804 unknown;
            PartyMemberData* member = member_;
            void* party = func_02010828(gameState);
            func_02086404(&statistics);
            func_02083ca0(member, vocation_);
            member->details_.unk_b0[vocation_] = 0;
            member->details_.levels_[vocation_] = 1;
            member->details_.unk_4e2 = NextRandomMax(GetBTRandom(), 16);
            sprintf(path, STRING(0x88, "data/prm/level%d.bin"), member->vocation_);
            func_0208247c(&levels);
            BackgroundLoader::AddLockGlobal();
            void* file = LoadFileIntoMemory(path, data_0211e33c, &size);
            if (file != NULL)
                func_02082490(&levels, file, size, member->details_.levels_[vocation_], 0);
            func_02083cbc(member, &levels, &levelStatistics);
            BackgroundLoader::RemoveLockGlobal();
            short* models = member->details_.appearance_.models_;
            for (int i = 0; i < 7; i++)
            {
                const void* name = func_020dedd0(&partNames_, models[sPartNames[i].model_]);
                if (name != NULL)
                    memcpy(member->details_.unk_10c[sPartNames[i].name_], name, 0x20);
            }
            func_02083e28(member, 0);
            func_020863c4(member);
            statistics.unk_14c_0 = member->unk_0_0;
            statistics.unk_14c_10 = member->unk_0_10;
            statistics.unk_14c_20 = member->unk_0_20;
            statistics.unk_150_0 = member->unk_4_0;
            statistics.unk_150_10 = member->unk_4_10;
            statistics.unk_150_20 = member->unk_4_20;
            statistics.unk_154_0 = member->unk_8_0;
            statistics.unk_154_10 = member->unk_6c;
            statistics.unk_154_20 = member->unk_6e;
            statistics.unk_158_0 = member->unk_6c;
            statistics.unk_158_10 = member->unk_6e;
            statistics.unk_158_20 = member->unk_70;
            statistics.unk_15c_0 = member->unk_72;
            statistics.unk_15c_10 = member->unk_c_0;
            func_0209a804(&unknown);
            func_0209a810(&unknown, &skills);
            LevelSkill* vocationSkills = skills.skills_[(unsigned char)member->vocation_];
            unsigned char level = member->details_.levels_[member->vocation_];
            for (int i = 0; i < 20; i++)
            {
                if (level >= vocationSkills[i].level_ && vocationSkills[i].level_ != 0)
                    func_02083b60(member, vocationSkills[i].skill_);
            }
            func_020830cc(member, &statistics);
            func_02086778(party, &statistics, 0, 0);
            flags_ |= 0x400;
            SetState(11);
        }
    }
    else if (step_ == 0xff)
    {
        func_0204b010(&backgrounds_[4], 0);
        func_0204bc74(&backgrounds_[4], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b04c(&backgrounds_[4], 0);
        func_0204b088(&backgrounds_[4], 0);
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 1, 0);
        func_0205deb4(&windows_[1], 3, 0);
        func_0205deb4(&windows_[1], 2, 0);
        KeyboardKey* key = func_ov003_0215f4fc(keyboard_, STRING(0x82, "1"));
        if (key != NULL)
            keyboard_->key_ = key;
        keyboard_->unk_1e = 1;
        keyboard_->unk_20 = 0;
        SetState(8);
        step_ = 1;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN17CharacterCreation8SetStateEh(); // CharacterCreation::SetState
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void CharacterCreation::State_Confirm()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x14
    sub sp, sp, #0x800
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_020d6c00
    ldrb r0, [r10, #0xc59]
    cmp r0, #0x0
    bne @L0218748c
    mov r0, r10
    bl _ZN17CharacterCreation17OpenConfirmWindowEv
    add r0, r10, #0x2b4
    mov r1, #0x3
    mov r2, #0x2
    bl func_0205deb4
    ldr r0, =data_02108760
    mov r1, #0x5
    mov r2, #0x0
    bl func_0205eaa0
    ldrb r0, [r10, #0xc59]
    add r0, r0, #0x1
    strb r0, [r10, #0xc59]
    b @L02187b00
@L0218748c:
    cmp r0, #0x1
    bne @L021874cc
    ldr r0, [r10, #0xd9c]
    mov r1, #0x1
    orr r2, r0, #0x2000
    ldr r0, =0x4001050
    str r2, [r10, #0xd9c]
    sub r2, r1, #0x9
    bl ColorEffect_ConfigureBrightnessAdjust
    ldr r0, [r10, #0xd9c]
    bic r0, r0, #0x1000000
    str r0, [r10, #0xd9c]
    ldrb r0, [r10, #0xc59]
    add r0, r0, #0x1
    strb r0, [r10, #0xc59]
    b @L02187b00
@L021874cc:
    cmp r0, #0x2
    bne @L021875d0
    add r0, r10, #0x2b4
    bl func_0205d794
    strb r0, [r10, #0xd84]
    add r0, r10, #0x2b4
    mov r1, #0x14
    mov r4, #0x0
    bl func_0205da38
    mov r6, r0
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    mov r5, r0
    ldr r0, =data_02114e30
    mov r1, #0x400
    bl func_02012444
    orr r0, r5, r0
    orrs r0, r6, r0
    beq @L02187558
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, r4
    bl func_0205eaa0
    add r0, r10, #0xd00
    ldrsb r0, [r0, #0x84]
    cmp r0, #0x0
    beq @L02187548
    cmp r0, #0x1
    moveq r4, #0x1
    b @L0218756c
@L02187548:
    ldrb r0, [r10, #0xc59]
    add r0, r0, #0x1
    strb r0, [r10, #0xc59]
    b @L0218756c
@L02187558:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    movne r4, #0x1
@L0218756c:
    ldrb r0, [r10, #0xc59]
    cmp r0, #0x3
    bne @L021875a4
    add r0, r10, #0x2b4
    mov r1, #0x0
    bl func_0205d6a0
    add r0, r10, #0x2b4
    mov r1, #0x3
    mov r2, #0x2
    bl func_0205deb4
    ldr r0, [r10, #0xd9c]
    bic r0, r0, #0x60
    str r0, [r10, #0xd9c]
    b @L02187b00
@L021875a4:
    cmp r4, #0x0
    beq @L02187b00
    add r0, r10, #0x2b4
    mov r1, #0x0
    bl func_0205d6a0
    ldr r1, [r10, #0xd9c]
    mov r0, #0xff
    bic r1, r1, #0x60
    str r1, [r10, #0xd9c]
    strb r0, [r10, #0xc59]
    b @L02187b00
@L021875d0:
    cmp r0, #0x3
    bne @L02187a38
    add r0, r10, #0x1b8
    mov r1, #0x0
    bl func_0204b010
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    mov r2, r1
    mov r3, r1
    add r0, r10, #0x1b8
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r10, #0x1b8
    mov r1, #0x0
    bl func_0204b04c
    add r0, r10, #0x1b8
    mov r1, #0x0
    bl func_0204b088
    ldrb r0, [r10, #0xd95]
    cmp r0, #0x0
    bne @L021876a4
    ldrb r0, [r10, #0xda3]
    ldr r1, =sSkinColors
    ldr r5, [r10, #0xd88]
    add r0, r10, r0
    ldrb r2, [r0, #0xda8]
    ldr r0, =0x4001050
    add r3, r4, #0x6000
    ldrb r4, [r1, r2]
    mov r1, #0x1
    mov r2, #0x0
    strb r4, [r5, #0x56a]
    strb r1, [r3, #0x3d4]
    bl ColorEffect_ConfigureBrightnessAdjust
    add r0, r10, #0x2b4
    mov r1, #0x3
    mov r2, #0x0
    bl func_0205deb4
    add r0, r10, #0x2b4
    bl func_0205d1e0
    add r0, r10, #0x2b4
    bl func_0205d228
    add r0, r10, #0x2b4
    bl func_0205d274
    add r0, r10, #0x2b4
    bl func_0205d2bc
    mov r0, r10
    mov r1, #0xa
    bl _ZN17CharacterCreation8SetStateEh
    b @L02187b00
@L021876a4:
    cmp r0, #0x1
    bne @L02187b00
    mov r0, r4
    ldr r6, [r10, #0xd88]
    bl func_02010828
    mov r7, r0
    add r0, sp, #0x500
    add r0, r0, #0xd8
    bl func_02086404
    ldrb r1, [r10, #0xda2]
    mov r0, r6
    bl func_02083ca0
    ldrb r0, [r10, #0xda2]
    mov r2, #0x0
    mov r1, #0x1
    add r0, r6, r0, lsl #0x2
    str r2, [r0, #0x138]
    ldrb r0, [r10, #0xda2]
    add r0, r6, r0, lsl #0x1
    add r0, r0, #0x100
    strh r1, [r0, #0x6c]
    bl GetBTRandom
    mov r1, #0x10
    bl NextRandomMax
    strb r0, [r6, #0x56a]
    ldr r2, [r6, #0x950]
    ldr r1, =sStrings+0x88
    add r0, sp, #0x14
    bl sprintf
    add r0, sp, #0x500
    add r0, r0, #0x84
    bl func_0208247c
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    ldr r1, =data_0211e33c
    add r0, sp, #0x14
    add r2, sp, #0x10
    bl LoadFileIntoMemory
    movs r1, r0
    beq @L02187768
    mov r0, #0x0
    str r0, [sp, #0x0]
    ldrb r3, [r10, #0xda2]
    add r0, sp, #0x500
    ldr r2, [sp, #0x10]
    add r3, r6, r3, lsl #0x1
    add r3, r3, #0x100
    ldrh r3, [r3, #0x6c]
    add r0, r0, #0x84
    bl func_02082490
@L02187768:
    add r1, sp, #0x500
    add r1, r1, #0x84
    add r2, sp, #0x5c0
    mov r0, r6
    bl func_02083cbc
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r6, #0x88
    add r8, r0, #0x400
    mov r9, #0x0
    add r4, r6, #0x194
    ldr r5, =sPartNames
    mov r11, #0x20
    b @L021877d8
@L0218779c:
    rsb r0, r9, r9, lsl #0x3
    ldrb r1, [r5, r0]
    add r0, r10, #0xc8
    mov r1, r1, lsl #0x1
    ldrsh r1, [r8, r1]
    bl func_020dedd0
    movs r1, r0
    beq @L021877d4
    rsb r0, r9, r9, lsl #0x3
    add r0, r5, r0
    ldrb r0, [r0, #0x1]
    mov r2, r11
    add r0, r4, r0, lsl #0x5
    bl memcpy
@L021877d4:
    add r9, r9, #0x1
@L021877d8:
    cmp r9, #0x7
    blt @L0218779c
    mov r0, r6
    mov r1, #0x0
    bl func_02083e28
    mov r0, r6
    bl func_020863c4
    add r1, sp, #0x700
    add r1, r1, #0x24
    ldr r0, [r6, #0x0]
    mov r3, #0x400
    rsb r3, r3, #0x0
    ldr r5, [r1, #0x0]
    mov r2, r0, lsl #0x16
    mov r0, r3, lsr #0x16
    and r5, r5, r3
    and r0, r0, r2, lsr #0x16
    orr r2, r5, r0
    str r2, [r1, #0x0]
    ldr r0, [r6, #0x0]
    ldr r4, =0xfff003ff
    mov r0, r0, lsl #0xc
    mov r0, r0, lsr #0x16
    ldr r8, [r1, #0x4]
    and r2, r2, r4
    mov r0, r0, lsl #0x16
    orr r5, r2, r0, lsr #0xc
    str r5, [r1, #0x0]
    ldr r0, [r6, #0x0]
    ldr r2, =0xc00fffff
    mov r0, r0, lsl #0x2
    mov r0, r0, lsr #0x16
    and r5, r5, r2
    mov r0, r0, lsl #0x16
    orr r0, r5, r0, lsr #0x2
    str r0, [r1, #0x0]
    ldr r5, [r6, #0x4]
    add r0, r4, #0x100000
    mov r5, r5, lsl #0x16
    and r8, r8, r3
    and r0, r0, r5, lsr #0x16
    orr r5, r8, r0
    str r5, [r1, #0x4]
    ldr r0, [r6, #0x4]
    ldr r8, [r1, #0x8]
    mov r0, r0, lsl #0xc
    mov r0, r0, lsr #0x16
    and r5, r5, r4
    mov r0, r0, lsl #0x16
    orr r5, r5, r0, lsr #0xc
    str r5, [r1, #0x4]
    ldr r0, [r6, #0x4]
    and r5, r5, r2
    mov r0, r0, lsl #0x2
    mov r0, r0, lsr #0x16
    mov r0, r0, lsl #0x16
    orr r0, r5, r0, lsr #0x2
    str r0, [r1, #0x4]
    ldr r5, [r6, #0x8]
    add r0, r4, #0x100000
    mov r5, r5, lsl #0x16
    and r8, r8, r3
    and r0, r0, r5, lsr #0x16
    orr r5, r8, r0
    str r5, [r1, #0x8]
    ldrh r0, [r6, #0x6c]
    and r5, r5, r4
    mov r0, r0, lsl #0x16
    orr r5, r5, r0, lsr #0xc
    str r5, [r1, #0x8]
    ldrh r0, [r6, #0x6e]
    and r5, r5, r2
    mov r0, r0, lsl #0x16
    orr r0, r5, r0, lsr #0x2
    str r0, [r1, #0x8]
    ldrh r8, [r6, #0x6c]
    ldr r5, [r1, #0xc]
    add r0, r4, #0x100000
    and r5, r5, r3
    and r0, r8, r0
    orr r8, r5, r0
    str r8, [r1, #0xc]
    ldrh r5, [r6, #0x6e]
    ldr r0, [r1, #0x10]
    and r8, r8, r4
    mov r5, r5, lsl #0x16
    orr r8, r8, r5, lsr #0xc
    str r8, [r1, #0xc]
    ldrh r5, [r6, #0x70]
    and r8, r8, r2
    and r3, r0, r3
    mov r5, r5, lsl #0x16
    orr r5, r8, r5, lsr #0x2
    str r5, [r1, #0xc]
    ldrh r5, [r6, #0x72]
    add r2, r4, #0x100000
    add r0, sp, #0xc
    and r2, r5, r2
    orr r3, r3, r2
    str r3, [r1, #0x10]
    ldr r2, [r6, #0xc]
    and r3, r3, r4
    mov r2, r2, lsl #0x16
    mov r2, r2, lsr #0x16
    mov r2, r2, lsl #0x16
    orr r2, r3, r2, lsr #0xc
    str r2, [r1, #0x10]
    bl func_0209a804
    add r0, sp, #0xc
    add r1, sp, #0x34
    bl func_0209a810
    ldr r3, [r6, #0x950]
    add r1, sp, #0x140
    add r0, r6, r3, lsl #0x1
    add r0, r0, #0x100
    ldrh r2, [r0, #0x6c]
    and r3, r3, #0xff
    mov r0, #0x50
    mla r5, r3, r0, r1
    and r4, r2, #0xff
    mov r8, #0x0
    b @L021879ec
@L021879c0:
    add r0, r5, r8, lsl #0x2
    ldrh r0, [r0, #0x2]
    mov r1, r8, lsl #0x2
    cmp r4, r0
    blt @L021879e8
    cmp r0, #0x0
    beq @L021879e8
    ldrh r1, [r5, r1]
    mov r0, r6
    bl func_02083b60
@L021879e8:
    add r8, r8, #0x1
@L021879ec:
    cmp r8, #0x14
    blt @L021879c0
    add r1, sp, #0x500
    add r1, r1, #0xd8
    mov r0, r6
    bl func_020830cc
    mov r2, #0x0
    add r1, sp, #0x500
    add r1, r1, #0xd8
    mov r0, r7
    mov r3, r2
    bl func_02086778
    ldr r1, [r10, #0xd9c]
    mov r0, r10
    orr r2, r1, #0x400
    mov r1, #0xb
    str r2, [r10, #0xd9c]
    bl _ZN17CharacterCreation8SetStateEh
    b @L02187b00
@L02187a38:
    cmp r0, #0xff
    bne @L02187b00
    add r0, r10, #0x1b8
    mov r1, #0x0
    bl func_0204b010
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    mov r2, r1
    mov r3, r1
    add r0, r10, #0x1b8
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r10, #0x1b8
    mov r1, #0x0
    bl func_0204b04c
    add r0, r10, #0x1b8
    mov r1, #0x0
    bl func_0204b088
    ldr r0, =0x4001050
    mov r1, #0x1
    mov r2, #0x0
    bl ColorEffect_ConfigureBrightnessAdjust
    add r0, r10, #0x2b4
    mov r1, #0x3
    mov r2, #0x0
    bl func_0205deb4
    add r0, r10, #0x2b4
    mov r1, #0x2
    mov r2, #0x0
    bl func_0205deb4
    ldr r0, [r10, #0xc0]
    ldr r1, =sStrings+0x82
    bl func_ov003_0215f4fc
    cmp r0, #0x0
    ldrne r1, [r10, #0xc0]
    mov r2, #0x0
    strne r0, [r1, #0x0]
    ldr r1, [r10, #0xc0]
    mov r0, #0x1
    strb r0, [r1, #0x1e]
    ldr r3, [r10, #0xc0]
    mov r0, r10
    mov r1, #0x8
    strb r2, [r3, #0x20]
    bl _ZN17CharacterCreation8SetStateEh
    mov r0, #0x1
    strb r0, [r10, #0xc59]
@L02187b00:
    add sp, sp, #0x14
    add sp, sp, #0x800
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// The models that the final state loads: into which allocator, the file, and which model (2: a file of its own)
struct ModelFile
{
    SafeAllocator* allocator_;
    const char* name_;
    unsigned char model_;
};

// Converts a fixed-point value that was converted to a float back, rounding it
#define FX32_FROM_FLOAT(x) ((int)((x) > 0.0f ? 0.5f + 4096.0f * (x) : 4096.0f * (x) - 0.5f))

void CharacterCreation::State_Finish()
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    Object3D* preview = character_->GetBody();
    void* unknown = func_020d6c00();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader == NULL)
        return;
    unsigned int ticks = gameState->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    UpdateFade(ticks);
    if (UpdateTimer(ticks) > 0)
        return;

    switch (step_)
    {
    case 0:
    {
        flags_ &= ~1;
        targetAngle_ = 0x7a;
        flags_ |= 8;
        Vector3fix position = sFinishPosition;
        Vector3fix target = sFinishTarget;
        func_0202ee38(camera_, &position, 0x1e000);
        func_0202ee58(camera_, &target, 0x1e000);
        unk_d98 = 90;
        flags_ |= 0x10000;
        func_0209c678(data_02109bf4, 120);
        step_ = 1;
        int* task = modelTasks_;
        for (unsigned char i = 0; i < 3; i++)
            *task++ = -1;
        SafeAllocator* allocator = previewAllocators_;
        for (unsigned char i = 0; i < 2; i++, allocator++)
            allocator->Reset();
        break;
    }
    case 1:
        if (flags_ & 8)
            break;
        if (func_0202eeb4(camera_) != 0)
            break;
        flags_ |= 0x800000;
        if (character_->GetBody()->normalizedAnimationTime_ >= 0xccc)
        {
            func_0205ebc0(data_02108760, 0x6f, 0x6f);
            step_ = 2;
        }
        break;
    case 2:
    {
        short bodyID = sex_ * 100 + 2001;
        short headID = sex_ * 100 + 2002;
        ModelFile files[4] = {{NULL, NULL, 0}, {NULL, NULL, 1}, {NULL, NULL, 2}, {NULL, NULL, 0}};
        files[0].allocator_ = previewAllocators_;
        files[0].name_ = func_020e0434(&texts_, headID);
        files[1].allocator_ = &previewAllocators_[1];
        files[1].name_ = func_020e0434(&texts_, bodyID);
        files[2].allocator_ = modelAllocator_;
        files[2].name_ = func_020e0434(&texts_, 0x898);
        ModelFile* file = files;
        const char* archive = STRING(0x35, "data/pack_lv5/chara_pd.gp2");
        for (; file->allocator_ != NULL; file++)
        {
            int task;
            if (file->model_ == 2)
                task = loader->QueueLoadFile(file->name_, file->allocator_);
            else
                task = loader->QueueLoadFileInGP2(archive, file->name_, file->allocator_);
            modelTasks_[file->model_] = task;
        }
        step_ = 3;
        break;
    }
    case 3:
    {
        int done = 1;
        int* task = modelTasks_;
        for (unsigned char i = 0; i < 3; i++, task++)
        {
            if (*task != -1 && loader->GetTaskStatus(*task) == 0)
                done = 0;
        }
        if (done)
            step_ = 4;
        break;
    }
    case 4:
    {
        int* task = modelTasks_;
        for (unsigned char i = 0; i < 3; i++, task++)
        {
            if (*task == -1)
                continue;
            if (loader->GetTaskStatus(*task) == 1)
            {
                unsigned int size = 0;
                void* file = NULL;
                loader->GetLoadedFileByID(*task, &file, &size);
                ObjectArchiveLoadInfo info;
                info.unk_0 = 0;
                info.allocator = NULL;
                info.unk_14 = 0;
                info.unk_18 = 0;
                info.unk_10 = 0;
                info.packageID = 0;
                info.fileData = file;
                info.unk_8 = size;
                switch (i)
                {
                case 0:
                    info.allocator = previewAllocators_;
                    info.packageID = 1;
                    preview->LoadFromCHRArchive(&info);
                    break;
                case 1:
                    info.allocator = &previewAllocators_[1];
                    object_.LoadFromCHRArchive(&info);
                    break;
                case 2:
                    info.allocator = modelAllocator_;
                    func_0207df50(unk_c68);
                    func_0207df90(unk_c68);
                    object2_.LoadFromCHRArchive(&info);
                    func_0207dfac(unk_c68);
                    break;
                }
            }
            loader->RemoveTask(*task);
            *task = -1;
        }
        step_ = 5;
        preview->StopCurrentAnimation();
        preview->MaybeSetRegularAnimation(func_020e0434(&texts_, 2500), 0);
        Vector3fix rotation;
        memset(&rotation, 0, sizeof(rotation));
        rotation = preview->rotation_;
        PartyMemberAppearance* appearance = &member_->details_.appearance_;
        int scaleX;
        int scaleY;
        short width = appearance->width_;
        scaleX = FX32_FROM_FLOAT(width / 4096.0f);
        scaleY = FX32_FROM_FLOAT(appearance->height_ / 4096.0f);
        int scaleZ = FX32_FROM_FLOAT(width / 4096.0f);
        Object3D* object = &object_;
        object->SetScale(scaleX, scaleY, scaleZ);
        object->rotation_ = rotation;
        object->StopCurrentAnimation();
        object->MaybeSetRegularAnimation(func_020e0434(&texts_, 2500), 0);
        Vector3fix position;
        position = ((Object3D*)((char*)preview + 0x408))->position_;
        Object3D* object2 = &object2_;
        object2->rotation_ = rotation;
        object2->position_ = position;
        object2->StopCurrentAnimation();
        object2->MaybeSetRegularAnimation(STRING(0x9d, "0"), 0);
        flags_ |= 0x200;
        timer_ = 30;
        step_ = 6;
        break;
    }
    case 6:
        func_0205ebfc(data_02108760, 0, 0);
        timer_ = 150;
        step_ = 7;
        break;
    case 7:
        func_020466e4(unknown, 0x100);
        SetBrightness(resources, 16, 40);
        func_0205ebfc(data_02108760, 1, 0);
        step_ = 8;
        break;
    case 8:
        if (IsBrightnessTransitionActive(resources))
            break;
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT, 0x1f, -16);
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 0x1f, -16);
        timer_ = 120;
        step_ = 9;
        break;
    case 9:
        if (timer_ > 0)
        {
            unsigned int elapsed = gameState->GetTickCount();
            if (elapsed == 0)
                elapsed = 1;
            timer_ -= elapsed;
            break;
        }
        SetBrightness(resources, -16, 120);
        step_ = 10;
        break;
    case 10:
        if (IsBrightnessTransitionActive(resources))
            break;
        func_020c39a0(REG_MASTER_BRIGHT, -16);
        func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
        func_020466f4(unknown, 0x100);
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT, 0x1f, 0);
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 0x1f, 0);
        func_0205ebec(data_02108760);
        step_ = 11;
        break;
    case 11:
        step_ = 0xff;
        SetState(11);
        break;
    }
}

void CharacterCreation::State_Exit()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (step_ == 0)
    {
        SetBrightness(resources, -16, 15);
        step_++;
    }
    else if (step_ == 1)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        func_0205d6a0(&windows_[0], 1);
        func_0205d6a0(&windows_[1], 1);
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 1, 0);
        SetState(12);
    }
}

void CharacterCreation::SwapCharacters()
{
    if (!(flags_ & 4))
        return;
    CharacterModel* next = nextCharacter_;
    if (next != NULL && next->loading_ != 0)
        return;
    if (flags_ & 0x40000)
    {
        character_->SetAngle(0x1eb);
        flags_ &= ~0x40000;
    }
    nextCharacter_->SetRotation(character_->GetRotation());
    Object3D* current = character_->GetBody();
    Object3D* object = nextCharacter_->GetBody();
    int length = 0;
    int currentLength = 0;
    const char* animation = (const char*)current->activeAnimationRecord_;
    if (object->activeAnimationRecord_ != NULL)
        length = func_020d2ff0((const char*)object->activeAnimationRecord_);
    if (animation != NULL)
        currentLength = func_020d2ff0(animation);
    if (length == currentLength && animation != NULL)
    {
        object->MaybeSetRegularAnimation(animation, 0);
        object->SetCurrentAnimationTime(current->animationTime_);
    }
    CharacterModel* swap = character_;
    character_ = nextCharacter_;
    nextCharacter_ = swap;
    if (flags_ & 0x20000)
    {
        PartyMemberAppearance* appearance = &member_->details_.appearance_;
        GetBodyScale(bodyType_[sex_], &appearance->width_, &appearance->height_);
        character_->SetScale(appearance->width_, appearance->height_);
        nextCharacter_->SetScale(appearance->width_, appearance->height_);
        flags_ &= ~0x20000;
    }
    flags_ &= ~4;
}

void CharacterCreation::UpdateCharacter()
{
    if (flags_ & 2)
    {
        nextCharacter_->Load(member_, member_->details_.unk_4e0, 0, 0);
        flags_ = (flags_ | 4) & ~2;
    }
}

void CharacterCreation::Turn(unsigned int ticks)
{
    if (flags_ & 8)
    {
        int done = 0;
        Vector3fix rotation = character_->GetRotation();
        int angle;
        int y = rotation.y;
        int difference = fix32ReduceAngle0To2Pi(targetAngle_ - y);
        if (difference >= 0 && difference < 0x3244)
        {
            angle = y + difference / 12;
            for (unsigned int i = 0; i < ticks - 1; i++)
                angle += fix32ReduceAngle0To2Pi(targetAngle_ - angle) / 12;
        }
        else if (difference >= 0x3244 && difference < 0x6488)
        {
            angle = y - (0x6488 - difference) / 12;
            for (unsigned int i = 0; i < ticks - 1; i++)
                angle -= (0x6488 - fix32ReduceAngle0To2Pi(targetAngle_ - angle)) / 12;
        }
        character_->SetAngle(fix32ReduceAngle0To2Pi(angle));
        int remaining = fix32ReduceAngle0To2Pi(targetAngle_ - angle);
        if ((remaining < 0 ? -remaining : remaining) < 40)
            done = 1;
        else if (((0x6488 - remaining) < 0 ? -(0x6488 - remaining) : (0x6488 - remaining)) < 40)
            done = 1;
        if (done)
        {
            character_->SetAngle(fix32ReduceAngle0To2Pi(targetAngle_));
            targetAngle_ = 0;
            flags_ &= ~8;
        }
    }
    else if (flags_ & 1)
    {
        int left = 0;
        int right = 0;
        int touched = 0;
        int x;
        int y;
        func_02012a84(&data_02114e54, &x, &y);
        if (data_02114e54.touching_ != 0 || (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0) ||
            data_02114e54.unk_54 != 0)
        {
            touched = 1;
            if (y >= 0xa9 && y <= 0xb1)
            {
                if (x >= 0xe && x <= 0x17)
                    left = 1;
                if (x >= 0x3b && x <= 0x44)
                    right = 1;
            }
        }
        if (touched == 0)
        {
            if (func_02012430(data_02114e30, 0x200))
                left = 1;
            if (func_02012430(data_02114e30, 0x100))
                right = 1;
        }
        if (left != 0 && right != 0)
        {
            targetAngle_ = 0x1eb;
            flags_ |= 8;
        }
        else if (left != 0 || right != 0)
        {
            Vector3fix rotation = character_->GetRotation();
            if (left != 0)
                rotation.y += (int)(4096.0f * (0.08f * ticks));
            if (right != 0)
                rotation.y -= (int)(4096.0f * (0.08f * ticks));
            rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
            character_->SetRotation(rotation);
        }
    }
}

void CharacterCreation::SetChoice(int choice)
{
    PartyMemberAppearance* appearance = &member_->details_.appearance_;
    int state = state_;
    CharacterModel* next = nextCharacter_;
    CharacterModel* current = character_;
    if (state == 1)
    {
        appearance->female_ = choice;
        next->Hide(0);
        next->Hide(2);
        next->Hide(3);
        next->Hide(4);
        flags_ |= 2;
    }
    else if (state == 2)
    {
        GetBodyScale(choice, &appearance->width_, &appearance->height_);
        current->SetScale(appearance->width_, appearance->height_);
        next->SetScale(appearance->width_, appearance->height_);
    }
    else if (state == 5)
    {
        appearance->models_[2] = GetModel(5, choice) + 0x233c;
        next->Hide(2);
        flags_ |= 2;
    }
    else if (state == 3)
    {
        appearance->models_[3] = GetModel(3, choice) + 0x2328;
        next->Hide(3);
        next->Hide(4);
        flags_ |= 2;
    }
    else if (state == 4)
    {
        appearance->hairColor_ = choice;
        next->Hide(4);
        flags_ |= 2;
    }
    else if (state == 6)
    {
        appearance->eyeColor_ = choice;
        current->UpdateColors();
    }
    else if (state == 7)
    {
        appearance->skinColor_ = choice;
        current->UpdateColors();
    }
}

int CharacterCreation::GetModel(int state, int choice)
{
    ChoiceIDs ids = sChoiceIDs;
    if (state == 5)
    {
        if (sex_ != 0)
        {
            ids.ids_[0] = 1;
            ids.ids_[1] = 0;
        }
        else
        {
            ids.ids_[0] = 4;
            ids.ids_[1] = 0;
            ids.ids_[2] = 1;
            ids.ids_[3] = 2;
            ids.ids_[4] = 3;
        }
        return ids.ids_[choice];
    }
    if (state == 3)
    {
        if (sex_ != 0)
        {
            ids.ids_[0] = 6;
            ids.ids_[1] = 0;
            ids.ids_[2] = 1;
            ids.ids_[3] = 2;
            ids.ids_[4] = 3;
            ids.ids_[5] = 4;
            ids.ids_[6] = 5;
        }
        return ids.ids_[choice];
    }
    return choice;
}

// NONMATCHING: the C matches 69.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The first value that it loads goes to r12 instead of r0: declaration orders, types, pointers and the compiler
// versions don't change it.
#ifdef NONMATCHING
void CharacterCreation::GetBodyScale(int bodyType, short* width, short* height)
{
    const BodyScale* scales = sBodyScales[sex_];
    *width = scales[bodyType].width_;
    *height = scales[bodyType].height_;
}
#else
asm void CharacterCreation::GetBodyScale(int bodyType, short* width, short* height)
{
    stmdb sp!, {r3, lr}
    ldrb r12, [r0, #0xda3]
    ldr lr, =sBodyScales
    mov r0, #0x14
    mla lr, r12, r0, lr
    mov r0, r1, lsl #0x2
    ldrsh r0, [lr, r0]
    add r1, lr, r1, lsl #0x2
    strh r0, [r2, #0x0]
    ldrsh r0, [r1, #0x2]
    strh r0, [r3, #0x0]
    ldmia sp!, {r3, pc}
}
#endif

void CharacterCreation::ResetCursor()
{
    int columns;
    int rows;
    int count;
    int unk;
    int choice;
    switch (state_)
    {
    case 1:
        columns = 1;
        rows = 2;
        count = 2;
        unk = 1;
        choice = sex_;
        break;
    case 2:
        columns = 5;
        rows = 1;
        count = 5;
        unk = 1;
        choice = bodyType_[sex_];
        break;
    case 3:
        columns = 5;
        rows = 2;
        choice = face_[sex_];
        count = 10;
        unk = 1;
        break;
    case 4:
        columns = 5;
        rows = 2;
        choice = hairColor_[sex_];
        count = 10;
        unk = 1;
        break;
    case 5:
        columns = 5;
        rows = 2;
        choice = hairStyle_[sex_];
        count = 10;
        unk = 1;
        break;
    case 6:
        columns = 4;
        rows = 2;
        choice = eyeColor_[sex_];
        count = 8;
        unk = 1;
        break;
    case 7:
        columns = 4;
        rows = 2;
        choice = skinColor_[sex_];
        count = 8;
        unk = 1;
        break;
    case 8:
        columns = 11;
        rows = 6;
        count = 0x42;
        unk = 1;
        choice = 0;
        break;
    }
    WindowCursor* cursor = &cursor_;
    func_0205bef8(cursor);
    func_0205ba68(cursor, columns, rows, 1);
    func_0205bacc(cursor, count);
    cursor->unk_4 = unk;
    func_0205bb04(cursor, choice);
    cursor->unk_3d = 0;
}

void CharacterCreation::SetGrid()
{
    ChoiceGrid* grid = &grid_;
    grid->Reset();
    for (int i = 0; sGrids[i] >= 0; i += 9)
    {
        if (state_ == sGrids[i])
        {
            grid->x_ = sGrids[i + 1];
            grid->y_ = sGrids[i + 2];
            grid->width_ = sGrids[i + 3];
            grid->height_ = sGrids[i + 4];
            grid->stepX_ = sGrids[i + 5];
            grid->stepY_ = sGrids[i + 6];
            grid->columns_ = sGrids[i + 7];
            grid->rows_ = sGrids[i + 8];
            return;
        }
    }
}

void CharacterCreation::SetCursor(int choice)
{
    ChoiceGrid* grid = &grid_;
    int y;
    int width;
    int height;
    int stepY;
    int columns = grid->columns_;
    y = grid->y_;
    width = grid->width_;
    height = grid->height_;
    stepY = grid->stepY_;
    cursorX_ = grid->stepX_ * (choice % columns) + grid->x_;
    cursorY_ = stepY * (choice / columns) + y;
    cursorWidth_ = width;
    cursorHeight_ = height;
    lastX_ = cursorX_;
    lastY_ = cursorY_;
}

// NONMATCHING: the C matches 97.3 %, so the build uses the original's instructions after #else (see Decompiling.md). In
// the update of the appearance for the sex's state, the original keeps the hair color in r9; the forms of the
// statements and of the declarations tried don't reproduce it.
#ifdef NONMATCHING
int CharacterCreation::UpdateChoice()
{
    int result = -1;
    int choice = -1;
    flags_ &= ~0x60;
    int x;
    int y;
    func_02012a84(&data_02114e54, &x, &y);
    int touched = 0;
    if (data_02114e54.touching_ != 0)
    {
        touched = 1;
        choice = GetTouchedChoice(x, y);
        touchedChoice_ = choice;
        if (choice == -2 || choice == -3)
        {
            if (choice == -2)
                flags_ |= 0x20;
            else if (choice == -3)
                flags_ |= 0x40;
            result = choice;
            func_0205eaa0(data_02108760, 1, 0);
        }
        else if (choice >= 101 && choice <= 108)
        {
            int state = choice - 100;
            result = choice;
            if (state <= lastStates_[sex_] && state != state_)
                func_0205eaa0(data_02108760, touched, 0);
        }
        else if (choice >= 0)
        {
            func_0205bb04(&cursor_, choice);
            if (state_ == 8)
            {
                if (flags_ & 0x200000)
                {
                    flags_ &= ~0x200000;
                    result = -2;
                }
                flags_ |= 0x100;
            }
            lastX_ = cursorX_;
            lastY_ = cursorY_;
        }
    }
    else if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
    {
        touched = 1;
    }
    else if (data_02114e54.unk_54 != 0)
    {
        touched = 1;
    }

    if (touched == 0)
    {
        unsigned int ticks = GameState::GetInstance()->GetTickCount();
        if (ticks == 0)
            ticks = 1;
        int unk = cursor_.unk_1c;
        if (func_0205bf58(&cursor_, ticks))
            choice = func_0205bb84(&cursor_);
        if (state_ == 8)
        {
            int mode = cursor_.unk_c;
            int type = func_0205bafc(&cursor_);
            if (mode == 1 && type == 8)
            {
                if (choice >= lastStates_[sex_])
                {
                    func_0205bb04(&cursor_, lastStates_[sex_] - 1);
                    choice = lastStates_[sex_] - 1;
                }
                if (func_02012444(data_02114e30, 0x80))
                {
                    WindowCursor* cursor = &cursor_;
                    func_0205bef8(cursor);
                    func_0205ba68(cursor, 11, 6, 1);
                    func_0205bacc(cursor, 0x42);
                    cursor->unk_4 = 1;
                    func_0205bb04(cursor, 0);
                    cursor->unk_3d = 0;
                    flags_ |= 0x2000;
                    if (savedKey_ != NULL)
                        keyboard_->key_ = savedKey_;
                    keyboard_->unk_18 = 0;
                    keyboard_->unk_1c = 0;
                    return -1;
                }
                if (choice >= 0)
                {
                    cursorX_ = choice * 16 + 0x78;
                    cursorY_ = 8;
                    cursorWidth_ = 16;
                    cursorHeight_ = 16;
                }
                if (func_02012444(data_02114e30, 1))
                {
                    result = func_0205bb84(&cursor_) + 101;
                    int state2 = result - 100;
                    if (state2 <= lastStates_[sex_] && state2 != state_)
                        func_0205eaa0(data_02108760, 1, 0);
                }
                return result;
            }
            if (keyboardResult_ == 0 && func_02012444(data_02114e30, 0x40))
            {
                savedKey_ = keyboard_->key_;
                keyboard_->key_ = NULL;
                WindowCursor* cursor = &cursor_;
                func_0205bef8(cursor);
                func_0205ba68(cursor, 8, 1, 1);
                func_0205bacc(cursor, 8);
                cursor->unk_4 = 1;
                func_0205bb04(cursor, state_ - 1);
                cursor->unk_3d = 0;
                cursor->unk_3c = 0;
                cursorX_ = (state_ - 1) * 16 + 0x78;
                cursorY_ = 8;
                cursorWidth_ = 16;
                cursorHeight_ = 16;
            }
        }
        else if (state_ != 8)
        {
            int mode = cursor_.unk_c;
            int type = func_0205bafc(&cursor_);
            if (mode == 1 && type == 8)
            {
                if (choice >= lastStates_[sex_])
                {
                    func_0205bb04(&cursor_, lastStates_[sex_] - 1);
                    choice = lastStates_[sex_] - 1;
                }
                if (func_02012444(data_02114e30, 0x80))
                {
                    ResetCursor();
                    flags_ |= 0x2000;
                    SetCursor(func_0205bb84(&cursor_));
                    return -1;
                }
                if (choice >= 0)
                {
                    cursorX_ = choice * 16 + 0x78;
                    cursorY_ = 8;
                    cursorWidth_ = 16;
                    cursorHeight_ = 16;
                }
                if (func_02012444(data_02114e30, 1))
                {
                    result = func_0205bb84(&cursor_) + 101;
                    int state2 = result - 100;
                    if (state2 <= lastStates_[sex_] && state2 != state_)
                        func_0205eaa0(data_02108760, 1, 0);
                }
                else if (func_02012444(data_02114e30, 2))
                {
                    result = -3;
                }
                if (result == 108)
                    func_0205ba68(&cursor_, 11, 6, 0);
                return result;
            }
            if (func_02012444(data_02114e30, 0x40) && unk == 0)
            {
                WindowCursor* cursor = &cursor_;
                func_0205bef8(cursor);
                func_0205ba68(cursor, 8, 1, 1);
                func_0205bacc(cursor, 8);
                cursor->unk_4 = 1;
                func_0205bb04(cursor, state_ - 1);
                cursor->unk_3d = 0;
                cursor->unk_3c = 0;
                cursorX_ = (state_ - 1) * 16 + 0x78;
                cursorY_ = 8;
                cursorWidth_ = 16;
                cursorHeight_ = 16;
                flags_ |= 0x2000;
                return -1;
            }
            if (func_02012444(data_02114e30, 1))
            {
                result = -2;
                func_0205eaa0(data_02108760, 1, 0);
            }
            else if (func_02012444(data_02114e30, 2))
            {
                result = -3;
            }
        }
    }

    flags_ &= ~0x10;
    if (choice >= 0 && (choice < 101 || choice > 108))
    {
        unsigned char* sex = &sex_;
        switch (state_)
        {
        case 1:
            if (*sex != choice)
                flags_ |= 0x10;
            *sex = choice;
            break;
        case 2:
        {
            unsigned char* value = &bodyType_[sex_];
            if (*value != choice)
                flags_ |= 0x10;
            *value = choice;
            break;
        }
        case 3:
        {
            unsigned char* value = &face_[sex_];
            if (*value != choice)
                flags_ |= 0x10;
            *value = choice;
            break;
        }
        case 4:
        {
            unsigned char* value = &hairColor_[sex_];
            if (*value != choice)
                flags_ |= 0x10;
            *value = choice;
            break;
        }
        case 5:
        {
            unsigned char* value = &hairStyle_[sex_];
            if (*value != choice)
                flags_ |= 0x10;
            *value = choice;
            break;
        }
        case 6:
        {
            unsigned char* value = &eyeColor_[sex_];
            if (*value != choice)
                flags_ |= 0x10;
            *value = choice;
            break;
        }
        case 7:
        {
            unsigned char* value = &skinColor_[sex_];
            if (*value != choice)
                flags_ |= 0x10;
            *value = choice;
            break;
        }
        case 8:
            break;
        }
    }
    if (flags_ & 0x10)
    {
        if (state_ != 8 || touched == 0)
            func_0205eaa0(data_02108760, 2, 0);
        SetChoice(choice);
        if (state_ == 1)
        {
            PartyMemberAppearance* appearance = &member_->details_.appearance_;
            flags_ |= 0x60000;
            appearance->eyeColor_ = eyeColor_[sex_];
            appearance->skinColor_ = skinColor_[sex_];
            appearance->hairColor_ = hairColor_[sex_];
            appearance->models_[2] = GetModel(5, hairStyle_[sex_]) + 0x233c;
            appearance->models_[3] = GetModel(3, face_[sex_]) + 0x2328;
        }
        if (touched == 0)
            SetCursor(choice);
        flags_ |= 0x6100;
    }
    if (result == 108)
    {
        int state = result - 100;
        if (state <= lastStates_[sex_] && state != state_)
            func_0205ba68(&cursor_, 11, 6, 0);
    }
    return result;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN17CharacterCreation11ResetCursorEv(); // CharacterCreation::ResetCursor
    void _ZN17CharacterCreation16GetTouchedChoiceEii(); // CharacterCreation::GetTouchedChoice
    void _ZN17CharacterCreation8GetModelEii(); // CharacterCreation::GetModel
    void _ZN17CharacterCreation9SetChoiceEi(); // CharacterCreation::SetChoice
    void _ZN17CharacterCreation9SetCursorEi(); // CharacterCreation::SetCursor
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK9GameState12GetTickCountEv(); // GameState::GetTickCount
}

asm int CharacterCreation::UpdateChoice()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x8
    mov r4, r0
    ldr r1, [r4, #0xd9c]
    ldr r0, =data_02114e54
    bic r3, r1, #0x60
    mvn r5, #0x0
    add r1, sp, #0x4
    add r2, sp, #0x0
    mov r6, r5
    str r3, [r4, #0xd9c]
    bl func_02012a84
    ldr r0, =data_02114e54
    mov r7, #0x0
    ldrb r1, [r0, #0x55]
    cmp r1, #0x0
    beq @L0218904c
    ldr r1, [sp, #0x4]
    ldr r2, [sp, #0x0]
    mov r0, r4
    mov r7, #0x1
    bl _ZN17CharacterCreation16GetTouchedChoiceEii
    mov r6, r0
    add r0, r6, #0x3
    str r6, [r4, #0xd8c]
    cmp r0, #0x1
    bhi @L02188f98
    mvn r0, #0x1
    cmp r6, r0
    ldreq r0, [r4, #0xd9c]
    orreq r0, r0, #0x20
    streq r0, [r4, #0xd9c]
    beq @L02188f80
    sub r0, r0, #0x1
    cmp r6, r0
    ldreq r0, [r4, #0xd9c]
    orreq r0, r0, #0x40
    streq r0, [r4, #0xd9c]
@L02188f80:
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    mov r5, r6
    bl func_0205eaa0
    b @L02189074
@L02188f98:
    cmp r6, #0x65
    blt @L02188fec
    cmp r6, #0x6c
    bgt @L02188fec
    ldrb r0, [r4, #0xda3]
    sub r1, r6, #0x64
    mov r5, r6
    add r0, r4, r0
    add r0, r0, #0xd00
    ldrsb r0, [r0, #0xa0]
    cmp r1, r0
    bgt @L02189074
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r1, r0
    beq @L02189074
    ldr r0, =data_02108760
    mov r1, r7
    mov r2, #0x0
    bl func_0205eaa0
    b @L02189074
@L02188fec:
    cmp r6, #0x0
    blt @L02189074
    add r0, r4, #0x3ec
    mov r1, r6
    add r0, r0, #0x800
    bl func_0205bb04
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r0, #0x8
    bne @L02189034
    ldr r0, [r4, #0xd9c]
    tst r0, #0x200000
    bicne r0, r0, #0x200000
    strne r0, [r4, #0xd9c]
    ldr r0, [r4, #0xd9c]
    mvnne r5, #0x1
    orr r0, r0, #0x100
    str r0, [r4, #0xd9c]
@L02189034:
    add r0, r4, #0xc00
    ldrsh r1, [r0, #0x4c]
    strh r1, [r0, #0x54]
    ldrsh r1, [r0, #0x4e]
    strh r1, [r0, #0x56]
    b @L02189074
@L0218904c:
    ldrb r1, [r0, #0x5f]
    cmp r1, #0x0
    ldrneh r0, [r0, #0x24]
    cmpne r0, #0x0
    movne r7, #0x1
    bne @L02189074
    ldr r0, =data_02114e54
    ldrb r0, [r0, #0x54]
    cmp r0, #0x0
    movne r7, #0x1
@L02189074:
    cmp r7, #0x0
    bne @L02189558
    bl _ZN9GameState11GetInstanceEv
    bl _ZNK9GameState12GetTickCountEv
    movs r1, r0
    add r0, r4, #0x3ec
    moveq r1, #0x1
    add r0, r0, #0x800
    ldr r8, [r4, #0xc08]
    bl func_0205bf58
    cmp r0, #0x0
    beq @L021890b4
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    bl func_0205bb84
    mov r6, r0
@L021890b4:
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r0, #0x8
    bne @L021892fc
    add r0, r4, #0x3ec
    ldr r8, [r4, #0xbf8]
    add r0, r0, #0x800
    bl func_0205bafc
    cmp r8, #0x1
    cmpeq r0, #0x8
    bne @L02189240
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0xda0
    ldrsb r1, [r0, r1]
    cmp r6, r1
    blt @L02189118
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    sub r1, r1, #0x1
    bl func_0205bb04
    ldrb r0, [r4, #0xda3]
    add r0, r4, r0
    add r0, r0, #0xd00
    ldrsb r0, [r0, #0xa0]
    sub r6, r0, #0x1
@L02189118:
    ldr r0, =data_02114e30
    mov r1, #0x80
    bl func_02012444
    cmp r0, #0x0
    beq @L021891ac
    add r5, r4, #0x3ec
    add r0, r5, #0x800
    bl func_0205bef8
    add r0, r5, #0x800
    mov r1, #0xb
    mov r2, #0x6
    mov r3, #0x1
    bl func_0205ba68
    add r0, r5, #0x800
    mov r1, #0x42
    bl func_0205bacc
    mov r2, #0x1
    add r0, r5, #0x800
    mov r1, #0x0
    str r2, [r5, #0x804]
    bl func_0205bb04
    mov r0, #0x0
    strb r0, [r5, #0x83d]
    ldr r0, [r4, #0xd9c]
    mov r2, #0x0
    orr r0, r0, #0x2000
    str r0, [r4, #0xd9c]
    ldr r1, [r4, #0xbc]
    cmp r1, #0x0
    ldrne r0, [r4, #0xc0]
    strne r1, [r0, #0x0]
    ldr r0, [r4, #0xc0]
    str r2, [r0, #0x18]
    ldr r1, [r4, #0xc0]
    sub r0, r2, #0x1
    strh r2, [r1, #0x1c]
    b @L02189840
@L021891ac:
    cmp r6, #0x0
    blt @L021891d8
    mov r0, r6, lsl #0x4
    add r1, r0, #0x78
    add r0, r4, #0xc00
    strh r1, [r0, #0x4c]
    mov r1, #0x8
    strh r1, [r0, #0x4e]
    mov r1, #0x10
    strh r1, [r0, #0x50]
    strh r1, [r0, #0x52]
@L021891d8:
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    beq @L02189238
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    bl func_0205bb84
    ldrb r1, [r4, #0xda3]
    add r5, r0, #0x65
    sub r2, r5, #0x64
    add r0, r4, r1
    add r0, r0, #0xd00
    ldrsb r0, [r0, #0xa0]
    cmp r2, r0
    bgt @L02189238
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r2, r0
    beq @L02189238
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
@L02189238:
    mov r0, r5
    b @L02189840
@L02189240:
    ldrb r0, [r4, #0xdb5]
    cmp r0, #0x0
    bne @L02189558
    ldr r0, =data_02114e30
    mov r1, #0x40
    bl func_02012444
    cmp r0, #0x0
    beq @L02189558
    ldr r0, [r4, #0xc0]
    add r8, r4, #0x3ec
    ldr r1, [r0, #0x0]
    add r0, r8, #0x800
    str r1, [r4, #0xbc]
    ldr r1, [r4, #0xc0]
    mov r2, #0x0
    str r2, [r1, #0x0]
    bl func_0205bef8
    mov r2, #0x1
    mov r3, r2
    add r0, r8, #0x800
    mov r1, #0x8
    bl func_0205ba68
    add r0, r8, #0x800
    mov r1, #0x8
    bl func_0205bacc
    mov r0, #0x1
    str r0, [r8, #0x804]
    add r0, r4, #0xc00
    ldrsb r1, [r0, #0x58]
    add r0, r8, #0x800
    sub r1, r1, #0x1
    bl func_0205bb04
    mov r0, #0x0
    strb r0, [r8, #0x83d]
    strb r0, [r8, #0x83c]
    add r0, r4, #0xc00
    ldrsb r3, [r0, #0x58]
    mov r2, #0x8
    mov r1, #0x10
    sub r3, r3, #0x1
    mov r3, r3, lsl #0x4
    add r3, r3, #0x78
    strh r3, [r0, #0x4c]
    strh r2, [r0, #0x4e]
    strh r1, [r0, #0x50]
    strh r1, [r0, #0x52]
    b @L02189558
@L021892fc:
    beq @L02189558
    add r0, r4, #0x3ec
    ldr r9, [r4, #0xbf8]
    add r0, r0, #0x800
    bl func_0205bafc
    cmp r9, #0x1
    cmpeq r0, #0x8
    bne @L02189468
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0xda0
    ldrsb r1, [r0, r1]
    cmp r6, r1
    blt @L02189354
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    sub r1, r1, #0x1
    bl func_0205bb04
    ldrb r0, [r4, #0xda3]
    add r0, r4, r0
    add r0, r0, #0xd00
    ldrsb r0, [r0, #0xa0]
    sub r6, r0, #0x1
@L02189354:
    ldr r0, =data_02114e30
    mov r1, #0x80
    bl func_02012444
    cmp r0, #0x0
    beq @L0218939c
    mov r0, r4
    bl _ZN17CharacterCreation11ResetCursorEv
    ldr r1, [r4, #0xd9c]
    add r0, r4, #0x3ec
    orr r1, r1, #0x2000
    add r0, r0, #0x800
    str r1, [r4, #0xd9c]
    bl func_0205bb84
    mov r1, r0
    mov r0, r4
    bl _ZN17CharacterCreation9SetCursorEi
    mvn r0, #0x0
    b @L02189840
@L0218939c:
    cmp r6, #0x0
    blt @L021893c8
    mov r0, r6, lsl #0x4
    add r1, r0, #0x78
    add r0, r4, #0xc00
    strh r1, [r0, #0x4c]
    mov r1, #0x8
    strh r1, [r0, #0x4e]
    mov r1, #0x10
    strh r1, [r0, #0x50]
    strh r1, [r0, #0x52]
@L021893c8:
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    beq @L0218942c
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    bl func_0205bb84
    ldrb r1, [r4, #0xda3]
    add r5, r0, #0x65
    sub r2, r5, #0x64
    add r0, r4, r1
    add r0, r0, #0xd00
    ldrsb r0, [r0, #0xa0]
    cmp r2, r0
    bgt @L02189440
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r2, r0
    beq @L02189440
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    b @L02189440
@L0218942c:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    mvnne r5, #0x2
@L02189440:
    cmp r5, #0x6c
    bne @L02189460
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    mov r1, #0xb
    mov r2, #0x6
    mov r3, #0x0
    bl func_0205ba68
@L02189460:
    mov r0, r5
    b @L02189840
@L02189468:
    ldr r0, =data_02114e30
    mov r1, #0x40
    bl func_02012444
    cmp r0, #0x0
    beq @L02189518
    cmp r8, #0x0
    bne @L02189518
    add r5, r4, #0x3ec
    add r0, r5, #0x800
    bl func_0205bef8
    mov r2, #0x1
    mov r3, r2
    add r0, r5, #0x800
    mov r1, #0x8
    bl func_0205ba68
    add r0, r5, #0x800
    mov r1, #0x8
    bl func_0205bacc
    mov r0, #0x1
    str r0, [r5, #0x804]
    add r0, r4, #0xc00
    ldrsb r1, [r0, #0x58]
    add r0, r5, #0x800
    sub r1, r1, #0x1
    bl func_0205bb04
    mov r0, #0x0
    strb r0, [r5, #0x83d]
    mov r2, #0x10
    strb r0, [r5, #0x83c]
    add r1, r4, #0xc00
    ldrsb r5, [r1, #0x58]
    mov r3, #0x8
    sub r0, r2, #0x11
    sub r5, r5, #0x1
    mov r5, r5, lsl #0x4
    add r5, r5, #0x78
    strh r5, [r1, #0x4c]
    strh r3, [r1, #0x4e]
    strh r2, [r1, #0x50]
    strh r2, [r1, #0x52]
    ldr r1, [r4, #0xd9c]
    orr r1, r1, #0x2000
    str r1, [r4, #0xd9c]
    b @L02189840
@L02189518:
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    beq @L02189544
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    mvn r5, #0x1
    bl func_0205eaa0
    b @L02189558
@L02189544:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    mvnne r5, #0x2
@L02189558:
    ldr r0, [r4, #0xd9c]
    cmp r6, #0x0
    bic r0, r0, #0x10
    str r0, [r4, #0xd9c]
    blt @L021896c0
    cmp r6, #0x65
    blt @L0218957c
    cmp r6, #0x6c
    ble @L021896c0
@L0218957c:
    add r0, r4, #0xc00
    ldrsb r1, [r0, #0x58]
    add r0, r4, #0xa3
    cmp r1, #0x8
    addls pc, pc, r1, lsl #0x2
    b @L021896c0
@L02189594:
    b @L021896c0
    b @L021895b8
    b @L021895d4
    b @L021895fc
    b @L02189624
    b @L0218964c
    b @L02189674
    b @L0218969c
    b @L021896c0
@L021895b8:
    ldrb r1, [r0, #0xd00]
    cmp r1, r6
    ldrne r1, [r4, #0xd9c]
    orrne r1, r1, #0x10
    strne r1, [r4, #0xd9c]
    strb r6, [r0, #0xd00]
    b @L021896c0
@L021895d4:
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0x1a4
    add r2, r0, #0xc00
    ldrb r0, [r2, r1]
    cmp r0, r6
    ldrne r0, [r4, #0xd9c]
    orrne r0, r0, #0x10
    strne r0, [r4, #0xd9c]
    strb r6, [r2, r1]
    b @L021896c0
@L021895fc:
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0x1ac
    add r2, r0, #0xc00
    ldrb r0, [r2, r1]
    cmp r0, r6
    ldrne r0, [r4, #0xd9c]
    orrne r0, r0, #0x10
    strne r0, [r4, #0xd9c]
    strb r6, [r2, r1]
    b @L021896c0
@L02189624:
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0xae
    add r2, r0, #0xd00
    ldrb r0, [r2, r1]
    cmp r0, r6
    ldrne r0, [r4, #0xd9c]
    orrne r0, r0, #0x10
    strne r0, [r4, #0xd9c]
    strb r6, [r2, r1]
    b @L021896c0
@L0218964c:
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0xa6
    add r2, r0, #0xd00
    ldrb r0, [r2, r1]
    cmp r0, r6
    ldrne r0, [r4, #0xd9c]
    orrne r0, r0, #0x10
    strne r0, [r4, #0xd9c]
    strb r6, [r2, r1]
    b @L021896c0
@L02189674:
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0xaa
    add r2, r0, #0xd00
    ldrb r0, [r2, r1]
    cmp r0, r6
    ldrne r0, [r4, #0xd9c]
    orrne r0, r0, #0x10
    strne r0, [r4, #0xd9c]
    strb r6, [r2, r1]
    b @L021896c0
@L0218969c:
    ldrb r1, [r4, #0xda3]
    add r0, r4, #0x1a8
    add r2, r0, #0xc00
    ldrb r0, [r2, r1]
    cmp r0, r6
    ldrne r0, [r4, #0xd9c]
    orrne r0, r0, #0x10
    strne r0, [r4, #0xd9c]
    strb r6, [r2, r1]
@L021896c0:
    ldr r0, [r4, #0xd9c]
    tst r0, #0x10
    beq @L021897f0
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r0, #0x8
    bne @L021896e4
    cmp r7, #0x0
    bne @L021896f4
@L021896e4:
    ldr r0, =data_02108760
    mov r1, #0x2
    mov r2, #0x0
    bl func_0205eaa0
@L021896f4:
    mov r0, r4
    mov r1, r6
    bl _ZN17CharacterCreation9SetChoiceEi
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r0, #0x1
    bne @L021897d0
    ldr r0, [r4, #0xd9c]
    ldr r2, [r4, #0xd88]
    orr r0, r0, #0x60000
    str r0, [r4, #0xd9c]
    ldrb r1, [r4, #0xda3]
    add r0, r2, #0x88
    add r8, r0, #0x400
    add r0, r4, r1
    ldrb r1, [r0, #0xdaa]
    ldrb r2, [r8, #0x14]
    mov r0, r4
    mov r1, r1, lsl #0x1d
    bic r2, r2, #0xe
    orr r1, r2, r1, lsr #0x1c
    strb r1, [r8, #0x14]
    ldrb r2, [r4, #0xda3]
    and r1, r1, #0xff
    bic r3, r1, #0xf0
    add r1, r4, r2
    ldrb r2, [r1, #0xda8]
    mov r1, #0x5
    mov r2, r2, lsl #0x1c
    orr r2, r3, r2, lsr #0x18
    strb r2, [r8, #0x14]
    ldrb r3, [r4, #0xda3]
    ldrb r2, [r8, #0x15]
    add r3, r4, r3
    ldrb r9, [r3, #0xdae]
    bic r3, r2, #0xf
    and r2, r9, #0xf
    orr r2, r3, r2
    strb r2, [r8, #0x15]
    ldrb r2, [r4, #0xda3]
    add r2, r4, r2
    ldrb r2, [r2, #0xda6]
    bl _ZN17CharacterCreation8GetModelEii
    add r0, r0, #0x33c
    add r0, r0, #0x2000
    strh r0, [r8, #0x4]
    ldrb r2, [r4, #0xda3]
    mov r0, r4
    mov r1, #0x3
    add r2, r4, r2
    ldrb r2, [r2, #0xdac]
    bl _ZN17CharacterCreation8GetModelEii
    add r0, r0, #0x328
    add r0, r0, #0x2000
    strh r0, [r8, #0x6]
@L021897d0:
    cmp r7, #0x0
    bne @L021897e4
    mov r0, r4
    mov r1, r6
    bl _ZN17CharacterCreation9SetCursorEi
@L021897e4:
    ldr r0, [r4, #0xd9c]
    orr r0, r0, #0x6100
    str r0, [r4, #0xd9c]
@L021897f0:
    cmp r5, #0x6c
    bne @L0218983c
    ldrb r0, [r4, #0xda3]
    sub r1, r5, #0x64
    add r0, r4, r0
    add r0, r0, #0xd00
    ldrsb r0, [r0, #0xa0]
    cmp r1, r0
    bgt @L0218983c
    add r0, r4, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r1, r0
    beq @L0218983c
    add r0, r4, #0x3ec
    add r0, r0, #0x800
    mov r1, #0xb
    mov r2, #0x6
    mov r3, #0x0
    bl func_0205ba68
@L0218983c:
    mov r0, r5
@L02189840:
    add sp, sp, #0x8
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

// NONMATCHING: the C matches 76.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The loop over the grid keeps other values in registers and on the stack (declaration orders and permute.py reached
// 78.6 %).
#ifdef NONMATCHING
int CharacterCreation::GetTouchedChoice(int x, int y)
{
    if (y >= 0xa9 && y <= 0xb1)
    {
        if (x >= 0x8e && x <= 0xbe)
            return -2;
        if (x >= 0xc8 && x <= 0xf0)
            return -3;
    }
    if (y >= 8 && y <= 0x18)
    {
        for (int i = 0; i < 8; i++)
        {
            int left = i * 16 + 0x78;
            int right = left + 16;
            if (x >= left && x <= right)
                return i + 101;
        }
    }

    short cursorHeight;
    short cursorWidth;
    int offsetY;
    int stepX;
    int stepY;
    ChoiceGrid* grid = &grid_;
    stepX = grid->stepX_;
    int height = grid->height_;
    stepY = grid->stepY_;
    int width = grid->width_;
    cursorWidth = width;
    cursorHeight = height;
    int columns = grid->columns_;
    int rows = grid->rows_;
    int choice = -4;
    for (int row = 0; row < rows; row++)
    {
        offsetY = stepY * row;
        for (int column = 0; column < columns; column++)
        {
            int left = grid->x_ + stepX * column;
            if (state_ == 8)
                break;
            if (x >= left && x <= left + width)
            {
                int top = grid->y_ + offsetY;
                if (y >= top && y <= top + height)
                {
                    choice = row * columns + column;
                    cursorX_ = left;
                    cursorY_ = top;
                    cursorWidth_ = cursorWidth;
                    cursorHeight_ = cursorHeight;
                    break;
                }
            }
        }
        if (choice >= 0)
            break;
    }
    int mode = cursor_.unk_c;
    int type = func_0205bafc(&cursor_);
    if (mode == 1 && type == 8 && choice >= 0 && choice != 101 && choice != 108)
    {
        ResetCursor();
        func_0205bb04(&cursor_, choice);
        flags_ |= 0x2000;
        SetCursor(func_0205bb84(&cursor_));
    }
    return choice;
}
#else
asm int CharacterCreation::GetTouchedChoice(int x, int y)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x18
    mov r4, r0
    cmp r2, #0xa9
    blt @L02189898
    cmp r2, #0xb1
    bgt @L02189898
    cmp r1, #0x8e
    blt @L02189884
    cmp r1, #0xbe
    mvnle r0, #0x1
    ble @L02189a44
@L02189884:
    cmp r1, #0xc8
    blt @L02189898
    cmp r1, #0xf0
    mvnle r0, #0x2
    ble @L02189a44
@L02189898:
    cmp r2, #0x8
    blt @L021898dc
    cmp r2, #0x18
    bgt @L021898dc
    mov r3, #0x0
    b @L021898d4
@L021898b0:
    mov r0, r3, lsl #0x4
    add r0, r0, #0x78
    cmp r1, r0
    add r0, r0, #0x10
    blt @L021898d0
    cmp r1, r0
    addle r0, r3, #0x65
    ble @L02189a44
@L021898d0:
    add r3, r3, #0x1
@L021898d4:
    cmp r3, #0x8
    blt @L021898b0
@L021898dc:
    add r9, r4, #0x2c
    ldr r0, [r9, #0xc10]
    ldr r12, [r9, #0xc0c]
    str r0, [sp, #0x4]
    ldr r0, [r9, #0xc14]
    ldr r3, [r9, #0xc08]
    str r0, [sp, #0x0]
    mov r0, r3, lsl #0x10
    mov r0, r0, asr #0x10
    mov r7, r12, lsl #0x10
    str r0, [sp, #0xc]
    mov r0, r7, asr #0x10
    ldr lr, [r9, #0xc18]
    ldr r11, [r9, #0xc1c]
    mvn r5, #0x3
    mov r6, #0x0
    str r0, [sp, #0x10]
    b @L021899cc
@L02189924:
    ldr r0, [sp, #0x0]
    mov r7, #0x0
    mul r8, r0, r6
    add r0, r4, #0xc00
    str r8, [sp, #0x8]
    str r0, [sp, #0x14]
    b @L021899b8
@L02189940:
    ldr r8, [sp, #0x14]
    ldr r0, [r9, #0xc00]
    ldrsb r10, [r8, #0x58]
    ldr r8, [sp, #0x4]
    mla r0, r8, r7, r0
    cmp r10, #0x8
    beq @L021899c0
    cmp r1, r0
    add r8, r0, r3
    blt @L021899b4
    cmp r1, r8
    bgt @L021899b4
    ldr r10, [r9, #0xc04]
    ldr r8, [sp, #0x8]
    add r10, r10, r8
    cmp r2, r10
    add r8, r10, r12
    blt @L021899b4
    cmp r2, r8
    bgt @L021899b4
    mla r5, r6, lr, r7
    add r7, r4, #0xc00
    strh r0, [r7, #0x4c]
    ldr r0, [sp, #0xc]
    strh r10, [r7, #0x4e]
    strh r0, [r7, #0x50]
    ldr r0, [sp, #0x10]
    strh r0, [r7, #0x52]
    b @L021899c0
@L021899b4:
    add r7, r7, #0x1
@L021899b8:
    cmp r7, lr
    blt @L02189940
@L021899c0:
    cmp r5, #0x0
    bge @L021899d4
    add r6, r6, #0x1
@L021899cc:
    cmp r6, r11
    blt @L02189924
@L021899d4:
    add r0, r4, #0x3ec
    ldr r6, [r4, #0xbf8]
    add r0, r0, #0x800
    bl func_0205bafc
    cmp r6, #0x1
    cmpeq r0, #0x8
    bne @L02189a40
    cmp r5, #0x0
    blt @L02189a40
    cmp r5, #0x65
    cmpne r5, #0x6c
    beq @L02189a40
    mov r0, r4
    bl _ZN17CharacterCreation11ResetCursorEv
    add r0, r4, #0x3ec
    mov r1, r5
    add r0, r0, #0x800
    bl func_0205bb04
    ldr r1, [r4, #0xd9c]
    add r0, r4, #0x3ec
    orr r1, r1, #0x2000
    add r0, r0, #0x800
    str r1, [r4, #0xd9c]
    bl func_0205bb84
    mov r1, r0
    mov r0, r4
    bl _ZN17CharacterCreation9SetCursorEi
@L02189a40:
    mov r0, r5
@L02189a44:
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static int ResolvePattern(ForbiddenWordFile* file, ForbiddenWordPattern* pattern);

// Checks the name for forbidden words (see ForbiddenWordChecker): sets 0x400000 in the flags if it has one, else 0x800
// NONMATCHING: the C matches 0.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Like ForbiddenWordChecker::Check of overlay 12 (NONMATCHING too), the checking of the name is compiled in another
// form, with other registers and stack slots.
#ifdef NONMATCHING
void CharacterCreation::CheckName()
{
    const char* text = names_[sex_];
    if (*text == 0)
        return;

    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    checker_.Initialize();
    unsigned int size = 0;
    unsigned int textsSize = 0;
    LoadFileIntoMemory(data_020f285c, data_0211e33c, &size);
    unsigned int offset = (size + 0x1ff) & ~0x1ff;
    LoadFileIntoMemory(data_020f2858, data_0211e33c + offset, &textsSize);
    func_020dfc40(&checker_.texts_);
    func_020e038c(&checker_.texts_, data_0211e33c + offset, textsSize);
    checker_.LoadFile(data_0211e33c, 0, ResolvePattern);
    checker_.unk_24 = 0;
    checker_.unk_28 = 0;
    if (textsSize != 0)
    {
        checker_.unk_24 = data_0211e33c + offset;
        checker_.unk_28 = textsSize;
    }

    // First, the name in capitals is compared with each text of data_020f2858, the names that aren't allowed
    int forbidden = 0;
    char upper[0x40];
    __clear(upper, sizeof(upper));
    char* upperEnd = upper;
    for (const char* character = text; *character != 0;)
    {
        CharacterInfo* info = (CharacterInfo*)func_0204254c(character, 1);
        char buffer[0xc];
        __clear(buffer, sizeof(buffer));
        int length = info->length_;
        const char* characters = info->text_;
        if (info->uppercase_)
        {
            checker_.ToUpper(characters, buffer);
            characters = buffer;
        }
        memcpy(upperEnd, characters, length);
        character += length;
        upperEnd += length;
    }
    int nameLength = strlen(upper);
    int nameCount = func_020e0424(&checker_.texts_);
    for (int i = 0; i < nameCount; i++)
    {
        const char* name = func_020e0434(&checker_.texts_, i);
        if (name != NULL && *name != 0 && strlen(name) == nameLength && strcmp(name, upper) == 0)
        {
            forbidden = 1;
            goto done;
        }
    }

    // Then the patterns, like ForbiddenWordChecker::Check of overlay 12
    ForbiddenWordRange words[30];
    char converted[0x200];
    char codes[0x80];
    __clear(words, sizeof(words));
    __clear(converted, sizeof(converted));
    __clear(codes, sizeof(codes));
    char* output = converted;
    int dollar = checker_.symbols_[8];
    int slash = checker_.symbols_[9];
    int at = checker_.symbols_[10];
    int ampersand = checker_.symbols_[11];
    unsigned char quote = checker_.symbols_[14];
    unsigned char tag = checker_.symbols_[13];
    while (*text != 0)
    {
        signed char code = func_020424e4(text, 1);
        CharacterInfo* info = (CharacterInfo*)func_020425b4(code, 1);
        if (info != 0 &&
            ((code >= 8 && code <= 0x45) || code == 0x4d || code == 0x53 || (code >= 0x78 && code <= 0xa9) ||
             (code == dollar || code == at || code == ampersand || code == 0x6b || code == quote)))
        {
            int length = info->length_;
            if (code == 0x6b)
                info = (CharacterInfo*)func_020425b4(slash, 1);
            char buffer[0xc];
            __clear(buffer, sizeof(buffer));
            const char* characters = info->text_;
            int size = info->length_;
            if (info->uppercase_)
            {
                checker_.ToUpper(characters, buffer);
                characters = buffer;
            }
            if (code >= 0x78 && code <= 0xa9)
            {
                signed char second = characters[1];
                if (!(second >= 'A' && second <= 'Z' || second >= 'a' && second <= 'z') || second == 's')
                {
                    signed char third = characters[2];
                    if (third >= 'a' && third <= 'z')
                        third -= 0x20;
                    memset(buffer, 0, sizeof(buffer));
                    buffer[0] = third;
                    characters = buffer;
                    size = 1;
                }
            }
            memcpy(output, characters, size);
            text += length;
            output += size;
        }
        else if (code == tag)
        {
            int length = info->length_;
            memcpy(output, sTagCharacter, 1);
            text += length;
            output++;
        }
        else
        {
            int length = 1;
            char character;
            if (info != 0)
            {
                length = info->length_;
                character = ',';
            }
            else
            {
                character = ' ';
            }
            *output = character;
            text += length;
            output++;
        }
    }

    func_020426bc(converted, codes, 1);
    ForbiddenWordRange* word = words;
    unsigned char separator = checker_.symbols_[12];
    const unsigned char* code = (const unsigned char*)codes;
    int column = 0;
    short position = 0;
    int count = 0;
    while (true)
    {
        unsigned int current = *code;
        if (word->active_)
        {
            if (current == 0 || current == 0xff || current == separator)
            {
                count++;
                word->length_ = position - word->start_;
                word->lineEnd_ = current == 0xff ? 1 : 0;
                word->active_ = 0;
                word++;
            }
        }
        else
        {
            if (current != 0 && current < 0xff && current != separator)
            {
                word->start_ = position;
                word->active_ = 1;
            }
            if (current == separator && count != 0)
                words[count - 1].lineEnd_ = 0;
        }
        if (word->active_ && column == 0x12)
        {
            count++;
            word->length_ = position - word->start_ + 1;
            word->lineEnd_ = 1;
            word++;
        }
        if (current == 0)
            break;
        column++;
        code++;
        position++;
        if (column == 0x13)
            column = 0;
    }

    word = words;
    for (int i = 0; i < count - 1; i++, word++)
    {
        int j = word->start_ + word->length_;
        word->lineEnd_ = 1;
        const unsigned char* character = (const unsigned char*)&codes[j];
        for (; j < word[1].start_; j++, character++)
        {
            if (checker_.symbols_[12] == *character)
            {
                word->lineEnd_ = 0;
                break;
            }
        }
    }

    for (int i = 0; i < 0x80; i++)
    {
        if ((signed char)checker_.symbols_[12] == codes[i])
            codes[i] = -1;
    }

    unsigned int patternCount = checker_.file_.header_ & 0xfff;
    for (int i = 0; i < patternCount; i = (short)(i + 1))
    {
        ForbiddenWordPattern* pattern = checker_.file_.patterns_ + i;
        ForbiddenWordRange* first = words;
        char patternCodes[5][0x40];
        __clear(patternCodes, sizeof(patternCodes));
        for (int j = 0; j < pattern->count_; j++)
        {
            func_020426bc(pattern->words_[j], patternCodes[j], 1);
            pattern->words_[j] = patternCodes[j];
        }

        int positions = count - pattern->count_ + 1;
        for (int j = 0; j < positions; j++, first++)
        {
            int found;
            ForbiddenWordRange* range = first;
            int k = 0;
            int wordCount = pattern->count_;
            int last = pattern->count_ - 1;
            while (true)
            {
                if (k >= wordCount)
                {
                    found = 1;
                    break;
                }
                if (k < last && !range->lineEnd_)
                {
                    found = 0;
                    break;
                }

                signed char length = pattern->lengths_[k];
                short rangeLength = range->length_;
                const char* patternWord = pattern->words_[k];
                int positions2 = rangeLength - length + 1;
                int matched;
                switch (pattern->types_[k])
                {
                case 0:
                    matched = length == rangeLength && checker_.FindText(patternWord, &codes[range->start_], length, 1);
                    break;
                case 3:
                    matched = rangeLength >= length && checker_.FindText(patternWord, &codes[range->start_], length, 1);
                    break;
                case 2:
                    matched = rangeLength >= length &&
                              checker_.FindText(patternWord, &codes[range->start_ + range->length_ - length], length, 1);
                    break;
                case 1:
                    matched = rangeLength >= length &&
                              checker_.FindText(patternWord, &codes[range->start_], length, positions2);
                    break;
                case 4:
                    matched = length == rangeLength && checker_.Match(patternWord, &codes[range->start_], length, 1);
                    break;
                case 7:
                    matched = rangeLength >= length && checker_.Match(patternWord, &codes[range->start_], length, 1);
                    break;
                case 6:
                    matched = rangeLength >= length &&
                              checker_.Match(patternWord, &codes[range->start_ + range->length_ - length], length, 1);
                    break;
                case 5:
                    matched = rangeLength >= length &&
                              checker_.Match(patternWord, &codes[range->start_], length, positions2);
                    break;
                default:
                    matched = 1;
                    break;
                }
                if (!matched)
                {
                    found = 0;
                    break;
                }
                k++;
                range++;
            }
            if (found)
            {
                forbidden = 1;
                goto done;
            }
        }
    }

done:
    BackgroundLoader::RemoveLockGlobal();
    if (forbidden)
        flags_ |= 0x400000;
    else
        flags_ |= 0x800;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN20ForbiddenWordChecker10InitializeEv(); // ForbiddenWordChecker::Initialize
    void _ZN20ForbiddenWordChecker5MatchEPKcS1_ii(); // ForbiddenWordChecker::Match
    void _ZN20ForbiddenWordChecker7ToUpperEPKcPc(); // ForbiddenWordChecker::ToUpper
    void _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii(); // ForbiddenWordChecker::FindText
}

asm void CharacterCreation::CheckName()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xfc
    sub sp, sp, #0x400
    mov r9, r0
    ldrb r0, [r9, #0xda3]
    ldr r1, [r9, #0xdb0]
    ldr r4, [r1, r0, lsl #0x2]
    ldrsb r0, [r4, #0x0]
    cmp r0, #0x0
    beq @L0218a400
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    add r0, r9, #0xfc
    bl _ZN20ForbiddenWordChecker10InitializeEv
    mov r2, #0x0
    ldr r0, =data_020f285c
    ldr r1, =data_0211e33c
    ldr r0, [r0, #0x0]
    str r2, [sp, #0x28]
    str r2, [sp, #0x2c]
    add r2, sp, #0x28
    bl LoadFileIntoMemory
    ldr r0, [sp, #0x28]
    mov r1, #0x200
    add r0, r0, #0xff
    add r0, r0, #0x100
    rsb r1, r1, #0x0
    and r8, r0, r1
    ldr r0, =data_020f2858
    ldr r1, =data_0211e33c
    ldr r0, [r0, #0x0]
    add r1, r1, r8
    add r2, sp, #0x2c
    bl LoadFileIntoMemory
    add r0, r9, #0xfc
    bl func_020dfc40
    ldr r1, =data_0211e33c
    ldr r2, [sp, #0x2c]
    add r0, r9, #0xfc
    add r1, r1, r8
    bl func_020e038c
    add r0, r9, #0x114
    mov r1, #0x0
    mov r2, #0xc
    bl memset
    ldr r1, =data_0211e33c
    cmp r1, #0x0
    beq @L02189bd8
    add r0, r9, #0x114
    mov r2, #0x4
    bl memcpy
    mov r0, #0x3
    add r1, r0, #0x4
    mvn r5, #0x3
    add r2, r0, #0x20
    ldr r0, =data_0211e33c
    and r1, r5, r1
    add r3, r0, r1
    str r3, [r9, #0x118]
    ldr r3, [r9, #0x114]
    and r2, r5, r2
    mov r3, r3, lsl #0x14
    mov r3, r3, lsr #0x14
    mul r2, r3, r2
    add r2, r2, #0x0
    add r1, r1, r2
    add r0, r0, r1
    str r0, [r9, #0x11c]
    ldr r0, [r9, #0x114]
    movs r0, r0, lsr #0x1f
    bne @L02189bd8
    ldr r6, [r9, #0x118]
    cmp r6, #0x0
    beq @L02189bb4
    ldr r0, [r9, #0x114]
    mov r0, r0, lsl #0x14
    movs r7, r0, lsr #0x14
    ldrne r0, =ResolvePattern
    cmpne r0, #0x0
    beq @L02189bb4
    mov r5, #0x0
    add r10, r9, #0x114
    b @L02189bac
@L02189b98:
    mov r0, r10
    mov r1, r6
    bl ResolvePattern
    add r5, r5, #0x1
    add r6, r6, #0x20
@L02189bac:
    cmp r5, r7
    blt @L02189b98
@L02189bb4:
    ldr r0, [r9, #0x114]
    ldr r1, =data_0211e33c
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [r9, #0x114]
    ldr r0, [r1, #0x0]
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [r1, #0x0]
@L02189bd8:
    mov r1, #0x0
    str r1, [r9, #0x120]
    add r0, r9, #0x100
    strh r1, [r0, #0x24]
    ldr r1, [sp, #0x2c]
    cmp r1, #0x0
    ldrne r1, =data_0211e33c
    addne r1, r1, r8
    strne r1, [r9, #0x120]
    ldrne r1, [sp, #0x2c]
    strneh r1, [r0, #0x24]
    add r0, sp, #0x48
    mov r1, #0x40
    bl __clear
    add r7, sp, #0x48
    mov r8, r4
    add r10, sp, #0x3c
    mov r6, #0x1
    mov r11, #0xc
@L02189c24:
    ldrsb r0, [r8, #0x0]
    cmp r0, #0x0
    beq @L02189c90
    mov r0, r8
    mov r1, r6
    bl func_0204254c
    mov r5, r0
    mov r0, r10
    mov r1, r11
    bl __clear
    ldrsb r0, [r5, #0x5]
    ldr r1, [r5, #0x0]
    mov r2, r0, lsl #0x1a
    mov r0, r0, lsl #0x18
    mov r5, r2, asr #0x1a
    movs r0, r0, asr #0x1f
    beq @L02189c78
    mov r2, r10
    add r0, r9, #0xfc
    bl _ZN20ForbiddenWordChecker7ToUpperEPKcPc
    mov r1, r10
@L02189c78:
    mov r0, r7
    mov r2, r5
    bl memcpy
    add r8, r8, r5
    add r7, r7, r5
    b @L02189c24
@L02189c90:
    add r0, sp, #0x48
    bl strlen
    mov r6, r0
    add r0, r9, #0xfc
    bl func_020e0424
    mov r8, r0
    mov r7, #0x0
    add r10, sp, #0x48
    b @L02189cfc
@L02189cb4:
    mov r1, r7, lsl #0x10
    add r0, r9, #0xfc
    mov r1, r1, asr #0x10
    bl func_020e0434
    movs r5, r0
    ldrnesb r1, [r5, #0x0]
    cmpne r1, #0x0
    beq @L02189cf8
    bl strlen
    cmp r0, r6
    bne @L02189cf8
    mov r0, r5
    mov r1, r10
    bl strcmp
    cmp r0, #0x0
    moveq r0, #0x1
    beq @L02189d08
@L02189cf8:
    add r7, r7, #0x1
@L02189cfc:
    cmp r7, r8
    blt @L02189cb4
    mov r0, #0x0
@L02189d08:
    cmp r0, #0x0
    movne r4, #0x1
    bne @L0218a3e4
    add r0, sp, #0x400
    add r0, r0, #0x48
    mov r1, #0xb4
    bl __clear
    add r0, sp, #0x248
    mov r1, #0x200
    bl __clear
    add r0, sp, #0x1c8
    mov r1, #0x80
    bl __clear
    ldrb r5, [r9, #0x12e]
    ldrb r0, [r9, #0x12f]
    add r6, sp, #0x248
    str r0, [sp, #0xc]
    ldrb r10, [r9, #0x130]
    ldrb r0, [r9, #0x131]
    str r0, [sp, #0x10]
    ldrb r0, [r9, #0x134]
    str r0, [sp, #0x14]
    ldrb r0, [r9, #0x133]
    str r0, [sp, #0x18]
@L02189d68:
    ldrsb r0, [r4, #0x0]
    cmp r0, #0x0
    beq @L02189f20
    mov r0, r4
    mov r1, #0x1
    bl func_020424e4
    mov r1, #0x1
    mov r7, r0
    bl func_020425b4
    movs r8, r0
    beq @L02189ef4
    cmp r7, #0x8
    blt @L02189da4
    cmp r7, #0x45
    ble @L02189de0
@L02189da4:
    cmp r7, #0x4d
    cmpne r7, #0x53
    beq @L02189de0
    cmp r7, #0x78
    blt @L02189dc0
    cmp r7, #0xa9
    ble @L02189de0
@L02189dc0:
    cmp r7, r5
    cmpne r7, r10
    ldrne r0, [sp, #0x10]
    cmpne r7, r0
    cmpne r7, #0x6b
    ldrne r0, [sp, #0x14]
    cmpne r7, r0
    bne @L02189ec4
@L02189de0:
    cmp r7, #0x6b
    ldrsb r0, [r8, #0x5]
    mov r11, r0, lsl #0x1a
    bne @L02189e00
    ldr r0, [sp, #0xc]
    mov r1, #0x1
    bl func_020425b4
    mov r8, r0
@L02189e00:
    add r0, sp, #0x30
    mov r1, #0xc
    bl __clear
    ldrsb r0, [r8, #0x5]
    ldr r1, [r8, #0x0]
    mov r2, r0, lsl #0x1a
    mov r0, r0, lsl #0x18
    mov r8, r2, asr #0x1a
    movs r0, r0, asr #0x1f
    beq @L02189e38
    add r0, r9, #0xfc
    add r2, sp, #0x30
    bl _ZN20ForbiddenWordChecker7ToUpperEPKcPc
    add r1, sp, #0x30
@L02189e38:
    cmp r7, #0x78
    blt @L02189eac
    cmp r7, #0xa9
    bgt @L02189eac
    ldrsb r7, [r1, #0x1]
    cmp r7, #0x41
    blt @L02189e5c
    cmp r7, #0x5a
    ble @L02189e6c
@L02189e5c:
    cmp r7, #0x61
    blt @L02189e74
    cmp r7, #0x7a
    bgt @L02189e74
@L02189e6c:
    cmp r7, #0x73
    bne @L02189eac
@L02189e74:
    ldrsb r7, [r1, #0x2]
    cmp r7, #0x61
    blt @L02189e90
    cmp r7, #0x7a
    suble r0, r7, #0x20
    movle r0, r0, lsl #0x18
    movle r7, r0, asr #0x18
@L02189e90:
    add r0, sp, #0x30
    mov r1, #0x0
    mov r2, #0xc
    bl memset
    strb r7, [sp, #0x30]
    add r1, sp, #0x30
    mov r8, #0x1
@L02189eac:
    mov r0, r6
    mov r2, r8
    bl memcpy
    add r4, r4, r11, asr #0x1a
    add r6, r6, r8
    b @L02189d68
@L02189ec4:
    ldr r0, [sp, #0x18]
    cmp r7, r0
    bne @L02189ef4
    ldrsb r2, [r8, #0x5]
    ldr r1, =sTagCharacter
    mov r0, r6
    mov r7, r2, lsl #0x1a
    mov r2, #0x1
    bl memcpy
    add r4, r4, r7, asr #0x1a
    add r6, r6, #0x1
    b @L02189d68
@L02189ef4:
    cmp r8, #0x0
    ldrnesb r0, [r8, #0x5]
    mov r1, #0x1
    movne r0, r0, lsl #0x1a
    movne r1, r0, asr #0x1a
    movne r0, #0x2c
    moveq r0, #0x20
    strb r0, [r6, #0x0]
    add r4, r4, r1
    add r6, r6, #0x1
    b @L02189d68
@L02189f20:
    add r0, sp, #0x248
    add r1, sp, #0x1c8
    mov r2, #0x1
    bl func_020426bc
    mov r8, #0x0
    add r4, sp, #0x400
    add r4, r4, #0x48
    ldrb r10, [r9, #0x132]
    add r5, sp, #0x1c8
    mov r7, r8
    mov r6, r8
    mov r0, r4
    mov r12, #0x1
    mov lr, r8
    mov r2, r8
@L02189f5c:
    ldrb r3, [r5, #0x0]
    ldrb r1, [r4, #0x5]
    cmp r1, #0x0
    beq @L02189fa8
    cmp r3, #0x0
    cmpne r3, #0xff
    cmpne r3, r10
    bne @L02189fe0
    ldrsh r1, [r4, #0x0]
    cmp r3, #0xff
    add r6, r6, #0x1
    sub r1, r7, r1
    strh r1, [r4, #0x2]
    moveq r1, #0x1
    movne r1, #0x0
    strb r1, [r4, #0x4]
    strb r2, [r4, #0x5]
    add r4, r4, #0x6
    b @L02189fe0
@L02189fa8:
    cmp r3, #0x0
    beq @L02189fc4
    cmp r3, #0xff
    bhs @L02189fc4
    cmp r3, r10
    strneh r7, [r4, #0x0]
    strneb r12, [r4, #0x5]
@L02189fc4:
    cmp r3, r10
    bne @L02189fe0
    cmp r6, #0x0
    subne r1, r6, #0x1
    movne r11, #0x6
    mlane r11, r1, r11, r0
    strneb lr, [r11, #0x4]
@L02189fe0:
    ldrb r1, [r4, #0x5]
    cmp r1, #0x0
    beq @L0218a014
    cmp r8, #0x12
    bne @L0218a014
    ldrsh r1, [r4, #0x0]
    add r6, r6, #0x1
    sub r1, r7, r1
    add r1, r1, #0x1
    strh r1, [r4, #0x2]
    mov r1, #0x1
    strb r1, [r4, #0x4]
    add r4, r4, #0x6
@L0218a014:
    cmp r3, #0x0
    beq @L0218a034
    add r8, r8, #0x1
    cmp r8, #0x13
    add r5, r5, #0x1
    add r7, r7, #0x1
    moveq r8, #0x0
    b @L02189f5c
@L0218a034:
    add r5, sp, #0x400
    mov r7, #0x0
    ldrb r4, [r9, #0x132]
    add r5, r5, #0x48
    sub r0, r6, #0x1
    mov r3, #0x1
    add r2, sp, #0x1c8
    mov r12, r7
    b @L0218a09c
@L0218a058:
    ldrsh r10, [r5, #0x0]
    ldrsh r1, [r5, #0x2]
    ldrsh r8, [r5, #0x6]
    add r11, r10, r1
    strb r3, [r5, #0x4]
    add r10, r2, r11
    b @L0218a08c
@L0218a074:
    ldrb r1, [r10, #0x0]
    cmp r4, r1
    streqb r12, [r5, #0x4]
    beq @L0218a094
    add r11, r11, #0x1
    add r10, r10, #0x1
@L0218a08c:
    cmp r11, r8
    blt @L0218a074
@L0218a094:
    add r7, r7, #0x1
    add r5, r5, #0x6
@L0218a09c:
    cmp r7, r0
    blt @L0218a058
    add r0, r9, #0x100
    ldrsb r3, [r0, #0x32]
    mov r4, #0x0
    mvn r0, #0x0
    add r2, sp, #0x1c8
    b @L0218a0cc
@L0218a0bc:
    ldrsb r1, [r2, r4]
    cmp r3, r1
    streqb r0, [r2, r4]
    add r4, r4, #0x1
@L0218a0cc:
    cmp r4, #0x80
    blt @L0218a0bc
    ldr r0, [r9, #0x114]
    mov r4, #0x0
    mov r0, r0, lsl #0x14
    mov r0, r0, lsr #0x14
    str r0, [sp, #0x24]
    b @L0218a3d4
@L0218a0ec:
    ldr r2, [r9, #0x118]
    add r0, sp, #0x88
    add r5, r2, r4, lsl #0x5
    add r2, sp, #0x400
    add r2, r2, #0x48
    mov r1, #0x140
    str r2, [sp, #0x20]
    bl __clear
    mov r8, #0x0
    add r7, sp, #0x88
    mov r10, #0x1
    b @L0218a138
@L0218a11c:
    ldr r0, [r5, r8, lsl #0x2]
    mov r2, r10
    add r1, r7, r8, lsl #0x6
    bl func_020426bc
    add r0, r7, r8, lsl #0x6
    str r0, [r5, r8, lsl #0x2]
    add r8, r8, #0x1
@L0218a138:
    ldrb r0, [r5, #0x1e]
    cmp r8, r0
    blt @L0218a11c
    sub r0, r6, r0
    add r0, r0, #0x1
    str r0, [sp, #0x1c]
    mov r11, #0x0
    add r10, sp, #0x1c8
    b @L0218a3bc
@L0218a15c:
    ldrb r0, [r5, #0x1e]
    ldr r7, [sp, #0x20]
    mov r8, #0x0
    str r0, [sp, #0x8]
    sub r0, r0, #0x1
    str r0, [sp, #0x4]
    b @L0218a390
@L0218a178:
    ldr r0, [sp, #0x4]
    cmp r8, r0
    bge @L0218a194
    ldrb r0, [r7, #0x4]
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0218a3a0
@L0218a194:
    add r0, r5, r8
    ldrb r12, [r0, #0x19]
    ldrsb r3, [r0, #0x14]
    ldrsh r0, [r7, #0x2]
    ldr r1, [r5, r8, lsl #0x2]
    cmp r12, #0x7
    sub r2, r0, r3
    add r2, r2, #0x1
    addls pc, pc, r12, lsl #0x2
    b @L0218a388
@L0218a1bc:
    b @L0218a1dc
    b @L0218a284
    b @L0218a244
    b @L0218a210
    b @L0218a2b4
    b @L0218a35c
    b @L0218a31c
    b @L0218a2e8
@L0218a1dc:
    cmp r3, r0
    movne r0, #0x0
    bne @L0218a3a0
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r7, #0x0]
    add r0, r9, #0xfc
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a210:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218a3a0
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r7, #0x0]
    add r0, r9, #0xfc
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a244:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218a3a0
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r12, [r7, #0x0]
    ldrsh r2, [r7, #0x2]
    add r0, r9, #0xfc
    add r2, r12, r2
    sub r2, r2, r3
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a284:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218a3a0
    str r2, [sp, #0x0]
    add r0, r9, #0xfc
    ldrsh r2, [r7, #0x0]
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a2b4:
    cmp r3, r0
    movne r0, #0x0
    bne @L0218a3a0
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r7, #0x0]
    add r0, r9, #0xfc
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a2e8:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218a3a0
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r7, #0x0]
    add r0, r9, #0xfc
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a31c:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218a3a0
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r12, [r7, #0x0]
    ldrsh r2, [r7, #0x2]
    add r0, r9, #0xfc
    add r2, r12, r2
    sub r2, r2, r3
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    bne @L0218a388
    mov r0, #0x0
    b @L0218a3a0
@L0218a35c:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218a3a0
    str r2, [sp, #0x0]
    ldrsh r2, [r7, #0x0]
    add r0, r9, #0xfc
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0218a3a0
@L0218a388:
    add r8, r8, #0x1
    add r7, r7, #0x6
@L0218a390:
    ldr r0, [sp, #0x8]
    cmp r8, r0
    blt @L0218a178
    mov r0, #0x1
@L0218a3a0:
    cmp r0, #0x0
    movne r4, #0x1
    bne @L0218a3e4
    ldr r0, [sp, #0x20]
    add r11, r11, #0x1
    add r0, r0, #0x6
    str r0, [sp, #0x20]
@L0218a3bc:
    ldr r0, [sp, #0x1c]
    cmp r11, r0
    blt @L0218a15c
    add r0, r4, #0x1
    mov r0, r0, lsl #0x10
    mov r4, r0, asr #0x10
@L0218a3d4:
    ldr r0, [sp, #0x24]
    cmp r4, r0
    blt @L0218a0ec
    mov r4, #0x0
@L0218a3e4:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    ldr r0, [r9, #0xd9c]
    cmp r4, #0x0
    orrne r0, r0, #0x400000
    strne r0, [r9, #0xd9c]
    orreq r0, r0, #0x800
    streq r0, [r9, #0xd9c]
@L0218a400:
    add sp, sp, #0xfc
    add sp, sp, #0x400
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Replaces the offsets of the pattern's words with their addresses
static int ResolvePattern(ForbiddenWordFile* file, ForbiddenWordPattern* pattern)
{
    for (int i = 0; i < pattern->count_; i++)
    {
        bool none = true;
        int offset = pattern->words_[i] - (const char*)0;
        if (offset != -1 && file->texts_ != 0)
            none = false;
        pattern->words_[i] = none ? 0 : file->texts_ + offset;
    }
    return 1;
}

void ForbiddenWordChecker::ToUpper(const char* text, char* output)
{
    while (*text != 0)
    {
        if (((*text >= 'a' && *text <= 'z') ? (*output = *text - 0x20) : (*output = *text)) != 0)
            text++;
        output++;
    }
}

// Whether a word is at one of the first positions of a text
int ForbiddenWordChecker::FindText(const char* word, const char* text, int length, int positions)
{
    for (int i = 0; i < positions; i++, text++)
    {
        if (memcmp(word, text, length) == 0)
            return 1;
    }
    return 0;
}

// Whether a pattern (with classes [...], repetitions {n,m}, digits : and the wildcard .{0,60}) matches the text at one
// of its first positions
// NONMATCHING: The loops over the pattern and the text are compiled in another form, with other registers (30.5 %)
#ifdef NONMATCHING
int ForbiddenWordChecker::Match(const char* pattern, const char* text, int length, int positions)
{
    int digit = symbols_[0];
    int classStart = symbols_[1];
    int classEnd = symbols_[2];
    int countStart = symbols_[3];
    int countEnd = symbols_[4];
    int wildcard = symbols_[7];
    for (int i = 0; i < positions; i++, text++)
    {
        const unsigned char* p = (const unsigned char*)pattern;
        const unsigned char* t = (const unsigned char*)text;
        while (true)
        {
            unsigned int symbol = *p;
            if (symbol == 0)
                return 1;

            int min = 1;
            unsigned char character = *t;
            int max = 1;
            const unsigned char* next = p;
            if (symbol == classStart)
            {
                while (*next != classEnd)
                    next++;
                next++;
            }
            else
            {
                next = p + 1;
            }
            if (*next == countStart)
            {
                min = next[1] - 8;
                max = next[3] - 8;
                if (next[4] - 8 == 0)
                    max *= 10;
            }

            int matches = 1;
            if (symbol == wildcard)
            {
                if (min == 0 && max == 60)
                {
                    while (true)
                    {
                        unsigned char current = *t;
                        if (current == 0 || current == 0xff)
                            return 0;
                        if (p[7] == current)
                            break;
                        t++;
                    }
                    p += 8;
                    t++;
                    continue;
                }
            }
            else if (symbol == digit)
            {
                if (character < 0x12 || character > 0x2b)
                    matches = 0;
            }
            else if (symbol == classStart)
            {
                char characters[8];
                __clear(characters, sizeof(characters));
                int negated = 0;
                char* output = characters;
                const unsigned char* current = p + 1;
                int range = 0;
                while (*current != symbols_[2])
                {
                    *output = *current;
                    if (*current == symbols_[5])
                        range = 2;
                    if (*current == symbols_[6])
                        negated = 1;
                    current++;
                    output++;
                }
                int length = strlen(characters);
                switch (negated + range)
                {
                    case 0:
                        matches = Contains((unsigned char*)characters, length, character);
                        break;
                    case 1:
                        matches = (unsigned char)characters[0] <= character &&
                                  character <= (unsigned char)characters[length - 1];
                        break;
                    case 2:
                        matches = Contains((unsigned char*)&characters[1], length - 1, character) == 0;
                        break;
                    case 3:
                        matches = !((unsigned char)characters[1] <= character &&
                                    character <= (unsigned char)characters[length - 2]);
                        break;
                }
                p += length + 1;
            }
            else if (symbol != character)
            {
                matches = 0;
            }

            if (matches)
            {
                for (int k = 0; k < min; k++)
                {
                    if (character != *t)
                    {
                        matches = 0;
                        break;
                    }
                    t++;
                }
                if (!matches)
                    break;
                while (min < max && character == *t)
                {
                    min++;
                    t++;
                }
            }
            else if (min != 0)
            {
                break;
            }

            p++;
            if (*p == countStart)
            {
                while (*p != countEnd)
                    p++;
                p++;
            }
        }
    }
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN20ForbiddenWordChecker8ContainsEPKhih(); // ForbiddenWordChecker::Contains
}

asm int ForbiddenWordChecker::Match(const char* pattern, const char* text, int length, int positions)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x30
    mov r10, r0
    ldr r0, [sp, #0x58]
    str r1, [sp, #0x0]
    str r0, [sp, #0x58]
    ldrb r0, [r10, #0x2a]
    str r2, [sp, #0x4]
    str r0, [sp, #0x24]
    ldrb r0, [r10, #0x2b]
    str r0, [sp, #0x20]
    ldrb r0, [r10, #0x2c]
    str r0, [sp, #0x1c]
    ldrb r0, [r10, #0x2d]
    str r0, [sp, #0x18]
    ldrb r0, [r10, #0x2e]
    str r0, [sp, #0x14]
    ldrb r0, [r10, #0x31]
    str r0, [sp, #0x10]
    mov r0, #0x0
    str r0, [sp, #0xc]
    b @L021859d8
@L021856dc:
    ldr r4, [sp, #0x0]
    ldr r5, [sp, #0x4]
@L021856e4:
    ldrb r1, [r4, #0x0]
    cmp r1, #0x0
    moveq r0, #0x1
    beq @L021859ec
    ldr r0, [sp, #0x20]
    mov r8, #0x1
    cmp r1, r0
    ldrb r6, [r5, #0x0]
    mov r11, r8
    mov r0, r4
    bne @L0218572c
@L02185710:
    ldrb r3, [r0, #0x0]
    ldr r2, [sp, #0x1c]
    cmp r3, r2
    addeq r0, r0, #0x1
    beq @L02185730
    add r0, r0, #0x1
    b @L02185710
@L0218572c:
    add r0, r4, #0x1
@L02185730:
    ldrb r3, [r0, #0x0]
    ldr r2, [sp, #0x18]
    cmp r3, r2
    bne @L02185764
    ldrb r3, [r0, #0x1]
    ldrb r2, [r0, #0x3]
    ldrb r0, [r0, #0x4]
    sub r8, r3, #0x8
    sub r11, r2, #0x8
    subs r0, r0, #0x8
    moveq r0, #0xa
    muleq r0, r11, r0
    moveq r11, r0
@L02185764:
    ldr r0, [sp, #0x10]
    cmp r1, r0
    mov r0, #0x1
    str r0, [sp, #0x8]
    bne @L021857b4
    cmp r8, #0x0
    cmpeq r11, #0x3c
    bne @L02185920
    ldrb r1, [r4, #0x7]
@L02185788:
    ldrb r0, [r5, #0x0]
    cmp r0, #0x0
    cmpne r0, #0xff
    moveq r0, #0x0
    beq @L021859ec
    cmp r1, r0
    addne r5, r5, #0x1
    bne @L02185788
    add r4, r4, #0x8
    add r5, r5, #0x1
    b @L021856e4
@L021857b4:
    ldr r0, [sp, #0x24]
    cmp r1, r0
    bne @L021857dc
    cmp r6, #0x12
    blo @L021857d0
    cmp r6, #0x2b
    bls @L02185920
@L021857d0:
    mov r0, #0x0
    str r0, [sp, #0x8]
    b @L02185920
@L021857dc:
    ldr r0, [sp, #0x20]
    cmp r1, r0
    bne @L02185914
    add r0, sp, #0x28
    mov r1, #0x8
    bl __clear
    mov r9, #0x0
    add r1, sp, #0x28
    add r0, r4, #0x1
    mov r7, r9
    ldrb r3, [r10, #0x2c]
    ldrb r2, [r10, #0x2f]
    ldrb lr, [r10, #0x30]
    b @L02185830
@L02185814:
    strb r12, [r1, #0x0]
    cmp r12, r2
    moveq r7, #0x2
    cmp r12, lr
    moveq r9, #0x1
    add r0, r0, #0x1
    add r1, r1, #0x1
@L02185830:
    ldrb r12, [r0, #0x0]
    cmp r12, r3
    bne @L02185814
    add r9, r9, r7
    add r0, sp, #0x28
    bl strlen
    mov r7, r0
    cmp r9, #0x0
    bne @L02185870
    mov r0, r10
    add r1, sp, #0x28
    mov r2, r7
    mov r3, r6
    bl _ZN20ForbiddenWordChecker8ContainsEPKhih
    str r0, [sp, #0x8]
    b @L02185908
@L02185870:
    cmp r9, #0x1
    bne @L021858a4
    sub r1, r7, #0x1
    add r0, sp, #0x28
    ldrb r1, [r0, r1]
    ldrb r0, [sp, #0x28]
    cmp r0, r6
    cmpls r6, r1
    movls r0, #0x1
    strls r0, [sp, #0x8]
    movhi r0, #0x0
    strhi r0, [sp, #0x8]
    b @L02185908
@L021858a4:
    cmp r9, #0x2
    bne @L021858d8
    mov r0, r10
    add r1, sp, #0x29
    sub r2, r7, #0x1
    mov r3, r6
    bl _ZN20ForbiddenWordChecker8ContainsEPKhih
    cmp r0, #0x0
    moveq r0, #0x1
    streq r0, [sp, #0x8]
    movne r0, #0x0
    strne r0, [sp, #0x8]
    b @L02185908
@L021858d8:
    cmp r9, #0x3
    bne @L02185908
    sub r1, r7, #0x2
    add r0, sp, #0x29
    ldrb r1, [r0, r1]
    ldrb r0, [sp, #0x29]
    cmp r0, r6
    cmpls r6, r1
    movhi r0, #0x1
    strhi r0, [sp, #0x8]
    movls r0, #0x0
    strls r0, [sp, #0x8]
@L02185908:
    add r0, r7, #0x1
    add r4, r4, r0
    b @L02185920
@L02185914:
    cmp r1, r6
    movne r0, #0x0
    strne r0, [sp, #0x8]
@L02185920:
    ldr r0, [sp, #0x8]
    cmp r0, #0x0
    beq @L02185988
    mov r1, #0x0
    b @L02185950
@L02185934:
    ldrb r0, [r5, #0x0]
    cmp r6, r0
    movne r0, #0x0
    strne r0, [sp, #0x8]
    bne @L02185958
    add r1, r1, #0x1
    add r5, r5, #0x1
@L02185950:
    cmp r1, r8
    blt @L02185934
@L02185958:
    ldr r0, [sp, #0x8]
    cmp r0, #0x0
    beq @L021859c0
    b @L0218597c
@L02185968:
    ldrb r0, [r5, #0x0]
    cmp r6, r0
    bne @L02185994
    add r8, r8, #0x1
    add r5, r5, #0x1
@L0218597c:
    cmp r8, r11
    blt @L02185968
    b @L02185994
@L02185988:
    bne @L02185994
    cmp r8, #0x0
    bne @L021859c0
@L02185994:
    ldrb r1, [r4, #0x1]!
    ldr r0, [sp, #0x18]
    cmp r1, r0
    bne @L021856e4
@L021859a4:
    ldrb r1, [r4, #0x0]
    ldr r0, [sp, #0x14]
    cmp r1, r0
    addne r4, r4, #0x1
    bne @L021859a4
    add r4, r4, #0x1
    b @L021856e4
@L021859c0:
    ldr r0, [sp, #0xc]
    add r0, r0, #0x1
    str r0, [sp, #0xc]
    ldr r0, [sp, #0x4]
    add r0, r0, #0x1
    str r0, [sp, #0x4]
@L021859d8:
    ldr r1, [sp, #0xc]
    ldr r0, [sp, #0x58]
    cmp r1, r0
    blt @L021856dc
    mov r0, #0x0
@L021859ec:
    add sp, sp, #0x30
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Whether a character is in a text
int ForbiddenWordChecker::Contains(const unsigned char* text, int length, unsigned char character)
{
    for (int i = 0; i < length; i++, text++)
    {
        if (*text == character)
            return 1;
    }
    return 0;
}

// Writes a random name, one of the texts from 20000 (men) or 21000 (women)
void CharacterCreation::SetRandomName()
{
    char* name = names_[sex_];
    memset(name, 0, 0x48);
    int count = sRandomNameCounts[sex_];
    int random = rand() % count;
    sprintf(name, func_020e0434(&texts_, random + (sex_ * 1000 + 20000)));
}

// Counts the timer down: whether it isn't over yet
int CharacterCreation::UpdateTimer(int ticks)
{
    if (timer_ > ticks)
    {
        timer_ -= ticks;
    }
    else
    {
        timer_ = 0;
        return 0;
    }
    return 1;
}
