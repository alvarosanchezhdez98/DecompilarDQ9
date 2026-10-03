// Overlay 15, the character viewer (see CharacterViewer.h)
// The compiler loads each variable from its own address with this pragma, like in the original
#pragma pool_data off
#include "Scene/Overlay_15/CharacterViewer.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Filesystem/GPC.h"
#include "Filesystem/LowNitroHandle.h"
#include "Filesystem/NarcHandle.h"
#include "Filesystem/FileAccessor.h"
#include "GameState/GameState.h"
#include "Graphics/NSBXX/Animation.h"
#include "Graphics/NSBXX/GeometryFifo.h"
#include "Graphics/NSBXX/RenderCommands.h"
#include "Graphics/NSBXX/RenderConfig.h"
#include "Graphics/Vector.h"
#include "Graphics/VRAMStaging.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "Resource/Script.h"
#include "System/Cache.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include "System/Timing.h"
#include "System/VRAM.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_MASTER_BRIGHT ((volatile unsigned short*)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((volatile unsigned short*)0x0400106c)

// The NitroSDK's FX_Mul
static inline fix32_t FX_Mul(fix32_t a, fix32_t b)
{
    return (fix32_t)(((int64_t)a * b + 0x800) >> 12);
}

// The colors of the characters' parts (func_02099cac returns them)
struct CharacterColors
{
    unsigned short hair_[10][2];
    unsigned short colors2_[8][2];
    unsigned short colors4_[8][4];
    unsigned short colors8_[8][8];
    unsigned short skin_[8][2];
    // The color of the models' edges
    unsigned short edge_;
};

// The sounds of a monster (func_02070fd0 returns them)
struct MonsterSounds
{
    char unk_0[0x14];
    unsigned int sounds_;
};

struct ViewerCamera;
struct Unknown_0203bd08;

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // The runtime's float functions, for the assembly
    void _fdiv();
    void _ffix();
    void _fflt();
    void _fgr();
    void _fmul();
    void _fsub();

    // The game's heap
    extern AllocatorUnion data_02114e20;
    // The pad
    extern char data_02114e30[];
    // The sound player
    extern char data_02108760[];
    // A buffer for the files
    extern unsigned char data_0211e33c[];
    // The archive and the file of the parts' names
    extern const char* data_020f2a30;
    extern const char* data_020f2a38;

    // Sets the game's resources
    void func_0200fb84(GameState* gameState, GameResources* resources);
    void func_020100c4(GameState* gameState, void* camera);
    ViewerCamera* func_020100cc(GameState* gameState);
    void func_02010124(GameState* gameState);
    // Returns whether the buttons are held
    bool func_02012430(void* pad, int buttons);
    // Returns whether the buttons were just pressed
    bool func_02012444(void* pad, int buttons);
    // Returns whether the buttons were just released
    bool func_02012468(void* pad, int buttons);
    // Returns whether the buttons were pressed or repeat
    bool func_0201248c(void* pad, int buttons);
    void* func_02012d88(AllocatorUnion* allocator, unsigned int size);
    void func_02012da4(AllocatorUnion* allocator, void* data);
    void func_02012de4(AllocatorUnion* allocator);
    void func_02012efc();
    int func_020d2ff0(const char* string);
    void func_02079a3c(GPCReadPair* pair);
    void func_0203dafc(ObjectArchiveLoadInfo* info);
    PartEntry* func_020dedd0(PartNameTable* names, short id);
    unsigned int func_020de234(const PartEntry* entry, int female);
    int func_020de2a4(const PartEntry* entry, int, int female);
    void func_020de848(PartNameTable* names);
    void func_020dea64(PartNameTable* names, SafeAllocator* allocator, void* file, unsigned int size,
        const unsigned char* categories, int count);
    PartEntry* func_020deda4(PartNameTable* names, int, PartEntry* entry);
    CharacterColors* func_02099cac();
    void func_02099d34(Model3D* model, int, int, int);
    void func_02099e18(Model3D* model, int, int, int);
    MonsterEntry* func_0206f4f0(void* monsters, short id);
    void func_0206efc4(void* monsters);
    void func_0206efd8(void* monsters, SafeAllocator* allocator);
    MonsterSounds* func_02070fd0(void* sounds, unsigned short id);
    void func_020709d8(void* sounds);
    void func_020709ec(void* sounds, SafeAllocator* allocator);
    void func_0205ebc0(void* sound, int, int);
    void func_0205ea20(void* sound, int);
    void func_020407b4(Object3D* object, int, int, int);
    void func_02054f80(void*);
    int func_02055180(void*, SafeAllocator* allocator, void* file, unsigned int size);
    void func_0205563c(ViewerEffect* effect);
    void func_02055718(ViewerEffect* effect, Object3D* object, SafeAllocator* allocator);
    void func_02055774(ViewerEffect* effect);
    void func_0205578c(ViewerEffect* effect);
    void func_020577cc(void*, unsigned short* polygons, unsigned short* quads);
    void func_0207de48(VRAMManagerState* state, int textureSize, int paletteSize);
    void func_0207df50(VRAMManagerState* state);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
    void func_02031234(int);
    void func_020a2cf0(void* camera);
    void func_020a3568(void* camera, int);
    void func_0202eab8(void* camera);
    // Draws a box
    void func_0208b5b4(Vector3fix position, Vector3fix size, int, int color);
    // Draws a mark at a position
    void func_0208b610(Vector3fix position, int color, int, int, int, int);
    ViewerCamera* func_020100bc(GameState* gameState);
    void func_020a20d8(void* camera);
    void func_020a2010(void* camera);
    void func_020a2794(void* camera);
    void func_020a27a0(void* camera);
    void func_0202df68(void* camera);
    void func_0202e0a4(void* camera);
    void func_0202e5d8(void* camera, int x, int y, int z);
    void func_0202e7d4(void* camera, int* x, int* y, int* z);
    // The debug menus
    void func_02028d58(int);
    void func_02028d68(int);
    void func_02028ddc();
    void func_02028dec(int);
    void func_02029060();
    void func_02029088();
    void func_020290ac(int);
    void func_020290e8(int x, int y, const char* text);
    void func_0202920c(int, int x, int y, int width, int height);
    void func_0202949c(DebugMenuItem* item);
    void func_020294cc(DebugMenuItem* item, const char* text);
    const char* func_02029560(DebugMenuItem* item);
    void func_02029568(DebugMenu* menu);
    void func_02029988(DebugMenu* menu, int);
    void func_0202a6c4(DebugMenu* menu);
    void func_0202a8cc(DebugMenu* menu, int);
    void func_0202a91c(DebugMenu* menu);
    void func_0202a944(DebugMenu* menu, DebugMenuItem* item);
    DebugMenuItem* func_0202a9ac(DebugMenu* menu, int index);
    const char* func_020e51cc(int id);
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b34(void* music, int, int, int, int);
    void func_02094b38(void* music, int);
    void func_02094b3c(void* music, int);
    int func_02094b4c(void* music);
    Unknown_0203bd08* func_0203bd08();
    void func_0203bd24();
    void func_0203bd88(Unknown_0203bd08*);
    void func_0203bdb0(Unknown_0203bd08*);
    void func_0203aa08(void*);
    MessageSystem* func_020421a0();
    void func_02042b30(MessageSystem* messages, VRAMManagerState* state);
    void func_020432c4(MessageSystem* messages);
    void func_0204359c(MessageSystem* messages, int);
    void func_020439b0(MessageSystem* messages, int);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    void func_02045d14(MessageSystem* messages, const char* text, unsigned short* line, int);
    void func_02045f3c(MessageSystem* messages, unsigned short* line, int x, int y, int color, int, int, int, int, int);
    void func_02069fec(MessageSystem* messages, const char* text, char* converted);
    void func_020bb48c(int, int);
    void func_020bb780(int, int);
    void func_020bbcb4();
    // NNS_SndMain
    void func_020bbd9c();
    void func_020bc028(int);
    // GX_DispOn
    void func_020c38d4();
    // GX_SetGraphicsMode
    void func_020c391c(int mode, int bgMode, int bg0Is3D);
    // GXS_SetGraphicsMode
    void func_020c3984(int bgMode);
    // GXx_SetMasterBrightness_
    void func_020c39a0(volatile unsigned short* reg, int brightness);
    // GXx_GetMasterBrightness_
    int func_020c39c8(volatile unsigned short* reg);
    void func_020c3a0c(int);
    // G3X_Init
    void func_020c51dc();
    // G3X_Reset
    void func_020c52e8();
    // G3X_InitMtxStack
    void func_020c537c();
    // G3X_ResetMtxStack
    void func_020c5414();
    // G3X_SetEdgeColorTable
    void func_020c555c(const unsigned short* colors);
    // G3X_SetClearColor
    void func_020c5588(int color, int alpha, int depth, int polygonID, int fog);
    // G3i_OrthoW_
    void func_020c5770(fix32_t top, fix32_t bottom, fix32_t left, fix32_t right, fix32_t near, fix32_t far,
                       fix32_t scaleW, int draw, void* matrix);
    // G3i_LookAt_
    void func_020c57d4(const Vector3fix* camera, const Vector3fix* up, const Vector3fix* target, int draw,
                       void* matrix);
    // OS_WaitVBlankIntr
    void func_020c9820();
    // MIi_CpuClearFast
    void func_020ca458(int value, void* dst, unsigned int len);
    void func_020d86d0(int, int);
}

ModelRenderContext* GetModel3DContext(Model3D* model);

// The camera of the game (func_020100cc returns it)
struct ViewerCamera
{
    int unk_0;
    Vector3fix eye_;
    Vector3fix target_;
};

// The original defines its constants before the first function, so the compiler sorts them by size, and the other
// variables after it, which it keeps in their order (without #pragma ipa file)
struct ModelExtension
{
    char text_[8];
};

struct FaceLetters
{
    char letters_[10];
};

struct EdgeColors
{
    unsigned short colors_[8];
};

struct ObjectSizes
{
    unsigned int sizes_[7];
};

struct DollAnimated
{
    int animated_[9];
};

struct PlayerBones
{
    int bones_[6][2];
};

struct PartSizes
{
    unsigned int sizes_[11][2];
};

struct VRAMSizes
{
    int sizes_[10][4];
};

struct DollBones
{
    char names_[9][0x14];
};

// The categories of parts that the viewer loads the names of
static const unsigned char sPartCategories[9] = {0, 1, 2, 3, 4, 5, 6, 7, 0xb};
// The color of the models' edges
static const EdgeColors sEdgeColors = {{0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086}};
// The parts whose palettes LoadDoll() loads
static const int sDollPalettes[] = {0, 1, 5, 6, 4, 7, -1};
// The sizes of the allocators of the objects that aren't characters
static const ObjectSizes sObjectSizes = {{0, 0, 0x15000, 0x35000, 0x10000, 0x5000, 0x5000}};
// The up vector of the camera of the menus
static const Vector3fix sMenuUp = {0, 0x1000, 0};
// The sizes of the parts' allocators, then of the buffer, for the players and the dolls
static const PartSizes sPartSizes = {{
    {0x2838, 0x5400}, {0x1968, 0x2000}, {0xb0c, 0x1400}, {0xd64, 0x1c00}, {0x810, 0xc00},
    {0x200, 0x1c00}, {0x200, 0x1c00}, {0x1064, 0x23e8}, {0xaac, 0x1b58}, {0x54c, 0x1400},
    {0xc000, 0x1000}}};
// The parts that DrawPlayer() draws at the bones of the body (it sets the bones)
static const PlayerBones sPlayerBones = {{{2, 0}, {3, 0}, {7, 0}, {9, 0}, {8, 0}, {-1, -1}}};
// The scales of the objects that aren't characters
static const Vector3fix sNpcScale = {0x10a, 0x10a, 0x10a};
static const Vector3fix sMonsterScale = {0x10a, 0x10a, 0x10a};
// The sizes of the textures and of the palettes of the parts, for the players then for the dolls
static const VRAMSizes sVRAMSizes = {{
    {0xc00, 0x200, 0x4400, 0x220}, {0x400, 0x40, 0x1000, 0x40}, {0x800, 0x40, 0x1000, 0x40}, {0, 0, 0, 0},
    {0x400, 0x40, 0x1000, 0x40}, {0x200, 0x40, 0x800, 0x40}, {0x200, 0x40, 0x800, 0x40},
    {0x400, 0x40, 0x800, 0x40}, {0x400, 0x40, 0x800, 0x40}, {0x400, 0x40, 0x800, 0x40}}};
static const Vector3fix sEffectScale = {0x10a, 0x10a, 0x10a};
// The extension of the parts' models
static const ModelExtension sModelExtension = {"nsbmd"};
// The target of the camera of the menus
static const Vector3fix sMenuTarget = {0, 0, -0x1000};
// The bones of the doll's body where DrawDoll() draws its parts
static const DollBones sDollBones = {{"", "head", "head", "head", "weaponR", "weaponL", "", "", ""}};
// The parts whose palettes LoadPlayer() loads
static const int sPlayerPalettes[] = {0, 1, 5, 6, 4, 7, -1};
// The parts of the dolls that are animated with the body
static const DollAnimated sDollAnimated = {{0, 0, 0, 0, 0, 0, 1, 1, 1}};
static const Vector3fix sCameraScale = {0x10a, 0x10a, 0x10a};
// The config that the commands fill
static ViewerConfig* sConfig;
// The letters of the faces' files, for each hundred of the body's file number
static const FaceLetters sFaceLetters = {"bbdccfcea"};
// The number of categories of parts whose names it loads
const int CharacterViewer::sCategoryCount = 9;

static int Command_SetEntryCount(Script::Parameter* params, int count);
static int Command_AddEntry(Script::Parameter* params, int count);
static int Command_SetPresetCount(Script::Parameter* params, int count);
static int Command_AddPreset(Script::Parameter* params, int count);

static int Command_SetEntryCount(Script::Parameter* params, int count)
{
    ViewerConfig* config = sConfig;
    config->SetEntryCount(params[0].ToInt());
    return 1;
}

static int Command_AddEntry(Script::Parameter* params, int count)
{
    const char* name = params[0].ToString();
    const char* file = params[1].ToString();
    int id = params[2].ToInt();
    int page = params[3].ToInt();
    int link = params[4].ToInt();
    ViewerEntry entry;
    entry.name_ = NULL;
    entry.file_ = NULL;
    entry.id_ = 0;
    entry.page_ = 0;
    entry.link_ = 0;
    if (name != NULL)
    {
        entry.name_ = (char*)func_02012d88(&data_02114e20, func_020d2ff0(name) + 1);
        if (entry.name_ != NULL)
            strcpy(entry.name_, name);
    }
    if (file != NULL)
    {
        entry.file_ = (char*)func_02012d88(&data_02114e20, func_020d2ff0(file) + 1);
        if (entry.file_ != NULL)
            strcpy(entry.file_, file);
    }
    entry.id_ = id;
    entry.page_ = page;
    entry.link_ = link;
    sConfig->AddEntry(&entry);
    return 1;
}

static int Command_SetPresetCount(Script::Parameter* params, int count)
{
    ViewerConfig* config = sConfig;
    config->SetPresetCount(params[0].ToInt());
    return 1;
}

static int Command_AddPreset(Script::Parameter* params, int count)
{
    const char* name = (params++)->ToString();
    ViewerPreset preset;
    preset.name_ = NULL;
    preset.items_ = NULL;
    if (name != NULL)
    {
        preset.name_ = (char*)func_02012d88(&data_02114e20, func_020d2ff0(name) + 1);
        if (preset.name_ != NULL)
            strcpy(preset.name_, name);
    }
    for (int i = 1; i < count; i += 3)
    {
        ViewerPresetItem* item;
        const char* file = params++->ToString();
        int id = params++->ToInt();
        int kind = params++->ToInt();
        item = (ViewerPresetItem*)func_02012d88(&data_02114e20, sizeof(ViewerPresetItem));
        item->file_ = NULL;
        item->id_ = 0;
        item->kind_ = 0;
        item->next_ = NULL;
        if (file != NULL)
        {
            item->file_ = (char*)func_02012d88(&data_02114e20, func_020d2ff0(file) + 1);
            if (item->file_ != NULL)
                strcpy(item->file_, file);
        }
        item->id_ = id;
        item->kind_ = kind;
        ViewerPresetItem** last = &preset.items_;
        while (*last != NULL)
            last = &(*last)->next_;
        *last = item;
    }
    sConfig->AddPreset(&preset);
    return 1;
}

// The commands of data/bin/charaview4.bin
static Script::OpcodeLookupEntry sCommands[] = {
    {0x64, Command_SetEntryCount},
    {0x65, Command_AddEntry},
    {0x66, Command_SetPresetCount},
    {0x67, Command_AddPreset},
    {0, NULL},
};

// The strings of the file, which the compiler pools in this order. Some functions are in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for them
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] =
    "data/bin/charaview4.bin\0"
    "\xff\xff\xff\0"
    "nsbtx\0"
    "d_%c%03d%s%s.%s\0"
    "p_%c%03d%s%s.%s\0"
    "md\0"
    "mp\0"
    "wp\0"
    "%s%02d%02d%c\0"
    "data/pack_lv5/chara_mp.gp2\0"
    "%s.chr\0"
    "%se.chr\0"
    "%sm.chr\0"
    "data/chara/%s.chr\0"
    "data/chara/%s%c.chr\0"
    "data/event_lv5/%s.chr\0"
    "stand\0"
    "data/pack_lv5/chara_pd.gp2\0"
    "%s.nsbca\0"
    "%s.bcfg\0"
    "data/pack_lv5/chara_pc.gp2\0"
    "waist\0"
    "arm1R\0"
    "arm1L\0"
    "PC\0"
    "DOLL\0"
    "%s_f.mon\0"
    "%s.mon\0"
    "data/pack_lv5/enemy.gp2\0"
    ".cchr\0"
    ".cmot\0"
    "data/chara_sub/%s.chr\0"
    "data/effect/%s.chr\0"
    "ARC\0"
    ".beff\0"
    "eye\0"
    "lookat\0"
    "pos\0"
    "head\0"
    "leg1L\0"
    "leg1R\0"
    "p\x81m\x8a\xe7\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x94\xaf\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x8a\x95\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x95\x9e\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x98r\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x83Y\x83\x7b\x83\x93\x81n\x81" "F%5d\x81^%5d\0"
    "p\x81m\x8c" "C\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x95\x90\x8a\xed\x81n\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x8f\x82\x81n\x81@\x81@\x81" "F%5d\x81^%5d\0"
    "p\x81m\x83\x81\x83\x82\x83\x8a\x81n\x81" "F%d\x81^%d\0"
    "pFPS :%.2f\0"
    "pT   :%d\0"
    "pQ   :%d\0"
    "p\x81m%s\x81n\0"
    "pSTEP :%0.2f\0"
    "pFRAME:%0.2f\0"
    "pRATE :%0.3f\0"
    "[Operation]\0"
    "Select :u,d\0"
    "Step   :R+r,l\0"
    "No Loop:L+A\0"
    "Loop   :L+A\0"
    "Play   :R+A\0"
    "Scene  :R\0"
    "Stop   :R+A\0"
    "Battle   :R\0"
    "No Battle:R\0"
    "Battle :L\0"
    "Field  :L\0"
    "[*]Aspect\0"
    "[-]Aspect\0"
    "[-]Floor\0"
    "[*]Monster Box\0"
    "[-]Monster Box\0"
    "[*]Sync Motion\0"
    "[-]Sync Motion\0"
    "[*]View Memory\0"
    "[-]View Memory\0"
    "[Top Menu]\0"
    "[Load]\0"
    "[Del]\0"
    "[Player]\0"
    "[Monster]\0"
    "[Effect]\0"
    "[NPC]\0"
    "[Motion Camera]\0"
    "[Gender]\0"
    "[Face]\0"
    "[Eye Colour]\0"
    "[Skin Colour]\0"
    "[Hairstyle]\0"
    "[Hair Colour]\0"
    "[\x82\xe6\x82\xeb\x82\xa2]\0"
    "[\x98r]\0"
    "[\x83Y\x83\x7b\x83\x93]\0"
    "[\x82\xad\x82\xc2]\0"
    "[\x95\x90\x8a\xed]\0"
    "[\x8f\x82]\0"
    "[\x8a\x95]\0"
    "[Add Motion]\0"
    "[Event Motion]\0"
    "[Skill Motion]\0"
    "[Build]\0"
    "[Event]\0"
    "[Villager]\0"
    "[NPC Motion]\0"
    "[Trick Motion]\0"
    "[Event Camera]\0"
    "[Skill Camera]\0"
    "[Option]\0"
    "[Info]\0"
    "[Move]\0"
    "[Preset]\0"
    "[%s]\0"
    "%s\x81" "F%s\0"
    "No Data\0"
    "[*]\0"
    "[-]\0"
    "[Motion]\0"
    "0123456789.FPSTQSIZERAMKB:abcdefghijklmnopqrstuvwxyz[]/";
#define STRING(offset, text) (sStrings + (offset))
#endif

void ViewerConfig::Clear()
{
    entries_ = NULL;
    entryCount_ = 0;
    presets_ = NULL;
    presetCount_ = 0;
}

void ViewerConfig::Free()
{
    for (int i = 0; i < entryCount_; i++)
    {
        if (entries_[i].name_ != NULL)
        {
            func_02012da4(&data_02114e20, entries_[i].name_);
            entries_[i].name_ = NULL;
        }
        if (entries_[i].file_ != NULL)
        {
            func_02012da4(&data_02114e20, entries_[i].file_);
            entries_[i].file_ = NULL;
        }
    }
    for (int i = 0; i < presetCount_; i++)
    {
        if (presets_[i].name_ != NULL)
        {
            func_02012da4(&data_02114e20, presets_[i].name_);
            presets_[i].name_ = NULL;
        }
        ViewerPresetItem* item = presets_[i].items_;
        while (item != NULL)
        {
            ViewerPresetItem* next = item->next_;
            if (item->file_ != NULL)
            {
                func_02012da4(&data_02114e20, item->file_);
                item->file_ = NULL;
            }
            func_02012da4(&data_02114e20, item);
            item = next;
        }
    }
    if (entries_ != NULL)
    {
        func_02012da4(&data_02114e20, entries_);
        entries_ = NULL;
    }
    if (presets_ != NULL)
    {
        func_02012da4(&data_02114e20, presets_);
        presets_ = NULL;
    }
    Clear();
}

void ViewerConfig::SetEntryCount(int count)
{
    Free();
    entries_ = (ViewerEntry*)func_02012d88(&data_02114e20, count * sizeof(ViewerEntry));
    entryCount_ = 0;
}

void ViewerConfig::SetPresetCount(int count)
{
    presets_ = (ViewerPreset*)func_02012d88(&data_02114e20, count * sizeof(ViewerPreset));
    presetCount_ = 0;
}

void ViewerConfig::AddEntry(ViewerEntry* entry)
{
    int index = entryCount_++;
    ViewerEntry* last = &entries_[index];
    last->name_ = entry->name_;
    last->file_ = entry->file_;
    last->id_ = entry->id_;
    last->page_ = entry->page_;
    last->link_ = entry->link_;
}

void ViewerConfig::AddPreset(ViewerPreset* preset)
{
    int index = presetCount_++;
    ViewerPreset* last = &presets_[index];
    last->name_ = preset->name_;
    last->items_ = preset->items_;
}


void ViewerConfig::Load(const char* path)
{
    unsigned int size;
    Script script;
    void* file;

    Free();
    BackgroundLoader::AddLockGlobal();
    if (path != NULL)
        file = LoadFileIntoMemory(path, data_0211e33c, &size);
    else
        file = LoadFileIntoMemory(STRING(0x0, "data/bin/charaview4.bin"), data_0211e33c, &size);
    if (file != NULL)
    {
        sConfig = this;
        script.Initialize();
        script.SetOpcodeLookup(sCommands);
        script.Load(file, size);
        script.Execute();
    }
    BackgroundLoader::RemoveLockGlobal();
}

ViewerEntry* ViewerConfig::GetEntry(int index)
{
    if (index < 0 || entryCount_ <= index)
        return NULL;
    return &entries_[index];
}

ViewerPreset* ViewerConfig::GetPreset(int index)
{
    if (index < 0 || presetCount_ <= index)
        return NULL;
    return &presets_[index];
}

// The bones of the camera objects: the position, the eye and the target
// (a string, which the code writes to)
#define sCameraBones ((unsigned char*)STRING(0x18, "\xff\xff\xff"))
// Where the hook writes the matrices of the camera's bones, when they're not NULL
struct CameraOutputs
{
    Matrix4x3* target_;
    Matrix4x3* position_;
    Matrix4x3* eye_;
    Matrix4x3 eyeMatrix_;
    Matrix4x3 targetMatrix_;
    Matrix4x3 positionMatrix_;
};
static CameraOutputs sCameraOutputs;

static int GetCurrentBone(RenderCommandHandler* handler);

// Saves the matrices of the camera's bones when they're computed (a hook of the render commands)
// NONMATCHING: the C matches 84.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler loads sCameraOutputs from the start of .bss, where sConfig is, while the original loads it from its own
// address.
#ifdef NONMATCHING
static void SaveCameraBones(RenderCommandHandler* handler)
{
    if (!(handler->flags_ & 0x10))
        return;
    if (sCameraBones[1] == GetCurrentBone(handler) && sCameraOutputs.eye_ != NULL)
    {
        GetCurrentPositionAndDirectionMatrices(sCameraOutputs.eye_, NULL);
        sCameraOutputs.eyeMatrix_ = *sCameraOutputs.eye_;
        Mat4x3_Multiply(sCameraOutputs.eye_, RenderConfig::GetInverseViewMatrix(), sCameraOutputs.eye_);
    }
    if (sCameraBones[2] == GetCurrentBone(handler) && sCameraOutputs.target_ != NULL)
    {
        GetCurrentPositionAndDirectionMatrices(sCameraOutputs.target_, NULL);
        sCameraOutputs.targetMatrix_ = *sCameraOutputs.target_;
        Mat4x3_Multiply(sCameraOutputs.target_, RenderConfig::GetInverseViewMatrix(), sCameraOutputs.target_);
    }
    if (sCameraBones[0] != GetCurrentBone(handler))
        return;
    if (sCameraOutputs.position_ == NULL)
        return;
    GetCurrentPositionAndDirectionMatrices(sCameraOutputs.position_, NULL);
    sCameraOutputs.positionMatrix_ = *sCameraOutputs.position_;
    Mat4x3_Multiply(sCameraOutputs.position_, RenderConfig::GetInverseViewMatrix(), sCameraOutputs.position_);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12RenderConfig20GetInverseViewMatrixEv(); // RenderConfig::GetInverseViewMatrix
}

static asm void SaveCameraBones(RenderCommandHandler* handler)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r4, r0
    ldr r1, [r4, #0x8]
    tst r1, #0x10
    ldmeqia sp!, {r3, r4, r5, pc}
    bl GetCurrentBone
    ldr r1, =sStrings+0x18
    ldrb r1, [r1, #0x1]
    cmp r1, r0
    bne @L0218bbb4
    ldr r0, =sCameraOutputs
    ldr r0, [r0, #0x8]
    cmp r0, #0x0
    beq @L0218bbb4
    mov r1, #0x0
    bl GetCurrentPositionAndDirectionMatrices
    ldr r0, =sCameraOutputs
    ldr r12, =sCameraOutputs+0xc
    ldr lr, [r0, #0x8]
    mov r5, #0x3
@L0218bb8c:
    ldmia lr!, {r0, r1, r2, r3}
    stmia r12!, {r0, r1, r2, r3}
    subs r5, r5, #0x1
    bne @L0218bb8c
    bl _ZN12RenderConfig20GetInverseViewMatrixEv
    ldr r2, =sCameraOutputs
    mov r1, r0
    ldr r0, [r2, #0x8]
    mov r2, r0
    bl Mat4x3_Multiply
@L0218bbb4:
    mov r0, r4
    bl GetCurrentBone
    ldr r1, =sStrings+0x18
    ldrb r1, [r1, #0x2]
    cmp r1, r0
    bne @L0218bc1c
    ldr r0, =sCameraOutputs
    ldr r0, [r0, #0x0]
    cmp r0, #0x0
    beq @L0218bc1c
    mov r1, #0x0
    bl GetCurrentPositionAndDirectionMatrices
    ldr r0, =sCameraOutputs
    ldr lr, =sCameraOutputs+0x3c
    ldr r5, [r0, #0x0]
    mov r12, #0x3
@L0218bbf4:
    ldmia r5!, {r0, r1, r2, r3}
    stmia lr!, {r0, r1, r2, r3}
    subs r12, r12, #0x1
    bne @L0218bbf4
    bl _ZN12RenderConfig20GetInverseViewMatrixEv
    ldr r2, =sCameraOutputs
    mov r1, r0
    ldr r0, [r2, #0x0]
    mov r2, r0
    bl Mat4x3_Multiply
@L0218bc1c:
    mov r0, r4
    bl GetCurrentBone
    ldr r1, =sStrings+0x18
    ldrb r1, [r1, #0x0]
    cmp r1, r0
    ldmneia sp!, {r3, r4, r5, pc}
    ldr r0, =sCameraOutputs
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    mov r1, #0x0
    bl GetCurrentPositionAndDirectionMatrices
    ldr r0, =sCameraOutputs
    ldr r12, =sCameraOutputs+0x6c
    ldr lr, [r0, #0x4]
    mov r4, #0x3
@L0218bc5c:
    ldmia lr!, {r0, r1, r2, r3}
    stmia r12!, {r0, r1, r2, r3}
    subs r4, r4, #0x1
    bne @L0218bc5c
    bl _ZN12RenderConfig20GetInverseViewMatrixEv
    ldr r2, =sCameraOutputs
    mov r1, r0
    ldr r0, [r2, #0x4]
    mov r2, r0
    bl Mat4x3_Multiply
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

static int GetCurrentBone(RenderCommandHandler* handler)
{
    if (handler->flags_ & 0x10)
        return handler->currentBoneMatrix_;
    return -1;
}

int ViewObject::Allocate()
{
    if (kind_ == Kind_Player || kind_ == Kind_Doll)
    {
        PartSizes sizes = sPartSizes;
        allocators_ = (SafeAllocator*)func_02012d88(&data_02114e20, 10 * sizeof(SafeAllocator));
        if (allocators_ == NULL)
        {
            Finish();
            return 0;
        }
        objects_ = (Object3D*)func_02012d88(&data_02114e20, 10 * sizeof(Object3D));
        if (objects_ == NULL)
        {
            Finish();
            return 0;
        }
        for (int i = 0; i < 10; i++)
        {
            allocators_[i].ResetAllocatorPointer();
            void* buffer = func_02012d88(&data_02114e20, sizes.sizes_[i][kind_]);
            if (buffer == NULL)
                return 0;
            allocators_[i].CreateTypeA(buffer, sizes.sizes_[i][kind_]);
            allocators_[i].Reset();
            objects_[i].Initialize();
        }
        parts_ = (int*)func_02012d88(&data_02114e20, 10 * sizeof(int));
        if (parts_ == NULL)
        {
            Finish();
            return 0;
        }
        memset(parts_, -1, 10 * sizeof(int));
        parts_[0] = 0x32cf;
        parts_[1] = 0x3f57;
        parts_[2] = 0x233c;
        parts_[3] = 0x2328;
        parts_[4] = 0x2328;
        parts_[5] = 0x36b7;
        parts_[6] = 0x42e0;
        if (kind_ == Kind_Player)
            slot_ = viewer_->FindPlayerSlot();
        else
            slot_ = viewer_->FindDollSlot();
        if (slot_ == NULL)
        {
            Finish();
            return 0;
        }
        slot_->used_ = 1;
        bufferSize_ = sizes.sizes_[10][kind_];
        buffer_ = func_02012d88(&data_02114e20, bufferSize_);
        if (buffer_ == NULL)
        {
            Finish();
            return 0;
        }
    }
    else
    {
        ObjectSizes sizes = sObjectSizes;
        allocators_ = (SafeAllocator*)func_02012d88(&data_02114e20, sizeof(SafeAllocator));
        if (allocators_ == NULL)
        {
            Finish();
            return 0;
        }
        allocators_->ResetAllocatorPointer();
        void* buffer = func_02012d88(&data_02114e20, sizes.sizes_[kind_]);
        if (buffer == NULL)
            return 0;
        allocators_->CreateTypeA(buffer, sizes.sizes_[kind_]);
        allocators_->Reset();
        slot_ = viewer_->FindSlot();
        if (slot_ == NULL)
        {
            Finish();
            return 0;
        }
        slot_->used_ = 1;
        if (kind_ == Kind_Npc || kind_ == Kind_Monster)
        {
            bufferSize_ = 0xc000;
            buffer_ = func_02012d88(&data_02114e20, bufferSize_);
            if (buffer_ == NULL)
            {
                Finish();
                return 0;
            }
        }
        objects_ = (Object3D*)func_02012d88(&data_02114e20, sizeof(Object3D));
        if (objects_ == NULL)
        {
            Finish();
            return 0;
        }
        objects_->Initialize();
        if (kind_ == Kind_Effect)
        {
            effect_ = (ViewerEffect*)func_02012d88(&data_02114e20, sizeof(ViewerEffect));
            if (effect_ == NULL)
            {
                Finish();
                return 0;
            }
            func_0205563c(effect_);
        }
    }
    return 1;
}

bool ViewObject::GetModelName(char* name, unsigned int part, int file)
{
    PartEntry* entry = func_020dedd0(&viewer_->parts_, parts_[part]);
    PartEntry* body = func_020dedd0(&viewer_->parts_, parts_[7]);
    int number = func_020de234(entry, female_);
    ModelExtension extension = sModelExtension;
    char suffix[2] = {0};
    char suffix2[2] = {0};
    switch (part)
    {
    case 0:
    case 1:
    case 2:
    default:
        break;
    case 4:
        strcpy(extension.text_, STRING(0x1c, "nsbtx"));
        suffix[0] = 'a';
        suffix[1] = 0;
        number += hairColor_;
        break;
    case 3:
        suffix[0] = 'a';
        suffix[1] = 0;
        if (body != NULL && body->unk_18 > -1)
        {
            int index = (int)func_020de234(body, female_) / 100;
            if ((unsigned int)index >= 10)
                return false;
            FaceLetters letters = sFaceLetters;
            char letter = letters.letters_[index];
            if (letter == 0)
                return false;
            suffix[0] = letter;
            if (index == 3 && female_ == 0 && entry->unk_18 == 0x2329)
                suffix[0] = 'f';
        }
        break;
    case 5:
    case 6:
        if (file)
            strcpy(extension.text_, STRING(0x1c, "nsbtx"));
        break;
    }
    if (file == 0)
        sprintf(name, STRING(0x22, "d_%c%03d%s%s.%s"), (char)entry->letter_, number, suffix, suffix2, extension.text_);
    else
        sprintf(name, STRING(0x32, "p_%c%03d%s%s.%s"), (char)entry->letter_, number, suffix, suffix2, extension.text_);
    return true;
}

void ViewObject::GetAnimationName(char* name, int field)
{
    PartEntry* weapon = func_020dedd0(&viewer_->parts_, parts_[8]);
    PartEntry* body = func_020dedd0(&viewer_->parts_, parts_[0]);
    unsigned int bodyAnimations = 0;
    unsigned int weaponAnimations = 0;
    if (body != NULL)
        bodyAnimations = body->model_->animations_;
    if (weapon != NULL)
        weaponAnimations = weapon->model_->animations_;
    char prefix[4] = {0};
    int letter;
    if (kind_ == Kind_Doll)
    {
        strcpy(prefix, STRING(0x42, "md"));
        if (female_ == 0)
            letter = 'm';
        else
            letter = 'w';
    }
    else
    {
        strcpy(prefix, STRING(0x45, "mp"));
        if (battle_ == 0)
            letter = 'n';
        else
            letter = 'b';
        if (field)
            letter = 'f';
    }
    if ((letter == 'n' || letter == 'f') && female_ == 1)
        strcpy(prefix, STRING(0x48, "wp"));
    sprintf(name, STRING(0x4b, "%s%02d%02d%c"), prefix, bodyAnimations, weaponAnimations, letter);
}

void ViewObject::LoadPalette(int part)
{
    PartEntry* entry = func_020dedd0(&viewer_->parts_, parts_[part]);
    if (entry == NULL || entry->model_ == NULL)
        return;
    VRAMManagerState* state = &slot_->states_[part];
    if (kind_ == Kind_Doll)
    {
        int count = func_020de2a4(entry, 0, female_);
        if (count == 0)
            return;
        count *= 2;
        NSBXXTex* texture = objects_[part].pModel_->GetTEX0();
        if (texture == NULL)
            return;
        int position = 0x30;
        unsigned short size = ((unsigned short)(texture->block4NumEightBytes_ << 3) + 0x1f) & ~0x1f;
        int start = 0x20;
        if (part == 0)
            start = 0x200;
        position -= size - start;
        CharacterColors* colors = func_02099cac();
        const void* source = NULL;
        int length = count * 2;
        switch (count)
        {
        case 2:
            source = colors->colors2_[eyeColor_];
            break;
        case 4:
            source = colors->colors4_[eyeColor_];
            break;
        case 8:
            source = colors->colors8_[eyeColor_];
            break;
        }
        unsigned int offset = (state->unk_68 & 0xffff) << 3;
        if (offset != 0 && length != 0)
        {
            LockStagedTextureVRAMCopying();
            CleanInvalidateCacheRange(source, length);
            MemoryMapTexturePalette();
            LoadToTexturePalette(source, offset + position, length);
            MemoryUnmapTexturePalette();
            CleanCacheRange(source, length);
            UnlockStagedTextureVRAMCopying();
        }
        return;
    }
    int colors = func_020de2a4(entry, 1, female_);
    Model3D* model = objects_[part].pModel_;
    unsigned char color = eyeColor_;
    if (part == 4)
        func_02099d34(model, colors, color, 0x10);
    else
        func_02099d34(model, colors, color, 4);
}

// NONMATCHING: the C matches 98.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler copies the capacity to another register before storing it as an argument.
#ifdef NONMATCHING
void ViewObject::LoadPlayerAnimations(const char* event)
{
    char name[0x80];
    char path[0x80];
    GPCReadPair pair;
    unsigned int size;

    objects_[0].RemoveAllAnimationPackages();
    objects_[1].RemoveAllAnimationPackages();
    SafeAllocator allocator;
    allocator.CreateTypeA(buffer_, bufferSize_);
    allocator.Reset();
    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    __clear(name, sizeof(name));
    __clear(path, sizeof(path));
    size = 0;
    unsigned char* buffer = data_0211e33c;
    unsigned int capacity = 0x30000;
    func_02079a3c(&pair);
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine,
        STRING(0x58, "data/pack_lv5/chara_mp.gp2"), buffer, size, capacity, false, NULL))
    {
        buffer += size;
        capacity -= size;
        GetAnimationName(name, 0);
        sprintf(path, STRING(0x73, "%s.chr"), name);
        if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, path))
        {
            ObjectArchiveLoadInfo info;
            func_0203dafc(&info);
            info.allocator = &allocator;
            info.unk_8 = size;
            info.fileData = buffer;
            info.unk_10 = 1;
            objects_[0].LoadFromCCHROrCMOTArchive(&info, NULL);
            buffer += size;
            capacity -= size;
        }
        if (battle_ == 1)
        {
            sprintf(path, STRING(0x7a, "%se.chr"), name);
            if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, path))
            {
                ObjectArchiveLoadInfo info;
                func_0203dafc(&info);
                info.allocator = &allocator;
                info.unk_8 = size;
                info.fileData = buffer;
                info.unk_10 = 1;
                objects_[0].LoadFromCCHROrCMOTArchive(&info, NULL);
                buffer += size;
                capacity -= size;
            }
            sprintf(path, STRING(0x82, "%sm.chr"), name);
            if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, path))
            {
                ObjectArchiveLoadInfo info;
                func_0203dafc(&info);
                info.allocator = &allocator;
                info.unk_8 = size;
                info.fileData = buffer;
                info.unk_10 = 1;
                objects_[0].LoadFromCCHROrCMOTArchive(&info, NULL);
                buffer += size;
                capacity -= size;
            }
        }
        GetAnimationName(name, 1);
        if (battle_ == 0)
            sprintf(path, STRING(0x7a, "%se.chr"), name);
        else
            sprintf(path, STRING(0x73, "%s.chr"), name);
        if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, path))
        {
            ObjectArchiveLoadInfo info;
            func_0203dafc(&info);
            info.allocator = &allocator;
            info.unk_8 = size;
            info.fileData = buffer;
            info.unk_10 = 1;
            objects_[0].LoadFromCCHROrCMOTArchive(&info, NULL);
        }
        pair.Reset();
    }
    if (event != NULL)
    {
        int letter = 'w';
        if (female_ == 0)
            letter = 'm';
        int page = viewer_->page_;
        if (page == 0x1f)
            sprintf(path, STRING(0x8a, "data/chara/%s.chr"), event, letter);
        else if (page == 0x20)
            sprintf(path, STRING(0x9c, "data/chara/%s%c.chr"), event, letter);
        else
            sprintf(path, STRING(0xb0, "data/event_lv5/%s.chr"), event, letter);
        if (LoadFileIntoMemory(path, data_0211e33c, &size))
        {
            ObjectArchiveLoadInfo info;
            func_0203dafc(&info);
            info.allocator = &allocator;
            info.fileData = data_0211e33c;
            info.unk_8 = size;
            info.unk_10 = 1;
            info.packageID = 4;
            objects_[0].LoadFromCCHROrCMOTArchive(&info, NULL);
        }
    }
    allocator.Destroy();
    BackgroundLoader::RemoveLockGlobal();
    objects_[0].StopCurrentAnimation();
    objects_[0].MaybeSetRegularAnimation(STRING(0xc6, "stand"), 0);
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10ViewObject16GetAnimationNameEPci(); // ViewObject::GetAnimationName
    void _ZN11GPCReadPair5ResetEv(); // GPCReadPair::Reset
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator7DestroyEv(); // SafeAllocator::Destroy
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN8Object3D20StopCurrentAnimationEv(); // Object3D::StopCurrentAnimation
    void _ZN8Object3D24MaybeSetRegularAnimationEPKci(); // Object3D::MaybeSetRegularAnimation
    void _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE(); // Object3D::LoadFromCCHROrCMOTArchive
    void _ZN8Object3D26RemoveAllAnimationPackagesEv(); // Object3D::RemoveAllAnimationPackages
}

asm void ViewObject::LoadPlayerAnimations(const char* event)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x218
    mov r7, r0
    ldr r0, [r7, #0x24]
    mov r6, r1
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r7, #0x24]
    add r0, r0, #0xac
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    add r0, sp, #0xb4
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r1, [r7, #0x14]
    ldr r2, [r7, #0x18]
    add r0, sp, #0xb4
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, sp, #0xb4
    bl _ZN13SafeAllocator5ResetEv
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    add r0, sp, #0x198
    mov r1, #0x80
    bl __clear
    add r0, sp, #0x118
    mov r1, #0x80
    bl __clear
    mov r0, #0x0
    str r0, [sp, #0x10]
    add r0, sp, #0xc8
    ldr r4, =data_0211e33c
    mov r5, #0x30000
    bl func_02079a3c
    add r1, sp, #0x10
    stmia sp, {r1, r5}
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    ldr r2, =sStrings+0x58
    add r0, sp, #0xc8
    add r1, sp, #0xcc
    mov r3, r4
    bl LoadAndDecompressGPCHeaderAndInnerFileInfo
    cmp r0, #0x0
    beq @L0218c804
    ldr r3, [sp, #0x10]
    add r1, sp, #0x198
    mov r0, r7
    mov r2, #0x0
    add r4, r4, r3
    sub r5, r5, r3
    bl _ZN10ViewObject16GetAnimationNameEPci
    ldr r1, =sStrings+0x73
    add r0, sp, #0x118
    add r2, sp, #0x198
    bl sprintf
    str r5, [sp, #0x0]
    add r1, sp, #0x118
    str r1, [sp, #0x4]
    add r0, sp, #0xc8
    add r1, sp, #0xcc
    mov r2, r4
    add r3, sp, #0x10
    bl DecompressFileFromGPCByName
    cmp r0, #0x0
    beq @L0218c678
    add r0, sp, #0x94
    bl func_0203dafc
    ldr r1, [sp, #0x10]
    add r2, sp, #0xb4
    mov r0, #0x1
    str r2, [sp, #0xa0]
    str r1, [sp, #0x9c]
    str r4, [sp, #0x98]
    str r0, [sp, #0xa4]
    ldr r0, [r7, #0x24]
    add r1, sp, #0x94
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    ldr r0, [sp, #0x10]
    add r4, r4, r0
    sub r5, r5, r0
@L0218c678:
    ldr r0, [r7, #0x48]
    cmp r0, #0x1
    bne @L0218c76c
    ldr r1, =sStrings+0x7a
    add r0, sp, #0x118
    add r2, sp, #0x198
    bl sprintf
    add r12, sp, #0x118
    add r0, sp, #0xc8
    add r1, sp, #0xcc
    add r3, sp, #0x10
    mov r2, r4
    stmia sp, {r5, r12}
    bl DecompressFileFromGPCByName
    cmp r0, #0x0
    beq @L0218c6f8
    add r0, sp, #0x74
    bl func_0203dafc
    ldr r1, [sp, #0x10]
    add r2, sp, #0xb4
    mov r0, #0x1
    str r2, [sp, #0x80]
    str r1, [sp, #0x7c]
    str r4, [sp, #0x78]
    str r0, [sp, #0x84]
    ldr r0, [r7, #0x24]
    add r1, sp, #0x74
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    ldr r0, [sp, #0x10]
    add r4, r4, r0
    sub r5, r5, r0
@L0218c6f8:
    ldr r1, =sStrings+0x82
    add r0, sp, #0x118
    add r2, sp, #0x198
    bl sprintf
    add r12, sp, #0x118
    add r0, sp, #0xc8
    add r1, sp, #0xcc
    add r3, sp, #0x10
    mov r2, r4
    stmia sp, {r5, r12}
    bl DecompressFileFromGPCByName
    cmp r0, #0x0
    beq @L0218c76c
    add r0, sp, #0x54
    bl func_0203dafc
    ldr r1, [sp, #0x10]
    add r2, sp, #0xb4
    mov r0, #0x1
    str r2, [sp, #0x60]
    str r1, [sp, #0x5c]
    str r4, [sp, #0x58]
    str r0, [sp, #0x64]
    ldr r0, [r7, #0x24]
    add r1, sp, #0x54
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    ldr r0, [sp, #0x10]
    add r4, r4, r0
    sub r5, r5, r0
@L0218c76c:
    add r1, sp, #0x198
    mov r0, r7
    mov r2, #0x1
    bl _ZN10ViewObject16GetAnimationNameEPci
    ldr r0, [r7, #0x48]
    add r2, sp, #0x198
    cmp r0, #0x0
    add r0, sp, #0x118
    bne @L0218c79c
    ldr r1, =sStrings+0x7a
    bl sprintf
    b @L0218c7a4
@L0218c79c:
    ldr r1, =sStrings+0x73
    bl sprintf
@L0218c7a4:
    add r12, sp, #0x118
    add r0, sp, #0xc8
    add r1, sp, #0xcc
    add r3, sp, #0x10
    mov r2, r4
    stmia sp, {r5, r12}
    bl DecompressFileFromGPCByName
    cmp r0, #0x0
    beq @L0218c7fc
    add r0, sp, #0x34
    bl func_0203dafc
    ldr r1, [sp, #0x10]
    add r2, sp, #0xb4
    mov r0, #0x1
    str r2, [sp, #0x40]
    str r1, [sp, #0x3c]
    str r4, [sp, #0x38]
    str r0, [sp, #0x44]
    ldr r0, [r7, #0x24]
    add r1, sp, #0x34
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
@L0218c7fc:
    add r0, sp, #0xc8
    bl _ZN11GPCReadPair5ResetEv
@L0218c804:
    cmp r6, #0x0
    beq @L0218c8c0
    ldrb r0, [r7, #0x3b]
    mov r3, #0x77
    cmp r0, #0x0
    ldr r0, [r7, #0x0]
    moveq r3, #0x6d
    ldr r0, [r0, #0x1a4]
    cmp r0, #0x1f
    bne @L0218c840
    ldr r1, =sStrings+0x8a
    add r0, sp, #0x118
    mov r2, r6
    bl sprintf
    b @L0218c868
@L0218c840:
    cmp r0, #0x20
    add r0, sp, #0x118
    bne @L0218c85c
    ldr r1, =sStrings+0x9c
    mov r2, r6
    bl sprintf
    b @L0218c868
@L0218c85c:
    ldr r1, =sStrings+0xb0
    mov r2, r6
    bl sprintf
@L0218c868:
    ldr r1, =data_0211e33c
    add r0, sp, #0x118
    add r2, sp, #0x10
    bl LoadFileIntoMemory
    cmp r0, #0x0
    beq @L0218c8c0
    add r0, sp, #0x14
    bl func_0203dafc
    ldr r2, [sp, #0x10]
    ldr r3, =data_0211e33c
    add r4, sp, #0xb4
    mov r1, #0x1
    mov r0, #0x4
    str r2, [sp, #0x1c]
    str r1, [sp, #0x24]
    str r4, [sp, #0x20]
    str r3, [sp, #0x18]
    str r0, [sp, #0x30]
    ldr r0, [r7, #0x24]
    add r1, sp, #0x14
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
@L0218c8c0:
    add r0, sp, #0xb4
    bl _ZN13SafeAllocator7DestroyEv
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    ldr r0, [r7, #0x24]
    bl _ZN8Object3D20StopCurrentAnimationEv
    ldr r0, [r7, #0x24]
    ldr r1, =sStrings+0xc6
    mov r2, #0x0
    bl _ZN8Object3D24MaybeSetRegularAnimationEPKci
    add r0, sp, #0xc8
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0xc8
    bl ZeroDestroyGPCPointer
    add sp, sp, #0x218
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

// NONMATCHING: the C matches 98.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler copies the capacity to another register before storing it as an argument.
#ifdef NONMATCHING
void ViewObject::LoadDollAnimations(const char* event)
{
    GPCReadPair pair;

    SafeAllocator allocator;
    allocator.CreateTypeA(buffer_, bufferSize_);
    allocator.Reset();
    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    unsigned char* buffer = data_0211e33c;
    char name[0x80];
    char path[0x80];
    unsigned int size = 0;
    func_02079a3c(&pair);
    unsigned int capacity = 0x30000;
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine,
        STRING(0xcc, "data/pack_lv5/chara_pd.gp2"), buffer, size, capacity, false, NULL))
    {
        buffer += size;
        capacity -= size;
        objects_[0].RemoveAllAnimationPackages();
        objects_[2].RemoveAllAnimationPackages();
        objects_[3].RemoveAllAnimationPackages();
        objects_[7].RemoveAllAnimationPackages();
        objects_[8].RemoveAllAnimationPackages();
        objects_[9].RemoveAllAnimationPackages();
        objects_[6].RemoveAllAnimationPackages();
        objects_[5].RemoveAllAnimationPackages();
        objects_[1].RemoveAllAnimationPackages();
        __clear(name, sizeof(name));
        __clear(path, sizeof(path));
        GetAnimationName(name, 0);
        sprintf(path, STRING(0xe7, "%s.nsbca"), name);
        DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, path);
        objects_[0].LoadType0AnimationFromFileInMemory(0, &allocator, buffer, size);
        unsigned int offset = size;
        capacity -= offset;
        sprintf(path, STRING(0xf0, "%s.bcfg"), name);
        DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer + offset, size, capacity, path);
        objects_[0].LoadType0AnimationPackageFromBCFGScript(&allocator, buffer + offset, size);
        allocator.Destroy();
        objects_[0].StopCurrentAnimation();
        objects_[0].MaybeSetRegularAnimation(STRING(0xc6, "stand"), 0);
    }
    BackgroundLoader::RemoveLockGlobal();
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN8Object3D34LoadType0AnimationFromFileInMemoryEiP13SafeAllocatorPKvj(); // Object3D::LoadType0AnimationFromFileInMemory
    void _ZN8Object3D39LoadType0AnimationPackageFromBCFGScriptEP13SafeAllocatorPKvj(); // Object3D::LoadType0AnimationPackageFromBCFGScript
}

asm void ViewObject::LoadDollAnimations(const char* event)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x178
    mov r6, r0
    add r0, sp, #0x14
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r1, [r6, #0x14]
    ldr r2, [r6, #0x18]
    add r0, sp, #0x14
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, sp, #0x14
    bl _ZN13SafeAllocator5ResetEv
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x10]
    add r0, sp, #0x128
    ldr r4, =data_0211e33c
    mov r5, #0x30000
    bl func_02079a3c
    add r1, sp, #0x10
    stmia sp, {r1, r5}
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    ldr r2, =sStrings+0xcc
    add r0, sp, #0x128
    add r1, sp, #0x12c
    mov r3, r4
    bl LoadAndDecompressGPCHeaderAndInnerFileInfo
    cmp r0, #0x0
    beq @L0218cafc
    ldr r1, [sp, #0x10]
    ldr r0, [r6, #0x24]
    add r4, r4, r1
    sub r5, r5, r1
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0x158
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0x204
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0xb4
    add r0, r0, #0x400
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0x560
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0x20c
    add r0, r0, #0x400
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0x8
    add r0, r0, #0x400
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0x35c
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    ldr r0, [r6, #0x24]
    add r0, r0, #0xac
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    add r0, sp, #0xa8
    mov r1, #0x80
    bl __clear
    add r0, sp, #0x28
    mov r1, #0x80
    bl __clear
    mov r0, r6
    add r1, sp, #0xa8
    mov r2, #0x0
    bl _ZN10ViewObject16GetAnimationNameEPci
    ldr r1, =sStrings+0xe7
    add r0, sp, #0x28
    add r2, sp, #0xa8
    bl sprintf
    str r5, [sp, #0x0]
    add r1, sp, #0x28
    str r1, [sp, #0x4]
    add r0, sp, #0x128
    add r1, sp, #0x12c
    mov r2, r4
    add r3, sp, #0x10
    bl DecompressFileFromGPCByName
    ldr r0, [sp, #0x10]
    mov r1, #0x0
    str r0, [sp, #0x0]
    ldr r0, [r6, #0x24]
    add r2, sp, #0x14
    mov r3, r4
    bl _ZN8Object3D34LoadType0AnimationFromFileInMemoryEiP13SafeAllocatorPKvj
    ldr r7, [sp, #0x10]
    ldr r1, =sStrings+0xf0
    add r0, sp, #0x28
    add r2, sp, #0xa8
    sub r5, r5, r7
    bl sprintf
    add r2, sp, #0x28
    str r5, [sp, #0x0]
    str r2, [sp, #0x4]
    add r0, sp, #0x128
    add r1, sp, #0x12c
    add r3, sp, #0x10
    add r2, r4, r7
    bl DecompressFileFromGPCByName
    ldr r0, [r6, #0x24]
    ldr r3, [sp, #0x10]
    add r1, sp, #0x14
    add r2, r4, r7
    bl _ZN8Object3D39LoadType0AnimationPackageFromBCFGScriptEP13SafeAllocatorPKvj
    add r0, sp, #0x14
    bl _ZN13SafeAllocator7DestroyEv
    ldr r0, [r6, #0x24]
    bl _ZN8Object3D20StopCurrentAnimationEv
    ldr r0, [r6, #0x24]
    ldr r1, =sStrings+0xc6
    mov r2, #0x0
    bl _ZN8Object3D24MaybeSetRegularAnimationEPKci
@L0218cafc:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, sp, #0x128
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0x128
    bl ZeroDestroyGPCPointer
    add sp, sp, #0x178
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void ViewObject::LoadEventAnimation(const char* event)
{
    objects_->RemoveAnimationPackageByID(3);
    if (event != NULL)
    {
        char path[0x80];
        SafeAllocator allocator;
        allocator.CreateTypeA(buffer_, bufferSize_);
        allocator.Reset();
        __clear(path, sizeof(path));
        BackgroundLoader::AddLockGlobal();
        unsigned int size = 0;
        sprintf(path, STRING(0xb0, "data/event_lv5/%s.chr"), event);
        if (LoadFileIntoMemory(path, data_0211e33c, &size))
        {
            ObjectArchiveLoadInfo info;
            func_0203dafc(&info);
            info.allocator = &allocator;
            info.fileData = data_0211e33c;
            info.unk_8 = size;
            info.unk_10 = 1;
            info.packageID = 3;
            objects_->LoadFromCCHROrCMOTArchive(&info, NULL);
        }
        BackgroundLoader::RemoveLockGlobal();
        allocator.Destroy();
    }
    objects_->StopCurrentAnimation();
    objects_->MaybeSetBCFGAnimation(0, loop_);
}

// NONMATCHING: the C matches 32.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers differ throughout, and so does the order of the fixed-point products; the original also computes the
// addresses of objects_[3], [4], [6] and [7] before adding the offset of their field, which the compiler folds.
#ifdef NONMATCHING
int ViewObject::LoadPlayer()
{
    char name[0x80];
    GPCReadPair pair;
    unsigned int size;

    func_020c9820();
    if (parts_[7] != objects_[7].GetModelId())
    {
        objects_[3].SetModelId(-1);
        objects_[4].SetModelId(-1);
    }
    if (parts_[1] != objects_[1].GetModelId())
        objects_[0].SetModelId(-1);
    int reloadAnimations = 0;
    if (parts_[8] != objects_[8].GetModelId() || parts_[1] != objects_[1].GetModelId() ||
        parts_[6] != objects_[6].GetModelId())
        reloadAnimations = 1;
    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    size = 0;
    unsigned char* buffer = data_0211e33c;
    unsigned int capacity = 0x30000;
    func_02079a3c(&pair);
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine,
        STRING(0xf8, "data/pack_lv5/chara_pc.gp2"), buffer, size, capacity, false, NULL))
    {
        buffer += size;
        capacity -= size;
        for (int i = 0; i < 10; i++)
        {
            if (reload_ != 2 && parts_[i] == objects_[i].unknown_2_)
                continue;
            VRAMManagerState* state = &slot_->states_[i];
            Vector3fix position = objects_[i].position_;
            SafeAllocator* allocator = &allocators_[i];
            allocator->Reset();
            func_0207df50(state);
            objects_[i].Initialize();
            objects_[i].position_ = position;
            objects_[i].unknown_2_ = parts_[i];
            if (parts_[i] < 0)
                continue;
            PartEntry* entry = func_020dedd0(&viewer_->parts_, parts_[i]);
            if (entry == NULL || !GetModelName(name, i, 1))
                continue;
            objects_[i].Destroy();
            switch (i)
            {
            case 0:
            case 1:
            {
                short scale = 0.065f * FX_Mul(height_, width_);
                objects_[i].SetScale(scale, (short)(0.065f * height_), scale);
                reloadAnimations = 1;
                break;
            }
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            {
                int x = fix32_Divide(0x1000, FX_Mul(height_, width_));
                int y = fix32_Divide(0x1000, height_);
                int z = x;
                if (i == 2 || i == 3 || i == 7)
                {
                    x = FX_Mul(x, height_ - 0.5f * (height_ - 0x1000));
                    y = FX_Mul(y, height_ - 0.5f * (height_ - 0x1000));
                    z = FX_Mul(z, height_ - 0.5f * (height_ - 0x1000));
                }
                objects_[i].SetScale((short)x, y, (short)z);
                if (i == 8)
                {
                    Model3D* body = objects_[0].pModel_;
                    unk_54 = 0;
                    unsigned int type = entry->type_;
                    if (type == 4)
                    {
                        func_020407b4(&objects_[i], 0, 0, 0);
                        if (body != NULL)
                            weaponBone_ = body->GetBoneIndex(STRING(0x113, "waist"));
                    }
                    else if (type == 6)
                    {
                        func_020407b4(&objects_[i], 0, 0, 0);
                        if (body != NULL)
                            weaponBone_ = body->GetBoneIndex(STRING(0x119, "arm1R"));
                        unk_54 = 1;
                    }
                    else if (type == 0xb)
                    {
                        func_020407b4(&objects_[i], FX_Mul(height_, 0x2666), FX_Mul(height_, -0x666), 0);
                        if (body != NULL)
                            weaponBone_ = body->GetBoneIndex(STRING(0x11f, "arm1L"));
                    }
                    else
                    {
                        func_020407b4(&objects_[i], FX_Mul(height_, -0x2666), FX_Mul(height_, -0x666), 0);
                        if (body != NULL)
                            weaponBone_ = body->GetBoneIndex(STRING(0x119, "arm1R"));
                    }
                }
                if (i == 9)
                    func_020407b4(&objects_[i], FX_Mul(height_, 0x2000), 0, 0);
                break;
            }
            }
            func_0207df90(state);
            DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, name);
            objects_[i].SetModelFromFileCopy(allocator, buffer, size, (Model3D::TextureStagingMode)0);
            buffer += size;
            capacity -= size;
            func_0207dfac(state);
            if (i == 4 && objects_[3].pModel_ != NULL)
                objects_[3].pModel_->ApplyTexturesFromModel(objects_[i].pModel_);
            Model3D* model = objects_[i].pModel_;
            if (model != NULL)
            {
                switch (i)
                {
                case 0:
                    model->CreateBoneMatrixAndMaterialArrays(allocator, 7);
                    model->StoreBoneMatrixAndMaterialArrayPointers();
                    break;
                case 1:
                case 6:
                case 5:
                case 4:
                    break;
                default:
                    model->CreateBoneMatrixAndMaterialArrays(allocator, 5);
                    model->StoreBoneMatrixAndMaterialArrayPointers();
                    break;
                }
            }
        }
        pair.Reset();
    }
    if (reloadAnimations)
        LoadPlayerAnimations(NULL);
    Model3D* body = objects_[0].pModel_;
    if (body != NULL)
    {
        body->RemoveTextures();
        Object3D* skin = &objects_[5];
        if (skin->unknown_2_ >= 0 && skin->pModel_ != NULL)
            body->ApplyTexturesFromModel(skin->pModel_);
        body->ApplyTexturesFromModel(body);
    }
    Model3D* head = objects_[1].pModel_;
    if (head != NULL)
    {
        head->RemoveTextures();
        Object3D* face = &objects_[6];
        if (face->unknown_2_ >= 0 && face->pModel_ != NULL)
            head->ApplyTexturesFromModel(face->pModel_);
        head->ApplyTexturesFromModel(head);
    }
    func_02099e18(objects_[2].pModel_, eyeColor_, hairColor_, skinColor_);
    for (int i = 0; sPlayerPalettes[i] >= 0; i++)
        LoadPalette(sPlayerPalettes[i]);
    BackgroundLoader::RemoveLockGlobal();
    reload_ = 0;
    name_ = STRING(0x125, "PC");
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10ViewObject11LoadPaletteEi(); // ViewObject::LoadPalette
    void _ZN10ViewObject12GetModelNameEPcji(); // ViewObject::GetModelName
    void _ZN10ViewObject20LoadPlayerAnimationsEPKc(); // ViewObject::LoadPlayerAnimations
    void _ZN7Model3D12GetBoneIndexEPKc(); // Model3D::GetBoneIndex
    void _ZN7Model3D14RemoveTexturesEv(); // Model3D::RemoveTextures
    void _ZN7Model3D22ApplyTexturesFromModelEPS_(); // Model3D::ApplyTexturesFromModel
    void _ZN7Model3D33CreateBoneMatrixAndMaterialArraysEP13SafeAllocatori(); // Model3D::CreateBoneMatrixAndMaterialArrays
    void _ZN7Model3D39StoreBoneMatrixAndMaterialArrayPointersEv(); // Model3D::StoreBoneMatrixAndMaterialArrayPointers
    void _ZN8Object3D10InitializeEv(); // Object3D::Initialize
    void _ZN8Object3D20SetModelFromFileCopyEP13SafeAllocatorPKvjN7Model3D18TextureStagingModeE(); // Object3D::SetModelFromFileCopy
    void _ZN8Object3D7DestroyEv(); // Object3D::Destroy
    void _ZN8Object3D8SetScaleEiii(); // Object3D::SetScale
    void _ZN8Vector3iaSERKS_(); // Vector3i::operator=
}

asm int ViewObject::LoadPlayer()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x128
    mov r10, r0
    bl func_020c9820
    ldr r3, [r10, #0x24]
    ldr r1, [r10, #0x20]
    add r0, r3, #0xb4
    add r0, r0, #0x400
    ldrsh r2, [r0, #0x2]
    ldr r0, [r1, #0x1c]
    cmp r0, r2
    beq @L0218cc6c
    add r0, r3, #0x204
    mvn r1, #0x0
    strh r1, [r0, #0x2]
    ldr r0, [r10, #0x24]
    add r0, r0, #0x2b0
    strh r1, [r0, #0x2]
@L0218cc6c:
    ldr r2, [r10, #0x24]
    ldr r0, [r10, #0x20]
    ldrsh r1, [r2, #0xae]
    ldr r0, [r0, #0x4]
    cmp r0, r1
    mvnne r0, #0x0
    strneh r0, [r2, #0x2]
    ldr r4, [r10, #0x24]
    ldr r2, [r10, #0x20]
    add r0, r4, #0x560
    ldrsh r3, [r0, #0x2]
    ldr r1, [r2, #0x20]
    mov r0, #0x0
    str r0, [sp, #0x18]
    cmp r1, r3
    ldreqsh r1, [r4, #0xae]
    ldreq r0, [r2, #0x4]
    cmpeq r0, r1
    addeq r0, r4, #0x8
    addeq r0, r0, #0x400
    ldreqsh r1, [r0, #0x2]
    ldreq r0, [r2, #0x18]
    cmpeq r0, r1
    movne r0, #0x1
    strne r0, [sp, #0x18]
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    mov r1, #0x0
    add r0, sp, #0xd8
    str r1, [sp, #0x48]
    ldr r6, =data_0211e33c
    mov r7, #0x30000
    bl func_02079a3c
    add r1, sp, #0x48
    stmia sp, {r1, r7}
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    ldr r2, =sStrings+0xf8
    add r0, sp, #0xd8
    add r1, sp, #0xdc
    mov r3, r6
    bl LoadAndDecompressGPCHeaderAndInnerFileInfo
    cmp r0, #0x0
    beq @L0218d3c0
    ldr r0, [sp, #0x48]
    mov r8, #0x0
    add r6, r6, r0
    sub r7, r7, r0
    ldr r0, =0xffffd99a
    add r0, r0, #0x2000
    str r0, [sp, #0x3c]
    ldr r0, =0xffffd99a
    rsb r0, r0, #0x0
    str r0, [sp, #0x38]
    ldr r0, =0xffffd99a
    add r0, r0, #0x2000
    str r0, [sp, #0x34]
    mvn r0, #0x0
    str r0, [sp, #0x30]
    b @L0218d3b0
@L0218cd60:
    ldrb r0, [r10, #0x2c]
    cmp r0, #0x2
    beq @L0218cd8c
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    ldr r1, [r10, #0x20]
    ldrsh r2, [r0, #0x2]
    ldr r0, [r1, r8, lsl #0x2]
    cmp r0, r2
    beq @L0218d3ac
@L0218cd8c:
    mov r0, #0x70
    mul r0, r8, r0
    str r0, [sp, #0x20]
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r1
    add r1, r0, #0x44
    mov r0, #0x14
    mul r4, r8, r0
    add r3, sp, #0x4c
    ldmia r1, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldmib r10, {r0, r5}
    ldr r0, [r0, #0x0]
    str r0, [sp, #0x1c]
    add r0, r5, r4
    bl _ZN13SafeAllocator5ResetEv
    ldr r1, [sp, #0x1c]
    ldr r0, [sp, #0x20]
    add r0, r1, r0
    bl func_0207df50
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r1
    bl _ZN8Object3D10InitializeEv
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    add r1, sp, #0x4c
    add r0, r0, #0x44
    bl _ZN8Vector3iaSERKS_
    ldr r0, [r10, #0x20]
    ldr r1, [r10, #0x24]
    ldr r2, [r0, r8, lsl #0x2]
    mov r0, #0xac
    mla r0, r8, r0, r1
    strh r2, [r0, #0x2]
    ldr r0, [r10, #0x20]
    ldr r0, [r0, r8, lsl #0x2]
    cmp r0, #0x0
    blt @L0218d3ac
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    ldr r0, [r10, #0x0]
    add r0, r0, #0x4c
    bl func_020dedd0
    str r0, [sp, #0x14]
    cmp r0, #0x0
    beq @L0218d3ac
    mov r0, r10
    add r1, sp, #0x58
    mov r2, r8
    mov r3, #0x1
    bl _ZN10ViewObject12GetModelNameEPcji
    cmp r0, #0x0
    beq @L0218d3ac
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r1
    bl _ZN8Object3D7DestroyEv
    cmp r8, #0x0
    cmpne r8, #0x1
    bne @L0218cf0c
    ldrsh r1, [r10, #0x42]
    ldrsh r0, [r10, #0x40]
    smull r2, r1, r0, r1
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r1, r1, r0
    mov r0, r2, lsr #0xc
    orr r0, r0, r1, lsl #0x14
    bl _fflt
    mov r1, r0
    ldr r0, =0x3d851eb8
    bl _fmul
    bl _ffix
    mov r0, r0, lsl #0x10
    mov r9, r0, asr #0x10
    ldrsh r0, [r10, #0x40]
    bl _fflt
    mov r1, r0
    ldr r0, =0x3d851eb8
    bl _fmul
    bl _ffix
    mov r0, r0, lsl #0x10
    mov r2, r0, asr #0x10
    ldr r3, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r3
    mov r1, r9
    mov r3, r9
    bl _ZN8Object3D8SetScaleEiii
    mov r0, #0x1
    str r0, [sp, #0x18]
    b @L0218d2ac
@L0218cf0c:
    cmp r8, #0x2
    cmpne r8, #0x3
    cmpne r8, #0x7
    cmpne r8, #0x8
    cmpne r8, #0x9
    bne @L0218d2ac
    ldrsh r2, [r10, #0x42]
    ldrsh r1, [r10, #0x40]
    mov r0, #0x1000
    smull r3, r2, r1, r2
    adds r3, r3, #0x800
    adc r2, r2, #0x0
    mov r1, r3, lsr #0xc
    orr r1, r1, r2, lsl #0x14
    bl fix32_Divide
    mov r9, r0
    ldrsh r1, [r10, #0x40]
    mov r0, #0x1000
    bl fix32_Divide
    cmp r8, #0x2
    cmpne r8, #0x3
    str r0, [sp, #0x10]
    mov r11, r9
    cmpne r8, #0x7
    bne @L0218d068
    ldrsh r0, [r10, #0x40]
    bl _fflt
    str r0, [sp, #0x24]
    ldrsh r0, [r10, #0x40]
    sub r0, r0, #0x1000
    bl _fflt
    mov r1, r0
    mov r0, #0x3f000000
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x24]
    bl _fsub
    bl _ffix
    smull r2, r1, r9, r0
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r0, r1, r0
    mov r9, r2, lsr #0xc
    orr r9, r9, r0, lsl #0x14
    ldrsh r0, [r10, #0x40]
    bl _fflt
    str r0, [sp, #0x28]
    ldrsh r0, [r10, #0x40]
    sub r0, r0, #0x1000
    bl _fflt
    mov r1, r0
    mov r0, #0x3f000000
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x28]
    bl _fsub
    bl _ffix
    ldr r1, [sp, #0x10]
    smull r3, r2, r1, r0
    mov r0, #0x800
    adds r3, r3, r0
    mov r0, #0x0
    adc r1, r2, r0
    mov r0, r3, lsr #0xc
    orr r0, r0, r1, lsl #0x14
    str r0, [sp, #0x10]
    ldrsh r0, [r10, #0x40]
    bl _fflt
    str r0, [sp, #0x2c]
    ldrsh r0, [r10, #0x40]
    sub r0, r0, #0x1000
    bl _fflt
    mov r1, r0
    mov r0, #0x3f000000
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x2c]
    bl _fsub
    bl _ffix
    smull r2, r1, r11, r0
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r0, r1, r0
    mov r11, r2, lsr #0xc
    orr r11, r11, r0, lsl #0x14
@L0218d068:
    mov r1, r9
    ldr r9, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r9
    ldr r2, [sp, #0x10]
    mov r3, r11
    bl _ZN8Object3D8SetScaleEiii
    cmp r8, #0x8
    bne @L0218d258
    ldr r0, [r10, #0x24]
    ldr r9, [r0, #0x8]
    mov r0, #0x0
    str r0, [r10, #0x54]
    ldr r0, [sp, #0x14]
    ldr r0, [r0, #0x8]
    mov r0, r0, lsl #0x17
    mov r0, r0, lsr #0x1b
    cmp r0, #0x4
    bne @L0218d0ec
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    mov r1, #0x0
    mov r2, r1
    mov r3, r1
    bl func_020407b4
    cmp r9, #0x0
    beq @L0218d258
    ldr r1, =sStrings+0x113
    mov r0, r9
    bl _ZN7Model3D12GetBoneIndexEPKc
    strb r0, [r10, #0x50]
    b @L0218d258
@L0218d0ec:
    cmp r0, #0x6
    bne @L0218d134
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    mov r1, #0x0
    mov r2, r1
    mov r3, r1
    bl func_020407b4
    cmp r9, #0x0
    beq @L0218d128
    ldr r1, =sStrings+0x119
    mov r0, r9
    bl _ZN7Model3D12GetBoneIndexEPKc
    strb r0, [r10, #0x50]
@L0218d128:
    mov r0, #0x1
    str r0, [r10, #0x54]
    b @L0218d258
@L0218d134:
    cmp r0, #0xb
    ldrsh r11, [r10, #0x40]
    mov r3, #0x0
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    bne @L0218d1d4
    mla r0, r8, r0, r1
    ldr r1, [sp, #0x38]
    mov lr, r11, asr #0x1f
    umull r12, r2, r11, r1
    adds r1, r12, #0x800
    mov r12, r3
    mla r2, r11, r12, r2
    ldr r12, [sp, #0x38]
    mov r1, r1, lsr #0xc
    mla r2, lr, r12, r2
    mov r12, r3
    adc r2, r2, r12
    orr r1, r1, r2, lsl #0x14
    ldr r2, [sp, #0x34]
    umull r12, r2, r11, r2
    str r12, [sp, #0x40]
    ldr r12, [sp, #0x30]
    mla r2, r11, r12, r2
    ldr r11, [sp, #0x34]
    mov r12, r3
    mla r2, lr, r11, r2
    ldr r11, [sp, #0x40]
    adds r11, r11, #0x800
    adc r12, r2, r12
    mov r2, r11, lsr #0xc
    orr r2, r2, r12, lsl #0x14
    bl func_020407b4
    cmp r9, #0x0
    beq @L0218d258
    ldr r1, =sStrings+0x11f
    mov r0, r9
    bl _ZN7Model3D12GetBoneIndexEPKc
    strb r0, [r10, #0x50]
    b @L0218d258
@L0218d1d4:
    mla r0, r8, r0, r1
    ldr r1, =0xffffd99a
    mov lr, r11, asr #0x1f
    umull r12, r2, r11, r1
    adds r1, r12, #0x800
    ldr r12, [sp, #0x30]
    mov r1, r1, lsr #0xc
    mla r2, r11, r12, r2
    ldr r12, =0xffffd99a
    mla r2, lr, r12, r2
    mov r12, r3
    adc r2, r2, r12
    orr r1, r1, r2, lsl #0x14
    ldr r2, [sp, #0x3c]
    umull r12, r2, r11, r2
    str r12, [sp, #0x44]
    ldr r12, [sp, #0x30]
    mla r2, r11, r12, r2
    ldr r11, [sp, #0x3c]
    mov r12, r3
    mla r2, lr, r11, r2
    ldr r11, [sp, #0x44]
    adds r11, r11, #0x800
    adc r12, r2, r12
    mov r2, r11, lsr #0xc
    orr r2, r2, r12, lsl #0x14
    bl func_020407b4
    cmp r9, #0x0
    beq @L0218d258
    ldr r1, =sStrings+0x119
    mov r0, r9
    bl _ZN7Model3D12GetBoneIndexEPKc
    strb r0, [r10, #0x50]
@L0218d258:
    cmp r8, #0x9
    bne @L0218d2ac
    ldrsh r12, [r10, #0x40]
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mov r2, #0x0
    mla r0, r8, r0, r1
    mov r1, #0x2000
    umull r11, r9, r12, r1
    mov r1, r2
    mla r9, r12, r1, r9
    mov lr, r12, asr #0x1f
    mov r1, #0x2000
    mla r9, lr, r1, r9
    adds r11, r11, #0x800
    mov r1, r2
    adc r9, r9, r1
    mov r1, r11, lsr #0xc
    mov r3, r2
    orr r1, r1, r9, lsl #0x14
    bl func_020407b4
@L0218d2ac:
    ldr r1, [sp, #0x1c]
    ldr r0, [sp, #0x20]
    add r0, r1, r0
    bl func_0207df90
    str r7, [sp, #0x0]
    add r0, sp, #0x58
    str r0, [sp, #0x4]
    add r0, sp, #0xd8
    add r1, sp, #0xdc
    mov r2, r6
    add r3, sp, #0x48
    bl DecompressFileFromGPCByName
    mov r0, #0x0
    str r0, [sp, #0x0]
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    ldr r3, [sp, #0x48]
    add r1, r5, r4
    mov r2, r6
    bl _ZN8Object3D20SetModelFromFileCopyEP13SafeAllocatorPKvjN7Model3D18TextureStagingModeE
    ldr r1, [sp, #0x1c]
    ldr r0, [sp, #0x20]
    add r0, r1, r0
    ldr r1, [sp, #0x48]
    add r6, r6, r1
    sub r7, r7, r1
    bl func_0207dfac
    cmp r8, #0x4
    bne @L0218d344
    ldr r2, [r10, #0x24]
    ldr r0, [r2, #0x20c]
    cmp r0, #0x0
    beq @L0218d344
    mov r1, #0xac
    mla r1, r8, r1, r2
    ldr r1, [r1, #0x8]
    bl _ZN7Model3D22ApplyTexturesFromModelEPS_
@L0218d344:
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r1
    ldr r9, [r0, #0x8]
    cmp r9, #0x0
    beq @L0218d3ac
    cmp r8, #0x0
    bne @L0218d380
    add r1, r5, r4
    mov r0, r9
    mov r2, #0x7
    bl _ZN7Model3D33CreateBoneMatrixAndMaterialArraysEP13SafeAllocatori
    mov r0, r9
    bl _ZN7Model3D39StoreBoneMatrixAndMaterialArrayPointersEv
    b @L0218d3ac
@L0218d380:
    cmp r8, #0x1
    cmpne r8, #0x6
    cmpne r8, #0x5
    cmpne r8, #0x4
    beq @L0218d3ac
    add r1, r5, r4
    mov r0, r9
    mov r2, #0x5
    bl _ZN7Model3D33CreateBoneMatrixAndMaterialArraysEP13SafeAllocatori
    mov r0, r9
    bl _ZN7Model3D39StoreBoneMatrixAndMaterialArrayPointersEv
@L0218d3ac:
    add r8, r8, #0x1
@L0218d3b0:
    cmp r8, #0xa
    blt @L0218cd60
    add r0, sp, #0xd8
    bl _ZN11GPCReadPair5ResetEv
@L0218d3c0:
    ldr r0, [sp, #0x18]
    cmp r0, #0x0
    beq @L0218d3d8
    mov r0, r10
    mov r1, #0x0
    bl _ZN10ViewObject20LoadPlayerAnimationsEPKc
@L0218d3d8:
    ldr r0, [r10, #0x24]
    ldr r4, [r0, #0x8]
    cmp r4, #0x0
    beq @L0218d424
    mov r0, r4
    bl _ZN7Model3D14RemoveTexturesEv
    ldr r0, [r10, #0x24]
    add r1, r0, #0x35c
    ldrsh r0, [r1, #0x2]
    cmp r0, #0x0
    blt @L0218d418
    ldr r1, [r1, #0x8]
    cmp r1, #0x0
    beq @L0218d418
    mov r0, r4
    bl _ZN7Model3D22ApplyTexturesFromModelEPS_
@L0218d418:
    mov r0, r4
    mov r1, r4
    bl _ZN7Model3D22ApplyTexturesFromModelEPS_
@L0218d424:
    ldr r0, [r10, #0x24]
    ldr r4, [r0, #0xb4]
    cmp r4, #0x0
    beq @L0218d474
    mov r0, r4
    bl _ZN7Model3D14RemoveTexturesEv
    ldr r0, [r10, #0x24]
    add r0, r0, #0x8
    add r1, r0, #0x400
    ldrsh r0, [r1, #0x2]
    cmp r0, #0x0
    blt @L0218d468
    ldr r1, [r1, #0x8]
    cmp r1, #0x0
    beq @L0218d468
    mov r0, r4
    bl _ZN7Model3D22ApplyTexturesFromModelEPS_
@L0218d468:
    mov r0, r4
    mov r1, r4
    bl _ZN7Model3D22ApplyTexturesFromModelEPS_
@L0218d474:
    ldr r0, [r10, #0x24]
    ldrb r1, [r10, #0x3e]
    ldrb r2, [r10, #0x3c]
    ldrb r3, [r10, #0x3d]
    ldr r0, [r0, #0x160]
    bl func_02099e18
    mov r5, #0x0
    ldr r4, =sPlayerPalettes
    b @L0218d4a8
@L0218d498:
    ldr r1, [r4, r5, lsl #0x2]
    mov r0, r10
    bl _ZN10ViewObject11LoadPaletteEi
    add r5, r5, #0x1
@L0218d4a8:
    ldr r0, [r4, r5, lsl #0x2]
    cmp r0, #0x0
    bge @L0218d498
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    mov r0, #0x0
    strb r0, [r10, #0x2c]
    ldr r1, =sStrings+0x125
    add r0, sp, #0xd8
    str r1, [r10, #0xc]
    mov r4, #0x1
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0xd8
    bl ZeroDestroyGPCPointer
    mov r0, r4
    add sp, sp, #0x128
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 37.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers differ throughout, and so does the order of the fixed-point products; the original also computes the
// addresses of objects_[3], [4], [6] and [7] before adding the offset of their field, which the compiler folds.
#ifdef NONMATCHING
int ViewObject::LoadDoll()
{
    char name[0x80];
    GPCReadPair pair;
    unsigned int size;

    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    func_020c9820();
    if (parts_[7] != objects_[7].GetModelId())
    {
        objects_[3].SetModelId(-1);
        objects_[4].SetModelId(-1);
    }
    if (parts_[1] != objects_[1].GetModelId())
        objects_[0].SetModelId(-1);
    int reloadAnimations = 0;
    if (parts_[8] != objects_[8].GetModelId() || parts_[1] != objects_[1].GetModelId())
        reloadAnimations = 1;
    size = 0;
    unsigned char* buffer = data_0211e33c;
    unsigned int capacity = 0x30000;
    func_02079a3c(&pair);
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine,
        STRING(0xcc, "data/pack_lv5/chara_pd.gp2"), buffer, size, capacity, false, NULL))
    {
        buffer += size;
        capacity -= size;
        for (int i = 0; i < 10; i++)
        {
            if (reload_ != 2 && parts_[i] == objects_[i].unknown_2_)
                continue;
            SafeAllocator* allocator = &allocators_[i];
            VRAMManagerState* state = &slot_->states_[i];
            allocator->Reset();
            func_0207df50(state);
            Vector3fix position = objects_[i].position_;
            objects_[i].Initialize();
            objects_[i].position_ = position;
            objects_[i].unknown_2_ = parts_[i];
            if (parts_[i] < 0)
                continue;
            PartEntry* entry = func_020dedd0(&viewer_->parts_, parts_[i]);
            if (entry == NULL)
                continue;
            if (!GetModelName(name, i, 0))
            {
                objects_[i].Initialize();
                objects_[i].unknown_2_ = -1;
                continue;
            }
            objects_[i].Destroy();
            switch (i)
            {
            case 0:
            {
                short scale = 0.065f * FX_Mul(height_, width_);
                objects_[i].SetScale(scale, (short)(0.065f * height_), scale);
                reloadAnimations = 1;
                break;
            }
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            {
                int x = fix32_Divide(0x1000, FX_Mul(height_, width_));
                int y = fix32_Divide(0x1000, height_);
                int z = x;
                if (i == 2 || i == 3 || i == 7)
                {
                    x = FX_Mul(x, height_ - 0.5f * (height_ - 0x1000));
                    y = FX_Mul(y, height_ - 0.5f * (height_ - 0x1000));
                    z = FX_Mul(z, height_ - 0.5f * (height_ - 0x1000));
                }
                objects_[i].SetScale((short)x, y, (short)z);
                break;
            }
            case 6:
            case 5:
            case 1:
            {
                short scale = 0.065f * FX_Mul(height_, width_);
                objects_[i].SetScale(scale, (short)(0.065f * height_), scale);
                break;
            }
            }
            if (i == 8 || i == 1)
            {
                reloadAnimations = 1;
                if (entry->type_ == 6)
                    unk_58 = 1;
                else
                    unk_58 = 0;
            }
            func_0207df90(state);
            DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer, size, capacity, name);
            objects_[i].SetModelFromFileCopy(allocator, buffer, size, (Model3D::TextureStagingMode)0);
            buffer += size;
            capacity -= size;
            func_0207dfac(state);
            if (i == 4 && objects_[3].pModel_ != NULL)
                objects_[3].pModel_->ApplyTexturesFromModel(objects_[i].pModel_);
        }
        pair.Reset();
    }
    CharacterColors* colors = func_02099cac();
    unsigned int offset = (slot_->states_[2].unk_68 & 0xffff) << 3;
    if (offset != 0)
    {
        CleanInvalidateCacheRange(colors->hair_[hairColor_], 4);
        CleanInvalidateCacheRange(colors->skin_[skinColor_], 4);
        CleanInvalidateCacheRange(colors->colors8_[eyeColor_], 0x10);
        func_020c9820();
        LockStagedTextureVRAMCopying();
        MemoryMapTexturePalette();
        LoadToTexturePalette(colors->hair_[hairColor_], offset + 0x24, 4);
        LoadToTexturePalette(colors->skin_[skinColor_], offset + 0x28, 4);
        LoadToTexturePalette(colors->colors8_[eyeColor_], offset + 0x30, 0x10);
        MemoryUnmapTexturePalette();
        UnlockStagedTextureVRAMCopying();
    }
    for (int i = 0; sDollPalettes[i] >= 0; i++)
        LoadPalette(sDollPalettes[i]);
    if (reloadAnimations)
        LoadDollAnimations(NULL);
    reload_ = 0;
    name_ = STRING(0x128, "DOLL");
    BackgroundLoader::RemoveLockGlobal();
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10ViewObject18LoadDollAnimationsEPKc(); // ViewObject::LoadDollAnimations
}

asm int ViewObject::LoadDoll()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x114
    mov r10, r0
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    bl func_020c9820
    ldr r3, [r10, #0x24]
    ldr r1, [r10, #0x20]
    add r0, r3, #0xb4
    add r0, r0, #0x400
    ldrsh r2, [r0, #0x2]
    ldr r0, [r1, #0x1c]
    cmp r0, r2
    beq @L0218d55c
    add r0, r3, #0x204
    mvn r1, #0x0
    strh r1, [r0, #0x2]
    ldr r0, [r10, #0x24]
    add r0, r0, #0x2b0
    strh r1, [r0, #0x2]
@L0218d55c:
    ldr r2, [r10, #0x24]
    ldr r0, [r10, #0x20]
    ldrsh r1, [r2, #0xae]
    ldr r0, [r0, #0x4]
    ldr r6, =data_0211e33c
    cmp r0, r1
    mvnne r0, #0x0
    strneh r0, [r2, #0x2]
    ldr r4, [r10, #0x24]
    ldr r2, [r10, #0x20]
    add r0, r4, #0x560
    ldrsh r3, [r0, #0x2]
    ldr r1, [r2, #0x20]
    mov r0, #0x0
    str r0, [sp, #0x18]
    cmp r1, r3
    ldreqsh r1, [r4, #0xae]
    ldreq r0, [r2, #0x4]
    mov r7, #0x30000
    cmpeq r0, r1
    movne r0, #0x1
    strne r0, [sp, #0x18]
    mov r1, #0x0
    add r0, sp, #0xc4
    str r1, [sp, #0x34]
    bl func_02079a3c
    add r0, sp, #0x34
    stmia sp, {r0, r7}
    mov r4, #0x0
    str r4, [sp, #0x8]
    ldr r2, =sStrings+0xcc
    add r0, sp, #0xc4
    add r1, sp, #0xc8
    mov r3, r6
    str r4, [sp, #0xc]
    bl LoadAndDecompressGPCHeaderAndInnerFileInfo
    cmp r0, #0x0
    beq @L0218dab4
    ldr r0, [sp, #0x34]
    mov r8, r4
    add r6, r6, r0
    sub r7, r7, r0
    mvn r0, #0x0
    str r0, [sp, #0x24]
    b @L0218daa4
@L0218d610:
    ldrb r0, [r10, #0x2c]
    cmp r0, #0x2
    beq @L0218d63c
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    ldr r1, [r10, #0x20]
    ldrsh r2, [r0, #0x2]
    ldr r0, [r1, r8, lsl #0x2]
    cmp r0, r2
    beq @L0218daa0
@L0218d63c:
    mov r0, #0x70
    mul r4, r8, r0
    ldr r0, [r10, #0x8]
    ldr r1, [r10, #0x4]
    str r0, [sp, #0x1c]
    mov r0, #0x14
    mul r0, r8, r0
    ldr r5, [r1, #0x0]
    ldr r1, [sp, #0x1c]
    str r0, [sp, #0x20]
    add r0, r1, r0
    bl _ZN13SafeAllocator5ResetEv
    add r0, r5, r4
    bl func_0207df50
    mov r0, #0xac
    mul r9, r8, r0
    ldr r1, [r10, #0x24]
    add r3, sp, #0x38
    add r0, r1, r9
    add r0, r0, #0x44
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r0, [r10, #0x24]
    add r0, r0, r9
    bl _ZN8Object3D10InitializeEv
    ldr r2, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r2
    add r1, sp, #0x38
    add r0, r0, #0x44
    bl _ZN8Vector3iaSERKS_
    ldr r0, [r10, #0x20]
    ldr r1, [r10, #0x24]
    ldr r2, [r0, r8, lsl #0x2]
    mov r0, #0xac
    mla r0, r8, r0, r1
    strh r2, [r0, #0x2]
    ldr r0, [r10, #0x20]
    ldr r0, [r0, r8, lsl #0x2]
    cmp r0, #0x0
    blt @L0218daa0
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    ldr r0, [r10, #0x0]
    add r0, r0, #0x4c
    bl func_020dedd0
    str r0, [sp, #0x14]
    cmp r0, #0x0
    beq @L0218daa0
    mov r0, r10
    add r1, sp, #0x44
    mov r2, r8
    mov r3, #0x0
    bl _ZN10ViewObject12GetModelNameEPcji
    cmp r0, #0x0
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r1
    bne @L0218d744
    bl _ZN8Object3D10InitializeEv
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r1, r8, r0, r1
    ldr r0, [sp, #0x24]
    strh r0, [r1, #0x2]
    b @L0218daa0
@L0218d744:
    bl _ZN8Object3D7DestroyEv
    cmp r8, #0x0
    bne @L0218d7d4
    ldrsh r1, [r10, #0x42]
    ldrsh r0, [r10, #0x40]
    smull r2, r1, r0, r1
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r1, r1, r0
    mov r0, r2, lsr #0xc
    orr r0, r0, r1, lsl #0x14
    bl _fflt
    mov r1, r0
    ldr r0, =0x3d851eb8
    bl _fmul
    bl _ffix
    mov r0, r0, lsl #0x10
    mov r9, r0, asr #0x10
    ldrsh r0, [r10, #0x40]
    bl _fflt
    mov r1, r0
    ldr r0, =0x3d851eb8
    bl _fmul
    bl _ffix
    mov r0, r0, lsl #0x10
    mov r2, r0, asr #0x10
    ldr r3, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r3
    mov r1, r9
    mov r3, r9
    bl _ZN8Object3D8SetScaleEiii
    mov r0, #0x1
    str r0, [sp, #0x18]
    b @L0218d9d8
@L0218d7d4:
    cmp r8, #0x2
    cmpne r8, #0x3
    cmpne r8, #0x7
    cmpne r8, #0x8
    cmpne r8, #0x9
    bne @L0218d950
    ldrsh r2, [r10, #0x42]
    ldrsh r1, [r10, #0x40]
    mov r0, #0x1000
    smull r3, r2, r1, r2
    adds r3, r3, #0x800
    adc r2, r2, #0x0
    mov r1, r3, lsr #0xc
    orr r1, r1, r2, lsl #0x14
    bl fix32_Divide
    mov r9, r0
    ldrsh r1, [r10, #0x40]
    mov r0, #0x1000
    bl fix32_Divide
    cmp r8, #0x2
    cmpne r8, #0x3
    str r0, [sp, #0x10]
    mov r11, r9
    cmpne r8, #0x7
    bne @L0218d930
    ldrsh r0, [r10, #0x40]
    bl _fflt
    str r0, [sp, #0x28]
    ldrsh r0, [r10, #0x40]
    sub r0, r0, #0x1000
    bl _fflt
    mov r1, r0
    mov r0, #0x3f000000
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x28]
    bl _fsub
    bl _ffix
    smull r2, r1, r9, r0
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r0, r1, r0
    mov r9, r2, lsr #0xc
    orr r9, r9, r0, lsl #0x14
    ldrsh r0, [r10, #0x40]
    bl _fflt
    str r0, [sp, #0x2c]
    ldrsh r0, [r10, #0x40]
    sub r0, r0, #0x1000
    bl _fflt
    mov r1, r0
    mov r0, #0x3f000000
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x2c]
    bl _fsub
    bl _ffix
    ldr r1, [sp, #0x10]
    smull r3, r2, r1, r0
    mov r0, #0x800
    adds r3, r3, r0
    mov r0, #0x0
    adc r1, r2, r0
    mov r0, r3, lsr #0xc
    orr r0, r0, r1, lsl #0x14
    str r0, [sp, #0x10]
    ldrsh r0, [r10, #0x40]
    bl _fflt
    str r0, [sp, #0x30]
    ldrsh r0, [r10, #0x40]
    sub r0, r0, #0x1000
    bl _fflt
    mov r1, r0
    mov r0, #0x3f000000
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x30]
    bl _fsub
    bl _ffix
    smull r2, r1, r11, r0
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r0, r1, r0
    mov r11, r2, lsr #0xc
    orr r11, r11, r0, lsl #0x14
@L0218d930:
    mov r1, r9
    ldr r9, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r9
    ldr r2, [sp, #0x10]
    mov r3, r11
    bl _ZN8Object3D8SetScaleEiii
    b @L0218d9d8
@L0218d950:
    cmp r8, #0x6
    cmpne r8, #0x5
    cmpne r8, #0x1
    bne @L0218d9d8
    ldrsh r1, [r10, #0x42]
    ldrsh r0, [r10, #0x40]
    smull r2, r1, r0, r1
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r1, r1, r0
    mov r0, r2, lsr #0xc
    orr r0, r0, r1, lsl #0x14
    bl _fflt
    mov r1, r0
    ldr r0, =0x3d851eb8
    bl _fmul
    bl _ffix
    mov r0, r0, lsl #0x10
    mov r9, r0, asr #0x10
    ldrsh r0, [r10, #0x40]
    bl _fflt
    mov r1, r0
    ldr r0, =0x3d851eb8
    bl _fmul
    bl _ffix
    mov r0, r0, lsl #0x10
    mov r2, r0, asr #0x10
    ldr r3, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r3
    mov r1, r9
    mov r3, r9
    bl _ZN8Object3D8SetScaleEiii
@L0218d9d8:
    cmp r8, #0x8
    cmpne r8, #0x1
    bne @L0218da10
    ldr r0, [sp, #0x14]
    ldr r1, [r0, #0x8]
    mov r0, #0x1
    str r0, [sp, #0x18]
    mov r0, r1, lsl #0x17
    mov r0, r0, lsr #0x1b
    cmp r0, #0x6
    moveq r0, #0x1
    streq r0, [r10, #0x58]
    movne r0, #0x0
    strne r0, [r10, #0x58]
@L0218da10:
    add r0, r5, r4
    bl func_0207df90
    str r7, [sp, #0x0]
    add r0, sp, #0x44
    str r0, [sp, #0x4]
    add r0, sp, #0xc4
    add r1, sp, #0xc8
    mov r2, r6
    add r3, sp, #0x34
    bl DecompressFileFromGPCByName
    ldr r1, [sp, #0x1c]
    ldr r0, [sp, #0x20]
    mov r2, r6
    add r1, r1, r0
    mov r0, #0x0
    str r0, [sp, #0x0]
    ldr r3, [r10, #0x24]
    mov r0, #0xac
    mla r0, r8, r0, r3
    ldr r3, [sp, #0x34]
    bl _ZN8Object3D20SetModelFromFileCopyEP13SafeAllocatorPKvjN7Model3D18TextureStagingModeE
    ldr r1, [sp, #0x34]
    add r0, r5, r4
    add r6, r6, r1
    sub r7, r7, r1
    bl func_0207dfac
    cmp r8, #0x4
    bne @L0218daa0
    ldr r2, [r10, #0x24]
    ldr r0, [r2, #0x20c]
    cmp r0, #0x0
    beq @L0218daa0
    mov r1, #0xac
    mla r1, r8, r1, r2
    ldr r1, [r1, #0x8]
    bl _ZN7Model3D22ApplyTexturesFromModelEPS_
@L0218daa0:
    add r8, r8, #0x1
@L0218daa4:
    cmp r8, #0xa
    blt @L0218d610
    add r0, sp, #0xc4
    bl _ZN11GPCReadPair5ResetEv
@L0218dab4:
    bl func_02099cac
    ldr r1, [r10, #0x4]
    mov r4, r0
    ldr r0, [r1, #0x0]
    ldr r0, [r0, #0x148]
    mov r0, r0, lsl #0x10
    movs r5, r0, lsr #0xd
    beq @L0218db64
    ldrb r0, [r10, #0x3c]
    mov r1, #0x4
    add r0, r4, r0, lsl #0x2
    bl CleanInvalidateCacheRange
    ldrb r0, [r10, #0x3d]
    add r2, r4, #0x108
    mov r1, #0x4
    add r0, r2, r0, lsl #0x2
    bl CleanInvalidateCacheRange
    ldrb r0, [r10, #0x3e]
    add r2, r4, #0x88
    mov r1, #0x10
    add r0, r2, r0, lsl #0x4
    bl CleanInvalidateCacheRange
    bl func_020c9820
    bl LockStagedTextureVRAMCopying
    bl MemoryMapTexturePalette
    ldrb r0, [r10, #0x3c]
    add r1, r5, #0x24
    mov r2, #0x4
    add r0, r4, r0, lsl #0x2
    bl LoadToTexturePalette
    add r3, r4, #0x108
    ldrb r0, [r10, #0x3d]
    add r1, r5, #0x28
    mov r2, #0x4
    add r0, r3, r0, lsl #0x2
    bl LoadToTexturePalette
    add r3, r4, #0x88
    add r1, r5, #0x30
    ldrb r0, [r10, #0x3e]
    mov r2, #0x10
    add r0, r3, r0, lsl #0x4
    bl LoadToTexturePalette
    bl MemoryUnmapTexturePalette
    bl UnlockStagedTextureVRAMCopying
@L0218db64:
    mov r5, #0x0
    ldr r4, =sDollPalettes
    b @L0218db80
@L0218db70:
    ldr r1, [r4, r5, lsl #0x2]
    mov r0, r10
    bl _ZN10ViewObject11LoadPaletteEi
    add r5, r5, #0x1
@L0218db80:
    ldr r0, [r4, r5, lsl #0x2]
    cmp r0, #0x0
    bge @L0218db70
    ldr r0, [sp, #0x18]
    cmp r0, #0x0
    beq @L0218dba4
    mov r0, r10
    mov r1, #0x0
    bl _ZN10ViewObject18LoadDollAnimationsEPKc
@L0218dba4:
    mov r1, #0x0
    ldr r0, =sStrings+0x128
    strb r1, [r10, #0x2c]
    str r0, [r10, #0xc]
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, sp, #0xc4
    mov r4, #0x1
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0xc4
    bl ZeroDestroyGPCPointer
    mov r0, r4
    add sp, sp, #0x114
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 87.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers differ from the second file onwards, and so does the order of the loads of the files' sizes.
#ifdef NONMATCHING
int ViewObject::LoadMonster(ViewerEntry* entry)
{
    VRAMManagerState* state;
    GPCReadPair pair;
    char name[0x10];
    monster_ = func_0206f4f0(viewer_->monsters_, entry->id_);

    if (monster_ == NULL)
        return 0;
    __clear(name, sizeof(name));
    state = slot_->states_;
    int result = 1;
    allocators_->Reset();
    func_0207df50(state);
    func_0207df90(state);
    if (viewer_->field_)
        sprintf(name, STRING(0x12d, "%s_f.mon"), monster_->unk_4);
    else
        sprintf(name, STRING(0x136, "%s.mon"), monster_->unk_4);
    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    func_02079a3c(&pair);
    unsigned int offset;
    unsigned int size;
    if (LoadAndDecompressGPCHeaderAndInnerFileInfo(&pair.pGPCFile, pair.machine,
        STRING(0x13d, "data/pack_lv5/enemy.gp2"), data_0211e33c, offset, 0x30000, false, NULL))
    {
        void* motions;
        unsigned char* buffer = data_0211e33c;
        unsigned int start = offset;
        if (DecompressFileFromGPCByName(pair.pGPCFile, pair.machine, buffer + start, size, 0x30000 - start, name))
        {
            void* models = NULL;
            const void* file = NULL;
            unsigned int fileSize = 0;
            unsigned int modelsSize = 0;
            unsigned int motionsSize = 0;
            motions = NULL;
            if (FindFilesInNarcBySubstring(buffer + start, STRING(0x155, ".cchr"), &file, &fileSize, 1))
                models = DecompressLZ77FileIntoAllocatedSpace(*allocators_, file, modelsSize);
            if (FindFilesInNarcBySubstring(buffer + start, STRING(0x15b, ".cmot"), &file, &fileSize, 1))
                motions = DecompressLZ77FileIntoAllocatedSpace(*allocators_, file, motionsSize);
            ObjectArchiveLoadInfo info;
            if (models != NULL)
            {
                func_0203dafc(&info);
                info.allocator = allocators_;
                info.unk_8 = modelsSize;
                info.fileData = models;
                info.unk_10 = 1;
                objects_->LoadFromCCHROrCMOTArchive(&info, NULL);
            }
            if (motions != NULL)
            {
                func_0203dafc(&info);
                info.allocator = allocators_;
                info.unk_8 = motionsSize;
                info.fileData = motions;
                info.unk_10 = 1;
                objects_->LoadFromCCHROrCMOTArchive(&info, NULL);
            }
            Vector3fix scale = sMonsterScale;
            objects_->SetScale(&scale);
            objects_->MaybeSetBCFGAnimation(0, loop_);
        }
        else
        {
            result = 0;
        }
        pair.Reset();
    }
    else
    {
        result = 0;
    }
    BackgroundLoader::RemoveLockGlobal();
    func_0207dfac(state);
    if (result == 0)
    {
        pair.Reset();
        ZeroDestroyGPCPointer(&pair.pGPCFile);
        return 0;
    }
    MonsterSounds* sounds = func_02070fd0(viewer_->monsterSounds_, entry->id_);
    if (sounds != NULL)
    {
        objects_->SetField78(sounds->sounds_);
        objects_->SetField7a(sounds->sounds_ >> 16);
        unsigned int value = sounds->sounds_;
        func_0205ebc0(data_02108760, (unsigned short)value, value >> 16);
    }
    name_ = monster_->name_;
    pair.Reset();
    ZeroDestroyGPCPointer(&pair.pGPCFile);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11GPCReadPair5ResetEv(); // GPCReadPair::Reset
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN8Object3D10SetField78Et(); // Object3D::SetField78
    void _ZN8Object3D10SetField7aEt(); // Object3D::SetField7a
    void _ZN8Object3D21MaybeSetBCFGAnimationEii(); // Object3D::MaybeSetBCFGAnimation
    void _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE(); // Object3D::LoadFromCCHROrCMOTArchive
    void _ZN8Object3D8SetScaleEPK8Vector3i(); // Object3D::SetScale
}

asm int ViewObject::LoadMonster(ViewerEntry* entry)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xb4
    mov r10, r0
    mov r9, r1
    ldr r0, [r10, #0x0]
    ldrsh r1, [r9, #0x8]
    add r0, r0, #0x64
    bl func_0206f4f0
    str r0, [r10, #0x10]
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0218dee4
    add r0, sp, #0x54
    mov r1, #0x10
    bl __clear
    ldr r0, [r10, #0x8]
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r10, #0x4]
    mov r5, #0x1
    ldr r6, [r0, #0x0]
    mov r0, r6
    bl func_0207df50
    mov r0, r6
    bl func_0207df90
    ldr r0, [r10, #0x0]
    ldr r1, [r10, #0x10]
    ldrb r0, [r0, #0x1a1]
    ldr r2, [r1, #0x4]
    cmp r0, #0x0
    add r0, sp, #0x54
    beq @L0218dc74
    ldr r1, =sStrings+0x12d
    bl sprintf
    b @L0218dc7c
@L0218dc74:
    ldr r1, =sStrings+0x136
    bl sprintf
@L0218dc7c:
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    add r0, sp, #0x64
    bl func_02079a3c
    add r1, sp, #0x24
    str r1, [sp, #0x0]
    mov r0, #0x30000
    str r0, [sp, #0x4]
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    ldr r2, =sStrings+0x13d
    ldr r3, =data_0211e33c
    add r0, sp, #0x64
    add r1, sp, #0x68
    bl LoadAndDecompressGPCHeaderAndInnerFileInfo
    cmp r0, #0x0
    beq @L0218de38
    ldr r4, [sp, #0x24]
    ldr r11, =data_0211e33c
    rsb r0, r4, #0x30000
    str r0, [sp, #0x0]
    add r7, sp, #0x54
    add r0, sp, #0x64
    add r1, sp, #0x68
    add r3, sp, #0x20
    add r2, r11, r4
    str r7, [sp, #0x4]
    bl DecompressFileFromGPCByName
    cmp r0, #0x0
    beq @L0218de28
    mov r7, #0x0
    ldr r1, =sStrings+0x155
    add r2, sp, #0x1c
    add r3, sp, #0x18
    str r7, [sp, #0x1c]
    str r7, [sp, #0x18]
    str r7, [sp, #0x14]
    str r7, [sp, #0x10]
    mov r12, #0x1
    add r0, r11, r4
    mov r8, r7
    str r12, [sp, #0x0]
    bl FindFilesInNarcBySubstring
    cmp r0, #0x0
    beq @L0218dd48
    ldr r0, [r10, #0x8]
    ldr r1, [sp, #0x1c]
    add r2, sp, #0x14
    bl DecompressLZ77FileIntoAllocatedSpace
    mov r7, r0
@L0218dd48:
    ldr r1, =sStrings+0x15b
    mov r12, #0x1
    add r2, sp, #0x1c
    add r3, sp, #0x18
    add r0, r11, r4
    str r12, [sp, #0x0]
    bl FindFilesInNarcBySubstring
    cmp r0, #0x0
    beq @L0218dd80
    ldr r0, [r10, #0x8]
    ldr r1, [sp, #0x1c]
    add r2, sp, #0x10
    bl DecompressLZ77FileIntoAllocatedSpace
    mov r8, r0
@L0218dd80:
    cmp r7, #0x0
    beq @L0218ddbc
    add r0, sp, #0x34
    bl func_0203dafc
    ldr r2, [r10, #0x8]
    ldr r1, [sp, #0x14]
    mov r0, #0x1
    str r2, [sp, #0x40]
    str r1, [sp, #0x3c]
    str r7, [sp, #0x38]
    str r0, [sp, #0x44]
    ldr r0, [r10, #0x24]
    add r1, sp, #0x34
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
@L0218ddbc:
    cmp r8, #0x0
    beq @L0218ddf8
    add r0, sp, #0x34
    bl func_0203dafc
    ldr r2, [r10, #0x8]
    ldr r1, [sp, #0x10]
    mov r0, #0x1
    str r2, [sp, #0x40]
    str r1, [sp, #0x3c]
    str r8, [sp, #0x38]
    str r0, [sp, #0x44]
    ldr r0, [r10, #0x24]
    add r1, sp, #0x34
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
@L0218ddf8:
    ldr r0, =sMonsterScale
    add r3, sp, #0x28
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r0, [r10, #0x24]
    mov r1, r3
    bl _ZN8Object3D8SetScaleEPK8Vector3i
    ldr r0, [r10, #0x24]
    ldr r2, [r10, #0x44]
    mov r1, #0x0
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    b @L0218de2c
@L0218de28:
    mov r5, #0x0
@L0218de2c:
    add r0, sp, #0x64
    bl _ZN11GPCReadPair5ResetEv
    b @L0218de3c
@L0218de38:
    mov r5, #0x0
@L0218de3c:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    mov r0, r6
    bl func_0207dfac
    cmp r5, #0x0
    bne @L0218de6c
    add r0, sp, #0x64
    mov r4, #0x0
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0x64
    bl ZeroDestroyGPCPointer
    mov r0, r4
    b @L0218dee4
@L0218de6c:
    ldr r0, [r10, #0x0]
    ldrh r1, [r9, #0x8]
    add r0, r0, #0x70
    bl func_02070fd0
    movs r4, r0
    beq @L0218dec0
    ldr r1, [r4, #0x14]
    ldr r0, [r10, #0x24]
    mov r1, r1, lsl #0x10
    mov r1, r1, lsr #0x10
    bl _ZN8Object3D10SetField78Et
    ldr r1, [r4, #0x14]
    ldr r0, [r10, #0x24]
    mov r1, r1, lsr #0x10
    bl _ZN8Object3D10SetField7aEt
    ldr r2, [r4, #0x14]
    ldr r0, =data_02108760
    mov r1, r2, lsl #0x10
    mov r1, r1, lsr #0x10
    mov r2, r2, lsr #0x10
    bl func_0205ebc0
@L0218dec0:
    ldr r1, [r10, #0x10]
    add r0, sp, #0x64
    ldr r1, [r1, #0x0]
    mov r4, #0x1
    str r1, [r10, #0xc]
    bl _ZN11GPCReadPair5ResetEv
    add r0, sp, #0x64
    bl ZeroDestroyGPCPointer
    mov r0, r4
@L0218dee4:
    add sp, sp, #0xb4
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 94.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The scheduling of the stores of the archive's load info differs.
#ifdef NONMATCHING
int ViewObject::LoadNpc(ViewerEntry* entry)
{
    char path[0x20];

    if (entry->file_ == NULL)
        return 0;
    __clear(path, sizeof(path));
    allocators_->Reset();
    int result = 1;
    VRAMManagerState* state = slot_->states_;
    func_0207df50(state);
    func_0207df90(state);
    sprintf(path, STRING(0x161, "data/chara_sub/%s.chr"), entry->file_);
    BackgroundLoader::AddLockGlobal();
    unsigned int size = 0;
    if (!LoadFileIntoMemory(path, data_0211e33c, &size))
    {
        result = 0;
    }
    else
    {
        ObjectArchiveLoadInfo info;
        func_0203dafc(&info);
        info.allocator = allocators_;
        info.fileData = data_0211e33c;
        info.unk_8 = size;
        info.unk_10 = 1;
        objects_->LoadFromCCHROrCMOTArchive(&info, NULL);
        Vector3fix scale = sNpcScale;
        objects_->SetScale(&scale);
        objects_->MaybeSetBCFGAnimation(0, loop_);
    }
    BackgroundLoader::RemoveLockGlobal();
    func_0207dfac(state);
    if (result)
    {
        name_ = entry->name_;
        return 1;
    }
    return 0;
}
#else
asm int ViewObject::LoadNpc(ViewerEntry* entry)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x50
    mov r6, r1
    ldr r1, [r6, #0x4]
    mov r7, r0
    cmp r1, #0x0
    moveq r0, #0x0
    beq @L0218e018
    add r0, sp, #0x30
    mov r1, #0x20
    bl __clear
    ldr r0, [r7, #0x8]
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r7, #0x4]
    mov r4, #0x1
    ldr r5, [r0, #0x0]
    mov r0, r5
    bl func_0207df50
    mov r0, r5
    bl func_0207df90
    ldr r1, =sStrings+0x161
    ldr r2, [r6, #0x4]
    add r0, sp, #0x30
    bl sprintf
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x0]
    ldr r1, =data_0211e33c
    add r0, sp, #0x30
    add r2, sp, #0x0
    bl LoadFileIntoMemory
    cmp r0, #0x0
    moveq r4, #0x0
    beq @L0218dff8
    add r0, sp, #0x10
    bl func_0203dafc
    ldr r3, [r7, #0x8]
    ldr r1, [sp, #0x0]
    ldr r2, =data_0211e33c
    mov r0, r4
    str r2, [sp, #0x14]
    str r1, [sp, #0x18]
    str r3, [sp, #0x1c]
    str r0, [sp, #0x20]
    ldr r0, [r7, #0x24]
    add r1, sp, #0x10
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    ldr r0, =sNpcScale
    add r3, sp, #0x4
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r0, [r7, #0x24]
    mov r1, r3
    bl _ZN8Object3D8SetScaleEPK8Vector3i
    ldr r0, [r7, #0x24]
    ldr r2, [r7, #0x44]
    mov r1, #0x0
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
@L0218dff8:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    mov r0, r5
    bl func_0207dfac
    cmp r4, #0x0
    ldrne r1, [r6, #0x0]
    moveq r0, #0x0
    movne r0, #0x1
    strne r1, [r7, #0xc]
@L0218e018:
    add sp, sp, #0x50
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

// NONMATCHING: the C matches 94.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers of the copy of the effect's file differ.
#ifdef NONMATCHING
int ViewObject::LoadEffect(ViewerEntry* entry)
{
    NarcHandle narc;
    NitroVM vm;
    char name[0x50];
    char path[0x20];

    if (entry->file_ == NULL)
        return 0;
    __clear(path, sizeof(path));
    allocators_->Reset();
    int result = 1;
    VRAMManagerState* state = slot_->states_;
    func_0207df50(state);
    func_0207df90(state);
    sprintf(path, STRING(0x177, "data/effect/%s.chr"), entry->file_);
    BackgroundLoader::AddLockGlobal();
    unsigned int size = 0;
    if (LoadFileIntoMemory(path, data_0211e33c, &size))
    {
        if (narc.Initialize(STRING(0x18a, "ARC"), data_0211e33c))
        {
            NitroVM_Initialize(&vm);
            for (int i = 0; PrepareReadFileInNARCByID(&vm, &narc, i); i++)
            {
                __clear(name, sizeof(name));
                NitroVM_WriteOutFilePath(&vm, name, sizeof(name));
                if (strstr(name, STRING(0x18e, ".beff")) != NULL)
                {
                    const void* file = narc.GetFileByIndex(i);
                    long fileSize;
                    unsigned int copySize = size;
                    if (copySize & 3)
                        copySize += 4 - (3 & copySize);
                    fileSize = vm.fileInfo.endOffset - vm.fileInfo.startOffset;
                    void* copy = allocators_->Allocate(copySize);
                    if (copy == NULL)
                    {
                        NitroVM_FinishRead(&vm);
                        narc.Destroy();
                        result = 0;
                    }
                    else
                    {
                        memcpy(copy, file, copySize);
                        effect_->unk_c = allocators_->Allocate(0x128);
                        func_02054f80(effect_->unk_c);
                        if (!func_02055180(effect_->unk_c, allocators_, copy, fileSize))
                            result = 0;
                    }
                    NitroVM_FinishRead(&vm);
                    break;
                }
                NitroVM_FinishRead(&vm);
            }
        }
        narc.Destroy();
        ObjectArchiveLoadInfo info;
        func_0203dafc(&info);
        info.allocator = allocators_;
        info.fileData = data_0211e33c;
        info.unk_8 = size;
        info.unk_10 = 1;
        objects_->LoadFromCHRArchive(&info);
        func_02055718(effect_, objects_, allocators_);
        Vector3fix scale = sEffectScale;
        objects_->SetScale(&scale);
        objects_->MaybeSetBCFGAnimation(0, loop_);
    }
    else
    {
        result = 0;
    }
    BackgroundLoader::RemoveLockGlobal();
    func_0207dfac(state);
    if (result)
    {
        name_ = entry->name_;
        return 1;
    }
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10NarcHandle10InitializeEPKcPKh(); // NarcHandle::Initialize
    void _ZN10NarcHandle7DestroyEv(); // NarcHandle::Destroy
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo(); // Object3D::LoadFromCHRArchive
    void _ZNK10NarcHandle14GetFileByIndexEj(); // NarcHandle::GetFileByIndex
}

asm int ViewObject::LoadEffect(ViewerEntry* entry)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x150
    mov r9, r1
    ldr r1, [r9, #0x4]
    mov r10, r0
    cmp r1, #0x0
    moveq r0, #0x0
    beq @L0218e288
    add r0, sp, #0x30
    mov r1, #0x20
    bl __clear
    ldr r0, [r10, #0x8]
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r10, #0x4]
    mov r4, #0x1
    ldr r5, [r0, #0x0]
    mov r0, r5
    bl func_0207df50
    mov r0, r5
    bl func_0207df90
    ldr r1, =sStrings+0x177
    ldr r2, [r9, #0x4]
    add r0, sp, #0x30
    bl sprintf
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x0]
    ldr r1, =data_0211e33c
    add r0, sp, #0x30
    add r2, sp, #0x0
    bl LoadFileIntoMemory
    cmp r0, #0x0
    beq @L0218e264
    ldr r1, =sStrings+0x18a
    ldr r2, =data_0211e33c
    add r0, sp, #0xe8
    bl _ZN10NarcHandle10InitializeEPKcPKh
    cmp r0, #0x0
    beq @L0218e1e8
    add r0, sp, #0xa0
    bl NitroVM_Initialize
    mov r8, #0x0
    add r7, sp, #0x50
    mov r6, #0x50
    add r11, sp, #0xa0
    b @L0218e1d0
@L0218e0e4:
    mov r0, r7
    mov r1, r6
    bl __clear
    mov r0, r11
    mov r1, r7
    mov r2, #0x50
    bl NitroVM_WriteOutFilePath
    ldr r1, =sStrings+0x18e
    mov r0, r7
    bl strstr
    cmp r0, #0x0
    beq @L0218e1c4
    add r0, sp, #0xe8
    mov r1, r8
    bl _ZNK10NarcHandle14GetFileByIndexEj
    ldr r8, [sp, #0x0]
    mov r6, r0
    ands r0, r8, #0x3
    rsbne r0, r0, #0x4
    addne r8, r8, r0
    ldr r2, [sp, #0xc8]
    ldr r1, [sp, #0xc4]
    ldr r0, [r10, #0x8]
    sub r7, r2, r1
    mov r1, r8
    bl _ZN13SafeAllocator8AllocateEj
    movs r11, r0
    bne @L0218e16c
    add r0, sp, #0xa0
    bl NitroVM_FinishRead
    add r0, sp, #0xe8
    bl _ZN10NarcHandle7DestroyEv
    mov r4, #0x0
    b @L0218e1b8
@L0218e16c:
    mov r1, r6
    mov r2, r8
    bl memcpy
    ldr r0, [r10, #0x8]
    mov r1, #0x128
    bl _ZN13SafeAllocator8AllocateEj
    ldr r1, [r10, #0x28]
    str r0, [r1, #0xc]
    ldr r0, [r10, #0x28]
    ldr r0, [r0, #0xc]
    bl func_02054f80
    ldr r0, [r10, #0x28]
    ldr r1, [r10, #0x8]
    ldr r0, [r0, #0xc]
    mov r2, r11
    mov r3, r7
    bl func_02055180
    cmp r0, #0x0
    moveq r4, #0x0
@L0218e1b8:
    add r0, sp, #0xa0
    bl NitroVM_FinishRead
    b @L0218e1e8
@L0218e1c4:
    mov r0, r11
    bl NitroVM_FinishRead
    add r8, r8, #0x1
@L0218e1d0:
    mov r0, r11
    add r1, sp, #0xe8
    mov r2, r8
    bl PrepareReadFileInNARCByID
    cmp r0, #0x0
    bne @L0218e0e4
@L0218e1e8:
    add r0, sp, #0xe8
    bl _ZN10NarcHandle7DestroyEv
    add r0, sp, #0x10
    bl func_0203dafc
    ldr r3, [r10, #0x8]
    ldr r1, [sp, #0x0]
    ldr r2, =data_0211e33c
    mov r0, #0x1
    str r1, [sp, #0x18]
    str r3, [sp, #0x1c]
    str r2, [sp, #0x14]
    str r0, [sp, #0x20]
    ldr r0, [r10, #0x24]
    add r1, sp, #0x10
    bl _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo
    ldr r0, [r10, #0x28]
    ldr r1, [r10, #0x24]
    ldr r2, [r10, #0x8]
    bl func_02055718
    ldr r0, =sEffectScale
    add r3, sp, #0x4
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r0, [r10, #0x24]
    mov r1, r3
    bl _ZN8Object3D8SetScaleEPK8Vector3i
    ldr r0, [r10, #0x24]
    ldr r2, [r10, #0x44]
    mov r1, #0x0
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    b @L0218e268
@L0218e264:
    mov r4, #0x0
@L0218e268:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    mov r0, r5
    bl func_0207dfac
    cmp r4, #0x0
    ldrne r1, [r9, #0x0]
    moveq r0, #0x0
    movne r0, #0x1
    strne r1, [r10, #0xc]
@L0218e288:
    add sp, sp, #0x150
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 96.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler writes sCameraBones from the start of .data, where sCommands is, while the original writes it from its
// own address.
#ifdef NONMATCHING
int ViewObject::LoadCamera(ViewerEntry* entry)
{
    char path[0x20];

    if (entry->file_ == NULL)
        return 0;
    __clear(path, sizeof(path));
    allocators_->Reset();
    int result = 1;
    VRAMManagerState* state = slot_->states_;
    func_0207df50(state);
    func_0207df90(state);
    if (kind_ == Kind_EventCamera)
        sprintf(path, STRING(0xb0, "data/event_lv5/%s.chr"), entry->file_);
    else
        sprintf(path, STRING(0x8a, "data/chara/%s.chr"), entry->file_);
    BackgroundLoader::AddLockGlobal();
    unsigned int size = 0;
    if (!LoadFileIntoMemory(path, data_0211e33c, &size))
    {
        result = 0;
    }
    else
    {
        ObjectArchiveLoadInfo info;
        func_0203dafc(&info);
        info.allocator = allocators_;
        info.fileData = data_0211e33c;
        info.unk_8 = size;
        info.unk_10 = 1;
        objects_->LoadFromCHRArchive(&info);
        Model3D* model = objects_->pModel_;
        sCameraBones[1] = model->GetBoneIndex(STRING(0x194, "eye"));
        sCameraBones[2] = model->GetBoneIndex(STRING(0x198, "lookat"));
        sCameraBones[0] = model->GetBoneIndex(STRING(0x19f, "pos"));
        ModelRenderContext* context = GetModel3DContext(model);
        SetModelRenderContextRenderCommandHook(context, SaveCameraBones, 0, 6, 3);
        context->flags_ |= 4;
        Vector3fix scale = sCameraScale;
        objects_->SetScale(&scale);
        objects_->MaybeSetBCFGAnimation(0, loop_);
    }
    BackgroundLoader::RemoveLockGlobal();
    func_0207dfac(state);
    if (result == 0)
        return 0;
    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return 0;
    void* camera = func_020100cc(gameState);
    if (camera == NULL)
        return 0;
    func_020a2cf0(camera);
    func_020a3568(camera, 0);
    name_ = entry->name_;
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN7Model3D12GetBoneIndexEPKc(); // Model3D::GetBoneIndex
    void _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo(); // Object3D::LoadFromCHRArchive
    void _ZN8Object3D21MaybeSetBCFGAnimationEii(); // Object3D::MaybeSetBCFGAnimation
    void _ZN8Object3D8SetScaleEPK8Vector3i(); // Object3D::SetScale
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int ViewObject::LoadCamera(ViewerEntry* entry)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
    sub sp, sp, #0x54
    mov r7, r1
    ldr r1, [r7, #0x4]
    mov r8, r0
    cmp r1, #0x0
    moveq r0, #0x0
    beq @L0218e46c
    add r0, sp, #0x34
    mov r1, #0x20
    bl __clear
    ldr r0, [r8, #0x8]
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r8, #0x4]
    mov r5, #0x1
    ldr r6, [r0, #0x0]
    mov r0, r6
    bl func_0207df50
    mov r0, r6
    bl func_0207df90
    ldrb r0, [r8, #0x1c]
    ldr r2, [r7, #0x4]
    cmp r0, #0x5
    add r0, sp, #0x34
    bne @L0218e314
    ldr r1, =sStrings+0xb0
    bl sprintf
    b @L0218e31c
@L0218e314:
    ldr r1, =sStrings+0x8a
    bl sprintf
@L0218e31c:
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r3, #0x0
    ldr r1, =data_0211e33c
    add r0, sp, #0x34
    add r2, sp, #0x4
    str r3, [sp, #0x4]
    bl LoadFileIntoMemory
    cmp r0, #0x0
    moveq r5, #0x0
    beq @L0218e418
    add r0, sp, #0x14
    bl func_0203dafc
    ldr r3, [r8, #0x8]
    ldr r1, [sp, #0x4]
    ldr r2, =data_0211e33c
    mov r0, #0x1
    str r1, [sp, #0x1c]
    str r3, [sp, #0x20]
    str r2, [sp, #0x18]
    str r0, [sp, #0x24]
    ldr r0, [r8, #0x24]
    add r1, sp, #0x14
    bl _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo
    ldr r0, [r8, #0x24]
    ldr r1, =sStrings+0x194
    ldr r4, [r0, #0x8]
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r2, =sStrings+0x18
    ldr r1, =sStrings+0x198
    strb r0, [r2, #0x1]
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r2, =sStrings+0x18
    ldr r1, =sStrings+0x19f
    strb r0, [r2, #0x2]
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r1, =sStrings+0x18
    strb r0, [r1, #0x0]
    mov r0, r4
    bl GetModel3DContext
    mov r1, #0x3
    str r1, [sp, #0x0]
    ldr r1, =SaveCameraBones
    mov r4, r0
    mov r2, #0x0
    mov r3, #0x6
    bl SetModelRenderContextRenderCommandHook
    ldr r1, [r4, #0x0]
    ldr r0, =sCameraScale
    orr r1, r1, #0x4
    str r1, [r4, #0x0]
    add r3, sp, #0x8
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r0, [r8, #0x24]
    mov r1, r3
    bl _ZN8Object3D8SetScaleEPK8Vector3i
    ldr r0, [r8, #0x24]
    ldr r2, [r8, #0x44]
    mov r1, #0x0
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
@L0218e418:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    mov r0, r6
    bl func_0207dfac
    cmp r5, #0x0
    moveq r0, #0x0
    beq @L0218e46c
    bl _ZN9GameState11GetInstanceEv
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0218e46c
    bl func_020100cc
    movs r4, r0
    moveq r0, #0x0
    beq @L0218e46c
    bl func_020a2cf0
    mov r0, r4
    mov r1, #0x0
    bl func_020a3568
    ldr r1, [r7, #0x0]
    mov r0, #0x1
    str r1, [r8, #0xc]
@L0218e46c:
    add sp, sp, #0x54
    ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
}
#endif

#define PAD_BUTTON_A 1
#define PAD_BUTTON_B 2
#define PAD_BUTTON_SELECT 4
#define PAD_BUTTON_START 8
#define PAD_KEY_RIGHT 0x10
#define PAD_KEY_LEFT 0x20
#define PAD_KEY_UP 0x40
#define PAD_KEY_DOWN 0x80
#define PAD_BUTTON_R 0x100
#define PAD_BUTTON_L 0x200
#define PAD_BUTTON_X 0x400
#define PAD_BUTTON_Y 0x800

// G3_PushMtx and G3_PopMtx(1)
#define MTX_PUSH (*(volatile int*)0x04000444)
#define MTX_POP (*(volatile int*)0x04000448)

void ViewObject::UpdatePlayer()
{
    if (reload_)
        LoadPlayer();
    Object3D* object = objects_;
    int advance = 0;
    if (playing_)
    {
        if (func_02012444(data_02114e30, PAD_BUTTON_R))
            advance = 1;
    }
    else
    {
        advance = 1;
    }
    if (!advance)
        return;
    object->AdvanceEffects();
}

void ViewObject::UpdateDoll()
{
    if (reload_)
        LoadDoll();
    int advance;
    Object3D* objects = objects_;
    Object3D* part = &objects[6];
    advance = 0;
    if (playing_)
    {
        if (func_02012444(data_02114e30, PAD_BUTTON_R))
            advance = 1;
    }
    else
    {
        advance = 1;
    }
    if (!advance)
        return;
    objects[0].AdvanceEffects();
    part->AdvanceEffects();
    objects[5].AdvanceEffects();
    objects[1].AdvanceEffects();
}

void ViewObject::UpdateMonster()
{
    int advance = 0;
    if (playing_)
    {
        if (func_02012444(data_02114e30, PAD_BUTTON_R))
            advance = 1;
    }
    else
    {
        advance = 1;
    }
    if (!advance)
        return;
    objects_->AdvanceEffects();
}

void ViewObject::UpdateNpc()
{
    int advance = 0;
    if (playing_)
    {
        if (func_02012444(data_02114e30, PAD_BUTTON_R))
            advance = 1;
    }
    else
    {
        advance = 1;
    }
    if (!advance)
        return;
    objects_->AdvanceEffects();
}

void ViewObject::UpdateEffect()
{
    int advance = 0;
    if (playing_)
    {
        if (func_02012444(data_02114e30, PAD_BUTTON_R))
            advance = 1;
    }
    else
    {
        advance = 1;
    }
    if (!advance)
        return;
    if (effect_->unk_c != NULL)
    {
        func_02055774(effect_);
        return;
    }
    objects_->AdvanceEffects();
}

// NONMATCHING: the C matches 66.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler loads sCameraOutputs from the start of .bss, where sConfig is, while the original loads it from its own
// address, which also changes the scheduling of the copies of the matrices' translations.
#ifdef NONMATCHING
void ViewObject::UpdateCamera()
{
    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return;
    ViewerCamera* camera = func_020100cc(gameState);
    if (camera == NULL)
        return;
    int advance = 0;
    if (playing_)
    {
        if (func_02012444(data_02114e30, PAD_BUTTON_R))
            advance = 1;
    }
    else
    {
        advance = 1;
    }
    if (!advance)
        return;
    Matrix4x3 eye;
    Matrix4x3 target;
    Matrix4x3 position;
    sCameraOutputs.eye_ = &eye;
    sCameraOutputs.target_ = &target;
    sCameraOutputs.position_ = &position;
    func_020c5414();
    RenderConfig::SubmitToFifo();
    objects_->MaybeUpdateBonePositions();
    sCameraOutputs.eye_ = NULL;
    sCameraOutputs.target_ = NULL;
    sCameraOutputs.position_ = NULL;
    Vector3fix eyePosition;
    Vector3fix targetPosition;
    Vector3fix positionPosition;
    eyePosition.x = eye.translation.x;
    eyePosition.y = eye.translation.y;
    eyePosition.z = eye.translation.z;
    targetPosition.x = target.translation.x;
    targetPosition.y = target.translation.y;
    targetPosition.z = target.translation.z;
    positionPosition.x = position.translation.x;
    positionPosition.y = position.translation.y;
    positionPosition.z = position.translation.z;
    Vector3fix scale = objects_->GetScale();
    Vector3fixMultiply(&eyePosition, &scale, &eyePosition);
    Vector3fixMultiply(&targetPosition, &scale, &targetPosition);
    Vector3fixMultiply(&positionPosition, &scale, &positionPosition);
    Vector3fix offset = objects_->position_;
    Vector3fix_Add(&eyePosition, &offset, &eyePosition);
    Vector3fix_Add(&targetPosition, &offset, &targetPosition);
    Vector3fix_Add(&positionPosition, &offset, &positionPosition);
    camera->target_ = targetPosition;
    camera->eye_ = eyePosition;
    func_0202eab8(camera);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12RenderConfig12SubmitToFifoEv(); // RenderConfig::SubmitToFifo
    void _ZN8Object3D24MaybeUpdateBonePositionsEv(); // Object3D::MaybeUpdateBonePositions
    void _ZN8Vector3iaSERKS_(); // Vector3i::operator=
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK8Object3D8GetScaleEv(); // Object3D::GetScale
}

asm void ViewObject::UpdateCamera()
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0xd8
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    cmp r0, #0x0
    beq @L0218e800
    bl func_020100cc
    movs r4, r0
    beq @L0218e800
    ldrb r0, [r5, #0x3a]
    mov r6, #0x0
    cmp r0, #0x0
    beq @L0218e6bc
    ldr r0, =data_02114e30
    mov r1, #0x100
    bl func_02012444
    cmp r0, #0x0
    movne r6, #0x1
    b @L0218e6c0
@L0218e6bc:
    mov r6, #0x1
@L0218e6c0:
    cmp r6, #0x0
    beq @L0218e800
    ldr r0, =sCameraOutputs
    add r1, sp, #0xa8
    str r1, [r0, #0x8]
    add r2, sp, #0x78
    add r1, sp, #0x48
    str r2, [r0, #0x0]
    str r1, [r0, #0x4]
    bl func_020c5414
    bl _ZN12RenderConfig12SubmitToFifoEv
    ldr r0, [r5, #0x24]
    bl _ZN8Object3D24MaybeUpdateBonePositionsEv
    ldr r0, =sCameraOutputs
    mov r1, #0x0
    str r1, [r0, #0x8]
    str r1, [r0, #0x0]
    str r1, [r0, #0x4]
    ldr r2, [sp, #0xcc]
    ldr r0, [sp, #0xd4]
    ldr r1, [sp, #0xd0]
    str r2, [sp, #0x3c]
    ldr r2, [sp, #0x9c]
    str r0, [sp, #0x44]
    ldr r0, [sp, #0xa4]
    str r1, [sp, #0x40]
    ldr r1, [sp, #0xa0]
    str r2, [sp, #0x30]
    ldr r2, [sp, #0x6c]
    str r0, [sp, #0x38]
    ldr r0, [sp, #0x74]
    str r1, [sp, #0x34]
    ldr r1, [sp, #0x70]
    str r0, [sp, #0x2c]
    str r2, [sp, #0x24]
    str r1, [sp, #0x28]
    ldr r1, [r5, #0x24]
    add r0, sp, #0x0
    bl _ZNK8Object3D8GetScaleEv
    add r0, sp, #0x0
    add r3, sp, #0x18
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x3c
    mov r1, r3
    mov r2, r0
    bl Vector3fixMultiply
    add r0, sp, #0x30
    add r1, sp, #0x18
    mov r2, r0
    bl Vector3fixMultiply
    add r0, sp, #0x24
    add r1, sp, #0x18
    mov r2, r0
    bl Vector3fixMultiply
    ldr r0, [r5, #0x24]
    add r3, sp, #0xc
    add r0, r0, #0x44
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x3c
    mov r1, r3
    mov r2, r0
    bl Vector3fix_Add
    add r0, sp, #0x30
    add r1, sp, #0xc
    mov r2, r0
    bl Vector3fix_Add
    add r0, sp, #0x24
    add r1, sp, #0xc
    mov r2, r0
    bl Vector3fix_Add
    add r0, r4, #0x10
    add r1, sp, #0x30
    bl _ZN8Vector3iaSERKS_
    add r1, sp, #0x3c
    add r0, r4, #0x4
    bl _ZN8Vector3iaSERKS_
    mov r0, r4
    bl func_0202eab8
@L0218e800:
    add sp, sp, #0xd8
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

// Adds the counts of an object's model to the info's
#define ADD_COUNTS(object)                                                                                             \
    {                                                                                                                  \
        NSBXXInternalModel* info;                                                                                      \
        if ((object)->pModel_ != NULL && (info = (object)->pModel_->rawInternalModel_) != NULL)                        \
        {                                                                                                              \
            triangles_ += info->numTriangles_;                                                                         \
            quads_ += (object)->pModel_->rawInternalModel_->numQuads_;                                                 \
        }                                                                                                              \
    }

// NONMATCHING: the C matches 85.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers of the body, its model and the bones differ (the permuter got 85.7 %).
#ifdef NONMATCHING
void ViewObject::DrawPlayer()
{
    int head;
    ModelRenderContext* context;
    triangles_ = quads_ = 0;
    Object3D* body = objects_;
    Model3D* model = body->pModel_;
    if (model == NULL)
        return;
    context = GetModel3DContext(model);
    if (context == NULL)
        return;
    MTX_PUSH = 0;
    body->Draw(true);
    ADD_COUNTS(body);
    MTX_POP = 1;
    head = model->GetBoneIndex(STRING(0x1a3, "head"));
    unsigned long arm1L = model->GetBoneIndex(STRING(0x11f, "arm1L"));
    unsigned int arm1R = model->GetBoneIndex(STRING(0x119, "arm1R"));
    model->GetBoneIndex(STRING(0x1a8, "leg1L"));
    model->GetBoneIndex(STRING(0x1ae, "leg1R"));
    PlayerBones bones = sPlayerBones;
    bones.bones_[4][1] = arm1R;
    bones.bones_[0][1] = head;
    bones.bones_[1][1] = head;
    bones.bones_[2][1] = head;
    bones.bones_[3][1] = arm1L;
    for (int(*bone)[2] = bones.bones_; (*bone)[0] >= 0; bone++)
    {
        Object3D* part = &objects_[(*bone)[0]];
        if (part->unknown_2_ >= 0)
        {
            GetModelBonePositionAndDirectionMatrices(context, NULL, NULL, (*bone)[1]);
            MTX_PUSH = 0;
            part->DrawSimple3(false);
            ADD_COUNTS(part);
            MTX_POP = 1;
        }
    }
    if (unk_54)
    {
        Object3D* weapon = &objects_[8];
        if (weapon->unknown_2_ >= 0)
        {
            GetModelBonePositionAndDirectionMatrices(context, NULL, NULL, arm1L);
            MTX_PUSH = 0;
            func_02031234(0x3244);
            weapon->DrawSimple2(false);
            ADD_COUNTS(weapon);
            MTX_POP = 1;
        }
    }
    MTX_PUSH = 0;
    if (body[1].unknown_2_ >= 0)
    {
        body->ApplyAnimations(&body[1]);
        body[1].Draw(false);
        if (body[1].pModel_ != NULL && body[1].pModel_->rawInternalModel_ != NULL)
        {
            triangles_ += body->pModel_->rawInternalModel_->numTriangles_;
            quads_ += body->pModel_->rawInternalModel_->numQuads_;
        }
    }
    MTX_POP = 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN8Object3D11DrawSimple2Eb(); // Object3D::DrawSimple2
    void _ZN8Object3D11DrawSimple3Eb(); // Object3D::DrawSimple3
    void _ZN8Object3D15ApplyAnimationsEPS_(); // Object3D::ApplyAnimations
    void _ZN8Object3D4DrawEb(); // Object3D::Draw
}

asm void ViewObject::DrawPlayer()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x30
    mov r1, #0x0
    mov r10, r0
    strh r1, [r10, #0x36]
    strh r1, [r10, #0x34]
    ldr r9, [r10, #0x24]
    ldr r8, [r9, #0x8]
    cmp r8, #0x0
    beq @L0218ead8
    mov r0, r8
    bl GetModel3DContext
    movs r5, r0
    beq @L0218ead8
    ldr r1, =0x4000444
    mov r2, #0x0
    str r2, [r1, #0x0]
    mov r0, r9
    mov r1, #0x1
    bl _ZN8Object3D4DrawEb
    ldr r0, [r9, #0x8]
    cmp r0, #0x0
    ldrne r0, [r0, #0x54]
    cmpne r0, #0x0
    beq @L0218e89c
    ldrh r1, [r10, #0x34]
    ldrh r0, [r0, #0x28]
    add r0, r1, r0
    strh r0, [r10, #0x34]
    ldr r0, [r9, #0x8]
    ldrh r1, [r10, #0x36]
    ldr r0, [r0, #0x54]
    ldrh r0, [r0, #0x2a]
    add r0, r1, r0
    strh r0, [r10, #0x36]
@L0218e89c:
    ldr r2, =0x4000448
    mov r3, #0x1
    ldr r1, =sStrings+0x1a3
    mov r0, r8
    str r3, [r2, #0x0]
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r4, r0
    ldr r1, =sStrings+0x11f
    mov r0, r8
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r6, r0
    ldr r1, =sStrings+0x119
    mov r0, r8
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r7, r0
    ldr r1, =sStrings+0x1a8
    mov r0, r8
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r1, =sStrings+0x1ae
    mov r0, r8
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r12, =sPlayerBones
    add r11, sp, #0x0
    mov r8, #0x3
@L0218e8fc:
    ldmia r12!, {r0, r1, r2, r3}
    stmia r11!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L0218e8fc
    str r7, [sp, #0x24]
    str r4, [sp, #0x4]
    str r4, [sp, #0xc]
    str r4, [sp, #0x14]
    str r6, [sp, #0x1c]
    add r7, sp, #0x0
    ldr r4, =0x4000444
    mov r11, #0x1
    b @L0218e9b0
@L0218e930:
    ldr r1, [r10, #0x24]
    mov r0, #0xac
    mla r8, r2, r0, r1
    ldrsh r0, [r8, #0x2]
    ldr r3, [r7, #0x4]
    cmp r0, #0x0
    blt @L0218e9ac
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    mov r1, #0x0
    mov r0, r8
    str r1, [r4, #0x0]
    bl _ZN8Object3D11DrawSimple3Eb
    ldr r0, [r8, #0x8]
    cmp r0, #0x0
    ldrne r0, [r0, #0x54]
    cmpne r0, #0x0
    beq @L0218e9a8
    ldrh r1, [r10, #0x34]
    ldrh r0, [r0, #0x28]
    add r0, r1, r0
    strh r0, [r10, #0x34]
    ldr r0, [r8, #0x8]
    ldrh r1, [r10, #0x36]
    ldr r0, [r0, #0x54]
    ldrh r0, [r0, #0x2a]
    add r0, r1, r0
    strh r0, [r10, #0x36]
@L0218e9a8:
    str r11, [r4, #0x4]
@L0218e9ac:
    add r7, r7, #0x8
@L0218e9b0:
    ldr r2, [r7, #0x0]
    cmp r2, #0x0
    bge @L0218e930
    ldr r0, [r10, #0x54]
    cmp r0, #0x0
    beq @L0218ea58
    ldr r0, [r10, #0x24]
    add r4, r0, #0x560
    ldrsh r0, [r4, #0x2]
    cmp r0, #0x0
    blt @L0218ea58
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    mov r3, r6
    bl GetModelBonePositionAndDirectionMatrices
    ldr r1, =0x4000444
    mov r2, #0x0
    ldr r0, =0x3244
    str r2, [r1, #0x0]
    bl func_02031234
    mov r0, r4
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
    ldr r0, [r4, #0x8]
    cmp r0, #0x0
    ldrne r0, [r0, #0x54]
    cmpne r0, #0x0
    beq @L0218ea4c
    ldrh r1, [r10, #0x34]
    ldrh r0, [r0, #0x28]
    add r0, r1, r0
    strh r0, [r10, #0x34]
    ldr r0, [r4, #0x8]
    ldrh r1, [r10, #0x36]
    ldr r0, [r0, #0x54]
    ldrh r0, [r0, #0x2a]
    add r0, r1, r0
    strh r0, [r10, #0x36]
@L0218ea4c:
    ldr r0, =0x4000448
    mov r1, #0x1
    str r1, [r0, #0x0]
@L0218ea58:
    ldr r0, =0x4000444
    mov r1, #0x0
    str r1, [r0, #0x0]
    ldrsh r0, [r9, #0xae]
    cmp r0, #0x0
    blt @L0218eacc
    mov r0, r9
    add r1, r9, #0xac
    bl _ZN8Object3D15ApplyAnimationsEPS_
    add r0, r9, #0xac
    mov r1, #0x0
    bl _ZN8Object3D4DrawEb
    ldr r0, [r9, #0xb4]
    cmp r0, #0x0
    ldrne r0, [r0, #0x54]
    cmpne r0, #0x0
    beq @L0218eacc
    ldr r0, [r9, #0x8]
    ldrh r1, [r10, #0x34]
    ldr r0, [r0, #0x54]
    ldrh r0, [r0, #0x28]
    add r0, r1, r0
    strh r0, [r10, #0x34]
    ldr r0, [r9, #0x8]
    ldrh r1, [r10, #0x36]
    ldr r0, [r0, #0x54]
    ldrh r0, [r0, #0x2a]
    add r0, r1, r0
    strh r0, [r10, #0x36]
@L0218eacc:
    ldr r0, =0x4000448
    mov r1, #0x1
    str r1, [r0, #0x0]
@L0218ead8:
    add sp, sp, #0x30
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void ViewObject::DrawDoll()
{
    unsigned short edge = func_02099cac()->edge_;
    unsigned short edges[8] = {edge, edge, edge, edge, edge, edge, edge, edge};
    func_020c555c(edges);
    quads_ = 0;
    triangles_ = 0;
    Model3D* model = objects_->pModel_;
    if (model == NULL)
        return;
    ModelRenderContext* context = GetModel3DContext(model);
    if (context == NULL)
        return;
    Object3D* parts[10];
    __clear(parts, sizeof(parts));
    parts[0] = &objects_[0];
    parts[1] = &objects_[2];
    parts[2] = &objects_[3];
    parts[3] = &objects_[7];
    parts[4] = &objects_[8];
    parts[5] = &objects_[9];
    parts[6] = &objects_[6];
    parts[7] = &objects_[5];
    parts[8] = &objects_[1];
    DollBones bones = sDollBones;
    DollAnimated animated = sDollAnimated;
    for (int i = 0; parts[i] != NULL; i++)
    {
        Object3D* part = parts[i];
        if (part->unknown_2_ >= 0)
        {
            if (strlen(bones.names_[i]) != 0)
            {
                GetModelBonePositionAndDirectionMatrices(context, NULL, NULL, model->GetBoneIndex(bones.names_[i]));
                part->EnableFlag(0x4000);
            }
            if (animated.animated_[i])
                objects_->ApplyAnimations(part);
            part->Draw(true);
        }
    }
}

void ViewObject::DrawMonster()
{
    if (monster_ != NULL && viewer_->monsterBox_)
    {
        Vector3fix position = objects_->position_;
        Vector3fix size;
        size.x = monster_->boxWidth_ * 4;
        size.y = monster_->boxHeight_;
        size.z = monster_->boxWidth_ * 4;
        RenderConfig::SubmitToFifo();
        func_0208b5b4(position, size, 0, 0x7fff);
    }
    MTX_PUSH = 0;
    objects_->Draw(false);
    RenderConfig::SubmitToFifo();
    MTX_POP = 1;
    triangles_ = quads_ = 0;
    triangles_ = objects_->pModel_->rawInternalModel_->numTriangles_;
    quads_ = objects_->pModel_->rawInternalModel_->numQuads_;
}

void ViewObject::DrawNpc()
{
    MTX_PUSH = 0;
    objects_->Draw(false);
    RenderConfig::SubmitToFifo();
    MTX_POP = 1;
    triangles_ = quads_ = 0;
    triangles_ = objects_->pModel_->rawInternalModel_->numTriangles_;
    quads_ = objects_->pModel_->rawInternalModel_->numQuads_;
}

void ViewObject::DrawEffect()
{
    triangles_ = quads_ = 0;
    if (effect_->unk_c != NULL)
    {
        MTX_PUSH = 0;
        func_0205578c(effect_);
        MTX_POP = 1;
        void* unknown = effect_->unk_4;
        if (unknown == NULL)
        {
            triangles_ = 0;
            quads_ = 0;
            return;
        }
        func_020577cc(unknown, &triangles_, &quads_);
        return;
    }
    MTX_PUSH = 0;
    objects_->Draw(false);
    MTX_POP = 1;
    triangles_ = objects_->pModel_->rawInternalModel_->numTriangles_;
    quads_ = objects_->pModel_->rawInternalModel_->numQuads_;
}

void ViewObject::Initialize()
{
    slot_ = NULL;
    allocators_ = NULL;
    name_ = NULL;
    monster_ = NULL;
    buffer_ = NULL;
    bufferSize_ = 0;
    kind_ = Kind_Player;
    parts_ = NULL;
    objects_ = NULL;
    effect_ = NULL;
    reload_ = 2;
    unk_30 = 0;
    triangles_ = 0;
    quads_ = 0;
    motion_ = -1;
    playing_ = 0;
    female_ = 0;
    skinColor_ = 0;
    hairColor_ = 0;
    eyeColor_ = 2;
    height_ = 0x1000;
    width_ = 0x1000;
    loop_ = 0x10;
    battle_ = 0;
    step_ = 0;
    viewer_ = NULL;
    weaponBone_ = 0;
    unk_54 = 0;
    unk_58 = 0;
}

int ViewObject::SetupFromEntry(CharacterViewer* viewer, ViewerEntry* entry)
{
    viewer_ = viewer;
    switch (viewer->page_)
    {
    case 4:
        if (entry->id_ == 0)
            kind_ = Kind_Player;
        else
            kind_ = Kind_Doll;
        break;
    case 11:
        kind_ = Kind_Npc;
        break;
    case 12:
        kind_ = Kind_Npc;
        break;
    case 6:
        kind_ = Kind_Monster;
        break;
    case 7:
        kind_ = Kind_Effect;
        break;
    case 13:
        kind_ = Kind_EventCamera;
        break;
    case 14:
        kind_ = Kind_SkillCamera;
        break;
    }
    return Allocate();
}

int ViewObject::SetupFromKind(CharacterViewer* viewer, unsigned int kind)
{
    viewer_ = viewer;
    switch (kind)
    {
    case 0:
        kind_ = Kind_Player;
        break;
    case 1:
        kind_ = Kind_Doll;
        break;
    case 2:
        kind_ = Kind_Monster;
        break;
    case 3:
        kind_ = Kind_Npc;
        break;
    case 4:
        kind_ = Kind_Npc;
        break;
    case 5:
        kind_ = Kind_EventCamera;
        break;
    case 6:
        kind_ = Kind_SkillCamera;
        break;
    case 7:
        kind_ = Kind_Effect;
        break;
    }
    return Allocate();
}

void ViewObject::Finish()
{
    int i;
    SafeAllocator* allocators = allocators_;
    if (allocators != NULL)
    {
        if (kind_ == Kind_Player || kind_ == Kind_Doll)
        {
            for (i = 0; i < 10; i++, allocators++)
            {
                SignedAllocatorHeader* buffer = allocators->GetSignedAllocator();
                allocators->Destroy();
                func_02012da4(&data_02114e20, buffer);
            }
        }
        else
        {
            SignedAllocatorHeader* buffer = allocators->GetSignedAllocator();
            allocators_->Destroy();
            func_02012da4(&data_02114e20, buffer);
        }
        func_02012da4(&data_02114e20, allocators_);
    }
    if (parts_ != NULL)
        func_02012da4(&data_02114e20, parts_);
    if (buffer_ != NULL)
        func_02012da4(&data_02114e20, buffer_);
    if (objects_ != NULL)
        func_02012da4(&data_02114e20, objects_);
    if (effect_ != NULL)
        func_02012da4(&data_02114e20, effect_);
    ViewerSlot* slot = slot_;
    if (slot != NULL)
        slot->used_ = 0;
    Initialize();
}

void ViewObject::Update()
{
    switch (kind_)
    {
    case Kind_Player:
        UpdatePlayer();
        break;
    case Kind_Doll:
        UpdateDoll();
        break;
    case Kind_Monster:
        UpdateMonster();
        break;
    case Kind_Npc:
        UpdateNpc();
        break;
    case Kind_Effect:
        UpdateEffect();
        break;
    case Kind_EventCamera:
        UpdateCamera();
        break;
    case Kind_SkillCamera:
        UpdateCamera();
        break;
    }
}

void ViewObject::Draw()
{
    switch (kind_)
    {
    case Kind_Player:
        DrawPlayer();
        break;
    case Kind_Doll:
        DrawDoll();
        break;
    case Kind_Monster:
        DrawMonster();
        break;
    case Kind_Npc:
        DrawNpc();
        break;
    case Kind_Effect:
        DrawEffect();
        break;
    }
}

int ViewObject::Load(ViewerEntry* entry)
{
    int result = 1;
    switch (kind_)
    {
    case Kind_Player:
        result = LoadPlayer();
        break;
    case Kind_Doll:
        result = LoadDoll();
        break;
    case Kind_Monster:
        result = LoadMonster(entry);
        break;
    case Kind_Npc:
        result = LoadNpc(entry);
        break;
    case Kind_Effect:
        result = LoadEffect(entry);
        break;
    case Kind_EventCamera:
        result = LoadCamera(entry);
        break;
    case Kind_SkillCamera:
        result = LoadCamera(entry);
        break;
    }
    return result;
}

void ViewObject::LoadMotion(const char* event)
{
    switch (kind_)
    {
    case Kind_Player:
        LoadPlayerAnimations(event);
        break;
    case Kind_Npc:
        LoadEventAnimation(event);
        break;
    case Kind_Monster:
        LoadEventAnimation(event);
        break;
    }
}

AnimationPackage* ViewObject::GetAnimationPackages()
{
    switch (kind_)
    {
    case Kind_Player:
    case Kind_Doll:
        return objects_[0].loadedAnimationPackageList_;
    default:
        return objects_->loadedAnimationPackageList_;
    }
}

void ViewObject::SetAnimation(const char* name)
{
    if (kind_ == Kind_Player || kind_ == Kind_Doll)
    {
        objects_[0].MaybeSetRegularAnimation(name, loop_ | 8);
        return;
    }
    objects_->MaybeSetRegularAnimation(name, loop_ | 8);
}

BCFG::AnimationRecord* ViewObject::GetAnimationRecord(const char* name)
{
    switch (kind_)
    {
    case Kind_Player:
    case Kind_Doll:
        return objects_[0].GetLoadedAnimationRecord(name);
    default:
        return objects_->GetLoadedAnimationRecord(name);
    }
}

float ViewObject::GetTime()
{
    switch (kind_)
    {
    case Kind_Player:
    case Kind_Doll:
        return objects_[0].animationTime_ / 4096.0f;
    default:
        return objects_->animationTime_ / 4096.0f;
    }
}

float ViewObject::GetProgress()
{
    switch (kind_)
    {
    case Kind_Player:
    case Kind_Doll:
        return objects_[0].normalizedAnimationTime_ / 4096.0f;
    default:
        return objects_->normalizedAnimationTime_ / 4096.0f;
    }
}

void ViewObject::Move(Vector3fix offset)
{
    Vector3fix position = {0};
    switch (kind_)
    {
    case Kind_Player:
        position = objects_[1].GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_[1].SetPosition(position);
        position = objects_[0].GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_[0].SetPosition(position);
        break;
    case Kind_Doll:
        position = objects_[6].GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_[6].SetPosition(position);
        position = objects_[1].GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_[1].SetPosition(position);
        position = objects_[5].GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_[5].SetPosition(position);
        position = objects_[0].GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_[0].SetPosition(position);
        break;
    default:
        position = objects_->GetPosition();
        Vector3fix_Add(&position, &offset, &position);
        objects_->SetPosition(position);
        break;
    }
}

void ViewObject::Turn(int angle)
{
    Vector3fix rotation = {0};
    switch (kind_)
    {
    case Kind_Player:
        rotation = objects_[1].GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_[1].SetRotation(rotation);
        rotation = objects_[0].GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_[0].SetRotation(rotation);
        break;
    case Kind_Doll:
        rotation = objects_[6].GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_[6].SetRotation(rotation);
        rotation = objects_[1].GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_[1].SetRotation(rotation);
        rotation = objects_[5].GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_[5].SetRotation(rotation);
        rotation = objects_[0].GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_[0].SetRotation(rotation);
        break;
    default:
        rotation = objects_->GetRotation();
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y + angle);
        objects_->SetRotation(rotation);
        break;
    }
}

// Draws a line of the info on the bottom screen
#define DRAW_TEXT(x, y, color)                                                                                         \
    {                                                                                                                  \
        memset(line, 0, sizeof(line));                                                                                 \
        MessageSystem* system = func_020421a0();                                                                       \
        char converted[0x40];                                                                                          \
        __clear(converted, sizeof(converted));                                                                         \
        func_02069fec(system, text, converted);                                                                        \
        func_02045d14(system, converted, line, 0);                                                                     \
        messages->unk_19b0 = 1;                                                                                        \
        func_02045f3c(messages, &line[1], x, y, color, 8, 0x14, 0, 1, 0x11);                                           \
    }

// NONMATCHING: the C matches 92.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The scheduling of the arguments of the text functions differs in a few lines (the register of the constant 0x11).
#ifdef NONMATCHING
void ViewObject::DrawMemory()
{
    char text[0x20];
    unsigned short line[0x20];

    MessageSystem* messages = func_020421a0();
    if (kind_ == Kind_Player || kind_ == Kind_Doll)
    {
        sprintf(text, STRING(0x1b4, "p\x81m\x8a\xe7\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[2].GetSizeWithLargestBlockRemoved(),
                allocators_[2].GetSize());
        DRAW_TEXT(0, 0, 0x7fff);
        sprintf(text, STRING(0x1ca, "p\x81m\x94\xaf\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[3].GetSizeWithLargestBlockRemoved(),
                allocators_[3].GetSize());
        DRAW_TEXT(0, 0xa, 0x7fff);
        sprintf(text, STRING(0x1e0, "p\x81m\x8a\x95\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[7].GetSizeWithLargestBlockRemoved(),
                allocators_[7].GetSize());
        DRAW_TEXT(0, 0x14, 0x7fff);
        sprintf(text, STRING(0x1f6, "p\x81m\x95\x9e\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[0].GetSizeWithLargestBlockRemoved(),
                allocators_[0].GetSize());
        DRAW_TEXT(0, 0x1e, 0x7fff);
        sprintf(text, STRING(0x20c, "p\x81m\x98r\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[5].GetSizeWithLargestBlockRemoved(),
                allocators_[5].GetSize());
        DRAW_TEXT(0, 0x28, 0x7fff);
        sprintf(text, STRING(0x222, "p\x81m\x83Y\x83\x7b\x83\x93\x81n\x81" "F%5d\x81^%5d"),
                allocators_[1].GetSizeWithLargestBlockRemoved(),
                allocators_[1].GetSize());
        DRAW_TEXT(0, 0x32, 0x7fff);
        sprintf(text, STRING(0x238, "p\x81m\x8c" "C\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[6].GetSizeWithLargestBlockRemoved(),
                allocators_[6].GetSize());
        DRAW_TEXT(0, 0x3c, 0x7fff);
        sprintf(text, STRING(0x24e, "p\x81m\x95\x90\x8a\xed\x81n\x81@\x81" "F%5d\x81^%5d"),
                allocators_[8].GetSizeWithLargestBlockRemoved(),
                allocators_[8].GetSize());
        DRAW_TEXT(0, 0x46, 0x7fff);
        sprintf(text, STRING(0x264, "p\x81m\x8f\x82\x81n\x81@\x81@\x81" "F%5d\x81^%5d"),
                allocators_[9].GetSizeWithLargestBlockRemoved(),
                allocators_[9].GetSize());
        DRAW_TEXT(0, 0x50, 0x7fff);
    }
    else
    {
        sprintf(text, STRING(0x27a, "p\x81m\x83\x81\x83\x82\x83\x8a\x81n\x81" "F%d\x81^%d"),
                allocators_->GetSizeWithLargestBlockRemoved(),
                allocators_->GetSize());
        DRAW_TEXT(0, 0, 0x7fff);
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv(); // SafeAllocator::GetSizeWithLargestBlockRemoved
    void _ZNK13SafeAllocator7GetSizeEv(); // SafeAllocator::GetSize
}

asm void ViewObject::DrawMemory()
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x2f8
    mov r5, r0
    bl func_020421a0
    ldrb r1, [r5, #0x1c]
    mov r4, r0
    ldr r0, [r5, #0x8]
    cmp r1, #0x0
    cmpne r1, #0x1
    bne @L0218fe94
    add r0, r0, #0x28
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    ldr r1, [r5, #0x8]
    mov r6, r0
    add r0, r1, #0x28
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x1b4
    add r0, sp, #0x2d8
    mov r2, r6
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x258
    mov r1, #0x40
    bl __clear
    mov r0, r6
    add r1, sp, #0x2d8
    add r2, sp, #0x258
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0x258
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r2, #0x0
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r0, #0x11
    add r1, sp, #0x200
    str r0, [sp, #0x14]
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, r2
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0x3c
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    add r0, r0, #0x3c
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x1ca
    mov r2, r6
    add r0, sp, #0x2d8
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x218
    mov r1, #0x40
    bl __clear
    add r1, sp, #0x2d8
    add r2, sp, #0x218
    mov r0, r6
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0x218
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r0, #0x11
    add r1, sp, #0x200
    str r0, [sp, #0x14]
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, #0xa
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0x8c
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    add r0, r0, #0x8c
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x1e0
    mov r2, r6
    add r0, sp, #0x2d8
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x1d8
    mov r1, #0x40
    bl __clear
    mov r0, r6
    add r1, sp, #0x2d8
    add r2, sp, #0x1d8
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0x1d8
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r3, #0x14
    str r3, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r6, #0x11
    add r1, sp, #0x200
    add r1, r1, #0x9a
    mov r0, r4
    str r6, [sp, #0x14]
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x1f6
    mov r2, r6
    add r0, sp, #0x2d8
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x198
    mov r1, #0x40
    bl __clear
    mov r0, r6
    add r1, sp, #0x2d8
    add r2, sp, #0x198
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0x198
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r0, #0x11
    add r1, sp, #0x200
    str r0, [sp, #0x14]
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, #0x1e
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0x64
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    add r0, r0, #0x64
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x20c
    add r0, sp, #0x2d8
    mov r2, r6
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x158
    mov r1, #0x40
    bl __clear
    mov r0, r6
    add r1, sp, #0x2d8
    add r2, sp, #0x158
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0x158
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r0, #0x11
    add r1, sp, #0x200
    str r0, [sp, #0x14]
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, #0x28
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0x14
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    add r0, r0, #0x14
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x222
    mov r2, r6
    add r0, sp, #0x2d8
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x118
    mov r1, #0x40
    bl __clear
    add r1, sp, #0x2d8
    add r2, sp, #0x118
    mov r0, r6
    bl func_02069fec
    add r1, sp, #0x118
    add r2, sp, #0x298
    mov r0, r6
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r3, #0x11
    add r1, sp, #0x200
    str r3, [sp, #0x14]
    add r1, r1, #0x9a
    mov r0, r4
    mov r3, #0x32
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0x78
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    add r0, r0, #0x78
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x238
    mov r2, r6
    add r0, sp, #0x2d8
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0xd8
    mov r1, #0x40
    bl __clear
    mov r0, r6
    add r1, sp, #0x2d8
    add r2, sp, #0xd8
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0xd8
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r0, #0x11
    add r1, sp, #0x200
    str r0, [sp, #0x14]
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, #0x3c
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0xa0
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    ldr r1, [r5, #0x8]
    mov r6, r0
    add r0, r1, #0xa0
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x24e
    add r0, sp, #0x2d8
    mov r2, r6
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r6, r0
    add r0, sp, #0x98
    mov r1, #0x40
    bl __clear
    mov r0, r6
    add r1, sp, #0x2d8
    add r2, sp, #0x98
    bl func_02069fec
    mov r0, r6
    add r1, sp, #0x98
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r1, #0x1
    add r0, r4, #0x1000
    strb r1, [r0, #0x9b0]
    rsb r0, r1, #0x8000
    str r0, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x14
    str r0, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r1, [sp, #0x10]
    mov r0, #0x11
    add r1, sp, #0x200
    str r0, [sp, #0x14]
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, #0x46
    bl func_02045f3c
    ldr r0, [r5, #0x8]
    add r0, r0, #0xb4
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    ldr r1, [r5, #0x8]
    mov r5, r0
    add r0, r1, #0xb4
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x264
    mov r2, r5
    add r0, sp, #0x2d8
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r5, r0
    add r0, sp, #0x58
    mov r1, #0x40
    bl __clear
    add r1, sp, #0x2d8
    add r2, sp, #0x58
    mov r0, r5
    bl func_02069fec
    mov r0, r5
    add r1, sp, #0x58
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r3, #0x1
    add r0, r4, #0x1000
    strb r3, [r0, #0x9b0]
    rsb r1, r3, #0x8000
    str r1, [sp, #0x0]
    mov r1, #0x8
    str r1, [sp, #0x4]
    mov r1, #0x14
    str r1, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r3, [sp, #0x10]
    mov r1, #0x11
    str r1, [sp, #0x14]
    add r1, sp, #0x200
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, #0x50
    bl func_02045f3c
    b @L0218ff4c
@L0218fe94:
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    mov r6, r0
    ldr r0, [r5, #0x8]
    bl _ZNK13SafeAllocator7GetSizeEv
    mov r3, r0
    ldr r1, =sStrings+0x27a
    add r0, sp, #0x2d8
    mov r2, r6
    bl sprintf
    add r0, sp, #0x298
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    bl func_020421a0
    mov r5, r0
    add r0, sp, #0x18
    mov r1, #0x40
    bl __clear
    mov r0, r5
    add r1, sp, #0x2d8
    add r2, sp, #0x18
    bl func_02069fec
    mov r0, r5
    add r1, sp, #0x18
    add r2, sp, #0x298
    mov r3, #0x0
    bl func_02045d14
    mov r3, #0x1
    add r0, r4, #0x1000
    strb r3, [r0, #0x9b0]
    rsb r1, r3, #0x8000
    str r1, [sp, #0x0]
    mov r1, #0x8
    str r1, [sp, #0x4]
    mov r1, #0x14
    str r1, [sp, #0x8]
    mov r2, #0x0
    str r2, [sp, #0xc]
    str r3, [sp, #0x10]
    mov r1, #0x11
    str r1, [sp, #0x14]
    add r1, sp, #0x200
    mov r0, r4
    add r1, r1, #0x9a
    mov r3, r2
    bl func_02045f3c
@L0218ff4c:
    add sp, sp, #0x2f8
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void ViewObject::SetPart(unsigned char part, int id)
{
    if (kind_ != Kind_Player && kind_ != Kind_Doll)
        return;
    if (id != parts_[part])
    {
        parts_[part] = id;
        reload_ = 1;
    }
}

void ViewObject::SetGender(unsigned char female)
{
    if (kind_ != Kind_Player && kind_ != Kind_Doll)
        return;
    if (female_ != female)
    {
        female_ = female;
        reload_ = 2;
    }
}

void ViewObject::SetSkinColor(unsigned char color)
{
    if (kind_ != Kind_Player && kind_ != Kind_Doll)
        return;
    if (skinColor_ != color)
    {
        skinColor_ = color;
        reload_ = 1;
    }
}

void ViewObject::SetEyeColor(unsigned char color)
{
    if (kind_ != Kind_Player && kind_ != Kind_Doll)
        return;
    if (eyeColor_ != color)
    {
        eyeColor_ = color;
        reload_ = 1;
    }
}

void ViewObject::SetHairColor(unsigned char color)
{
    if (kind_ != Kind_Player && kind_ != Kind_Doll)
        return;
    if (hairColor_ == color)
        return;
    objects_[4].unknown_2_ = -1;
    hairColor_ = color;
    reload_ = 1;
}

void ViewObject::SetBuild(short width, short height)
{
    if (kind_ != Kind_Player && kind_ != Kind_Doll)
        return;
    if (width_ == width && height_ == height)
        return;
    width_ = width;
    height_ = height;
    reload_ = 2;
}

void ViewObject::ToggleBattle()
{
    battle_++;
    battle_ %= 2;
    switch (kind_)
    {
    case Kind_Player:
        LoadPlayerAnimations(NULL);
        break;
    case Kind_Doll:
        LoadDollAnimations(NULL);
        break;
    }
}

void ViewObject::SaveStep()
{
    DebugMenuItem* item = func_0202a9ac(&viewer_->menuList_, motion_);
    if (item == NULL)
        return;
    BCFG::AnimationRecord* record = GetAnimationRecord(func_02029560(item));
    if (record != NULL)
        step_ = record->frameRate;
}

void ViewObject::SetStep(int step)
{
    DebugMenuItem* item = func_0202a9ac(&viewer_->menuList_, motion_);
    if (item == NULL)
        return;
    BCFG::AnimationRecord* record = GetAnimationRecord(func_02029560(item));
    if (record != NULL)
        record->frameRate = step;
}

void ViewObject::AddStep(int step)
{
    DebugMenuItem* item = func_0202a9ac(&viewer_->menuList_, motion_);
    if (item == NULL)
        return;
    BCFG::AnimationRecord* record = GetAnimationRecord(func_02029560(item));
    if (record == NULL)
        return;
    fix32_t start;
    fix32_t end = record->endTime;
    start = record->startTime;
    record->frameRate += step;
    if (record->frameRate < 0)
        record->frameRate = 0;
    if (record->frameRate > end - start)
        record->frameRate = end - start;
}

// The geometry engine's registers
#define REG_DISP3DCNT (*(volatile unsigned short*)0x04000060)
#define MTX_MODE (*(volatile int*)0x04000440)
#define GXFIFO_COLOR (*(volatile int*)0x04000480)
#define GXFIFO_VTX_10 (*(volatile int*)0x0400048c)
#define GXFIFO_POLYGON_ATTR (*(volatile int*)0x040004a4)
#define GXFIFO_BEGIN_VTXS (*(volatile int*)0x04000500)
#define GXFIFO_END_VTXS (*(volatile int*)0x04000504)

// The NitroSDK's OS_TicksToMicroSeconds
#define TICKS_TO_MICROSECONDS(ticks) (((ticks) * 64 * 1000) / 33514)

void CharacterViewer::Draw()
{
    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return;
    func_020c52e8();
    func_020c5414();
    RenderConfig::Reset();
    REG_DISP3DCNT = (REG_DISP3DCNT & ~0x3000) | 8;
    REG_DISP3DCNT = (REG_DISP3DCNT & ~0x3000) | 0x10;
    REG_DISP3DCNT = (REG_DISP3DCNT & ~0x3000) | 0x20;
    {
        EdgeColors colors = sEdgeColors;
        func_020c555c(colors.colors_);
    }
    ViewerCamera* camera = func_020100bc(gameState);
    if (camera != NULL)
        func_0202e0a4(camera);
    RenderConfig::SubmitToFifo();
    SendQueuedDataToGeometryFifo();
    DrawObjects();
    func_020c52e8();
    func_020c5414();
    MTX_MODE = 0;
    {
        Vector3fix target = sMenuTarget;
        Vector3fix eye = {0};
        Vector3fix up = sMenuUp;
        func_020c57d4(&eye, &up, &target, 1, NULL);
    }
    func_020c5770(0, 0xc0000, 0, 0x100000, -0x400000, 0x400000, 0x400000, 1, NULL);
    MTX_MODE = 2;
    DrawMenu();
    DrawInfo();
    func_020d86d0(1, 0);
    UpdateAndApplyBrightness((GameResources*)this);
}

void CharacterViewer::DrawObjects()
{
    if (floor_)
    {
        GXFIFO_POLYGON_ATTR = 0x1f00c0;
        MTX_PUSH = 0;
        GXFIFO_BEGIN_VTXS = 1;
        GXFIFO_COLOR = 0x5294;
        GXFIFO_VTX_10 = 0x3000;
        GXFIFO_VTX_10 = 0x3000;
        GXFIFO_VTX_10 = 0x3000;
        GXFIFO_VTX_10 = 0xd000;
        GXFIFO_VTX_10 = 0xd000;
        GXFIFO_VTX_10 = 0xd000;
        GXFIFO_VTX_10 = 0xd000;
        GXFIFO_VTX_10 = 0x3000;
        GXFIFO_END_VTXS = 0;
        MTX_POP = 1;
    }
    if (aspect_)
    {
        ViewerCamera* camera = func_020100bc(GameState::GetInstance());
        func_0208b610(camera->target_, 0x3dff, 0x800, 0x800, 0x800, 0);
    }
    for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
        node->object_->Draw();
}

void CharacterViewer::DrawMenu()
{
    if (!IsMenuChanged())
        return;
    func_02029060();
    if (menuList_.unk_6c != 2)
        redraw_ = 0;
    func_02028d58(unk_354);
    func_02029988(&menuList_, 1);
    menuList_.unk_70 = 0;
    func_02028d58(0);
    func_0202920c(0xf, 0x81, 0x17, 6, 0x9e);
    func_0202920c(1, 0x82, 0x18, 4, 0x9c);
    func_0202920c(0xf, 0x82, 24.0f + scrollBarStep_ * (int)menuList_.top_, 4, scrollBarSize_);
    DrawHelp();
    func_02029088();
    func_020bbcb4();
}

// Writes a text to a line of the info on the bottom screen
#define PREPARE_TEXT()                                                                                                 \
    {                                                                                                                  \
        memset(line, 0, sizeof(line));                                                                                 \
        MessageSystem* system = func_020421a0();                                                                       \
        char converted[0x40];                                                                                          \
        __clear(converted, sizeof(converted));                                                                         \
        func_02069fec(system, text, converted);                                                                        \
        func_02045d14(system, converted, line, 0);                                                                     \
    }

// Draws the line of the info
#define DRAW_LINE(x, y, color)                                                                                         \
    {                                                                                                                  \
        messages->unk_19b0 = 1;                                                                                        \
        func_02045f3c(messages, &line[1], x, y, color, 8, 0x14, 0, 1, 0x11);                                           \
    }

void CharacterViewer::DrawInfo()
{
    char text[0x20];
    unsigned short line[0x20];

    MessageSystem* messages = func_020421a0();
    sprintf(text, STRING(0x28e, "pFPS :%.2f"), fps_);
    PREPARE_TEXT();
    DRAW_LINE(0, 0xa0, 0x7fff);
    unsigned short triangles = 0;
    if (current_ != NULL)
        triangles = current_->triangles_;
    sprintf(text, STRING(0x299, "pT   :%d"), triangles);
    PREPARE_TEXT();
    DRAW_LINE(0, 0xaa, 0x7fff);
    unsigned short quads = 0;
    if (current_ != NULL)
        quads = current_->quads_;
    sprintf(text, STRING(0x2a2, "pQ   :%d"), quads);
    PREPARE_TEXT();
    messages->unk_19b0 = 1;
    if (quads != 0)
        func_02045f3c(messages, &line[1], 0, 0xb4, 0x1f, 8, 0x14, 0, 1, 0x11);
    else
        func_02045f3c(messages, &line[1], 0, 0xb4, 0x7fff, 8, 0x14, 0, 1, 0x11);
    if (menu_ == Menu_Motion)
    {
        DebugMenuItem* item = func_0202a9ac(&menuList_, current_->motion_);
        if (item == NULL)
            return;
        BCFG::AnimationRecord* record = current_->GetAnimationRecord(func_02029560(item));
        if (record == NULL)
            return;
        sprintf(text, STRING(0x2ab, "p\x81m%s\x81n"), record->name);
        PREPARE_TEXT();
        DRAW_LINE(0x96, 0x96, 0x7fff);
        sprintf(text, STRING(0x2b3, "pSTEP :%0.2f"), record->frameRate / 4096.0f);
        PREPARE_TEXT();
        DRAW_LINE(0xa0, 0xa0, 0x7fff);
        sprintf(text, STRING(0x2c0, "pFRAME:%0.2f"), current_->GetTime());
        PREPARE_TEXT();
        DRAW_LINE(0xa0, 0xaa, 0x7fff);
        sprintf(text, STRING(0x2cd, "pRATE :%0.3f"), current_->GetProgress());
        PREPARE_TEXT();
        DRAW_LINE(0xa0, 0xb4, 0x7fff);
    }
    if (viewMemory_ && current_ != NULL)
        current_->DrawMemory();
}

void CharacterViewer::DrawHelp()
{
    func_020290e8(0x87, 0xa, STRING(0x2da, "[Operation]"));
    func_020290e8(0x91, 0x18, STRING(0x2e6, "Select :u,d"));
    if (menu_ == Menu_Motion)
    {
        func_020290e8(0x91, 0x26, STRING(0x2f2, "Step   :R+r,l"));
        if (current_->loop_ == 0)
            func_020290e8(0x91, 0x34, STRING(0x300, "No Loop:L+A"));
        else
            func_020290e8(0x91, 0x34, STRING(0x30c, "Loop   :L+A"));
        if (current_->playing_)
        {
            func_020290e8(0x91, 0x42, STRING(0x318, "Play   :R+A"));
            func_020290e8(0x91, 0x50, STRING(0x324, "Scene  :R"));
            return;
        }
        func_020290e8(0x91, 0x42, STRING(0x32e, "Stop   :R+A"));
        return;
    }
    if (page_ == 0x22 || IsLookPage())
    {
        if (current_->battle_ == 0)
            func_020290e8(0x91, 0x26, STRING(0x33a, "Battle   :R"));
        else
            func_020290e8(0x91, 0x26, STRING(0x346, "No Battle:R"));
    }
    if (page_ != 6)
        return;
    if (field_)
    {
        func_020290e8(0x91, 0x26, STRING(0x352, "Battle :L"));
        return;
    }
    func_020290e8(0x91, 0x26, STRING(0x35c, "Field  :L"));
}

bool CharacterViewer::IsLookPage()
{
    switch (page_)
    {
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
        return true;
    default:
        return false;
    }
}

bool CharacterViewer::IsMenuChanged()
{
    if (redraw_)
        return true;
    if (!IsCameraMoving() && func_02012430(data_02114e30, PAD_KEY_UP | PAD_KEY_DOWN))
        return true;
    if (!IsCameraMoving() && func_02012468(data_02114e30, PAD_KEY_UP | PAD_KEY_DOWN))
        return true;
    return false;
}

bool CharacterViewer::IsPartPage()
{
    int page = page_;
    if (page == 17)
        return true;
    if (page == 20)
        return true;
    if (page == 23)
        return true;
    if (page == 24)
        return true;
    if (page == 25)
        return true;
    if (page == 26)
        return true;
    if (page == 27)
        return true;
    if (page == 28)
        return true;
    if (page == 22)
        return true;
    return false;
}

// NONMATCHING: the C matches 97.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original's switch on lastKind_ starts with a test of negative values that no form of the switch gave.
#ifdef NONMATCHING
void CharacterViewer::Update()
{
    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return;
    ViewerCamera* camera = func_020100bc(gameState);
    if (camera != NULL)
        func_020a20d8(camera);
    for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
        node->object_->Update();
    if (!func_02012444(data_02114e30, PAD_BUTTON_SELECT))
        return;
    int menu = menu_;
    menu_ = otherMenu_;
    otherMenu_ = menu;
    if (menu_ == Menu_Option)
    {
        PushPage(page_);
        page_ = 0x23;
    }
    else
    {
        int page;
        do
            page = PopPage();
        while (page >= 0x23);
        switch (lastKind_)
        {
        case ViewObject::Kind_Player:
        case ViewObject::Kind_Doll:
            while (page >= 0xf)
                page = PopPage();
            break;
        case ViewObject::Kind_Npc:
            while (page >= 0x21)
                page = PopPage();
            break;
        }
        lastKind_ = -1;
        if (menu_ == Menu_Motion)
            menu_ = Menu_Top;
        page_ = page;
    }
    OpenMenu(0);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10ViewObject6UpdateEv(); // ViewObject::Update
    void _ZN15CharacterViewer7PopPageEv(); // CharacterViewer::PopPage
    void _ZN15CharacterViewer8OpenMenuEi(); // CharacterViewer::OpenMenu
    void _ZN15CharacterViewer8PushPageEi(); // CharacterViewer::PushPage
}

asm void CharacterViewer::Update()
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r4, r0
    bl _ZN9GameState11GetInstanceEv
    cmp r0, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    bl func_020100bc
    cmp r0, #0x0
    beq @L02190da0
    bl func_020a20d8
@L02190da0:
    ldr r5, [r4, #0x2c]
    b @L02190db4
@L02190da8:
    ldr r0, [r5, #0x0]
    bl _ZN10ViewObject6UpdateEv
    ldr r5, [r5, #0x4]
@L02190db4:
    cmp r5, #0x0
    bne @L02190da8
    ldr r0, =data_02114e30
    mov r1, #0x4
    bl func_02012444
    cmp r0, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    ldr r1, [r4, #0x194]
    ldr r0, [r4, #0x198]
    str r0, [r4, #0x194]
    str r1, [r4, #0x198]
    ldr r0, [r4, #0x194]
    cmp r0, #0x2
    bne @L02190e04
    ldr r1, [r4, #0x1a4]
    mov r0, r4
    bl _ZN15CharacterViewer8PushPageEi
    mov r0, #0x23
    str r0, [r4, #0x1a4]
    b @L02190e74
@L02190e04:
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
    cmp r0, #0x23
    bge @L02190e04
    ldrsb r1, [r4, #0x38]
    cmp r1, #0x0
    blt @L02190e70
    cmpne r1, #0x1
    beq @L02190e3c
    cmp r1, #0x2
    beq @L02190e50
    b @L02190e58
@L02190e34:
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
@L02190e3c:
    cmp r0, #0xf
    bge @L02190e34
    b @L02190e58
@L02190e48:
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
@L02190e50:
    cmp r0, #0x21
    bge @L02190e48
@L02190e58:
    mvn r1, #0x0
    strb r1, [r4, #0x38]
    ldr r1, [r4, #0x194]
    cmp r1, #0x1
    moveq r1, #0x0
    streq r1, [r4, #0x194]
@L02190e70:
    str r0, [r4, #0x1a4]
@L02190e74:
    mov r0, r4
    mov r1, #0x0
    bl _ZN15CharacterViewer8OpenMenuEi
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

void CharacterViewer::UpdateTopMenu()
{
    if (IsCameraMoving())
        return;
    if (func_02012444(data_02114e30, PAD_BUTTON_A))
    {
        int index = menuList_.GetIndex();
        cursors_[page_] = index;
        switch (page_)
        {
        case 2:
            DeleteObject(index);
            return;
        case 3:
            SelectObject(index);
            return;
        case 40:
            LoadPreset(index);
            return;
        default:
        {
            int start = 0;
            FindEntry(page_, &start);
            index += start;
            ViewerEntry* entry = FindEntry(page_, &index);
            if (entry == NULL)
                break;
            if (entry->link_ != 0)
            {
                PushPage(page_);
                page_ = entry->link_;
                OpenMenu(0);
                return;
            }
            if (IsLookPage())
            {
                SetLook(index);
                return;
            }
            if (page_ == 0x21)
            {
                current_->LoadMotion(entry->file_);
                menu_ = Menu_Motion;
                OpenMenu(0);
                current_->motion_ = 0;
                current_->SaveStep();
                return;
            }
            if (func_02012430(data_02114e30, PAD_BUTTON_R))
            {
                ViewObjectNode* node = objects_;
                while (node != NULL)
                {
                    node->object_->Finish();
                    func_02012da4(&data_02114e20, node->object_);
                    ViewObjectNode* next = node;
                    node = node->next_;
                    func_02012da4(&data_02114e20, next);
                }
                objects_ = NULL;
            }
            ViewObject* object = AddObject(entry);
            if (object != NULL && !func_02012430(data_02114e30, PAD_BUTTON_L))
            {
                current_ = object;
                switch (object->kind_)
                {
                case ViewObject::Kind_Player:
                case ViewObject::Kind_Doll:
                    PushPage(page_);
                    page_ = 0x22;
                    OpenMenu(0);
                    return;
                case ViewObject::Kind_Npc:
                    PushPage(page_);
                    page_ = 0x21;
                    OpenMenu(0);
                    return;
                default:
                    menu_ = Menu_Motion;
                    OpenMenu(0);
                    current_->motion_ = 0;
                    current_->SaveStep();
                    return;
                }
            }
            break;
        }
        }
    }
    else if (func_02012444(data_02114e30, PAD_BUTTON_B))
    {
        if (page_ > 0)
        {
            cursors_[page_] = menuList_.GetIndex();
            if (page_ == 8)
                ResetCamera();
            int page = PopPage();
            if (page >= 0)
            {
                page_ = page;
                OpenMenu(0);
            }
        }
    }
    else
    {
        if (func_0201248c(data_02114e30, PAD_KEY_LEFT))
        {
            short first = menuList_.first_;
            int cursor = menuList_.cursor_ - 8;
            if (cursor < first)
                cursor = first;
            menuList_.cursor_ = cursor;
            redraw_ = 1;
            return;
        }
        if (func_0201248c(data_02114e30, PAD_KEY_RIGHT))
        {
            short last = menuList_.last_;
            int cursor = menuList_.cursor_ + 8;
            if (cursor > last)
                cursor = last;
            menuList_.cursor_ = cursor;
            redraw_ = 1;
            return;
        }
        if (func_02012444(data_02114e30, PAD_BUTTON_L))
        {
            if (page_ == 6)
            {
                field_ = field_ == 0;
                redraw_ = 1;
            }
        }
        else if (func_02012444(data_02114e30, PAD_BUTTON_R) && (page_ == 0x22 || IsLookPage()))
        {
            current_->ToggleBattle();
            redraw_ = 1;
        }
    }
}

int DebugMenu::GetIndex()
{
    return cursor_ - first_;
}

void CharacterViewer::UpdateMotionMenu()
{
    if (IsCameraMoving())
        return;
    if (func_02012468(data_02114e30, PAD_KEY_LEFT) || func_02012468(data_02114e30, PAD_KEY_RIGHT) ||
        func_02012468(data_02114e30, PAD_BUTTON_R))
    {
        repeatDelay_ = 0x1e;
        repeatTimer_ = 0;
    }
    if (func_02012444(data_02114e30, PAD_BUTTON_A))
    {
        if (func_02012430(data_02114e30, PAD_BUTTON_R))
        {
            ViewObject* current = current_;
            current->playing_ = current->playing_ == 0;
            redraw_ = 1;
            return;
        }
        if (func_02012430(data_02114e30, PAD_BUTTON_L))
        {
            ViewObject* current = current_;
            int loop = current->loop_;
            if (syncMotion_)
            {
                for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
                {
                    if (loop == 0)
                        node->object_->loop_ = 1;
                    else
                        node->object_->loop_ = 0;
                }
            }
            else if (loop == 0)
            {
                current->loop_ = 1;
            }
            else
            {
                current->loop_ = 0;
            }
        }
        current_->SetStep(current_->step_);
        current_->motion_ = menuList_.GetIndex();
        DebugMenuItem* item = func_0202a9ac(&menuList_, menuList_.GetIndex());
        if (item != NULL)
        {
            if (syncMotion_)
            {
                for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
                    node->object_->SetAnimation(func_02029560(item));
            }
            else
            {
                current_->SetAnimation(func_02029560(item));
            }
        }
        current_->SaveStep();
        redraw_ = 1;
        return;
    }
    if (func_02012444(data_02114e30, PAD_BUTTON_B))
    {
        current_->SetStep(current_->step_);
        current_->playing_ = 0;
        current_->motion_ = -1;
        current_->loop_ = 0;
        current_->step_ = 0;
        menu_ = Menu_Top;
        OpenMenu(0);
        return;
    }
    if (func_02012444(data_02114e30, PAD_BUTTON_R))
    {
        if (current_->playing_)
            redraw_ = 1;
        return;
    }
    if (func_0201248c(data_02114e30, PAD_KEY_LEFT))
    {
        if (func_02012430(data_02114e30, PAD_BUTTON_R))
        {
            current_->AddStep(-0x28);
        }
        else
        {
            short first = menuList_.first_;
            int cursor = menuList_.cursor_ - 8;
            if (cursor < first)
                cursor = first;
            menuList_.cursor_ = cursor;
        }
        redraw_ = 1;
        return;
    }
    if (func_0201248c(data_02114e30, PAD_KEY_RIGHT))
    {
        if (func_02012430(data_02114e30, PAD_BUTTON_R))
        {
            current_->AddStep(0x28);
        }
        else
        {
            short last = menuList_.last_;
            int cursor = menuList_.cursor_ + 8;
            if (cursor > last)
                cursor = last;
            menuList_.cursor_ = cursor;
        }
        redraw_ = 1;
        return;
    }
    if (func_02012430(data_02114e30, PAD_KEY_LEFT))
    {
        if (!func_02012430(data_02114e30, PAD_BUTTON_R))
            return;
        if (repeatTimer_ < repeatDelay_)
        {
            repeatTimer_++;
            return;
        }
        repeatTimer_ = 0;
        repeatDelay_ -= 10;
        current_->AddStep(-0x28);
        redraw_ = 1;
        return;
    }
    if (!func_02012430(data_02114e30, PAD_KEY_RIGHT))
        return;
    if (!func_02012430(data_02114e30, PAD_BUTTON_R))
        return;
    if (repeatTimer_ < repeatDelay_)
    {
        repeatTimer_++;
        return;
    }
    repeatTimer_ = 0;
    repeatDelay_ -= 10;
    current_->AddStep(0x28);
    redraw_ = 1;
}

// NONMATCHING: the C matches 97.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original's switch on lastKind_ starts with a test of negative values that no form of the switch gave.
#ifdef NONMATCHING
void CharacterViewer::UpdateOptionMenu()
{
    if (IsCameraMoving())
        return;
    if (page_ == 0x27)
        MoveSelected();
    if (func_02012444(data_02114e30, PAD_BUTTON_A))
    {
        int index = menuList_.GetIndex();
        cursors_[page_] = index;
        switch (page_)
        {
        case 0x24:
            PickObject(index);
            return;
        case 0x26:
            ToggleOption();
            return;
        case 0x25:
            MoveMenu(index);
            return;
        case 0x27:
            break;
        default:
        {
            int start = 0;
            FindEntry(page_, &start);
            index += start;
            ViewerEntry* entry = FindEntry(page_, &index);
            if (entry->link_ != 0)
            {
                PushPage(page_);
                page_ = entry->link_;
                OpenMenu(0);
                return;
            }
            break;
        }
        }
    }
    else if (func_02012444(data_02114e30, PAD_BUTTON_B))
    {
        if (page_ > 0x23)
        {
            cursors_[page_] = menuList_.GetIndex();
            page_ = PopPage();
            OpenMenu(0);
            return;
        }
        int menu = menu_;
        menu_ = otherMenu_;
        otherMenu_ = menu;
        int page;
        do
            page = PopPage();
        while (page >= 0x23);
        switch (lastKind_)
        {
        case ViewObject::Kind_Player:
        case ViewObject::Kind_Doll:
            while (page >= 0xf)
                page = PopPage();
            break;
        case ViewObject::Kind_Npc:
            while (page >= 0x21)
                page = PopPage();
            break;
        }
        lastKind_ = -1;
        if (menu_ == Menu_Motion)
            menu_ = Menu_Top;
        page_ = page;
        OpenMenu(0);
        selected_ = NULL;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN15CharacterViewer10PickObjectEi(); // CharacterViewer::PickObject
    void _ZN15CharacterViewer12MoveSelectedEv(); // CharacterViewer::MoveSelected
    void _ZN15CharacterViewer12ToggleOptionEv(); // CharacterViewer::ToggleOption
    void _ZN15CharacterViewer14IsCameraMovingEv(); // CharacterViewer::IsCameraMoving
    void _ZN15CharacterViewer8MoveMenuEi(); // CharacterViewer::MoveMenu
    void _ZN15CharacterViewer9FindEntryEiPi(); // CharacterViewer::FindEntry
    void _ZN9DebugMenu8GetIndexEv(); // DebugMenu::GetIndex
}

asm void CharacterViewer::UpdateOptionMenu()
{
    stmdb sp!, {r3, r4, r5, lr}
    sub sp, sp, #0x8
    mov r4, r0
    bl _ZN15CharacterViewer14IsCameraMovingEv
    cmp r0, #0x0
    bne @L02191868
    ldr r0, [r4, #0x1a4]
    cmp r0, #0x27
    bne @L02191694
    mov r0, r4
    bl _ZN15CharacterViewer12MoveSelectedEv
@L02191694:
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    beq @L02191780
    add r0, r4, #0x2c4
    bl _ZN9DebugMenu8GetIndexEv
    str r0, [sp, #0x4]
    ldr r1, [r4, #0x1a4]
    add r1, r4, r1, lsl #0x1
    add r1, r1, #0x200
    strh r0, [r1, #0x68]
    ldr r0, [r4, #0x1a4]
    sub r0, r0, #0x24
    cmp r0, #0x3
    addls pc, pc, r0, lsl #0x2
    b @L02191714
@L021916d8:
    b @L021916e8
    b @L02191704
    b @L021916f8
    b @L02191868
@L021916e8:
    ldr r1, [sp, #0x4]
    mov r0, r4
    bl _ZN15CharacterViewer10PickObjectEi
    b @L02191868
@L021916f8:
    mov r0, r4
    bl _ZN15CharacterViewer12ToggleOptionEv
    b @L02191868
@L02191704:
    ldr r1, [sp, #0x4]
    mov r0, r4
    bl _ZN15CharacterViewer8MoveMenuEi
    b @L02191868
@L02191714:
    mov r0, #0x0
    str r0, [sp, #0x0]
    ldr r1, [r4, #0x1a4]
    add r2, sp, #0x0
    mov r0, r4
    bl _ZN15CharacterViewer9FindEntryEiPi
    ldr r1, [sp, #0x4]
    ldr r0, [sp, #0x0]
    add r2, sp, #0x4
    add r0, r1, r0
    str r0, [sp, #0x4]
    ldr r1, [r4, #0x1a4]
    mov r0, r4
    bl _ZN15CharacterViewer9FindEntryEiPi
    mov r5, r0
    ldrb r0, [r5, #0xb]
    cmp r0, #0x0
    beq @L02191868
    ldr r1, [r4, #0x1a4]
    mov r0, r4
    bl _ZN15CharacterViewer8PushPageEi
    ldrb r2, [r5, #0xb]
    mov r0, r4
    mov r1, #0x0
    str r2, [r4, #0x1a4]
    bl _ZN15CharacterViewer8OpenMenuEi
    b @L02191868
@L02191780:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    beq @L02191868
    ldr r0, [r4, #0x1a4]
    cmp r0, #0x23
    ble @L021917d4
    add r0, r4, #0x2c4
    bl _ZN9DebugMenu8GetIndexEv
    ldr r1, [r4, #0x1a4]
    add r1, r4, r1, lsl #0x1
    add r1, r1, #0x200
    strh r0, [r1, #0x68]
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
    str r0, [r4, #0x1a4]
    mov r0, r4
    mov r1, #0x0
    bl _ZN15CharacterViewer8OpenMenuEi
    b @L02191868
@L021917d4:
    ldr r1, [r4, #0x194]
    ldr r0, [r4, #0x198]
    str r0, [r4, #0x194]
    str r1, [r4, #0x198]
@L021917e4:
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
    cmp r0, #0x23
    bge @L021917e4
    ldrsb r1, [r4, #0x38]
    cmp r1, #0x0
    blt @L02191850
    cmpne r1, #0x1
    beq @L0219181c
    cmp r1, #0x2
    beq @L02191830
    b @L02191838
@L02191814:
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
@L0219181c:
    cmp r0, #0xf
    bge @L02191814
    b @L02191838
@L02191828:
    mov r0, r4
    bl _ZN15CharacterViewer7PopPageEv
@L02191830:
    cmp r0, #0x21
    bge @L02191828
@L02191838:
    mvn r1, #0x0
    strb r1, [r4, #0x38]
    ldr r1, [r4, #0x194]
    cmp r1, #0x1
    moveq r1, #0x0
    streq r1, [r4, #0x194]
@L02191850:
    str r0, [r4, #0x1a4]
    mov r0, r4
    mov r1, #0x0
    bl _ZN15CharacterViewer8OpenMenuEi
    mov r0, #0x0
    str r0, [r4, #0x34]
@L02191868:
    add sp, sp, #0x8
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

void CharacterViewer::MoveSelected()
{
    if (selected_ == NULL)
        return;
    GameState::GetInstance();
    Vector3fix move = {0};
    Matrix3x3 view;
    if (func_02012430(data_02114e30, PAD_KEY_UP))
        move.z = -0x199;
    if (func_02012430(data_02114e30, PAD_KEY_DOWN))
        move.z = 0x199;
    if (func_02012430(data_02114e30, PAD_KEY_RIGHT))
        move.x = 0x199;
    if (func_02012430(data_02114e30, PAD_KEY_LEFT))
        move.x = -0x199;
    memcpy(&view, RenderConfig::GetInverseViewMatrix(), sizeof(view));
    Mat3x3_ApplyToVector(&move, &view, &move);
    move.y = 0;
    Vector3fix_Normalize(&move, &move);
    Vector3fixMultiplyScalar(&move, 0x199, &move);
    if (func_02012430(data_02114e30, PAD_BUTTON_X))
        move.y += 0x199;
    if (func_02012430(data_02114e30, PAD_BUTTON_Y))
        move.y -= 0x199;
    selected_->Move(move);
    if (func_02012430(data_02114e30, PAD_BUTTON_L))
        selected_->Turn(0x199);
    if (func_02012430(data_02114e30, PAD_BUTTON_R))
        selected_->Turn(-0x199);
}

ViewObject* CharacterViewer::AddObject(ViewerEntry* entry)
{
    ViewObjectNode* node = (ViewObjectNode*)func_02012d88(&data_02114e20, sizeof(ViewObjectNode));
    if (node == NULL)
        return NULL;
    node->object_ = NULL;
    node->next_ = NULL;
    ViewObject* object = node->object_ = (ViewObject*)func_02012d88(&data_02114e20, sizeof(ViewObject));
    if (object == NULL)
    {
        func_02012da4(&data_02114e20, node);
        return NULL;
    }
    object->Initialize();
    if (!object->SetupFromEntry(this, entry))
    {
        func_02012da4(&data_02114e20, node->object_);
        node->object_ = NULL;
        func_02012da4(&data_02114e20, node);
        return NULL;
    }
    if (!object->Load(entry))
    {
        node->object_->Finish();
        func_02012da4(&data_02114e20, node->object_);
        node->object_ = NULL;
        func_02012da4(&data_02114e20, node);
        return NULL;
    }
    ViewObjectNode** last = &objects_;
    while (*last != NULL)
        last = &(*last)->next_;
    *last = node;
    return node->object_;
}

void CharacterViewer::DeleteObject(int index)
{
    ViewObjectNode* node = objects_;
    if (node == NULL)
        return;
    int i = 0;
    ViewObjectNode* previous = NULL;
    ViewObjectNode* next = node->next_;
    for (; i < index; i++)
    {
        previous = node;
        node = next;
        next = next->next_;
    }
    node->object_->Finish();
    func_02012da4(&data_02114e20, node->object_);
    func_02012da4(&data_02114e20, node);
    if (previous != NULL)
        previous->next_ = next;
    else
        objects_ = next;
    unsigned short count = menuList_.count_;
    if (count - 1 <= cursors_[2])
    {
        cursors_[2] = count - 2;
        if (cursors_[2] < 0)
            cursors_[2] = 0;
    }
    OpenMenu(0);
}

void CharacterViewer::SelectObject(int index)
{
    ViewObjectNode* node = objects_;
    if (node == NULL)
        return;
    for (int i = 0; i < index; i++)
        node = node->next_;
    if (node == NULL)
        return;
    current_ = node->object_;
    switch (node->object_->kind_)
    {
    case ViewObject::Kind_Player:
    case ViewObject::Kind_Doll:
        PushPage(page_);
        page_ = 0x22;
        OpenMenu(0);
        return;
    case ViewObject::Kind_Npc:
        PushPage(page_);
        page_ = 0x21;
        OpenMenu(0);
        return;
    default:
        menu_ = Menu_Motion;
        OpenMenu(0);
        current_->motion_ = 0;
        current_->SaveStep();
        return;
    }
}

// NONMATCHING: the C matches 92.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original tests kinds 8, 9 and 10 with three compares, where the compiler subtracts 8 and compares the range.
#ifdef NONMATCHING
void CharacterViewer::LoadPreset(int index)
{
    ViewerPreset* preset = config_.GetPreset(index);
    if (preset == NULL)
        return;
    if (func_02012430(data_02114e30, PAD_BUTTON_R))
    {
        ViewObjectNode* node = objects_;
        while (node != NULL)
        {
            node->object_->Finish();
            func_02012da4(&data_02114e20, node->object_);
            ViewObjectNode* next = node;
            node = node->next_;
            func_02012da4(&data_02114e20, next);
        }
        objects_ = NULL;
    }
    ViewerPresetItem* item = preset->items_;
    int page;
    ViewObject* object = NULL;
    while (item != NULL)
    {
        int kind = item->kind_;
        page = page_;
        if (kind == 8 || kind == 9 || kind == 10)
        {
            switch (item->kind_)
            {
            case 10:
                page_ = 0x20;
                break;
            case 8:
                page_ = 0x1e;
                break;
            case 9:
                page_ = 0x1f;
                break;
            }
            if (object != NULL)
                object->LoadMotion(item->file_);
            page_ = page;
        }
        else if (item->kind_ == 11)
        {
            if (object != NULL)
                object->LoadMotion(item->file_);
        }
        else
        {
            ViewObjectNode* node = (ViewObjectNode*)func_02012d88(&data_02114e20, sizeof(ViewObjectNode));
            if (node == NULL)
                return;
            node->object_ = NULL;
            node->next_ = NULL;
            object = node->object_ = (ViewObject*)func_02012d88(&data_02114e20, sizeof(ViewObject));
            if (object == NULL)
            {
                func_02012da4(&data_02114e20, node);
                return;
            }
            object->Initialize();
            if (!object->SetupFromKind(this, item->kind_))
            {
                func_02012da4(&data_02114e20, node->object_);
                node->object_ = NULL;
                func_02012da4(&data_02114e20, node);
                return;
            }
            ViewerEntry entry;
            entry.name_ = NULL;
            entry.file_ = NULL;
            entry.id_ = 0;
            entry.page_ = 0;
            entry.link_ = 0;
            entry.name_ = item->file_;
            entry.file_ = item->file_;
            entry.id_ = item->id_;
            if (!object->Load(&entry))
            {
                node->object_->Finish();
                func_02012da4(&data_02114e20, node->object_);
                node->object_ = NULL;
                func_02012da4(&data_02114e20, node);
                return;
            }
            ViewObjectNode** last = &objects_;
            while (*last != NULL)
                last = &(*last)->next_;
            *last = node;
        }
        item = item->next_;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10ViewObject10InitializeEv(); // ViewObject::Initialize
    void _ZN10ViewObject10LoadMotionEPKc(); // ViewObject::LoadMotion
    void _ZN10ViewObject13SetupFromKindEP15CharacterViewerj(); // ViewObject::SetupFromKind
    void _ZN10ViewObject4LoadEP11ViewerEntry(); // ViewObject::Load
    void _ZN10ViewObject6FinishEv(); // ViewObject::Finish
    void _ZN12ViewerConfig9GetPresetEi(); // ViewerConfig::GetPreset
}

asm void CharacterViewer::LoadPreset(int index)
{
    stmdb sp!, {r4, r5, r6, r7, lr}
    sub sp, sp, #0xc
    mov r7, r0
    add r0, r7, #0x3c
    bl _ZN12ViewerConfig9GetPresetEi
    movs r5, r0
    beq @L02191e94
    ldr r0, =data_02114e30
    mov r1, #0x100
    bl func_02012430
    cmp r0, #0x0
    beq @L02191ce0
    ldr r6, [r7, #0x2c]
    ldr r4, =data_02114e20
    b @L02191cd0
@L02191cac:
    ldr r0, [r6, #0x0]
    bl _ZN10ViewObject6FinishEv
    ldr r1, [r6, #0x0]
    mov r0, r4
    bl func_02012da4
    mov r1, r6
    mov r0, r4
    ldr r6, [r6, #0x4]
    bl func_02012da4
@L02191cd0:
    cmp r6, #0x0
    bne @L02191cac
    mov r0, #0x0
    str r0, [r7, #0x2c]
@L02191ce0:
    ldr r4, [r5, #0x4]
    mov r6, #0x0
    b @L02191e8c
@L02191cec:
    ldrb r0, [r4, #0x6]
    ldr r5, [r7, #0x1a4]
    cmp r0, #0x8
    cmpne r0, #0x9
    cmpne r0, #0xa
    bne @L02191d54
    cmp r0, #0x8
    beq @L02191d24
    cmp r0, #0x9
    beq @L02191d30
    cmp r0, #0xa
    moveq r0, #0x20
    streq r0, [r7, #0x1a4]
    b @L02191d38
@L02191d24:
    mov r0, #0x1e
    str r0, [r7, #0x1a4]
    b @L02191d38
@L02191d30:
    mov r0, #0x1f
    str r0, [r7, #0x1a4]
@L02191d38:
    cmp r6, #0x0
    beq @L02191d4c
    ldr r1, [r4, #0x0]
    mov r0, r6
    bl _ZN10ViewObject10LoadMotionEPKc
@L02191d4c:
    str r5, [r7, #0x1a4]
    b @L02191e88
@L02191d54:
    cmp r0, #0xb
    bne @L02191d74
    cmp r6, #0x0
    beq @L02191e88
    ldr r1, [r4, #0x0]
    mov r0, r6
    bl _ZN10ViewObject10LoadMotionEPKc
    b @L02191e88
@L02191d74:
    ldr r0, =data_02114e20
    mov r1, #0x8
    bl func_02012d88
    movs r5, r0
    beq @L02191e94
    mov r2, #0x0
    str r2, [r5, #0x0]
    ldr r0, =data_02114e20
    mov r1, #0x5c
    str r2, [r5, #0x4]
    bl func_02012d88
    movs r6, r0
    str r0, [r5, #0x0]
    bne @L02191dbc
    ldr r0, =data_02114e20
    mov r1, r5
    bl func_02012da4
    b @L02191e94
@L02191dbc:
    bl _ZN10ViewObject10InitializeEv
    ldrb r2, [r4, #0x6]
    mov r0, r6
    mov r1, r7
    bl _ZN10ViewObject13SetupFromKindEP15CharacterViewerj
    cmp r0, #0x0
    bne @L02191dfc
    ldr r1, [r5, #0x0]
    ldr r0, =data_02114e20
    bl func_02012da4
    mov r2, #0x0
    ldr r0, =data_02114e20
    mov r1, r5
    str r2, [r5, #0x0]
    bl func_02012da4
    b @L02191e94
@L02191dfc:
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    strh r0, [sp, #0x8]
    strb r0, [sp, #0xa]
    strb r0, [sp, #0xb]
    ldr r0, [r4, #0x0]
    add r1, sp, #0x0
    str r0, [sp, #0x0]
    ldr r2, [r4, #0x0]
    mov r0, r6
    str r2, [sp, #0x4]
    ldrh r2, [r4, #0x4]
    strh r2, [sp, #0x8]
    bl _ZN10ViewObject4LoadEP11ViewerEntry
    cmp r0, #0x0
    bne @L02191e6c
    ldr r0, [r5, #0x0]
    bl _ZN10ViewObject6FinishEv
    ldr r1, [r5, #0x0]
    ldr r0, =data_02114e20
    bl func_02012da4
    mov r2, #0x0
    ldr r0, =data_02114e20
    mov r1, r5
    str r2, [r5, #0x0]
    bl func_02012da4
    b @L02191e94
@L02191e6c:
    add r0, r7, #0x2c
    b @L02191e78
@L02191e74:
    add r0, r1, #0x4
@L02191e78:
    ldr r1, [r0, #0x0]
    cmp r1, #0x0
    bne @L02191e74
    str r5, [r0, #0x0]
@L02191e88:
    ldr r4, [r4, #0x8]
@L02191e8c:
    cmp r4, #0x0
    bne @L02191cec
@L02191e94:
    add sp, sp, #0xc
    ldmia sp!, {r4, r5, r6, r7, pc}
}
#endif

void CharacterViewer::PickObject(int index)
{
    int i;
    ViewObjectNode* node = objects_;
    if (node == NULL)
        return;
    for (i = 0; i < index; i++)
        node = node->next_;
    if (node == NULL)
        return;
    selected_ = node->object_;
    PushPage(page_);
    page_ = 0x25;
    OpenMenu(0);
}

void CharacterViewer::ToggleOption()
{
    int index = menuList_.GetIndex();
    DebugMenuItem* item = func_0202a9ac(&menuList_, menuList_.cursor_);
    switch (index)
    {
    case 0:
    {
        aspect_ = !aspect_;
        if (aspect_)
            func_020294cc(item, STRING(0x366, "[*]Aspect"));
        else
            func_020294cc(item, STRING(0x370, "[-]Aspect"));
        break;
    }
    case 1:
        floor_ = floor_ == 0;
        func_020294cc(item, STRING(0x37a, "[-]Floor"));
        break;
    case 2:
    {
        monsterBox_ = !monsterBox_;
        if (monsterBox_)
            func_020294cc(item, STRING(0x383, "[*]Monster Box"));
        else
            func_020294cc(item, STRING(0x392, "[-]Monster Box"));
        break;
    }
    case 3:
    {
        syncMotion_ = !syncMotion_;
        if (syncMotion_)
            func_020294cc(item, STRING(0x3a1, "[*]Sync Motion"));
        else
            func_020294cc(item, STRING(0x3b0, "[-]Sync Motion"));
        break;
    }
    case 4:
    {
        viewMemory_ = !viewMemory_;
        if (viewMemory_)
            func_020294cc(item, STRING(0x3bf, "[*]View Memory"));
        else
            func_020294cc(item, STRING(0x3ce, "[-]View Memory"));
        break;
    }
    }
    redraw_ = 1;
}

void CharacterViewer::MoveMenu(int choice)
{
    ViewObject* selected = selected_;
    if (selected == NULL)
        return;
    switch (choice)
    {
    case 0:
        PushPage(page_);
        page_ = 0x27;
        OpenMenu(0);
        return;
    case 1:
    {
        ViewObjectNode* node = objects_;
        ViewObjectNode* previous = NULL;
        while (node != NULL)
        {
            if (node->object_ == selected)
                break;
            previous = node;
            node = node->next_;
        }
        if (node != NULL)
        {
            ViewObjectNode* next = node->next_;
            node->object_->Finish();
            func_02012da4(&data_02114e20, node->object_);
            func_02012da4(&data_02114e20, node);
            if (previous != NULL)
                previous->next_ = next;
            else
                objects_ = next;
            ViewObject* current = current_;
            if (selected_ == current)
            {
                lastKind_ = current->kind_;
                current_ = NULL;
            }
            selected_ = NULL;
        }
        cursors_[0x24] = 0;
        page_ = PopPage();
        OpenMenu(0);
        return;
    }
    }
}

void CharacterViewer::SetLook(int index)
{
    if (current_ == NULL)
        return;
    int position = index;
    int setPart;
    int part;
    ViewerEntry* entry = FindEntry(page_, &position);
    setPart = 0;
    part = 0;
    switch (page_)
    {
    case 15:
        current_->SetGender(entry->id_);
        break;
    case 17:
        part = 2;
        setPart = 1;
        break;
    case 18:
        setPart = 1;
        break;
    case 19:
        setPart = 1;
        break;
    case 21:
        setPart = 1;
        break;
    case 25:
        part = 1;
        setPart = 1;
        break;
    case 27:
        part = 8;
        setPart = 1;
        break;
    case 28:
        part = 9;
        setPart = 1;
        break;
    case 22:
        part = 7;
        setPart = 1;
        break;
    case 20:
        part = 3;
        setPart = 1;
        break;
    case 24:
        part = 5;
        setPart = 1;
        break;
    case 26:
        part = 6;
        setPart = 1;
        break;
    case 23:
        setPart = 1;
        break;
    case 16:
        setPart = 1;
        break;
    case 30:
    case 31:
    case 32:
        current_->LoadMotion(entry->file_);
        menu_ = Menu_Motion;
        OpenMenu(0);
        current_->motion_ = 0;
        current_->SaveStep();
        break;
    }
    if (!setPart)
        return;
    for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
    {
        if (page_ == 18)
        {
            node->object_->SetSkinColor(entry->id_);
        }
        else if (page_ == 19)
        {
            node->object_->SetEyeColor(entry->id_);
        }
        else if (page_ == 21)
        {
            node->object_->SetHairColor(entry->id_);
        }
        else if (page_ == 20)
        {
            node->object_->SetPart(part, entry->id_);
            node->object_->SetPart(4, entry->id_);
        }
        else if (page_ == 23)
        {
            node->object_->SetPart(part, entry->id_);
            PartEntry* skin = func_020deda4(&parts_, 0x61, func_020dedd0(&parts_, node->object_->parts_[0]));
            if (skin != NULL)
                node->object_->SetPart(5, skin->unk_18);
            else
                node->object_->SetPart(5, 0x36b0);
        }
        else if (page_ == 16)
        {
            if (current_->female_ == 0)
            {
                switch (entry->id_)
                {
                case 0:
                    node->object_->SetBuild(0xeb8, 0x109f);
                    break;
                case 1:
                    node->object_->SetBuild(0xe35, 0x1028);
                    break;
                case 2:
                    node->object_->SetBuild(0xf0a, 0xfae);
                    break;
                case 3:
                    node->object_->SetBuild(0x1024, 0xf33);
                    break;
                case 4:
                    node->object_->SetBuild(0xf1e, 0xeb4);
                    break;
                }
            }
            else
            {
                switch (entry->id_)
                {
                case 0:
                    node->object_->SetBuild(0xeb8, 0x1051);
                    break;
                case 1:
                    node->object_->SetBuild(0xe39, 0xffb);
                    break;
                case 2:
                    node->object_->SetBuild(0xee1, 0xf85);
                    break;
                case 3:
                    node->object_->SetBuild(0x1024, 0xf33);
                    break;
                case 4:
                    node->object_->SetBuild(0xeb8, 0xeb4);
                    break;
                }
            }
        }
        else
        {
            node->object_->SetPart(part, entry->id_);
        }
    }
}

void CharacterViewer::ResetCamera()
{
    int x;
    int y;
    int z;

    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return;
    ViewerCamera* camera = func_020100cc(gameState);
    if (camera == NULL)
        return;
    func_020a2cf0(camera);
    func_020a3568(camera, 2);
    func_0202e7d4(camera, &x, &y, &z);
    func_0202e5d8(camera, x, 0x13d7, z);
}

bool CharacterViewer::IsCameraMoving()
{
    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return false;
    ViewerCamera* camera = func_020100bc(gameState);
    if (camera == NULL)
        return false;
    if (func_02012430(data_02114e30, PAD_BUTTON_X | PAD_BUTTON_Y))
    {
        func_020a2794(camera);
        return true;
    }
    func_020a27a0(camera);
    return false;
}

void CharacterViewer::InitializeVRAM()
{
    VRAMSizes sizes = sVRAMSizes;
    for (int i = 0; i < 4; i++)
    {
        playerSlots_[i].states_ = (VRAMManagerState*)func_02012d88(&data_02114e20, 10 * sizeof(VRAMManagerState));
        dollSlots_[i].states_ = (VRAMManagerState*)func_02012d88(&data_02114e20, 10 * sizeof(VRAMManagerState));
        ViewerSlot* slot = &slots_[i];
        slot->states_ = (VRAMManagerState*)func_02012d88(&data_02114e20, sizeof(VRAMManagerState));
        for (int j = 0; j < 10; j++)
        {
            func_0207de48(&playerSlots_[i].states_[j], sizes.sizes_[j][0], sizes.sizes_[j][1]);
            func_0207de48(&dollSlots_[i].states_[j], sizes.sizes_[j][2], sizes.sizes_[j][3]);
        }
        func_0207de48(slots_[i].states_, 0x4000, 0x400);
    }
    func_0207de48(&vramState_, 0x4000, 0x40);
}

// NONMATCHING: the C matches 98.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The scheduling of two loads of items_ and of the increment of the entries' index differs.
#ifdef NONMATCHING
void CharacterViewer::OpenMenu(int unk)
{
    char title[0x80];
    char name[0x100];
    char option[0x80];
    int index;
    int count;
    ViewerEntry* entry;

    if (items_ != NULL)
    {
        func_02012da4(&data_02114e20, items_);
        items_ = NULL;
    }
    unk_354 = unk;
    __clear(title, sizeof(title));
    func_0202a91c(&menuList_);
    func_02029568(&menuList_);
    menuList_.flags_ |= 6;
    if (menu_ == Menu_Top || menu_ == Menu_Option)
    {
        switch (page_)
        {
        case 0:
            func_020294cc(&menuList_.title_, STRING(0x3dd, "[Top Menu]"));
            break;
        case 1:
            func_020294cc(&menuList_.title_, STRING(0x3e8, "[Load]"));
            break;
        case 2:
            func_020294cc(&menuList_.title_, STRING(0x3ef, "[Del]"));
            break;
        case 3:
            func_020294cc(&menuList_.title_, STRING(0x2da, "[Operation]"));
            break;
        case 4:
            func_020294cc(&menuList_.title_, STRING(0x3f5, "[Player]"));
            break;
        case 6:
            func_020294cc(&menuList_.title_, STRING(0x3fe, "[Monster]"));
            break;
        case 7:
            func_020294cc(&menuList_.title_, STRING(0x408, "[Effect]"));
            break;
        case 5:
            func_020294cc(&menuList_.title_, STRING(0x411, "[NPC]"));
            break;
        case 8:
            func_020294cc(&menuList_.title_, STRING(0x417, "[Motion Camera]"));
            break;
        case 15:
            func_020294cc(&menuList_.title_, STRING(0x427, "[Gender]"));
            break;
        case 17:
            func_020294cc(&menuList_.title_, STRING(0x430, "[Face]"));
            break;
        case 18:
            func_020294cc(&menuList_.title_, STRING(0x437, "[Eye Colour]"));
            break;
        case 19:
            func_020294cc(&menuList_.title_, STRING(0x444, "[Skin Colour]"));
            break;
        case 20:
            func_020294cc(&menuList_.title_, STRING(0x452, "[Hairstyle]"));
            break;
        case 21:
            func_020294cc(&menuList_.title_, STRING(0x45e, "[Hair Colour]"));
            break;
        case 23:
            func_020294cc(&menuList_.title_, STRING(0x46c, "[\x82\xe6\x82\xeb\x82\xa2]"));
            break;
        case 24:
            func_020294cc(&menuList_.title_, STRING(0x475, "[\x98r]"));
            break;
        case 25:
            func_020294cc(&menuList_.title_, STRING(0x47a, "[\x83Y\x83\x7b\x83\x93]"));
            break;
        case 26:
            func_020294cc(&menuList_.title_, STRING(0x483, "[\x82\xad\x82\xc2]"));
            break;
        case 27:
            func_020294cc(&menuList_.title_, STRING(0x48a, "[\x95\x90\x8a\xed]"));
            break;
        case 28:
            func_020294cc(&menuList_.title_, STRING(0x491, "[\x8f\x82]"));
            break;
        case 22:
            func_020294cc(&menuList_.title_, STRING(0x496, "[\x8a\x95]"));
            break;
        case 29:
            func_020294cc(&menuList_.title_, STRING(0x49b, "[Add Motion]"));
            break;
        case 30:
            func_020294cc(&menuList_.title_, STRING(0x4a8, "[Event Motion]"));
            break;
        case 31:
            func_020294cc(&menuList_.title_, STRING(0x4b7, "[Skill Motion]"));
            break;
        case 16:
            func_020294cc(&menuList_.title_, STRING(0x4c6, "[Build]"));
            break;
        case 11:
            func_020294cc(&menuList_.title_, STRING(0x4ce, "[Event]"));
            break;
        case 12:
            func_020294cc(&menuList_.title_, STRING(0x4d6, "[Villager]"));
            break;
        case 33:
            func_020294cc(&menuList_.title_, STRING(0x4e1, "[NPC Motion]"));
            break;
        case 32:
            func_020294cc(&menuList_.title_, STRING(0x4ee, "[Trick Motion]"));
            break;
        case 13:
            func_020294cc(&menuList_.title_, STRING(0x4fd, "[Event Camera]"));
            break;
        case 14:
            func_020294cc(&menuList_.title_, STRING(0x50c, "[Skill Camera]"));
            break;
        case 34:
            func_020294cc(&menuList_.title_, STRING(0x2da, "[Operation]"));
            break;
        case 35:
            func_020294cc(&menuList_.title_, STRING(0x51b, "[Option]"));
            break;
        case 36:
            func_020294cc(&menuList_.title_, STRING(0x2da, "[Operation]"));
            break;
        case 38:
            func_020294cc(&menuList_.title_, STRING(0x524, "[Info]"));
            break;
        case 39:
            func_020294cc(&menuList_.title_, STRING(0x52b, "[Move]"));
            break;
        case 40:
            func_020294cc(&menuList_.title_, STRING(0x532, "[Preset]"));
            break;
        case 37:
            if (selected_ != NULL)
                sprintf(title, STRING(0x53b, "[%s]"), selected_->name_);
            func_020294cc(&menuList_.title_, title);
            break;
        }
        count = 0;
        if (page_ == 2 || page_ == 3 || page_ == 36)
        {
            for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
                count++;
            if (count == 0)
                items_ = (DebugMenuItem*)func_02012d88(&data_02114e20, sizeof(DebugMenuItem));
            else
                items_ = (DebugMenuItem*)func_02012d88(&data_02114e20, count * sizeof(DebugMenuItem));
            if (count == 0)
            {
                func_0202949c(items_);
                func_020294cc(items_, func_020e51cc(1000));
                func_0202a944(&menuList_, items_);
                count = 1;
            }
            else
            {
                count = 0;
                for (ViewObjectNode* node = objects_; node != NULL; node = node->next_)
                {
                    func_0202949c(&items_[count]);
                    func_020294cc(&items_[count], node->object_->name_);
                    func_0202a944(&menuList_, &items_[count]);
                    count++;
                }
            }
        }
        else if (page_ == 40)
        {
            items_ = (DebugMenuItem*)func_02012d88(&data_02114e20, config_.presetCount_ * sizeof(DebugMenuItem));
            for (; count < config_.presetCount_; count++)
            {
                ViewerPreset* preset = config_.GetPreset(count);
                func_0202949c(&items_[count]);
                func_020294cc(&items_[count], preset->name_);
                func_0202a944(&menuList_, &items_[count]);
            }
        }
        else
        {
            index = 0;
            for (entry = FindEntry(page_, &index); entry != NULL; entry = FindEntry(page_, &index))
            {
                index++;
                count++;
            }
            items_ = (DebugMenuItem*)func_02012d88(&data_02114e20, count * sizeof(DebugMenuItem));
            count = 0;
            index = 0;
            for (entry = FindEntry(page_, &index); entry != NULL; entry = FindEntry(page_, &index))
            {
                func_0202949c(&items_[count]);
                if (page_ == 6)
                {
                    MonsterEntry* monster = func_0206f4f0(monsters_, entry->id_);
                    if (monster != NULL)
                    {
                        __clear(name, sizeof(name));
                        sprintf(name, STRING(0x540, "%s\x81" "F%s"), monster->unk_4 + 1, monster->name_);
                        func_020294cc(&items_[count], name);
                    }
                    else if ((unsigned short)entry->id_ == 0)
                    {
                        func_020294cc(&items_[count], entry->name_);
                    }
                    else
                    {
                        func_020294cc(&items_[count], STRING(0x547, "No Data"));
                    }
                }
                else if (IsPartPage())
                {
                    PartEntry* part = func_020dedd0(&parts_, entry->id_);
                    if (part != NULL)
                    {
                        if (part->unk_4 != 0)
                            func_020294cc(&items_[count], (const char*)part->unk_4);
                        else
                            func_020294cc(&items_[count], entry->name_);
                    }
                    else
                    {
                        func_020294cc(&items_[count], entry->name_);
                    }
                }
                else if (page_ == 0x26)
                {
                    __clear(option, sizeof(option));
                    unsigned char on = 0;
                    switch (count)
                    {
                    case 0:
                        on = aspect_;
                        break;
                    case 1:
                        on = floor_;
                        break;
                    case 2:
                        on = monsterBox_;
                        break;
                    case 3:
                        on = syncMotion_;
                        break;
                    case 4:
                        on = viewMemory_;
                        break;
                    }
                    if (on)
                        sprintf(option, STRING(0x54f, "[*]"));
                    else
                        sprintf(option, STRING(0x553, "[-]"));
                    strcat(option, entry->name_);
                    func_020294cc(&items_[count], option);
                }
                else
                {
                    func_020294cc(&items_[count], entry->name_);
                }
                func_0202a944(&menuList_, &items_[count]);
                index++;
                count++;
            }
        }
        menuList_.SetRange(0, count - 1);
        menuList_.SetIndex(cursors_[page_]);
        func_0202a6c4(&menuList_);
        func_0202a8cc(&menuList_, 1);
    }
    else
    {
        func_020294cc(&menuList_.title_, STRING(0x557, "[Motion]"));
        count = 0;
        for (AnimationPackage* package = current_->GetAnimationPackages(); package != NULL; package = package->pNext)
        {
            BCFG* bcfg = &package->bcfgData;
            if (bcfg != NULL)
                count += bcfg->GetNumAnimations();
        }
        items_ = (DebugMenuItem*)func_02012d88(&data_02114e20, count * sizeof(DebugMenuItem));
        AnimationPackage* package = current_->GetAnimationPackages();
        index = 0;
        for (; package != NULL; package = package->pNext)
        {
            BCFG* bcfg = &package->bcfgData;
            if (bcfg != NULL)
            {
                int animations = bcfg->GetNumAnimations();
                for (int i = 0; i < animations; i++)
                {
                    BCFG::AnimationRecord* record = bcfg->GetAnimationRecord(i);
                    if (record != NULL)
                    {
                        func_0202949c(&items_[index]);
                        func_020294cc(&items_[index], record->name);
                        func_0202a944(&menuList_, &items_[index++]);
                    }
                }
            }
        }
        menuList_.SetRange(0, count - 1);
        menuList_.SetIndex(0);
        func_0202a6c4(&menuList_);
        func_0202a8cc(&menuList_, 1);
    }
    int rows = menuList_.rows_;
    float ratio = (float)rows / count;
    if (ratio > 1.0f)
        ratio = 1.0f;
    scrollBarSize_ = 156.0f * ratio;
    int hidden = count - rows;
    scrollBarStep_ = (float)(0x9c - scrollBarSize_) / hidden;
    if (scrollBarSize_ < 4)
    {
        scrollBarStep_ -= (float)(4 - scrollBarSize_) / hidden;
        scrollBarSize_ = 4;
    }
    redraw_ = 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10ViewObject20GetAnimationPackagesEv(); // ViewObject::GetAnimationPackages
    void _ZN15CharacterViewer10IsPartPageEv(); // CharacterViewer::IsPartPage
    void _ZN4BCFG18GetAnimationRecordEi(); // BCFG::GetAnimationRecord
    void _ZN9DebugMenu8SetIndexEi(); // DebugMenu::SetIndex
    void _ZN9DebugMenu8SetRangeEii(); // DebugMenu::SetRange
    void _ZNK4BCFG16GetNumAnimationsEv(); // BCFG::GetNumAnimations
}

asm void CharacterViewer::OpenMenu(int unk)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x204
    mov r9, r0
    mov r4, r1
    ldr r1, [r9, #0x344]
    cmp r1, #0x0
    beq @L0219272c
    ldr r0, =data_02114e20
    bl func_02012da4
    mov r0, #0x0
    str r0, [r9, #0x344]
@L0219272c:
    add r0, sp, #0x184
    mov r1, #0x80
    str r4, [r9, #0x354]
    bl __clear
    add r0, r9, #0x2c4
    bl func_0202a91c
    add r0, r9, #0x2c4
    bl func_02029568
    ldrb r0, [r9, #0x331]
    orr r0, r0, #0x6
    strb r0, [r9, #0x331]
    ldr r0, [r9, #0x194]
    cmp r0, #0x0
    cmpne r0, #0x2
    bne @L02192ea4
    ldr r0, [r9, #0x1a4]
    cmp r0, #0x28
    addls pc, pc, r0, lsl #0x2
    b @L02192aa4
@L02192778:
    b @L0219281c
    b @L0219282c
    b @L0219283c
    b @L0219284c
    b @L0219285c
    b @L0219288c
    b @L0219286c
    b @L0219287c
    b @L0219289c
    b @L02192aa4
    b @L02192aa4
    b @L021929bc
    b @L021929cc
    b @L021929fc
    b @L02192a0c
    b @L021928ac
    b @L021929ac
    b @L021928bc
    b @L021928cc
    b @L021928dc
    b @L021928ec
    b @L021928fc
    b @L0219296c
    b @L0219290c
    b @L0219291c
    b @L0219292c
    b @L0219293c
    b @L0219294c
    b @L0219295c
    b @L0219297c
    b @L0219298c
    b @L0219299c
    b @L021929ec
    b @L021929dc
    b @L02192a1c
    b @L02192a2c
    b @L02192a3c
    b @L02192a7c
    b @L02192a4c
    b @L02192a5c
    b @L02192a6c
@L0219281c:
    ldr r1, =sStrings+0x3dd
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219282c:
    ldr r1, =sStrings+0x3e8
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219283c:
    ldr r1, =sStrings+0x3ef
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219284c:
    ldr r1, =sStrings+0x2da
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219285c:
    ldr r1, =sStrings+0x3f5
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219286c:
    ldr r1, =sStrings+0x3fe
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219287c:
    ldr r1, =sStrings+0x408
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219288c:
    ldr r1, =sStrings+0x411
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219289c:
    ldr r1, =sStrings+0x417
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021928ac:
    ldr r1, =sStrings+0x427
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021928bc:
    ldr r1, =sStrings+0x430
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021928cc:
    ldr r1, =sStrings+0x437
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021928dc:
    ldr r1, =sStrings+0x444
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021928ec:
    ldr r1, =sStrings+0x452
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021928fc:
    ldr r1, =sStrings+0x45e
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219290c:
    ldr r1, =sStrings+0x46c
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219291c:
    ldr r1, =sStrings+0x475
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219292c:
    ldr r1, =sStrings+0x47a
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219293c:
    ldr r1, =sStrings+0x483
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219294c:
    ldr r1, =sStrings+0x48a
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219295c:
    ldr r1, =sStrings+0x491
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219296c:
    ldr r1, =sStrings+0x496
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219297c:
    ldr r1, =sStrings+0x49b
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219298c:
    ldr r1, =sStrings+0x4a8
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L0219299c:
    ldr r1, =sStrings+0x4b7
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021929ac:
    ldr r1, =sStrings+0x4c6
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021929bc:
    ldr r1, =sStrings+0x4ce
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021929cc:
    ldr r1, =sStrings+0x4d6
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021929dc:
    ldr r1, =sStrings+0x4e1
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021929ec:
    ldr r1, =sStrings+0x4ee
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L021929fc:
    ldr r1, =sStrings+0x4fd
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a0c:
    ldr r1, =sStrings+0x50c
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a1c:
    ldr r1, =sStrings+0x2da
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a2c:
    ldr r1, =sStrings+0x51b
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a3c:
    ldr r1, =sStrings+0x2da
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a4c:
    ldr r1, =sStrings+0x524
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a5c:
    ldr r1, =sStrings+0x52b
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a6c:
    ldr r1, =sStrings+0x532
    add r0, r9, #0x2c4
    bl func_020294cc
    b @L02192aa4
@L02192a7c:
    ldr r0, [r9, #0x34]
    cmp r0, #0x0
    beq @L02192a98
    ldr r2, [r0, #0xc]
    ldr r1, =sStrings+0x53b
    add r0, sp, #0x184
    bl sprintf
@L02192a98:
    add r1, sp, #0x184
    add r0, r9, #0x2c4
    bl func_020294cc
@L02192aa4:
    ldr r0, [r9, #0x1a4]
    mov r7, #0x0
    cmp r0, #0x2
    cmpne r0, #0x3
    cmpne r0, #0x24
    bne @L02192b84
    ldr r0, [r9, #0x2c]
    b @L02192acc
@L02192ac4:
    ldr r0, [r0, #0x4]
    add r7, r7, #0x1
@L02192acc:
    cmp r0, #0x0
    bne @L02192ac4
    cmp r7, #0x0
    bne @L02192aec
    ldr r0, =data_02114e20
    mov r1, #0x40
    bl func_02012d88
    b @L02192af8
@L02192aec:
    ldr r0, =data_02114e20
    mov r1, r7, lsl #0x6
    bl func_02012d88
@L02192af8:
    str r0, [r9, #0x344]
    cmp r7, #0x0
    bne @L02192b34
    ldr r0, [r9, #0x344]
    bl func_0202949c
    mov r0, #0x3e8
    bl func_020e51cc
    mov r1, r0
    ldr r0, [r9, #0x344]
    bl func_020294cc
    ldr r1, [r9, #0x344]
    add r0, r9, #0x2c4
    bl func_0202a944
    mov r7, #0x1
    b @L02192e64
@L02192b34:
    ldr r4, [r9, #0x2c]
    mov r7, #0x0
    b @L02192b78
@L02192b40:
    ldr r0, [r9, #0x344]
    add r0, r0, r7, lsl #0x6
    bl func_0202949c
    ldr r1, [r4, #0x0]
    ldr r0, [r9, #0x344]
    ldr r1, [r1, #0xc]
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    ldr r1, [r9, #0x344]
    add r0, r9, #0x2c4
    add r1, r1, r7, lsl #0x6
    bl func_0202a944
    ldr r4, [r4, #0x4]
    add r7, r7, #0x1
@L02192b78:
    cmp r4, #0x0
    bne @L02192b40
    b @L02192e64
@L02192b84:
    cmp r0, #0x28
    bne @L02192bf4
    ldr r1, [r9, #0x48]
    ldr r0, =data_02114e20
    mov r1, r1, lsl #0x6
    bl func_02012d88
    str r0, [r9, #0x344]
    b @L02192be4
@L02192ba4:
    mov r1, r7
    add r0, r9, #0x3c
    bl _ZN12ViewerConfig9GetPresetEi
    ldr r1, [r9, #0x344]
    mov r4, r0
    add r0, r1, r7, lsl #0x6
    bl func_0202949c
    ldr r0, [r9, #0x344]
    ldr r1, [r4, #0x0]
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    ldr r1, [r9, #0x344]
    add r0, r9, #0x2c4
    add r1, r1, r7, lsl #0x6
    bl func_0202a944
    add r7, r7, #0x1
@L02192be4:
    ldr r0, [r9, #0x48]
    cmp r7, r0
    blt @L02192ba4
    b @L02192e64
@L02192bf4:
    str r7, [sp, #0x0]
    ldr r1, [r9, #0x1a4]
    add r2, sp, #0x0
    mov r0, r9
    bl _ZN15CharacterViewer9FindEntryEiPi
    mov r8, r0
    add r4, sp, #0x0
    b @L02192c38
@L02192c14:
    ldr r1, [sp, #0x0]
    mov r0, r9
    add r1, r1, #0x1
    str r1, [sp, #0x0]
    ldr r1, [r9, #0x1a4]
    mov r2, r4
    add r7, r7, #0x1
    bl _ZN15CharacterViewer9FindEntryEiPi
    mov r8, r0
@L02192c38:
    cmp r8, #0x0
    bne @L02192c14
    ldr r0, =data_02114e20
    mov r1, r7, lsl #0x6
    bl func_02012d88
    str r0, [r9, #0x344]
    mov r7, #0x0
    str r7, [sp, #0x0]
    ldr r1, [r9, #0x1a4]
    add r2, sp, #0x0
    mov r0, r9
    bl _ZN15CharacterViewer9FindEntryEiPi
    mov r8, r0
    ldr r11, =sStrings+0x547
    add r5, sp, #0x84
    mov r4, #0x100
    ldr r10, =sStrings+0x540
    b @L02192e5c
@L02192c80:
    ldr r0, [r9, #0x344]
    add r0, r0, r7, lsl #0x6
    bl func_0202949c
    ldr r0, [r9, #0x1a4]
    cmp r0, #0x6
    bne @L02192d14
    ldrsh r1, [r8, #0x8]
    add r0, r9, #0x64
    bl func_0206f4f0
    movs r6, r0
    beq @L02192ce4
    mov r0, r5
    mov r1, r4
    bl __clear
    mov r0, r5
    mov r1, r10
    ldr r2, [r6, #0x4]
    ldr r3, [r6, #0x0]
    add r2, r2, #0x1
    bl sprintf
    ldr r0, [r9, #0x344]
    mov r1, r5
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192ce4:
    ldrh r0, [r8, #0x8]
    cmp r0, #0x0
    ldr r0, [r9, #0x344]
    bne @L02192d04
    ldr r1, [r8, #0x0]
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192d04:
    mov r1, r11
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192d14:
    mov r0, r9
    bl _ZN15CharacterViewer10IsPartPageEv
    cmp r0, #0x0
    beq @L02192d78
    ldrsh r1, [r8, #0x8]
    add r0, r9, #0x4c
    bl func_020dedd0
    cmp r0, #0x0
    beq @L02192d64
    ldr r1, [r0, #0x4]
    ldr r0, [r9, #0x344]
    cmp r1, #0x0
    beq @L02192d54
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192d54:
    ldr r1, [r8, #0x0]
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192d64:
    ldr r0, [r9, #0x344]
    ldr r1, [r8, #0x0]
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192d78:
    ldr r0, [r9, #0x1a4]
    cmp r0, #0x26
    bne @L02192e18
    add r0, sp, #0x4
    mov r1, #0x80
    bl __clear
    mov r0, #0x0
    cmp r7, #0x4
    addls pc, pc, r7, lsl #0x2
    b @L02192dd8
@L02192da0:
    b @L02192db4
    b @L02192dbc
    b @L02192dc4
    b @L02192dcc
    b @L02192dd4
@L02192db4:
    ldrb r0, [r9, #0x19c]
    b @L02192dd8
@L02192dbc:
    ldrb r0, [r9, #0x19d]
    b @L02192dd8
@L02192dc4:
    ldrb r0, [r9, #0x19e]
    b @L02192dd8
@L02192dcc:
    ldrb r0, [r9, #0x19f]
    b @L02192dd8
@L02192dd4:
    ldrb r0, [r9, #0x1a0]
@L02192dd8:
    cmp r0, #0x0
    add r0, sp, #0x4
    beq @L02192df0
    ldr r1, =sStrings+0x54f
    bl sprintf
    b @L02192df8
@L02192df0:
    ldr r1, =sStrings+0x553
    bl sprintf
@L02192df8:
    ldr r1, [r8, #0x0]
    add r0, sp, #0x4
    bl strcat
    ldr r0, [r9, #0x344]
    add r1, sp, #0x4
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
    b @L02192e28
@L02192e18:
    ldr r0, [r9, #0x344]
    ldr r1, [r8, #0x0]
    add r0, r0, r7, lsl #0x6
    bl func_020294cc
@L02192e28:
    ldr r1, [r9, #0x344]
    add r0, r9, #0x2c4
    add r1, r1, r7, lsl #0x6
    bl func_0202a944
    ldr r1, [sp, #0x0]
    mov r0, r9
    add r1, r1, #0x1
    str r1, [sp, #0x0]
    ldr r1, [r9, #0x1a4]
    add r2, sp, #0x0
    add r7, r7, #0x1
    bl _ZN15CharacterViewer9FindEntryEiPi
    mov r8, r0
@L02192e5c:
    cmp r8, #0x0
    bne @L02192c80
@L02192e64:
    add r0, r9, #0x2c4
    sub r2, r7, #0x1
    mov r1, #0x0
    bl _ZN9DebugMenu8SetRangeEii
    ldr r1, [r9, #0x1a4]
    add r0, r9, #0x2c4
    add r1, r9, r1, lsl #0x1
    add r1, r1, #0x200
    ldrsh r1, [r1, #0x68]
    bl _ZN9DebugMenu8SetIndexEi
    add r0, r9, #0x2c4
    bl func_0202a6c4
    add r0, r9, #0x2c4
    mov r1, #0x1
    bl func_0202a8cc
    b @L02192fc4
@L02192ea4:
    ldr r1, =sStrings+0x557
    add r0, r9, #0x2c4
    bl func_020294cc
    ldr r0, [r9, #0x30]
    mov r7, #0x0
    bl _ZN10ViewObject20GetAnimationPackagesEv
    mov r4, r0
    b @L02192ed8
@L02192ec4:
    adds r0, r4, #0x4
    beq @L02192ed4
    bl _ZNK4BCFG16GetNumAnimationsEv
    add r7, r7, r0
@L02192ed4:
    ldr r4, [r4, #0x28]
@L02192ed8:
    cmp r4, #0x0
    bne @L02192ec4
    ldr r0, =data_02114e20
    mov r1, r7, lsl #0x6
    bl func_02012d88
    str r0, [r9, #0x344]
    ldr r0, [r9, #0x30]
    bl _ZN10ViewObject20GetAnimationPackagesEv
    mov r1, #0x0
    mov r5, r0
    str r1, [sp, #0x0]
    mov r11, r1
    b @L02192f8c
@L02192f0c:
    adds r6, r5, #0x4
    beq @L02192f88
    mov r0, r6
    bl _ZNK4BCFG16GetNumAnimationsEv
    mov r8, r0
    mov r10, r11
    b @L02192f80
@L02192f28:
    mov r0, r6
    mov r1, r10
    bl _ZN4BCFG18GetAnimationRecordEi
    movs r4, r0
    beq @L02192f7c
    ldr r1, [r9, #0x344]
    ldr r0, [sp, #0x0]
    add r0, r1, r0, lsl #0x6
    bl func_0202949c
    ldr r2, [r9, #0x344]
    ldr r0, [sp, #0x0]
    mov r1, r4
    add r0, r2, r0, lsl #0x6
    bl func_020294cc
    ldr r2, [sp, #0x0]
    add r0, r9, #0x2c4
    add r1, r2, #0x1
    str r1, [sp, #0x0]
    ldr r1, [r9, #0x344]
    add r1, r1, r2, lsl #0x6
    bl func_0202a944
@L02192f7c:
    add r10, r10, #0x1
@L02192f80:
    cmp r10, r8
    blt @L02192f28
@L02192f88:
    ldr r5, [r5, #0x28]
@L02192f8c:
    cmp r5, #0x0
    bne @L02192f0c
    add r0, r9, #0x2c4
    sub r2, r7, #0x1
    mov r1, #0x0
    bl _ZN9DebugMenu8SetRangeEii
    add r0, r9, #0x2c4
    mov r1, #0x0
    bl _ZN9DebugMenu8SetIndexEi
    add r0, r9, #0x2c4
    bl func_0202a6c4
    add r0, r9, #0x2c4
    mov r1, #0x1
    bl func_0202a8cc
@L02192fc4:
    add r0, r9, #0x300
    ldrh r5, [r0, #0x26]
    mov r0, r5
    bl _fflt
    mov r4, r0
    mov r0, r7
    bl _fflt
    mov r1, r0
    mov r0, r4
    bl _fdiv
    mov r1, #0x3f800000
    mov r4, r0
    bl _fgr
    movhi r4, #0x3f800000
    ldr r0, =0x431c0000
    mov r1, r4
    bl _fmul
    bl _ffix
    str r0, [r9, #0x348]
    sub r5, r7, r5
    rsb r0, r0, #0x9c
    bl _fflt
    mov r4, r0
    mov r0, r5
    bl _fflt
    mov r1, r0
    mov r0, r4
    bl _fdiv
    str r0, [r9, #0x34c]
    ldr r0, [r9, #0x348]
    cmp r0, #0x4
    bge @L0219307c
    rsb r0, r0, #0x4
    bl _fflt
    mov r4, r0
    mov r0, r5
    bl _fflt
    mov r1, r0
    mov r0, r4
    bl _fdiv
    mov r1, r0
    ldr r0, [r9, #0x34c]
    bl _fsub
    str r0, [r9, #0x34c]
    mov r0, #0x4
    str r0, [r9, #0x348]
@L0219307c:
    mov r0, #0x1
    strb r0, [r9, #0x350]
    add sp, sp, #0x204
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void DebugMenu::SetRange(int first, int last)
{
    first_ = first;
    cursor_ = first_;
    last_ = last;
}

void DebugMenu::SetIndex(int index)
{
    cursor_ = index + first_;
}

ViewerEntry* CharacterViewer::FindEntry(int page, int* index)
{
    for (int i = *index; i < config_.entryCount_; i++)
    {
        ViewerEntry* entry = config_.GetEntry(i);
        if (entry == NULL)
            break;
        if (page == entry->page_)
        {
            *index = i;
            return entry;
        }
    }
    return NULL;
}

void CharacterViewer::PushPage(int page)
{
    history_[historyCount_++] = page;
}

int CharacterViewer::PopPage()
{
    if (historyCount_ <= 0)
        return -1;
    historyCount_--;
    int page = history_[historyCount_];
    history_[historyCount_] = -1;
    return page;
}

ViewerSlot* CharacterViewer::FindPlayerSlot()
{
    for (int i = 0; i < 4; i++)
    {
        if (playerSlots_[i].used_ == 0)
            return &playerSlots_[i];
    }
    return NULL;
}

ViewerSlot* CharacterViewer::FindDollSlot()
{
    for (int i = 0; i < 4; i++)
    {
        if (dollSlots_[i].used_ == 0)
            return &dollSlots_[i];
    }
    return NULL;
}

ViewerSlot* CharacterViewer::FindSlot()
{
    for (int i = 0; i < 4; i++)
    {
        if (slots_[i].used_ == 0)
            return &slots_[i];
    }
    return NULL;
}

void CharacterViewer::Initialize()
{
    InitializeBrightnessState((GameResources*)this);
    objects_ = NULL;
    current_ = NULL;
    selected_ = NULL;
    lastKind_ = -1;
    menu_ = -1;
    otherMenu_ = -1;
    aspect_ = 1;
    floor_ = 1;
    monsterBox_ = 1;
    syncMotion_ = 1;
    viewMemory_ = 0;
    field_ = 0;
    page_ = -1;
    memset(history_, -1, sizeof(history_));
    historyCount_ = 0;
    elapsed_ = 0;
    workStart_ = 0;
    workEnd_ = 0;
    averageWork_ = 0;
    fps_ = 0;
    unk_250[0] = 0;
    unk_250[1] = 0;
    unk_250[2] = 0;
    unk_250[3] = 0;
    unk_250[4] = 0;
    unk_250[5] = 0;
    memset(cursors_, 0, sizeof(cursors_));
    scrollBarSize_ = 0;
    scrollBarStep_ = 0;
    repeatDelay_ = 0x1e;
    repeatTimer_ = 0;
    buffer_ = NULL;
    func_02029568(&menuList_);
    menuList_.unk_40 = 1;
    items_ = NULL;
    redraw_ = 0;
    for (int i = 0; i < 4; i++)
    {
        playerSlots_[i].Initialize();
        dollSlots_[i].Initialize();
        slots_[i].Initialize();
    }
}

void ViewerSlot::Initialize()
{
    states_ = NULL;
    used_ = 0;
}

void CharacterViewer::Finish()
{
    ViewObjectNode* node = objects_;
    while (node != NULL)
    {
        node->object_->Finish();
        func_02012da4(&data_02114e20, node->object_);
        ViewObjectNode* next = node;
        node = node->next_;
        func_02012da4(&data_02114e20, next);
    }
    for (int i = 0; i < 4; i++)
    {
        if (playerSlots_[i].states_ != NULL)
            func_02012da4(&data_02114e20, playerSlots_[i].states_);
        if (dollSlots_[i].states_ != NULL)
            func_02012da4(&data_02114e20, dollSlots_[i].states_);
        if (slots_[i].states_ != NULL)
            func_02012da4(&data_02114e20, slots_[i].states_);
    }
    func_02012da4(&data_02114e20, partsAllocator_.GetSignedAllocator());
    func_02012da4(&data_02114e20, monstersAllocator_.GetSignedAllocator());
    func_02012da4(&data_02114e20, soundsAllocator_.GetSignedAllocator());
    partsAllocator_.Destroy();
    monstersAllocator_.Destroy();
    soundsAllocator_.Destroy();
    config_.Free();
    if (buffer_ != NULL)
    {
        func_02012da4(&data_02114e20, buffer_);
        buffer_ = NULL;
    }
    if (items_ == NULL)
        return;
    func_02012da4(&data_02114e20, items_);
    items_ = NULL;
}

// NONMATCHING: the C matches 94.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers of the display control writes differ (as in CharacterCreationScene::Run()), and so do the ones of the
// average time.
#ifdef NONMATCHING
void CharacterViewer::Run()
{
    char camera[0x2c8];

    GameState* gameState = GameState::GetInstance();
    if (gameState == NULL)
        return;
    func_0200fb84(gameState, (GameResources*)this);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    loader->MaybeReset();
    void* sound = func_02094a00();
    func_02094b3c(sound, 0xa);
    func_02094b3c(sound, 0xc);
    func_02094b34(sound, 0x69, 0, 0, 0);
    func_02094b38(sound, 0x69);
    func_02094b38(sound, 0);
    while (!func_02094b4c(sound))
        loader->RemoveAllLocks();
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    Unknown_0203bd08* unknown = func_0203bd08();
    func_0203bd24();
    LockStagedTextureVRAMCopying();
    MapVRAMBanksToLCDC(0x1ff);
    func_020ca458(0, (void*)0x06800000, 0xa4000);
    DisableLCDCMappedVRAMBanks();
    ReleaseTextureImageVRAMBanks();
    MapVRAMBanksToTextureImage(0xb);
    ReleaseTexturePaletteVRAMBanks();
    MapVRAMBanksToTexturePalette(0x60);
    DISPCNT &= ~0x07000000;
    DISPCNT &= ~0x38000000;
    DISPCNT = (DISPCNT & ~0x1f00) | 0x100;
    func_020c391c(1, 0, 1);
    func_020c3984(0);
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x1100;
    ReleaseSubBGVRAMBanks();
    MapVRAMBanksToSubBG(4);
    ReleaseSubObjVRAMBanks();
    MapVRAMBanksToSubObj(0x100);
    DISPCNTSUB = (DISPCNTSUB & ~0x300010) | 0x10;
    UpdateVRAMStagingVRAMBanks();
    UnlockStagedTextureVRAMCopying();
    func_020c39a0(REG_MASTER_BRIGHT, 0);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, 0);
    POWCNT &= ~0x8000;
    Finish3DRendering();
    func_020c51dc();
    func_020c537c();
    BG1CNT &= ~BGCNT_MASK_PRIORITY;
    BG0CNT = (BG0CNT & ~BGCNT_MASK_PRIORITY) | 1;
    BG0CNTSUB &= ~BGCNT_MASK_PRIORITY;
    *(volatile unsigned int*)0x04001010 = 0;
    buffer_ = func_02012d88(&data_02114e20, 0x6000);
    func_02028ddc();
    func_02028d68(4);
    func_02028dec(1);
    func_020bb48c(3, 1);
    func_020bb780(0x8000, 1);
    InitializeVRAM();
    func_020c5588(0x594a, 0x10, 0x7fff, 0, 0);
    config_.Clear();
    config_.Load(NULL);
    memset(cursors_, 0, sizeof(cursors_));
    partsAllocator_.ResetAllocatorPointer();
    partsAllocator_.CreateTypeA(func_02012d88(&data_02114e20, 0x17600), 0x17600);
    partsAllocator_.Reset();
    func_020de848(&parts_);
    BackgroundLoader::AddLockGlobal();
    unsigned int size = 0;
    void* file = ExtractFileFromGP2(data_020f2a38, data_020f2a30, &size);
    if (file != NULL)
        func_020dea64(&parts_, &partsAllocator_, file, size, sPartCategories, sCategoryCount);
    BackgroundLoader::RemoveLockGlobal();
    monstersAllocator_.ResetAllocatorPointer();
    monstersAllocator_.CreateTypeA(func_02012d88(&data_02114e20, 0x20000), 0x20000);
    monstersAllocator_.Reset();
    func_0206efc4(monsters_);
    func_0206efd8(monsters_, &monstersAllocator_);
    soundsAllocator_.ResetAllocatorPointer();
    soundsAllocator_.CreateTypeA(func_02012d88(&data_02114e20, 0x20000), 0x20000);
    soundsAllocator_.Reset();
    func_020709d8(monsterSounds_);
    func_020709ec(monsterSounds_, &soundsAllocator_);
    func_0202df68(camera);
    func_020a2cf0(camera);
    func_020a2010(camera);
    func_020a27a0(camera);
    func_020100c4(gameState, camera);
    ResetCamera();
    func_0205ea20(data_02108760, 0x65);
    func_020c9820();
    func_020c38d4();
    DISPCNTSUB |= 0x10000;
    func_02010124(gameState);
    func_020c3a0c(0);
    GetCurrentTimestamp();
    MessageSystem* messages = func_020421a0();
    func_02042b30(messages, &vramState_);
    func_0207df50(&vramState_);
    func_0207df90(&vramState_);
    func_020432c4(messages);
    func_0207dfac(&vramState_);
    func_0204500c(messages, STRING(0x560, "0123456789.FPSTQSIZERAMKB:abcdefghijklmnopqrstuvwxyz[]/"), 0, 0xe3);
    messages->unk_195a = 8;
    for (unsigned int i = 0; i < 0x10; i++)
    {
        func_0204359c(messages, 0x10);
        func_020439b0(messages, 0);
    }
    menu_ = Menu_Top;
    otherMenu_ = Menu_Option;
    page_ = 0;
    OpenMenu(0);
    func_02012de4(&data_02114e20);
    unsigned long long last = GetCurrentTimestamp();
    while (true)
    {
        func_02012efc();
        int quit;
        if (func_02012430(data_02114e30, PAD_BUTTON_SELECT) && func_02012430(data_02114e30, PAD_BUTTON_START))
            quit = 1;
        else if (page_ == 0 && func_02012444(data_02114e30, PAD_BUTTON_B))
            quit = 1;
        else
            quit = 0;
        if (quit)
        {
            func_020bc028(0);
            break;
        }
        if (func_02012444(data_02114e30, PAD_BUTTON_START))
            ResetCamera();
        switch (menu_)
        {
        case Menu_Top:
            UpdateTopMenu();
            break;
        case Menu_Motion:
            UpdateMotionMenu();
            break;
        case Menu_Option:
            UpdateOptionMenu();
            break;
        }
        Update();
        Draw();
        func_0203bd88(unknown);
        func_0203aa08(data_02108760);
        func_020bbd9c();
        unsigned long long previous = workEnd_;
        workEnd_ = TICKS_TO_MICROSECONDS(GetCurrentTimestamp());
        if (workStart_ < workEnd_)
            averageWork_ = (averageWork_ + (workEnd_ - workStart_)) / 2;
        if (previous < workEnd_)
        {
            elapsed_ += (workEnd_ - previous) / 1000;
            if (elapsed_ > 1000)
            {
                elapsed_ = 0;
                fps_ = 1000000.0f / averageWork_;
            }
        }
        loader->RemoveAllLocks();
        workStart_ = TICKS_TO_MICROSECONDS(GetCurrentTimestamp());
        if (func_020c39c8(REG_MASTER_BRIGHT) > -16)
            func_020c9820();
        GetCurrentTimestamp();
        func_0203bdb0(unknown);
        func_020290ac(1);
        gameState->CalculateDeltaTime(TICKS_TO_MICROSECONDS(GetCurrentTimestamp() - last));
        last = GetCurrentTimestamp();
    }
    func_02094b38(sound, 0x69);
    func_02094ab0(sound);
    func_0205ea20(data_02108760, 0x64);
    func_020a2010(camera);
    func_020a2cf0(camera);
    func_0202df68(camera);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12ViewerConfig4LoadEPKc(); // ViewerConfig::Load
    void _ZN12ViewerConfig5ClearEv(); // ViewerConfig::Clear
    void _ZN15CharacterViewer11ResetCameraEv(); // CharacterViewer::ResetCamera
    void _ZN15CharacterViewer13UpdateTopMenuEv(); // CharacterViewer::UpdateTopMenu
    void _ZN15CharacterViewer14InitializeVRAMEv(); // CharacterViewer::InitializeVRAM
    void _ZN15CharacterViewer16UpdateMotionMenuEv(); // CharacterViewer::UpdateMotionMenu
    void _ZN15CharacterViewer16UpdateOptionMenuEv(); // CharacterViewer::UpdateOptionMenu
    void _ZN15CharacterViewer4DrawEv(); // CharacterViewer::Draw
    void _ZN15CharacterViewer6UpdateEv(); // CharacterViewer::Update
    void _ZN16BackgroundLoader10MaybeResetEv(); // BackgroundLoader::MaybeReset
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader14RemoveAllLocksEv(); // BackgroundLoader::RemoveAllLocks
    void _ZN9GameState18CalculateDeltaTimeEy(); // GameState::CalculateDeltaTime
    void _ll_udiv();
    void _ll_uto_f();
}

asm void CharacterViewer::Run()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x2ec
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    movs r6, r0
    beq @L02193c78
    mov r1, r10
    bl func_0200fb84
    bl _ZN16BackgroundLoader11GetInstanceEv
    str r0, [sp, #0x14]
    bl _ZN16BackgroundLoader10MaybeResetEv
    bl func_02094a00
    mov r7, r0
    mov r1, #0xa
    bl func_02094b3c
    mov r0, r7
    mov r1, #0xc
    bl func_02094b3c
    mov r2, #0x0
    mov r0, r7
    mov r1, #0x69
    mov r3, r2
    str r2, [sp, #0x0]
    bl func_02094b34
    mov r0, r7
    mov r1, #0x69
    bl func_02094b38
    mov r0, r7
    mov r1, #0x0
    bl func_02094b38
    b @L0219357c
@L02193574:
    ldr r0, [sp, #0x14]
    bl _ZN16BackgroundLoader14RemoveAllLocksEv
@L0219357c:
    mov r0, r7
    bl func_02094b4c
    cmp r0, #0x0
    beq @L02193574
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    bl func_0203bd08
    str r0, [sp, #0x10]
    bl func_0203bd24
    bl LockStagedTextureVRAMCopying
    ldr r0, =0x1ff
    bl MapVRAMBanksToLCDC
    mov r0, #0x0
    mov r1, #0x6800000
    mov r2, #0xa4000
    bl func_020ca458
    bl DisableLCDCMappedVRAMBanks
    bl ReleaseTextureImageVRAMBanks
    mov r0, #0xb
    bl MapVRAMBanksToTextureImage
    bl ReleaseTexturePaletteVRAMBanks
    mov r0, #0x60
    bl MapVRAMBanksToTexturePalette
    mov r4, #0x4000000
    ldr r1, [r4, #0x0]
    mov r0, #0x1
    bic r1, r1, #0x7000000
    str r1, [r4, #0x0]
    ldr r2, [r4, #0x0]
    mov r1, #0x0
    bic r2, r2, #0x38000000
    str r2, [r4, #0x0]
    ldr r3, [r4, #0x0]
    mov r2, r0
    bic r3, r3, #0x1f00
    orr r3, r3, #0x100
    str r3, [r4, #0x0]
    bl func_020c391c
    mov r0, #0x0
    bl func_020c3984
    ldr r1, =0x4001000
    ldr r0, [r1, #0x0]
    bic r0, r0, #0x1f00
    orr r0, r0, #0x1100
    str r0, [r1, #0x0]
    bl ReleaseSubBGVRAMBanks
    mov r0, #0x4
    bl MapVRAMBanksToSubBG
    bl ReleaseSubObjVRAMBanks
    mov r0, #0x100
    bl MapVRAMBanksToSubObj
    ldr r2, =0x4001000
    ldr r0, =0xffcfffef
    ldr r1, [r2, #0x0]
    and r0, r1, r0
    orr r0, r0, #0x10
    str r0, [r2, #0x0]
    bl UpdateVRAMStagingVRAMBanks
    bl UnlockStagedTextureVRAMCopying
    ldr r0, =0x400006c
    mov r1, #0x0
    bl func_020c39a0
    ldr r0, =0x400106c
    mov r1, #0x0
    bl func_020c39a0
    ldr r1, =0x4000304
    ldrh r0, [r1, #0x0]
    bic r0, r0, #0x8000
    strh r0, [r1, #0x0]
    bl Finish3DRendering
    bl func_020c51dc
    bl func_020c537c
    ldr r1, =0x400000a
    ldr r4, =0x4001008
    ldrh r0, [r1, #0x0]
    sub r5, r1, #0x2
    mov r2, #0x0
    bic r0, r0, #0x3
    strh r0, [r1, #0x0]
    ldrh r3, [r5, #0x0]
    ldr r0, =data_02114e20
    mov r1, #0x6000
    bic r3, r3, #0x3
    orr r3, r3, #0x1
    strh r3, [r5, #0x0]
    ldrh r3, [r4, #0x0]
    bic r3, r3, #0x3
    strh r3, [r4, #0x0]
    str r2, [r4, #0x8]
    bl func_02012d88
    str r0, [r10, #0x84]
    bl func_02028ddc
    mov r0, #0x4
    bl func_02028d68
    mov r0, #0x1
    bl func_02028dec
    mov r0, #0x3
    mov r1, #0x1
    bl func_020bb48c
    mov r0, #0x8000
    mov r1, #0x1
    bl func_020bb780
    mov r0, r10
    bl _ZN15CharacterViewer14InitializeVRAMEv
    mov r3, #0x0
    ldr r0, =0x594a
    ldr r2, =0x7fff
    mov r1, #0x10
    str r3, [sp, #0x0]
    bl func_020c5588
    add r0, r10, #0x3c
    bl _ZN12ViewerConfig5ClearEv
    add r0, r10, #0x3c
    mov r1, #0x0
    bl _ZN12ViewerConfig4LoadEPKc
    add r0, r10, #0x268
    mov r1, #0x0
    mov r2, #0x52
    bl memset
    add r0, r10, #0x88
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r0, =data_02114e20
    ldr r1, =0x17600
    bl func_02012d88
    mov r1, r0
    ldr r2, =0x17600
    add r0, r10, #0x88
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r10, #0x88
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x4c
    bl func_020de848
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x20]
    ldr r0, =data_020f2a38
    ldr r1, =data_020f2a30
    ldr r0, [r0, #0x0]
    ldr r1, [r1, #0x0]
    add r2, sp, #0x20
    bl ExtractFileFromGP2
    movs r2, r0
    beq @L021937e8
    ldr r1, =sPartCategories
    mov r0, #0x9
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    ldr r3, [sp, #0x20]
    add r0, r10, #0x4c
    add r1, r10, #0x88
    bl func_020dea64
@L021937e8:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r10, #0x9c
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r0, =data_02114e20
    mov r1, #0x20000
    bl func_02012d88
    mov r1, r0
    add r0, r10, #0x9c
    mov r2, #0x20000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r10, #0x9c
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x64
    bl func_0206efc4
    add r0, r10, #0x64
    add r1, r10, #0x9c
    bl func_0206efd8
    add r0, r10, #0xb0
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r0, =data_02114e20
    mov r1, #0x20000
    bl func_02012d88
    mov r1, r0
    add r0, r10, #0xb0
    mov r2, #0x20000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r10, #0xb0
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x70
    bl func_020709d8
    add r0, r10, #0x70
    add r1, r10, #0xb0
    bl func_020709ec
    add r0, sp, #0x24
    bl func_0202df68
    add r0, sp, #0x24
    bl func_020a2cf0
    add r0, sp, #0x24
    bl func_020a2010
    add r0, sp, #0x24
    bl func_020a27a0
    mov r0, r6
    add r1, sp, #0x24
    bl func_020100c4
    mov r0, r10
    bl _ZN15CharacterViewer11ResetCameraEv
    ldr r0, =data_02108760
    mov r1, #0x65
    bl func_0205ea20
    bl func_020c9820
    bl func_020c38d4
    ldr r2, =0x4001000
    mov r0, r6
    ldr r1, [r2, #0x0]
    orr r1, r1, #0x10000
    str r1, [r2, #0x0]
    bl func_02010124
    mov r0, #0x0
    bl func_020c3a0c
    bl GetCurrentTimestamp
    bl func_020421a0
    add r1, r10, #0x124
    mov r4, r0
    bl func_02042b30
    add r0, r10, #0x124
    bl func_0207df50
    add r0, r10, #0x124
    bl func_0207df90
    mov r0, r4
    bl func_020432c4
    add r0, r10, #0x124
    bl func_0207dfac
    ldr r1, =sStrings+0x560
    mov r0, r4
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r9, #0x0
    mov r1, #0x8
    add r0, r4, #0x1000
    strb r1, [r0, #0x95a]
    mov r8, #0x10
    mov r5, r9
    b @L02193954
@L02193938:
    mov r0, r4
    mov r1, r8
    bl func_0204359c
    mov r0, r4
    mov r1, r5
    bl func_020439b0
    add r9, r9, #0x1
@L02193954:
    cmp r9, #0x10
    blo @L02193938
    mov r1, #0x0
    str r1, [r10, #0x194]
    mov r0, #0x2
    str r0, [r10, #0x198]
    mov r0, r10
    str r1, [r10, #0x1a4]
    bl _ZN15CharacterViewer8OpenMenuEi
    ldr r0, =data_02114e20
    bl func_02012de4
    bl GetCurrentTimestamp
    str r0, [sp, #0x8]
    str r1, [sp, #0x1c]
    mov r5, #0x3e8
    mvn r4, #0xf
@L02193994:
    bl func_02012efc
    ldr r0, =data_02114e30
    mov r1, #0x4
    bl func_02012430
    cmp r0, #0x0
    beq @L021939c4
    ldr r0, =data_02114e30
    mov r1, #0x8
    bl func_02012430
    cmp r0, #0x0
    movne r0, #0x1
    bne @L021939ec
@L021939c4:
    ldr r0, [r10, #0x1a4]
    cmp r0, #0x0
    bne @L021939e8
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    movne r0, #0x1
    bne @L021939ec
@L021939e8:
    mov r0, #0x0
@L021939ec:
    cmp r0, #0x0
    beq @L02193a00
    mov r0, #0x0
    bl func_020bc028
    b @L02193c40
@L02193a00:
    ldr r0, =data_02114e30
    mov r1, #0x8
    bl func_02012444
    cmp r0, #0x0
    beq @L02193a1c
    mov r0, r10
    bl _ZN15CharacterViewer11ResetCameraEv
@L02193a1c:
    ldr r0, [r10, #0x194]
    cmp r0, #0x0
    beq @L02193a3c
    cmp r0, #0x1
    beq @L02193a48
    cmp r0, #0x2
    beq @L02193a54
    b @L02193a5c
@L02193a3c:
    mov r0, r10
    bl _ZN15CharacterViewer13UpdateTopMenuEv
    b @L02193a5c
@L02193a48:
    mov r0, r10
    bl _ZN15CharacterViewer16UpdateMotionMenuEv
    b @L02193a5c
@L02193a54:
    mov r0, r10
    bl _ZN15CharacterViewer16UpdateOptionMenuEv
@L02193a5c:
    mov r0, r10
    bl _ZN15CharacterViewer6UpdateEv
    mov r0, r10
    bl _ZN15CharacterViewer4DrawEv
    ldr r0, [sp, #0x10]
    bl func_0203bd88
    ldr r0, =data_02108760
    bl func_0203aa08
    bl func_020bbd9c
    ldr r9, [r10, #0x23c]
    ldr r8, [r10, #0x240]
    bl GetCurrentTimestamp
    mov r11, #0xfa00
    mov r3, #0x0
    umull r11, lr, r0, r11
    mov r12, r3
    mla lr, r0, r12, lr
    mov r0, r11
    mov r11, #0xfa00
    mla lr, r1, r11, lr
    ldr r2, =0x82ea
    mov r1, lr
    bl _ll_udiv
    str r0, [r10, #0x23c]
    str r1, [r10, #0x240]
    ldr r0, [r10, #0x238]
    ldr r3, [r10, #0x23c]
    ldr r2, [r10, #0x234]
    cmp r0, r1
    cmpeq r2, r3
    bhs @L02193b04
    subs r3, r3, r2
    sbc r2, r1, r0
    ldr r1, [r10, #0x244]
    ldr r0, [r10, #0x248]
    adds r1, r3, r1
    adc r0, r2, r0
    mov r2, r1, lsr #0x1
    mov r1, r0, lsr #0x1
    orr r2, r2, r0, lsl #0x1f
    str r2, [r10, #0x244]
    str r1, [r10, #0x248]
@L02193b04:
    ldr r0, [r10, #0x23c]
    ldr r1, [r10, #0x240]
    cmp r8, r1
    cmpeq r9, r0
    bhs @L02193b80
    subs r0, r0, r9
    sbc r1, r1, r8
    mov r2, #0x3e8
    mov r3, #0x0
    bl _ll_udiv
    ldr r3, [r10, #0x22c]
    ldr r2, [r10, #0x230]
    adds r0, r3, r0
    str r0, [r10, #0x22c]
    adc r1, r2, r1
    mov r0, #0x0
    str r1, [r10, #0x230]
    cmp r1, r0
    ldr r0, [r10, #0x22c]
    cmpeq r0, r5
    bls @L02193b80
    mov r0, #0x0
    str r0, [r10, #0x22c]
    str r0, [r10, #0x230]
    ldr r0, [r10, #0x244]
    ldr r1, [r10, #0x248]
    bl _ll_uto_f
    mov r1, r0
    ldr r0, =0x49742400
    bl _fdiv
    str r0, [r10, #0x24c]
@L02193b80:
    ldr r0, [sp, #0x14]
    bl _ZN16BackgroundLoader14RemoveAllLocksEv
    bl GetCurrentTimestamp
    mov r8, #0xfa00
    mov r3, #0x0
    umull r11, r9, r0, r8
    mov r8, r3
    mla r9, r0, r8, r9
    mov r8, #0xfa00
    mla r9, r1, r8, r9
    ldr r2, =0x82ea
    mov r0, r11
    mov r1, r9
    bl _ll_udiv
    str r0, [r10, #0x234]
    ldr r0, =0x400006c
    str r1, [r10, #0x238]
    bl func_020c39c8
    cmp r0, r4
    ble @L02193bd4
    bl func_020c9820
@L02193bd4:
    bl GetCurrentTimestamp
    ldr r0, [sp, #0x10]
    bl func_0203bdb0
    mov r0, #0x1
    bl func_020290ac
    bl GetCurrentTimestamp
    ldr r2, [sp, #0x8]
    mov r3, #0x0
    subs r9, r0, r2
    ldr r0, [sp, #0x1c]
    mov r11, r3
    sbc r8, r1, r0
    mov r0, #0xfa00
    umull r0, r1, r9, r0
    mla r1, r9, r11, r1
    mov r9, #0xfa00
    mla r1, r8, r9, r1
    ldr r2, =0x82ea
    bl _ll_udiv
    mov r2, r1
    mov r1, r0
    mov r0, r6
    bl _ZN9GameState18CalculateDeltaTimeEy
    bl GetCurrentTimestamp
    str r0, [sp, #0x8]
    str r1, [sp, #0x1c]
    b @L02193994
@L02193c40:
    mov r0, r7
    mov r1, #0x69
    bl func_02094b38
    mov r0, r7
    bl func_02094ab0
    ldr r0, =data_02108760
    mov r1, #0x64
    bl func_0205ea20
    add r0, sp, #0x24
    bl func_020a2010
    add r0, sp, #0x24
    bl func_020a2cf0
    add r0, sp, #0x24
    bl func_0202df68
@L02193c78:
    add sp, sp, #0x2ec
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif
