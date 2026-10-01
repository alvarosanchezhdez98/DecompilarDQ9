// The end of the battles of overlay 0: the results of a victory (the experience, the levels, the skill points, the
// spells and the skills learned, the gold, the items dropped, the quests and the titles), and the end of a defeat
#include "Scene/Overlay_23/BattleEnd.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "GameState/PartyMember.h"
#include "GameState/PlayRecords.h"
#include "Grotto/Main/ActiveGrottoClass.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/Memory.h"
#include "Text/MessageSystem.h"
#include "Util/Random.h"
#include "World/Object3D.h"
#include <std_library_functions.h>

#define REG_DISPCNT_SUB (*(volatile unsigned int*)0x04001000)
// The flags of a party member: 1 when they are down
#define MEMBER_FLAGS(member) (*(unsigned int*)(member)->unk_130)

// The party, which func_02010828 returns
struct Party
{
    char unk_0[0xf6c];
    unsigned int gold_;
    char unk_f70[8];
    unsigned char members_[4];
    unsigned char count_;
};

// The data of the current zone, which func_02012fe4 returns
struct ZoneData
{
    unsigned short id_;
    char unk_2[0x23ec - 2];
    ActiveGrottoClass grotto_;
};

// A monster's record in the monster list (see func_020ac020)
struct MonsterRecord
{
    // How many the party defeated
    unsigned int defeated_ : 10;
    unsigned int unk_0_10 : 1;
    // How many times it dropped its first and its second item
    unsigned int drops1_ : 7;
    unsigned int drops2_ : 7;
    unsigned int unk_0_25 : 7;
};

// A title (ttlname%d.gp2) or a guide shown after a battle
struct GuideEntry
{
    unsigned int unk_0;
    const char* text_;
    int unk_8;
};

// Flags of a game object
struct ObjectFlags
{
    unsigned char unk_0 : 4;
    unsigned char visible_ : 1;
    unsigned char unk_5 : 3;
};

// What func_ov017_021b8478 returns
struct Unknown_021b8478
{
    char unk_0[0xc];
    int unk_c;
};

// A quest (0x10 bytes)
struct QuestEntry
{
    unsigned int id_ : 9;
    unsigned int unk_0_9 : 5;
    // Its goal is reached
    unsigned int cleared_ : 1;
    unsigned int done_ : 1;
    unsigned int accepted_ : 1;
    unsigned int unk_0_17 : 15;
    char unk_4[0xc];
};

// What func_02094d6c returns: the quests
struct QuestList
{
    unsigned char count_;
    char unk_1[3];
    QuestEntry quests_[1];
};

// The drops of a monster (see func_02070fd0)
struct MonsterDrops
{
    char unk_0[2];
    unsigned char rarity2_;
    unsigned char rarity1_;
    unsigned short item2_;
    unsigned short item1_;
};

// What GetTreasureMapTypeFromItemID() writes
struct TreasureMapType
{
    // 1: a regular map, 2: a legacy boss's
    unsigned char type_;
    unsigned char boss_;
    unsigned short legacy_;
};

// A spell or a skill of a vocation that a member learns
struct LearnedSkill
{
    char unk_0[2];
    short name_;
};

// A new skill ability of skilltable.bin
struct SkillEntry
{
    unsigned short unk_0_0 : 11;
    unsigned short vocation_ : 5;
    short id_;
    unsigned int value_ : 5;
    unsigned int unk_4_5 : 7;
    unsigned int points_ : 8;
    unsigned int kind_ : 5;
    unsigned int unk_4_25 : 7;
};

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // The runtime's functions, for the assembly of the NONMATCHING functions
    void _fadd();
    void _fdiv();
    void _fflt();
    void _ffltu();
    void _ffix();
    void _ffixu();
    void _fls();
    void _fmul();
    void _u32_div_f();

    // The ID of overlay 13, which the linker script defines
    extern unsigned int OVERLAY_13_ID[];
    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    extern char data_02114e54[];
    extern const char* data_020f2a30;
    extern const char* data_020f2a38;

    GameResources* func_0200fb8c(GameState* gameState);
    GameObject* func_0200fea4(GameState* gameState, int object);
    PartyMember* func_0200ff1c(GameState* gameState, unsigned int member);
    int func_0200ff58(GameState* gameState, int member);
    int func_02010038(GameState* gameState, unsigned char* members);
    signed char func_02010088(PartyMember* member);
    signed char func_020100a8(GameState* gameState);
    int func_02010750(GameState* gameState);
    void func_0201075c(GameState* gameState, int);
    Party* func_02010828(GameState* gameState);
    int func_020114ec(GameState* gameState, unsigned char* members);
    int func_02011518(GameState* gameState, unsigned char index);
    void func_02011744(GameState* gameState);
    void func_020117cc(GameState* gameState, DetailedTreasureMapData* map);
    int func_02012444(void*, int);
    ZoneData* func_02012fe4();
    int func_0201b588(unsigned short zone);
    int func_0201b5d8(unsigned short zone);
    unsigned char func_0202053c(PartyMember* member);
    void* func_0202ae18();
    int func_0202b7d8(void*);
    int func_0202c1a4(void*);
    int func_0202c1c0(void*, int member);
    int func_0202c508(void*);
    int func_0202c540(void*);
    void func_0202e5c8(BattleCamera* camera, int, int, int);
    void func_0202e5d8(BattleCamera* camera, int, int, int);
    void func_0202ea4c(BattleCamera* camera);
    void func_0202ed0c(BattleCamera* camera, void*);
    void* func_0202ed64();
    int func_02032370(int);
    void func_02033b88(GameObject* object, int);
    void func_0203400c(GameObject* object);
    void func_02039e70();
    void func_0203a54c();
    void func_0203b4e8(GameResources* resources, int);
    void func_02042058(char* text, const char* append);
    MessageSystem* func_020421a0();
    void func_020426bc(void*, char*, int);
    void func_02043124(MessageSystem* messages);
    void func_02043204(MessageSystem* messages);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    int func_020457e0(MessageSystem* messages);
    void func_02046380(MessageSystem* messages);
    void func_02046574(MessageSystem* messages, int index, const char* text);
    void func_020465c0(MessageSystem* messages, int index, int value);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    void func_02048588(void*, GameObject* object);
    void func_02048614(GameObject* object);
    void func_02048850(GameObject* object, void*);
    void func_02048cf0(GameObject* object, int);
    void func_02049ae4(GameObject* object);
    void func_02049b54(Vector3i* position, GameObject* object);
    void func_02049c88(GameObject* object, void*);
    void func_02049f28(GameObject* object);
    void func_02049f3c(GameObject* object);
    PartyMemberData* func_02053c6c(PartyMember* member);
    unsigned int func_02053dfc(PartyMember* member);
    void func_02053ec8(PartyMember* member, int);
    void* func_02057924();
    void func_02057f00(void*, int);
    void func_0205d6a0(TextWindow* window, int);
    void func_0205ea20(void* sound, int id);
    void func_0205eaa0(void* sound, int id, int);
    void* func_0205ec34();
    int func_02061bd8(PartyMember* member);
    void func_0206df6c(void*, void*, int, int);
    int func_0206dfb0(void*, void*, int);
    void func_0206efc4(void* monsters);
    void func_0206f200(void* monsters, SafeAllocator* allocator, void* file, unsigned int size, short monster);
    MonsterEntry* func_0206f4f0(void* monsters, short id);
    MonsterDrops* func_02070fd0(void* drops, int monster);
    void func_020727d8(TextList* texts);
    void func_020728ac(TextList* texts, SafeAllocator* allocator, void* file, unsigned int size, int, int, int);
    const char* func_02072a68(TextList* texts, int id);
    void func_02076ccc(void*, int);
    void* func_020797dc();
    const char** func_02079e2c(void*, short);
    void func_0207cbe8(void*);
    int func_0207ccf0(void*, short item, int, int member, int, int, int);
    int func_0207d300(void*, short item, int, int);
    void* func_0207d78c();
    void func_0207da94(void*, unsigned char);
    int func_02082490(BattleLevelUp* levelUp, void* file, unsigned int size, unsigned char vocation,
        int experience);
    int func_02083b00(PartyMemberData* data, int);
    void func_02083cbc(PartyMemberData* data, BattleResultStats* before, BattleResultStats* after);
    void func_02083e28(PartyMemberData* data, int);
    int func_0208538c(PartyMemberData* data);
    int func_02086ef0(Party* party, int member);
    void* func_02094a00();
    void func_02094b30(void* music, int, int);
    void func_02094b34(void* music, int, int, int, int);
    void func_02094b40(void* music);
    int func_02094b4c(void* music);
    QuestList* func_02094d6c();
    int func_02096134(QuestList* quests, short quest);
    void func_0209a338(void* table);
    void func_0209a470(void* table, SafeAllocator* allocator, void* file, unsigned int size);
    SkillEntry* func_0209a594(void* table, unsigned short id);
    unsigned char func_0209a678(void* table, PartyMember* member, unsigned short* skills);
    void func_0209a804(void* table);
    void func_0209a8b4(void* table, SafeAllocator* allocator, void* file, unsigned int size);
    LearnedSkill* func_0209a9dc(void* table, unsigned char);
    signed char func_0209aa54(void* table, PartyMember* member, BattleEndSkills* skills, int);
    void func_0209c678(void*, int);
    void func_0209c6d8(void*, int);
    void func_0209c7fc(void*);
    int func_0209ca2c(void*);
    void func_0209e3dc(QuestScript* script, BattleData* data);
    void func_0209e46c(QuestScript* script);
    void func_0209fd64(QuestScript* script, SafeAllocator* allocator, void* file, unsigned int size);
    void func_0209fe10(QuestScript* script, int quest);
    void func_0209fe18(QuestScript* script);
    void func_0209fe9c(TitleScript* script);
    void func_0209fee4(TitleScript* script, SafeAllocator* allocator, void* file, unsigned int size);
    void func_0209ff64(TitleScript* script, int);
    void func_0209ff6c(TitleScript* script);
    void func_020a0110(PlayTime* time, int);
    void func_020a0300(PlayTime* time, int);
    void func_020a0330(PlayRecords* records, int);
    void func_020a0388(PlayRecords* records, int);
    void func_020a0858(PlayRecords* records, int);
    void func_020a13c4(void* guides);
    void func_020a13e4(void* guides, SafeAllocator* allocator, short* ids, unsigned short count, int);
    GuideEntry* func_020a15bc(void* guides, short id);
    void func_020a1940(unsigned int overlay);
    void func_020a1ef0(int);
    void func_020a1f4c(int);
    int func_020a35e0(BattleInfo* info, unsigned char member);
    void func_020a367c(BattleInfo* info, unsigned char member);
    void func_020abe84(int, short* id, MonsterRecord* record, int);
    int func_020ac020(int, short* id, MonsterRecord* record, int);
    int func_020d2ff0(const char* text);
    void* func_020d6c00();
    void func_020d6d18(int);
    void func_020d6f0c();
    void func_020d7334(void*, int);
    void func_020d784c(QuestMessages* messages);
    void func_020d7870(QuestMessages* messages, SafeAllocator* allocator, void* file, unsigned int size, int);
    const char* func_020d794c(QuestMessages* messages, short id);
    void func_020dcf7c(short item, MessageName* name);
    int func_020dd11c(unsigned char vocation, unsigned char skill);
    void func_020de824(void*);
    void func_020de848(void*);
    void func_020de868(void* icons);
    void func_020de9a4(void* names, SafeAllocator* allocator, void* file, unsigned int size, short* items, int count);
    void func_020dea64(void* icons, SafeAllocator* allocator, void* file, unsigned int size, const unsigned char* ids,
        int count);
    int func_020deb08(void* icons);
    void func_020dfc2c(TextTable* texts);
    void func_020dfc40(TextTable* texts);
    void func_020e0028(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size, short* ids, int count);
    const char* func_020e0434(TextTable* texts, short id);
    void* func_020e3808();
    void func_020e392c(void*, int, int);
    void func_020e3994(void*, int, int);
    void func_020e39d4(void*, int, int, int);
    void func_020e46c4(MessageName* name);
    void func_020e4864(const char* name, char* text, int, int, int, int);
    void func_020e4bf4(MessageName* name, int member);
    void func_020e4c74(MessageName* name, GameObject* object);
    void func_020e4ce8(MessageName* name, GameObject* object, int);
    const char* func_020e51cc(int);
    void func_020e526c(void* table);
    const char** func_020e5294(void* table, short id);
    void func_020e5604(void* table, SafeAllocator* allocator, void* file, unsigned int size);

    int func_ov000_02153e40(BattleData* data, short* objects, int count, int);
    int func_ov000_0215e9fc(BattleData* data, short* objects, int count, int);
    int func_ov000_0215ec1c(BattleData* data, short* objects, int count, int);
    void func_ov000_0215fa70(BattleData* data, short, int, int);
    void func_ov000_0215fa84(BattleData* data, short* type, short* monster, short* item);
    void func_ov000_02160d80(BattleScene* scene, int);
    BattleCamera* func_ov000_02160f14(BattleScene* scene);
    void func_ov000_02160fa8(BattleScene* scene, int flag);
    int func_ov000_02160fd4(BattleScene* scene, int flag);
    void func_ov000_021626a0(BattleScene* scene, int, int);
    void* func_ov000_02162d88(BattleScene* scene, unsigned short);
    void* func_ov000_02163524(BattleScene* scene);
    void func_ov000_021639b4(BattleScene* scene);
    void func_ov000_02163a7c(BattleScene* scene);
    void func_ov000_02163b60(BattleScene* scene);
    void func_ov000_02163b90(BattleScene* scene, int);
    int func_ov000_02163c80(BattleScene* scene, int);
    void func_ov000_02167dd8(BattleScene* scene);
    void func_ov000_0216d2d0(BattleCamera* camera);
    void func_ov000_0216d370(BattleCamera* camera, int, int, int);
    void func_ov000_0216d50c(BattleCamera* camera);
    void func_ov000_0216d530(BattleCamera* camera, int object);
    void func_ov000_0216e3c4(BattleCamera* camera);
    void func_ov000_02174a50(BattleMenu* menu, int);
    void func_ov000_021823a4(void*);
    int func_ov017_02195658();
    int func_ov017_021959b4();
    void func_ov017_021a23b0(GameResources* resources, int);
    void* func_ov017_021a278c(GameResources* resources, int);
    Unknown_021b8478* func_ov017_021b8478(void*);
    void func_ov017_021c9ad4(unsigned short);
    void func_ov017_021c9b20(unsigned short, int);
    void func_ov017_021c9e00(int member, int, int, int);
    void func_ov017_021cbfb8(unsigned short, int);
    void func_ov017_021cc730(int member, int, int, int);
    void func_ov017_021ccc34(int member);
    void func_ov017_021ccea4(int member, BattleEndSkills* skills, unsigned char count);
    void func_ov017_021cd0d8(int member, unsigned short* skills, unsigned char count);
    void func_ov017_021cd218(unsigned short, unsigned short gold, unsigned short level, unsigned char monsters,
        int victory, int monster);
    void func_ov017_021cd35c(unsigned short, void* drops, unsigned char count, signed char mask);
    void func_ov017_021cd4c8(unsigned short, unsigned short item, signed char mask);
    void func_ov017_021cd590(unsigned short, int* experience, unsigned char, int);
    void func_ov017_021ce704(int member);
    void func_ov017_021cfc74(int);
    void func_ov017_021d2400();
}




// The highest level, the icons of the quests' items and how many, and the size of the quests' heap
const short BattleScene::sMaxLevel = 99;
static const unsigned char sIconIds[] = {8, 9, 10};
const int BattleScene::sIconCount = 3;
const unsigned int BattleScene::sQuestHeapSize = 0xf000;
#ifndef NONMATCHING
// The initializer of End_Start's sounds, which the compiler creates from its C
static const int sSoundIds[] = {2, 1, 3, 0x1c, 0xe, -1};
#endif
static char sFormat[] = "%s";

static BattleEnd* sEnd;
static unsigned int sTimer;

static unsigned int GetMemberExperience(PartyMember* member);
static void SetVector(Vector3i* vector, int x, int y, int z);
static void SetMenuHidden(BattleMenu* menu, int hidden);
static int IsTitleScriptDone(TitleScript* script);
static void ClearPage(GuidePage* page);
static void SetPage(GuidePage* page, GuideEntry* entry);
static void SetPageTitle(GuidePage* page, const char* title);
static void SetGuideUnk400(GuideWindow* guide, unsigned char set);
static int IsQuestScriptDone(QuestScript* script);
static int IsMessageDone();
static void ResetMembers();
static int CanLearnSkill(int member);

// Clears what a monster's record counts. End_Results inlines every function it can (see there), but not this one
#pragma dont_inline on
void ClearRecord(MonsterRecord* record)
{
    record->defeated_ = 0;
    record->unk_0_10 = 0;
    record->drops1_ = 0;
    record->drops2_ = 0;
}
#pragma dont_inline reset

// The name of a monster that the texts write
MessageName GetMonsterName(MessageName name, MonsterEntry* monster)
{
    func_020e46c4(&name);
    name.text_ = monster->name_;
    name.unk_4 = monster->unk_14;
    name.unk_8_0 = monster->unk_18_0;
    name.unk_8_6 = monster->unk_18_6;
    name.unk_8_12 = monster->unk_18_12;
    name.unk_8_18 = monster->unk_18_18;
    name.unk_8_24 = monster->unk_18_24;
    name.unk_8_26 = monster->unk_18_26;
    name.unk_8_27 = monster->unk_18_27;
    name.unk_8_28 = monster->unk_18_28;
    name.unk_8_31 = 0;
    return name;
}

// Whether all the members of the party are dead
int IsPartyDead()
{
    GameState* gameState = GameState::GetInstance();
    Party* party = func_02010828(gameState);
    for (int i = 0; i < party->count_; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, party->members_[i]);
        if (member != NULL && func_02010088(member) == 0)
            return 0;
    }
    return 1;
}

void BattleScene::FadeBosses(int frames)
{
    GameState* gameState = GameState::GetInstance();
    for (int i = 0; i < bossCount_; i++)
    {
        GameObject* boss = func_0200fea4(gameState, bosses_[i]);
        if (frames > 0)
            boss->obj3D_.TransitionInheritedAlpha(0, frames);
        else
            boss->obj3D_.SetInheritedAlpha(0);
    }
}

// The states of the end of a victory (see BattleScene::End_Start()), which UpdateVictory() runs
extern BattleScene::StateFunction sEndStates[];
static int sEndStatesGuard;

void BattleScene::UpdateVictory()
{
    GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_ov017_0218b5b0();
    BattleInfo* info = info_;
    int member = func_ov017_02195658();
    if (member > 0)
    {
        void* unk = func_0207d78c();
        func_ov000_02174a50(&menu_, member);
        func_020a367c(info, member);
        func_0207da94(unk, member);
        if (member == info->leader_)
        {
            for (int i = 0; i < 4; i++)
            {
                if (func_020a35e0(info, i))
                {
                    info->leader_ = i;
                    break;
                }
            }
        }
    }
    if (!(sEndStatesGuard & 1))
    {
        sEndStates[17] = NULL;
        sEndStatesGuard |= 1;
    }
    endState_ = (this->*sEndStates[endState_])();
    int end = 0;
    if (func_ov017_021959b4() && busy_ == 0)
    {
        func_ov000_02160fa8(this, 0x2000000);
        end = 1;
    }
    if (end)
    {
        sEnd->experience_.Finish();
        if (resultWindow_ != NULL)
        {
            resultWindow_->Close();
            resultWindow_->Finish();
            resultWindow_ = NULL;
        }
        if (sEnd->task_ > -1)
            loader->RemoveTask(sEnd->task_);
        if (sEnd->task2_ > -1)
            loader->RemoveTask(sEnd->task2_);
        if (sEnd->task3_ > -1)
            loader->RemoveTask(sEnd->task3_);
        sEnd->task_ = -1;
        sEnd->task2_ = -1;
        sEnd->task3_ = -1;
        return;
    }
    if (resultWindow_ != NULL)
        resultWindow_->Update();
}

BattleScene::StateFunction sEndStates[18] = {
    &BattleScene::End_Start, &BattleScene::End_Results, &BattleScene::End_Load, &BattleScene::End_Victory,
    &BattleScene::End_LegacyBoss, &BattleScene::End_Experience, &BattleScene::End_ShowExperience,
    &BattleScene::End_LevelUp, &BattleScene::End_SkillPoints, &BattleScene::End_SkillArts,
    &BattleScene::End_Spells, &BattleScene::End_Gold, &BattleScene::End_NewSkillPoints, &BattleScene::End_Drops,
    &BattleScene::End_Quest, &BattleScene::End_Titles, &BattleScene::End_Finish,
};

// The file's strings: in the original the compiler pools them after the other data, which the assembly of the
// NONMATCHING functions can't reference, so they're one array here (see ItemInfoWindow.cpp)
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] =
    "data/bin/str_bres.gp2\0str_bres_<LG>.bin\0data/prm/skilltable.bin\0data/prm/spelltable.bin\0data/prm/mon_data.gp2\0"
    "mon_data_<LG>.nat\0stand\0data/prm/skl_art.gp2\0skl_art_<LG>.nat\0data/scenario/title_skl.stb\0"
    "data/bin/ttlname%d.gp2\0ttlname%d_<LG>.nat\0data/scenario/btl_qmes.gp2\0btl_qmes_<LG>.bin\0"
    "data/scenario/quest_btl_%d.stb\0data/scenario/title_btl.stb";
#define STRING(offset, text) (sStrings + (offset))
#endif

// NONMATCHING: the C matches 89.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and the literal pool: the original loads sEnd's address twice
#ifdef NONMATCHING
int BattleScene::End_Start()
{
    GameState::GetInstance();
    GameResources* resources = func_ov017_0218b5b0();
    void* unk = func_0202ae18();
    MessageSystem* messages = func_020421a0();
    func_020466e4(func_020d6c00(), 0x20000);
    func_ov017_021c9ad4(info_->unk_8);
    func_ov017_021a23b0(resources, info_->unk_8);
    func_0209c678(data_02109bf4, 0);
    func_ov000_0216d370(&camera_, 0, 0, 1);
    void* sounds = func_02057924();
    int ids[] = {2, 1, 3, 0x1c, 0xe, -1};
    for (int* id = ids; *id >= 0; id++)
        func_02057f00(sounds, *id);
    if (unk_ea4 != 0)
    {
        func_020d6f0c();
        func_020d6d18(unk_ea4);
        unk_ea4 = 0;
    }
    func_ov000_021823a4(unk_6ffc);
    func_02039e70();
    func_0203a54c();
    SafeAllocator* allocator = &resources->allocators_[5];
    allocator->Reset();
    BattleEnd* end = (BattleEnd*)allocator->Allocate(sizeof(BattleEnd));
    sEnd = end;
    end->step_ = 0;
    end->task_ = -1;
    end->task2_ = -1;
    end->task3_ = -1;
    end->nothing_ = 0;
    end->current_ = -1;
    end->skill_ = 0;
    end->newSkillCount_ = 0;
    end->drop_ = -1;
    end->member_ = 0;
    for (int i = 0; i < 4; i++)
        end->learns_[i] = 0;
    end->next_ = -1;
    memset(end->skills_, 0, 0x20);
    memset(end->skillCounts_, 0, sizeof(end->skillCounts_));
    memset(end->members_, 0, sizeof(end->members_));
    end->memberCount_ = 0;
    func_0209a338(end->skillTable_);
    func_0209a804(end->spellTable_);
    end->experience_.Initialize();
    func_0206efc4(end->monsters_);
    func_020a1ef0(1);
    sEnd->experience_.Load(allocator);
    if (func_0202c540(unk) != 0 && info_->legacyBoss_ != 0)
    {
        func_02046380(messages);
        DetailedTreasureMapData::LegacyBossMapData* legacy = &func_02012fe4()->grotto_.GetDetailedData()->legacy_;
        MessageName name;
        func_020e46c4(&name);
        void* monsters = info_->monsters_;
        for (int i = 0; i < 3; i++)
        {
            MonsterEntry* monster = func_0206f4f0(monsters, legacy->alternateVersionIDs_[i]);
            if (monster != NULL)
            {
                name = GetMonsterName(name, monster);
                messages->unk_10 = &name;
                break;
            }
        }
        char text[0x100];
        sprintf(text, func_020e51cc(200));
        func_0204500c(messages, text, 1, 0xe3);
        messages->busy_ = 1;
        func_0209c6d8(data_02109bf4, 0x36);
    }
    if (func_0202c508(unk) != 0 && info_->unk_c == 0x13)
    {
        void* unk2 = func_020e3808();
        func_020e3994(unk2, 1, -1);
        func_020e392c(unk2, 1, 0x71e8);
        func_020e39d4(unk2, 0, 1, 0x71e8);
    }
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11MessageNameaSERKS_(); // MessageName::operator=
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN15ExperienceTable10InitializeEv(); // ExperienceTable::Initialize
    void _ZN15ExperienceTable4LoadEP13SafeAllocator(); // ExperienceTable::Load
    void _ZN17ActiveGrottoClass15GetDetailedDataEv(); // ActiveGrottoClass::GetDetailedData
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int BattleScene::End_Start()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x134
    mov r4, r0
    bl _ZN9GameState11GetInstanceEv
    bl func_ov017_0218b5b0
    mov r5, r0
    bl func_0202ae18
    mov r6, r0
    bl func_020421a0
    mov r7, r0
    bl func_020d6c00
    mov r1, #0x20000
    bl func_020466e4
    ldr r0, [r4, #0x2a0]
    ldrh r0, [r0, #0x8]
    bl func_ov017_021c9ad4
    ldr r1, [r4, #0x2a0]
    mov r0, r5
    ldrh r1, [r1, #0x8]
    bl func_ov017_021a23b0
    ldr r0, =data_02109bf4
    mov r1, #0x0
    bl func_0209c678
    add r0, r4, #0x18
    mov r1, #0x0
    add r0, r0, #0xc00
    mov r2, r1
    mov r3, #0x1
    bl func_ov000_0216d370
    bl func_02057924
    add r12, sp, #0x1c
    ldr lr, =sSoundIds
    mov r8, r0
    ldmia lr!, {r0, r1, r2, r3}
    mov r9, r12
    stmia r12!, {r0, r1, r2, r3}
    ldmia lr, {r0, r1}
    stmia r12, {r0, r1}
    b @L021edcb0
@L021edca4:
    mov r0, r8
    bl func_02057f00
    add r9, r9, #0x4
@L021edcb0:
    ldr r1, [r9, #0x0]
    cmp r1, #0x0
    bge @L021edca4
    ldr r0, [r4, #0xea4]
    cmp r0, #0x0
    beq @L021edcdc
    bl func_020d6f0c
    ldr r0, [r4, #0xea4]
    bl func_020d6d18
    mov r0, #0x0
    str r0, [r4, #0xea4]
@L021edcdc:
    add r0, r4, #0x3fc
    add r0, r0, #0x6c00
    bl func_ov000_021823a4
    bl func_02039e70
    bl func_0203a54c
    add r5, r5, #0x9c
    mov r0, r5
    bl _ZN13SafeAllocator5ResetEv
    ldr r1, =0x2790
    mov r0, r5
    bl _ZN13SafeAllocator8AllocateEj
    ldr r1, =sEnd
    mov r8, r0
    mov r2, #0x0
    str r8, [r1, #0x0]
    str r2, [r8, #0x0]
    sub r0, r2, #0x1
    str r0, [r8, #0x4]
    str r0, [r8, #0x8]
    str r0, [r8, #0xc]
    strb r2, [r8, #0x10]
    str r0, [r8, #0x18]
    str r2, [r8, #0x70]
    strb r2, [r8, #0xe2]
    strb r0, [r8, #0xe4]
    strb r2, [r8, #0x11]
    mov r1, r2
    b @L021edd58
@L021edd4c:
    add r0, r8, r2
    strb r1, [r0, #0x12]
    add r2, r2, #0x1
@L021edd58:
    cmp r2, #0x4
    blt @L021edd4c
    mvn r3, #0x0
    add r0, r8, #0x1c
    mov r1, #0x0
    mov r2, #0x20
    strb r3, [r8, #0xe5]
    bl memset
    add r0, r8, #0x6c
    mov r1, #0x0
    mov r2, #0x4
    bl memset
    ldr r2, =0x2670
    add r0, r8, #0x118
    mov r1, #0x0
    bl memset
    add r0, r8, #0x2000
    mov r1, #0x0
    strb r1, [r0, #0x788]
    add r0, r8, #0xe8
    bl func_0209a338
    add r0, r8, #0xf0
    bl func_0209a804
    add r0, r8, #0xf4
    bl _ZN15ExperienceTable10InitializeEv
    add r0, r8, #0x10c
    bl func_0206efc4
    mov r0, #0x1
    bl func_020a1ef0
    ldr r0, =sEnd
    mov r1, r5
    ldr r0, [r0, #0x0]
    add r0, r0, #0xf4
    bl _ZN15ExperienceTable4LoadEP13SafeAllocator
    mov r0, r6
    bl func_0202c540
    cmp r0, #0x0
    ldrne r0, [r4, #0x2a0]
    ldrneb r0, [r0, #0x25]
    cmpne r0, #0x0
    beq @L021edebc
    mov r0, r7
    bl func_02046380
    bl func_02012fe4
    add r0, r0, #0x3ec
    add r0, r0, #0x2000
    bl _ZN17ActiveGrottoClass15GetDetailedDataEv
    add r5, r0, #0x4c
    add r0, sp, #0x10
    bl func_020e46c4
    ldr r0, [r4, #0x2a0]
    mov r8, #0x0
    add r9, r0, #0x278
    b @L021ede78
@L021ede30:
    add r0, r5, r8, lsl #0x1
    ldrsh r1, [r0, #0x4]
    add r0, r9, #0x400
    bl func_0206f4f0
    cmp r0, #0x0
    beq @L021ede74
    str r0, [sp, #0x0]
    add r1, sp, #0x10
    add r0, sp, #0x4
    ldmia r1, {r1, r2, r3}
    bl GetMonsterName
    add r0, sp, #0x10
    add r1, sp, #0x4
    bl _ZN11MessageNameaSERKS_
    add r0, sp, #0x10
    str r0, [r7, #0x10]
    b @L021ede80
@L021ede74:
    add r8, r8, #0x1
@L021ede78:
    cmp r8, #0x3
    blt @L021ede30
@L021ede80:
    mov r0, #0xc8
    bl func_020e51cc
    mov r1, r0
    add r0, sp, #0x34
    bl sprintf
    add r1, sp, #0x34
    mov r0, r7
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r0, #0x1
    str r0, [r7, #0x998]
    ldr r0, =data_02109bf4
    mov r1, #0x36
    bl func_0209c6d8
@L021edebc:
    mov r0, r6
    bl func_0202c508
    cmp r0, #0x0
    beq @L021edf14
    ldr r0, [r4, #0x2a0]
    ldr r0, [r0, #0xc]
    cmp r0, #0x13
    bne @L021edf14
    bl func_020e3808
    mov r1, #0x1
    sub r2, r1, #0x2
    mov r4, r0
    bl func_020e3994
    ldr r2, =0x71e8
    mov r0, r4
    mov r1, #0x1
    bl func_020e392c
    ldr r3, =0x71e8
    mov r0, r4
    mov r1, #0x0
    mov r2, #0x1
    bl func_020e39d4
@L021edf14:
    mov r0, #0x1
    add sp, sp, #0x134
    ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
}
#endif

MessageName& MessageName::operator=(const MessageName& other)
{
    text_ = other.text_;
    unk_4 = other.unk_4;
    ((unsigned int*)this)[2] = ((const unsigned int*)&other)[2];
    return *this;
}

// NONMATCHING: the C matches 92.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Registers of the first loop and of the victory's kinds. The copy of PartyMemberData is its implicit operator=,
// which the original inlines: always_inline does it here (and dont_inline keeps ClearRecord a call)
#ifdef NONMATCHING
inline unsigned int GetScaled(int value, float multiplier) { return value * multiplier; }
inline unsigned int GetScaled(unsigned int value, float multiplier) { return value * multiplier; }
#pragma always_inline on
int BattleScene::End_Results()
{
    long flag;
    int count;
    int leader;
    int kinds;
    BattleMonster* monster;
    GameState* gameState;
    long ids[8];
    int experience[4];
    gameState = GameState::GetInstance();
    if (sEnd->experience_.Update() == 0)
        return endState_;
    if (BackgroundLoader::GetInstance()->GetNumQueuedTasks() > 0)
        return endState_;
    GameResources* resources = func_ov017_0218b5b0();
    BattleData* data2;
    GameObject* object;
    MessageSystem* messages = func_020421a0();
    void* unk = func_0202ae18();
    unsigned int defeated;
    long i;
    PlayRecords records;
    short objects[0x10];
    BattleData* data = data_;
    if (data != NULL)
    {
        GameState* gameState2 = GameState::GetInstance();
        int count = 0;
        count += func_ov000_0215e9fc(data, objects, 0x10, 0);
        count += func_ov000_0215ec1c(data, &objects[count], 0x10 - count, 0);
        for (int i = 0; i < count; i++)
        {
            GameObject* object = gameState2->GetCombatantByIndex(objects[i]);
            if (object != NULL)
                func_02049ae4(object);
        }
    }
    ResetMembers();
    if (!func_0202b7d8(unk) || info_->leader_ == func_0202c1a4(unk))
    {
        int monsterCount;
        long leader;
        earnedExperience_ = GetScaled(data_->experience_, data_->experienceMultiplier_);
        unsigned int total;
        earnedGold_ = GetScaled(data_->gold_, data_->goldMultiplier_);
        turns_ = data_->unk_8e20;
        short monsters[4];
        int count = func_ov000_0215e9fc(data_, monsters, 4, 1);
        monsterMask_ = 0;
        for (int i = 0; i < count; i++)
            monsterMask_ |= 1 << monsters[i];
        for (int i = 0; i < 4; i++)
        {
            if (func_020a35e0(info_, i))
                experience_[i] = GetExperience(i, 0);
        }
        data2 = data_;
        monsterCount = data2->monsterCount_;
        BattleMonster* defeated = data2->monsters_;
        if (monsterCount == 0)
        {
            unsigned char* unk2 = &data2->unk_81b0;
            flag = 0;
            unsigned char unk3 = unk2[0];
            if (unk3 <= data2->unk_8e15)
                flag = 1;
            if (((BattleData*)(unk2 - 0x81b0))->unk_81b1_6 > 1)
            {
                victory_ = flag == 0 ? 5 : 8;
                victoryMonster_ = 0;
            }
            else if (unk3 > 1)
            {
                victoryMonster_ = *(unsigned short*)(0x4e + unk2);
                victory_ = flag == 0 ? 4 : 7;
                victoryMonster_ = *(unsigned short*)(unk2 + 0x4e);
            }
            else
            {
                victory_ = flag == 0 ? 3 : 6;
                victoryMonster_ = *(unsigned short*)(unk2 + 0x4e);
            }
        }
        else
        {
            total = 0;
            kinds = 0;

            for (int i = 0; i < monsterCount; i++)
            {
                total += defeated[i].count_;
                long j;
                for (j = 0; j < kinds; j++)
                {
                    if (defeated[i].id_ == ids[j])
                        break;
                }
                if (j == kinds)
                    ids[kinds++] = defeated[i].id_;
            }
            if (total == 1)
            {
                victory_ = 0;
                victoryMonster_ = defeated->id_;
            }
            else if (kinds > 1)
            {
                victory_ = 2;
                victoryMonster_ = 0;
            }
            else
            {
                victory_ = 1;
                victoryMonster_ = defeated->id_;
            }
        }
        ComputeDrops();
        func_ov017_021cd218(info_->unk_8, earnedGold_, turns_, monsterMask_, victory_, victoryMonster_);
        if (info_->legacyBoss_ == 0)
        {
            func_ov017_021cd590(info_->unk_8, experience_, 0, 0);
            func_ov017_021cd35c(info_->unk_8, drops_, dropCount_, memberMask_);
            if (map_ != 0)
                func_ov017_021cd4c8(info_->unk_8, mapItem_, memberMask_);
            if (data_->unk_8e34 != 0)
            {
                unsigned int base = GetScaled(data_->unk_8e34, data_->experienceMultiplier_);
                GameState* gameState2 = GameState::GetInstance();

                for (int i = 0; i < 4; i++)
                {
                    if (func_020a35e0(info_, i))
                        experience[i] = GetExperience(i, base);
                }
                func_ov017_021cd590(info_->unk_8, experience, 0, 1);
                int leader = func_020100a8(gameState2);
                PlayRecords records;
                func_020ac4c0(&records);
                func_020a0858(&records, experience[leader]);
                func_020a0300(&records.unk_68, experience[leader]);
                func_020ac494(&records);
            }
        }
    }
    else
    {
        if (resources->unknown_42e2 != 0)
            func_ov000_02160fa8(this, 0x2000000);
        if (func_0202c540(unk) && info_->legacyBoss_ != 0)
            messages->unk_19b2 = 0;
        if (!func_ov000_02160fd4(this, 0x2000))
            return endState_;
        if (!func_ov000_02160fd4(this, 0x4000))
            return endState_;
        if (!func_ov000_02160fd4(this, 0x8000))
            return endState_;
    }
    BattleMonster* monsters;
    int monsterCount;
    monsterCount = data_->monsterCount_;
    monsters = data_->monsters_;
    for (i = 0; i < monsterCount; i++)
    {
        monster = &monsters[i];
        MonsterRecord record;
        short id;
        ClearRecord(&record);
        id = monster->record_;
        if (func_020ac020(0, &id, &record, 1))
        {
            unsigned int defeated = record.defeated_ + monster->count_;
            if (defeated > 999)
                defeated = 999;
            record.defeated_ = defeated;
            if (monster->unk_6 != 0)
                record.unk_0_10 = monster->unk_6;
            func_020abe84(0, &id, &record, 1);
        }
    }
    BattleResultMember* member = sEnd->members_;
    for (int i = 0; i < 4; i++)
    {
        if (!func_020a35e0(info_, i))
            continue;
        PartyMember* partyMember = func_0200ff1c(gameState, i);
        if (partyMember == NULL)
            continue;
        member->id_ = i;
        member->vocation_ = partyMember->data_->vocation_;
        member->level_ = func_0202053c(partyMember);
        member->dead_ = func_02010088(partyMember);
        member->experience_ = experience_[i] + GetMemberExperience(partyMember);
        member->data_ = *func_02053c6c(partyMember);
        strcpy(member->name_, partyMember->status_->name_);
        member++;
        sEnd->memberCount_++;
    }
    sEnd->idCount_ = func_020114ec(gameState, sEnd->ids_);
    if (info_->legacyBoss_ == 0)
        sEnd->nothing_ = AddExperience(info_, experience_, &gold_, 0) ? 1 : 0;
    if (func_0202c540(unk) && info_->unk_c == 0x13)
        func_020e39d4(func_020e3808(), 0, 1, 0x71e8);
    return 2;
}
#pragma always_inline reset
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11BattleScene12ComputeDropsEv(); // BattleScene::ComputeDrops
    void _ZN11BattleScene13AddExperienceEP10BattleInfoPiS2_i(); // BattleScene::AddExperience
    void _ZN11BattleScene13GetExperienceEij(); // BattleScene::GetExperience
    void _ZN15ExperienceTable6UpdateEv(); // ExperienceTable::Update
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader17GetNumQueuedTasksEv(); // BackgroundLoader::GetNumQueuedTasks
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState19GetCombatantByIndexEi(); // GameState::GetCombatantByIndex
}

asm int BattleScene::End_Results()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x124
    mov r7, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    str r0, [sp, #0x8]
    ldr r0, [r1, #0x0]
    add r0, r0, #0xf4
    bl _ZN15ExperienceTable6UpdateEv
    cmp r0, #0x0
    ldreq r0, [r7, #0xeac]
    beq @L021eea84
    bl _ZN16BackgroundLoader11GetInstanceEv
    bl _ZN16BackgroundLoader17GetNumQueuedTasksEv
    cmp r0, #0x0
    ldrgt r0, [r7, #0xeac]
    bgt @L021eea84
    bl func_ov017_0218b5b0
    mov r4, r0
    bl func_020421a0
    mov r5, r0
    bl func_0202ae18
    ldr r6, [r7, #0x29c]
    str r0, [sp, #0x10]
    cmp r6, #0x0
    beq @L021ee030
    bl _ZN9GameState11GetInstanceEv
    mov r8, #0x0
    mov r9, r0
    add r1, sp, #0x24
    mov r0, r6
    mov r2, #0x10
    mov r3, r8
    bl func_ov000_0215e9fc
    add r8, r0, #0x0
    add r1, sp, #0x24
    mov r0, r6
    rsb r2, r8, #0x10
    add r1, r1, r8, lsl #0x1
    mov r3, #0x0
    bl func_ov000_0215ec1c
    add r8, r8, r0
    mov r6, #0x0
    add r10, sp, #0x24
    b @L021ee028
@L021ee008:
    mov r0, r6, lsl #0x1
    ldrsh r1, [r10, r0]
    mov r0, r9
    bl _ZN9GameState19GetCombatantByIndexEi
    cmp r0, #0x0
    beq @L021ee024
    bl func_02049ae4
@L021ee024:
    add r6, r6, #0x1
@L021ee028:
    cmp r6, r8
    blt @L021ee008
@L021ee030:
    bl ResetMembers
    ldr r0, [sp, #0x10]
    bl func_0202b7d8
    cmp r0, #0x0
    beq @L021ee05c
    ldr r0, [sp, #0x10]
    bl func_0202c1a4
    ldr r1, [r7, #0x2a0]
    ldrsb r1, [r1, #0x2a]
    cmp r1, r0
    bne @L021ee46c
@L021ee05c:
    ldr r0, [r7, #0x29c]
    add r1, r0, #0x8000
    ldr r0, [r1, #0xe28]
    ldr r4, [r1, #0xe3c]
    bl _fflt
    mov r1, r4
    bl _fmul
    bl _ffixu
    add r1, r7, #0x5000
    str r0, [r1, #0x8c0]
    ldr r0, [r7, #0x29c]
    add r1, r0, #0x8000
    ldr r0, [r1, #0xe2c]
    ldr r4, [r1, #0xe40]
    bl _fflt
    mov r1, r4
    bl _fmul
    bl _ffixu
    add r1, r7, #0x5000
    str r0, [r1, #0x8c4]
    ldr r0, [r7, #0x29c]
    add r2, r7, #0x5800
    add r0, r0, #0x8000
    ldr r0, [r0, #0xe20]
    add r1, sp, #0x1c
    strh r0, [r2, #0xcc]
    ldr r0, [r7, #0x29c]
    mov r2, #0x4
    mov r3, #0x1
    bl func_ov000_0215e9fc
    mov r6, #0x0
    add r1, r7, #0x5000
    strb r6, [r1, #0x8c8]
    add r1, r7, #0xc8
    add r5, r1, #0x5800
    mov r3, #0x1
    add r2, sp, #0x1c
    b @L021ee10c
@L021ee0f4:
    mov r1, r6, lsl #0x1
    ldrb r4, [r5, #0x0]
    ldrsh r1, [r2, r1]
    add r6, r6, #0x1
    orr r1, r4, r3, lsl r1
    strb r1, [r5, #0x0]
@L021ee10c:
    cmp r6, r0
    blt @L021ee0f4
    mov r5, #0x0
    mov r4, r5
    b @L021ee154
@L021ee120:
    ldr r0, [r7, #0x2a0]
    and r1, r5, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021ee150
    mov r0, r7
    mov r1, r5
    mov r2, r4
    bl _ZN11BattleScene13GetExperienceEij
    add r1, r7, r5, lsl #0x2
    add r1, r1, #0x5000
    str r0, [r1, #0x758]
@L021ee150:
    add r5, r5, #0x1
@L021ee154:
    cmp r5, #0x4
    blt @L021ee120
    ldr r3, [r7, #0x29c]
    add r1, r3, #0x8000
    ldr r0, [r1, #0xe30]
    add r2, r3, #0x66
    cmp r0, #0x0
    add r5, r2, #0x8d00
    bne @L021ee21c
    add r0, r3, #0x1b0
    add r0, r0, #0x8000
    ldrb r2, [r1, #0xe15]
    ldrb r4, [r1, #0x1b0]
    ldrb r1, [r0, #0x1]
    cmp r4, r2
    mov r1, r1, lsl #0x18
    mov r2, #0x0
    mov r1, r1, lsr #0x1e
    movls r2, #0x1
    cmp r1, #0x1
    bls @L021ee1cc
    cmp r2, #0x0
    moveq r1, #0x5
    add r0, r7, #0x5000
    movne r1, #0x8
    strb r1, [r0, #0x8c9]
    add r0, r7, #0x5800
    mov r1, #0x0
    strh r1, [r0, #0xca]
    b @L021ee2e8
@L021ee1cc:
    cmp r4, #0x1
    bls @L021ee1f8
    cmp r2, #0x0
    moveq r2, #0x4
    add r1, r7, #0x5000
    movne r2, #0x7
    strb r2, [r1, #0x8c9]
    ldrh r1, [r0, #0x4e]
    add r0, r7, #0x5800
    strh r1, [r0, #0xca]
    b @L021ee2e8
@L021ee1f8:
    cmp r2, #0x0
    moveq r2, #0x3
    add r1, r7, #0x5000
    movne r2, #0x6
    strb r2, [r1, #0x8c9]
    ldrh r1, [r0, #0x4e]
    add r0, r7, #0x5800
    strh r1, [r0, #0xca]
    b @L021ee2e8
@L021ee21c:
    mov r1, #0x0
    mov r2, r1
    mov r3, r1
    add r10, sp, #0x54
    mov r8, #0xa
    b @L021ee288
@L021ee234:
    mul r6, r3, r8
    ldrh r9, [r5, r6]
    mov r4, #0x0
    add r12, r5, r6
    mov r9, r9, lsl #0x12
    add r1, r1, r9, lsr #0x15
    b @L021ee264
@L021ee250:
    ldrh r11, [r12, #0x2]
    ldr r9, [r10, r4, lsl #0x2]
    cmp r11, r9
    beq @L021ee26c
    add r4, r4, #0x1
@L021ee264:
    cmp r4, r2
    blt @L021ee250
@L021ee26c:
    cmp r4, r2
    addeq r4, r5, r6
    ldreqh r4, [r4, #0x2]
    moveq r6, r2
    addeq r2, r2, #0x1
    streq r4, [r10, r6, lsl #0x2]
    add r3, r3, #0x1
@L021ee288:
    cmp r3, r0
    blt @L021ee234
    cmp r1, #0x1
    bne @L021ee2b4
    add r0, r7, #0x5000
    mov r1, #0x0
    strb r1, [r0, #0x8c9]
    ldrh r1, [r5, #0x2]
    add r0, r7, #0x5800
    strh r1, [r0, #0xca]
    b @L021ee2e8
@L021ee2b4:
    cmp r2, #0x1
    add r0, r7, #0x5000
    movle r1, #0x1
    strleb r1, [r0, #0x8c9]
    ldrleh r1, [r5, #0x2]
    addle r0, r7, #0x5800
    strleh r1, [r0, #0xca]
    ble @L021ee2e8
    mov r1, #0x2
    strb r1, [r0, #0x8c9]
    add r0, r7, #0x5800
    mov r1, #0x0
    strh r1, [r0, #0xca]
@L021ee2e8:
    mov r0, r7
    bl _ZN11BattleScene12ComputeDropsEv
    add r3, r7, #0x5000
    ldrb r0, [r3, #0x8c9]
    add r2, r7, #0x5800
    str r0, [sp, #0x0]
    ldrh r0, [r2, #0xca]
    str r0, [sp, #0x4]
    ldr r0, [r7, #0x2a0]
    ldr r1, [r3, #0x8c4]
    ldrh r0, [r0, #0x8]
    mov r1, r1, lsl #0x10
    ldrh r2, [r2, #0xcc]
    ldrb r3, [r3, #0x8c8]
    mov r1, r1, lsr #0x10
    bl func_ov017_021cd218
    ldr r1, [r7, #0x2a0]
    ldrb r0, [r1, #0x25]
    cmp r0, #0x0
    bne @L021ee4f4
    ldrh r0, [r1, #0x8]
    add r1, r7, #0x358
    mov r2, #0x0
    mov r3, r2
    add r1, r1, #0x5400
    bl func_ov017_021cd590
    ldr r0, [r7, #0x2a0]
    add r2, r7, #0x5000
    add r3, r7, #0x5900
    add r1, r7, #0x8d0
    ldrh r0, [r0, #0x8]
    ldrb r2, [r2, #0x900]
    ldrsb r3, [r3, #0x1]
    add r1, r1, #0x5000
    bl func_ov017_021cd35c
    add r0, r7, #0x6000
    ldr r0, [r0, #0xe24]
    cmp r0, #0x0
    beq @L021ee3a0
    ldr r0, [r7, #0x2a0]
    add r1, r7, #0x6e00
    add r2, r7, #0x5900
    ldrh r0, [r0, #0x8]
    ldrh r1, [r1, #0x28]
    ldrsb r2, [r2, #0x1]
    bl func_ov017_021cd4c8
@L021ee3a0:
    ldr r0, [r7, #0x29c]
    add r1, r0, #0x8000
    ldr r0, [r1, #0xe34]
    cmp r0, #0x0
    beq @L021ee4f4
    ldr r4, [r1, #0xe3c]
    bl _ffltu
    mov r1, r4
    bl _fmul
    bl _ffixu
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    mov r6, r0
    mov r8, #0x0
    add r4, sp, #0x44
    b @L021ee40c
@L021ee3e0:
    ldr r0, [r7, #0x2a0]
    and r1, r8, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021ee408
    mov r0, r7
    mov r1, r8
    mov r2, r5
    bl _ZN11BattleScene13GetExperienceEij
    str r0, [r4, r8, lsl #0x2]
@L021ee408:
    add r8, r8, #0x1
@L021ee40c:
    cmp r8, #0x4
    blt @L021ee3e0
    ldr r0, [r7, #0x2a0]
    add r1, sp, #0x44
    ldrh r0, [r0, #0x8]
    mov r2, #0x0
    mov r3, #0x1
    bl func_ov017_021cd590
    mov r0, r6
    bl func_020100a8
    mov r4, r0
    add r0, sp, #0x74
    bl func_020ac4c0
    add r1, sp, #0x44
    ldr r1, [r1, r4, lsl #0x2]
    add r0, sp, #0x74
    bl func_020a0858
    add r1, sp, #0x44
    ldr r1, [r1, r4, lsl #0x2]
    add r0, sp, #0xdc
    bl func_020a0300
    add r0, sp, #0x74
    bl func_020ac494
    b @L021ee4f4
@L021ee46c:
    add r0, r4, #0x4000
    ldrb r0, [r0, #0x2e2]
    cmp r0, #0x0
    beq @L021ee488
    mov r0, r7
    mov r1, #0x2000000
    bl func_ov000_02160fa8
@L021ee488:
    ldr r0, [sp, #0x10]
    bl func_0202c540
    cmp r0, #0x0
    ldrne r0, [r7, #0x2a0]
    ldrneb r0, [r0, #0x25]
    cmpne r0, #0x0
    addne r0, r5, #0x1000
    movne r1, #0x0
    strneb r1, [r0, #0x9b2]
    mov r0, r7
    mov r1, #0x2000
    bl func_ov000_02160fd4
    cmp r0, #0x0
    ldreq r0, [r7, #0xeac]
    beq @L021eea84
    mov r0, r7
    mov r1, #0x4000
    bl func_ov000_02160fd4
    cmp r0, #0x0
    ldreq r0, [r7, #0xeac]
    beq @L021eea84
    mov r0, r7
    mov r1, #0x8000
    bl func_ov000_02160fd4
    cmp r0, #0x0
    ldreq r0, [r7, #0xeac]
    beq @L021eea84
@L021ee4f4:
    ldr r1, [r7, #0x29c]
    mov r4, #0x400
    add r0, r1, #0x8000
    add r1, r1, #0x66
    mov r8, #0x0
    add r9, r1, #0x8d00
    ldr r10, [r0, #0xe30]
    rsb r4, r4, #0x0
    ldr r5, =0x3e7
    b @L021ee5b4
@L021ee51c:
    mov r0, #0xa
    mla r6, r8, r0, r9
    add r0, sp, #0x18
    bl ClearRecord
    ldrsh r2, [r6, #0x4]
    mov r0, #0x0
    add r1, sp, #0x14
    strh r2, [sp, #0x14]
    add r2, sp, #0x18
    mov r3, #0x1
    bl func_020ac020
    cmp r0, #0x0
    beq @L021ee5b0
    ldrh r0, [r6, #0x0]
    ldr r1, [sp, #0x18]
    add r2, sp, #0x18
    mov r0, r0, lsl #0x12
    mov r1, r1, lsl #0x16
    mov r0, r0, lsr #0x15
    add r0, r0, r1, lsr #0x16
    ldr r1, [sp, #0x18]
    cmp r0, r5
    movhi r0, r5
    and r0, r0, r4, lsr #0x16
    and r1, r1, r4
    orr r1, r1, r0
    str r1, [sp, #0x18]
    ldrb r0, [r6, #0x6]
    mov r3, #0x1
    cmp r0, #0x0
    bicne r1, r1, #0x400
    movne r0, r0, lsl #0x1f
    orrne r0, r1, r0, lsr #0x15
    strne r0, [sp, #0x18]
    mov r0, #0x0
    add r1, sp, #0x14
    bl func_020abe84
@L021ee5b0:
    add r8, r8, #0x1
@L021ee5b4:
    cmp r8, r10
    blt @L021ee51c
    ldr r0, =sEnd
    mov r5, #0x0
    ldr r0, [r0, #0x0]
    add r4, r0, #0x118
    b @L021ee9d4
@L021ee5d0:
    ldr r0, [r7, #0x2a0]
    and r1, r5, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021ee9d0
    ldr r0, [sp, #0x8]
    mov r1, r5
    bl func_0200ff1c
    movs r6, r0
    beq @L021ee9d0
    strb r5, [r4, #0x0]
    ldr r1, [r6, #0x150]
    ldr r1, [r1, #0x950]
    strb r1, [r4, #0x1]
    bl func_0202053c
    strb r0, [r4, #0x2]
    mov r0, r6
    bl func_02010088
    strb r0, [r4, #0x3]
    mov r0, r6
    bl GetMemberExperience
    add r1, r7, r5, lsl #0x2
    add r1, r1, #0x5000
    ldr r1, [r1, #0x758]
    add r0, r1, r0
    str r0, [r4, #0x4]
    mov r0, r6
    bl func_02053c6c
    mov r10, r0
    mov r12, r10
    ldmia r12!, {r0, r1, r2, r3}
    add r9, r4, #0x38
    stmia r9!, {r0, r1, r2, r3}
    mov r0, r12
    ldmia r0, {r0, r1}
    stmia r9, {r0, r1}
    add r8, r10, #0x18
    add lr, r4, #0x50
    mov r11, #0x2
    str r12, [sp, #0xc]
@L021ee670:
    ldmia r8!, {r0, r1, r2, r3}
    stmia lr!, {r0, r1, r2, r3}
    subs r11, r11, #0x1
    bne @L021ee670
    ldr r0, [r8, #0x0]
    add r11, r10, #0x3c
    str r0, [lr, #0x0]
    add r9, r4, #0x74
    mov r8, #0x5
@L021ee694:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee694
    ldmia r11, {r0, r1}
    stmia r9, {r0, r1}
    add r11, r10, #0x94
    add r9, r4, #0xcc
    mov r8, #0xa
@L021ee6b8:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee6b8
    ldr r0, [r11, #0x0]
    add r11, r10, #0x138
    str r0, [r9, #0x0]
    add r9, r4, #0x170
    mov r8, #0x3
@L021ee6dc:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee6dc
    ldr r0, [r11, #0x0]
    add r3, r10, #0x16c
    str r0, [r9, #0x0]
    add r2, r4, #0x1a4
    mov r1, #0xd
@L021ee700:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L021ee700
    add r0, r10, #0x86
    add r1, r4, #0xbe
    add r2, r1, #0x100
    add r3, r0, #0x100
    mov r1, #0xd
@L021ee724:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021ee724
    add r11, r10, #0x194
    add r9, r4, #0x1cc
    mov r8, #0x16
@L021ee740:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee740
    add r11, r10, #0x2f4
    add r9, r4, #0x32c
    mov r8, #0x16
@L021ee75c:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee75c
    add r0, r10, #0x54
    add r1, r4, #0x8c
    add r2, r1, #0x400
    add r3, r0, #0x400
    mov r1, #0x8
@L021ee780:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L021ee780
    add r0, r10, #0x64
    add r1, r4, #0x9c
    add r2, r1, #0x400
    add r3, r0, #0x400
    mov r1, #0x1b
@L021ee7a4:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021ee7a4
    add r0, r4, #0xb8
    add r2, r10, #0x480
    add r0, r0, #0x400
    ldmia r2, {r2, r3}
    stmia r0, {r2, r3}
    add r1, r10, #0x88
    add r3, r1, #0x400
    add r2, r4, #0x4c0
    mov r1, #0xe
@L021ee7d8:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L021ee7d8
    add r0, r10, #0xa4
    add r1, r4, #0xdc
    add r2, r1, #0x400
    add r3, r0, #0x400
    mov r1, #0x60
@L021ee7fc:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L021ee7fc
    add r0, r10, #0x500
    ldrh r3, [r0, #0x64]
    add r1, r4, #0x500
    add r2, r4, #0x1a8
    strh r3, [r1, #0x9c]
    ldrh r9, [r0, #0x66]
    add r3, r2, #0x400
    add r8, r10, #0x570
    strh r9, [r1, #0x9e]
    ldrsh r0, [r0, #0x68]
    mov r2, #0x180
    strh r0, [r1, #0xa0]
    ldrb r0, [r10, #0x56a]
    strb r0, [r4, #0x5a2]
    ldrb r0, [r10, #0x56b]
    strb r0, [r4, #0x5a3]
    ldrb r0, [r10, #0x56c]
    strb r0, [r4, #0x5a4]
    ldrb r0, [r10, #0x56d]
    strb r0, [r4, #0x5a5]
    ldrb r0, [r10, #0x56e]
    strb r0, [r4, #0x5a6]
    ldrb r0, [r10, #0x56f]
    strb r0, [r4, #0x5a7]
@L021ee86c:
    ldrb r0, [r8], #0x1
    subs r2, r2, #0x1
    strb r0, [r3], #0x1
    bne @L021ee86c
    add r0, r4, #0x328
    add r11, r10, #0x6f0
    add r9, r0, #0x400
    mov r8, #0x16
@L021ee88c:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee88c
    add r0, r4, #0x88
    add r11, r10, #0x850
    add r9, r0, #0x800
    mov r8, #0x9
@L021ee8ac:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    subs r8, r8, #0x1
    bne @L021ee8ac
    ldmia r11, {r0, r1, r2}
    stmia r9, {r0, r1, r2}
    add r3, r10, #0xec
    add r8, r4, #0x124
    add r3, r3, #0x800
    add r2, r8, #0x800
    mov r1, #0x24
@L021ee8d8:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021ee8d8
    add r0, r4, #0x148
    add r3, r10, #0x910
    add r2, r0, #0x800
    mov r1, #0x9
@L021ee8f8:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021ee8f8
    add r0, r10, #0x11c
    add r1, r4, #0x154
    add r8, r0, #0x800
    add r9, r1, #0x800
    ldmia r8!, {r0, r1, r2, r3}
    stmia r9!, {r0, r1, r2, r3}
    ldmia r8, {r0, r1}
    add r2, r10, #0x134
    stmia r9, {r0, r1}
    add r3, r4, #0x16c
    add r8, r2, #0x800
    add r2, r3, #0x800
    mov r1, #0x18
@L021ee93c:
    ldrb r0, [r8], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021ee93c
    ldr r0, [r10, #0x94c]
    add r1, r10, #0x900
    str r0, [r4, #0x984]
    ldr r0, [r10, #0x950]
    add r2, r4, #0x900
    str r0, [r4, #0x988]
    ldrh r3, [r1, #0x54]
    add r0, r4, #0x8
    strh r3, [r2, #0x8c]
    ldrsh r3, [r1, #0x56]
    strh r3, [r2, #0x8e]
    ldrsh r3, [r1, #0x58]
    strh r3, [r2, #0x90]
    ldrsh r3, [r1, #0x5a]
    strh r3, [r2, #0x92]
    ldrsh r3, [r1, #0x5c]
    strh r3, [r2, #0x94]
    ldrsh r3, [r1, #0x5e]
    strh r3, [r2, #0x96]
    ldrh r3, [r1, #0x60]
    strh r3, [r2, #0x98]
    ldrh r1, [r1, #0x62]
    strh r1, [r2, #0x9a]
    ldr r1, [r6, #0x134]
    bl strcpy
    ldr r1, =sEnd
    add r0, r4, #0x19c
    ldr r1, [r1, #0x0]
    add r4, r0, #0x800
    add r0, r1, #0x2000
    ldrb r1, [r0, #0x788]
    add r1, r1, #0x1
    strb r1, [r0, #0x788]
@L021ee9d0:
    add r5, r5, #0x1
@L021ee9d4:
    cmp r5, #0x4
    blt @L021ee5d0
    ldr r1, =sEnd
    ldr r0, [sp, #0x8]
    ldr r1, [r1, #0x0]
    add r1, r1, #0x89
    add r1, r1, #0x2700
    bl func_020114ec
    ldr r1, =sEnd
    ldr r1, [r1, #0x0]
    add r1, r1, #0x2000
    strb r0, [r1, #0x78d]
    ldr r1, [r7, #0x2a0]
    ldrb r0, [r1, #0x25]
    cmp r0, #0x0
    bne @L021eea4c
    add r2, r7, #0x358
    add r3, r7, #0x368
    mov r4, #0x0
    mov r0, r7
    add r2, r2, #0x5400
    add r3, r3, #0x5400
    str r4, [sp, #0x0]
    bl _ZN11BattleScene13AddExperienceEP10BattleInfoPiS2_i
    cmp r0, #0x0
    ldr r0, =sEnd
    movne r1, #0x1
    ldr r0, [r0, #0x0]
    moveq r1, r4
    strb r1, [r0, #0x10]
@L021eea4c:
    ldr r0, [sp, #0x10]
    bl func_0202c540
    cmp r0, #0x0
    beq @L021eea80
    ldr r0, [r7, #0x2a0]
    ldr r0, [r0, #0xc]
    cmp r0, #0x13
    bne @L021eea80
    bl func_020e3808
    ldr r3, =0x71e8
    mov r1, #0x0
    mov r2, #0x1
    bl func_020e39d4
@L021eea80:
    mov r0, #0x2
@L021eea84:
    add sp, sp, #0x124
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// The experience of a member in their vocation
static unsigned int GetMemberExperience(PartyMember* member)
{
    PartyMemberData* data = member->data_;
    return data->unk_138[data->vocation_];
}

// Adds items to the bag (0x38 bytes)
struct ItemAdder
{
    SafeAllocator allocator_;
    char unk_14[0x18];
    void* names_;
    char unk_30[8];

    ItemAdder()
    {
        func_020de824(unk_14);
        func_0207cbe8(this);
        func_0207cbe8(this);
    }
};

// NONMATCHING: the C matches 74.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_Load()
{
    GameResources* resources = func_ov017_0218b5b0();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    BattleEnd* end = sEnd;
    SafeAllocator* allocator = &resources->allocators_[5];
    if (end->step_ == 0)
    {
        func_020a1940((unsigned int)OVERLAY_13_ID);
        end->task_ = loader->QueueLoadFileInGP2(STRING(0x0, "data/bin/str_bres.gp2"), STRING(0x16, "str_bres_<LG>.bin"), NULL);
        end->step_++;
    }
    else if (end->step_ == 1)
    {
        if (!loader->GetTaskStatus(end->task_))
            return endState_;
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(end->task_, &file, &size);
        func_020727d8(&texts_);
        func_020728ac(&texts_, allocator, file, size, 0, 0, 0);
        loader->RemoveTask(end->task_);
        end->task_ = loader->QueueLoadFileInGP2(data_020f2a38, data_020f2a30, NULL);
        end->step_++;
    }
    else if (end->step_ == 2)
    {
        if (!loader->GetTaskStatus(end->task_))
            return endState_;
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(end->task_, &file, &size);
        int count = dropCount_;
        if (count > 8)
            count = 8;
        unsigned short items[10];
        BattleDrop* drop = drops_;
        unsigned short* item = items;
        for (int i = 0; i < count; i++)
        {
            *item++ = drop->item_;
            drop += 1;
        }
        if (data_->quest_ > 0)
        {
            short type;
            short monster;
            short item;
            func_ov000_0215fa84(data_, &type, &monster, &item);
            items[count++] = item;
            if (type == 0x18 && IsPartyDead())
                data_->unk_8e97 = 1;
        }
        itemNames_ = allocator->Allocate(0x18);
        func_020de848(itemNames_);
        func_020de9a4(itemNames_, allocator, file, size, (short*)items, (unsigned short)count);
        loader->RemoveTask(end->task_);
        if (data_->quest_ > 0)
        {
            count--;
            ItemAdder adder;
            adder.names_ = itemNames_;
            func_0207d300(&adder, items[count], 1, 0);
        }
        void* names = itemNames_;
        BattleDrop* drop2 = drops_;
        signed char mask = memberMask_;
        GameState* gameState = GameState::GetInstance();
        Party* party = func_02010828(gameState);
        int found = 0;
        for (int i = 0; i < party->count_; i++)
        {
            if (mask & (1 << party->members_[i]))
            {
                found = 1;
                break;
            }
        }
        if (found)
        {
            int leader = func_020100a8(gameState);
            int leaderGets = mask & (1 << leader);
            BattleDrop* drop = drop2;
            for (int i = 0; i < count; i++)
            {
                ItemAdder adder;
                adder.names_ = names;
                int member = drop->member_;
                int result;
                if (member < 0)
                {
                    result = func_0207d300(&adder, drop->item_, 1, 1);
                }
                else
                {
                    if (leader != member && (func_0202c1c0(func_0202ae18(), member) != 0 || leader != 0) &&
                        leaderGets)
                        member = leader;
                    result = func_0207ccf0(&adder, drop->item_, 1, member, 1, 0, 1);
                }
                drop->full_ = 0;
                if (result == 2)
                    drop->full_ = 1;
                drop++;
            }
        }
        end->task_ = loader->QueueLoadFile(STRING(0x28, "data/prm/skilltable.bin"), NULL);
        end->step_++;
    }
    else if (end->step_ == 3)
    {
        if (!loader->GetTaskStatus(end->task_))
            return endState_;
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(end->task_, &file, &size);
        func_0209a338(end->skillTable_);
        func_0209a470(end->skillTable_, allocator, file, size);
        loader->RemoveTask(end->task_);
        end->task_ = loader->QueueLoadFile(STRING(0x40, "data/prm/spelltable.bin"), NULL);
        end->step_++;
    }
    else if (end->step_ == 4)
    {
        if (!loader->GetTaskStatus(end->task_))
            return endState_;
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(end->task_, &file, &size);
        func_0209a804(end->spellTable_);
        func_0209a8b4(end->spellTable_, allocator, file, size);
        loader->RemoveTask(end->task_);
        end->Reset();
        return 3;
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN9BattleEnd5ResetEv(); // BattleEnd::Reset
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int BattleScene::End_Load()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xc0
    mov r10, r0
    bl func_ov017_0218b5b0
    mov r5, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldr r1, =sEnd
    mov r4, r0
    ldr r9, [r1, #0x0]
    add r6, r5, #0x9c
    ldr r1, [r9, #0x0]
    cmp r1, #0x0
    bne @L021eeb10
    ldr r0, =0xd
    bl func_020a1940
    ldr r1, =sStrings
    ldr r2, =sStrings+0x16
    mov r0, r4
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r9, #0x4]
    ldr r0, [r9, #0x0]
    add r0, r0, #0x1
    str r0, [r9, #0x0]
    b @L021eef80
@L021eeb10:
    cmp r1, #0x1
    bne @L021eebb0
    ldr r1, [r9, #0x4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021eef84
    ldr r1, [r9, #0x4]
    add r2, sp, #0x34
    add r3, sp, #0x38
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r10, #0x104
    add r0, r0, #0x5800
    bl func_020727d8
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    add r0, r10, #0x104
    ldr r2, [sp, #0x34]
    ldr r3, [sp, #0x38]
    add r0, r0, #0x5800
    mov r1, r6
    bl func_020728ac
    ldr r1, [r9, #0x4]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r1, =data_020f2a38
    ldr r2, =data_020f2a30
    ldr r1, [r1, #0x0]
    ldr r2, [r2, #0x0]
    mov r0, r4
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r9, #0x4]
    ldr r0, [r9, #0x0]
    add r0, r0, #0x1
    str r0, [r9, #0x0]
    b @L021eef80
@L021eebb0:
    cmp r1, #0x2
    bne @L021eee9c
    ldr r1, [r9, #0x4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021eef84
    ldr r1, [r9, #0x4]
    add r2, sp, #0x2c
    add r3, sp, #0x30
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r10, #0x5000
    ldrb r5, [r0, #0x900]
    add r0, r10, #0x8d0
    add r2, r0, #0x5000
    cmp r5, #0x8
    movgt r5, #0x8
    add r1, sp, #0xac
    mov r3, #0x0
    b @L021eec10
@L021eec04:
    ldrh r0, [r2], #0x6
    add r3, r3, #0x1
    strh r0, [r1], #0x2
@L021eec10:
    cmp r3, r5
    blt @L021eec04
    ldr r0, [r10, #0x29c]
    add r1, r0, #0x8e00
    ldrsh r1, [r1, #0x4a]
    cmp r1, #0x0
    ble @L021eec74
    add r1, sp, #0x18
    add r2, sp, #0x14
    add r3, sp, #0x16
    bl func_ov000_0215fa84
    ldrsh r0, [sp, #0x18]
    mov r2, r5, lsl #0x1
    ldrsh r3, [sp, #0x16]
    add r1, sp, #0xac
    cmp r0, #0x18
    strh r3, [r1, r2]
    add r5, r5, #0x1
    bne @L021eec74
    bl IsPartyDead
    cmp r0, #0x0
    ldrne r0, [r10, #0x29c]
    movne r1, #0x1
    addne r0, r0, #0x8000
    strneb r1, [r0, #0xe97]
@L021eec74:
    mov r0, r6
    mov r1, #0x18
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x90c]
    bl func_020de848
    add r0, sp, #0xac
    str r0, [sp, #0x0]
    mov r0, r5, lsl #0x10
    mov r0, r0, lsr #0x10
    str r0, [sp, #0x4]
    add r0, r10, #0x5000
    ldr r0, [r0, #0x90c]
    ldr r2, [sp, #0x2c]
    ldr r3, [sp, #0x30]
    mov r1, r6
    bl func_020de9a4
    ldr r1, [r9, #0x4]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r0, [r10, #0x29c]
    add r0, r0, #0x8e00
    ldrsh r0, [r0, #0x4a]
    cmp r0, #0x0
    ble @L021eed24
    add r0, sp, #0x74
    sub r5, r5, #0x1
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, sp, #0x88
    bl func_020de824
    add r0, sp, #0x74
    bl func_0207cbe8
    add r0, sp, #0x74
    bl func_0207cbe8
    add r0, r10, #0x5000
    ldr r1, [r0, #0x90c]
    mov r3, r5, lsl #0x1
    str r1, [sp, #0xa0]
    add r1, sp, #0xac
    ldrsh r1, [r1, r3]
    add r0, sp, #0x74
    mov r2, #0x1
    mov r3, #0x0
    bl func_0207d300
@L021eed24:
    add r0, r10, #0x5000
    ldr r0, [r0, #0x90c]
    add r1, r10, #0x8d0
    add r2, r10, #0x5900
    add r6, r1, #0x5000
    str r0, [sp, #0xc]
    ldrsb r11, [r2, #0x1]
    bl _ZN9GameState11GetInstanceEv
    mov r7, r0
    bl func_02010828
    mov r3, #0x0
    mov r2, r3
    mov r1, #0x1
    b @L021eed74
@L021eed5c:
    add r8, r0, r2
    ldrb r8, [r8, #0xf78]
    tst r11, r1, lsl r8
    movne r3, r1
    bne @L021eed80
    add r2, r2, #0x1
@L021eed74:
    ldrb r8, [r0, #0xf7c]
    cmp r2, r8
    blt @L021eed5c
@L021eed80:
    cmp r3, #0x0
    beq @L021eee78
    mov r0, r7
    bl func_020100a8
    mov r8, r0
    mov r0, #0x1
    and r0, r11, r0, lsl r8
    mov r7, #0x0
    str r0, [sp, #0x10]
    b @L021eee70
@L021eeda8:
    add r0, sp, #0x3c
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, sp, #0x50
    bl func_020de824
    add r0, sp, #0x3c
    bl func_0207cbe8
    add r0, sp, #0x3c
    bl func_0207cbe8
    ldr r0, [sp, #0xc]
    str r0, [sp, #0x68]
    ldrsb r11, [r6, #0x5]
    cmp r11, #0x0
    bge @L021eedf4
    ldrsh r1, [r6, #0x0]
    mov r2, #0x1
    add r0, sp, #0x3c
    mov r3, r2
    bl func_0207d300
    b @L021eee4c
@L021eedf4:
    cmp r8, r11
    beq @L021eee20
    bl func_0202ae18
    mov r1, r11
    bl func_0202c1c0
    cmp r0, #0x0
    cmpeq r8, #0x0
    beq @L021eee20
    ldr r0, [sp, #0x10]
    cmp r0, #0x0
    movne r11, r8
@L021eee20:
    mov r0, #0x1
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    mov r0, #0x1
    str r0, [sp, #0x8]
    ldrsh r1, [r6, #0x0]
    mov r3, r11
    add r0, sp, #0x3c
    mov r2, #0x1
    bl func_0207ccf0
@L021eee4c:
    cmp r0, #0x2
    ldrh r0, [r6, #0x2]
    add r7, r7, #0x1
    bic r0, r0, #0x8000
    strh r0, [r6, #0x2]
    ldreqh r0, [r6, #0x2]
    orreq r0, r0, #0x8000
    streqh r0, [r6, #0x2]
    add r6, r6, #0x6
@L021eee70:
    cmp r7, r5
    blt @L021eeda8
@L021eee78:
    ldr r1, =sStrings+0x28
    mov r0, r4
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r9, #0x4]
    ldr r0, [r9, #0x0]
    add r0, r0, #0x1
    str r0, [r9, #0x0]
    b @L021eef80
@L021eee9c:
    cmp r1, #0x3
    bne @L021eef18
    ldr r1, [r9, #0x4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021eef84
    ldr r1, [r9, #0x4]
    add r2, sp, #0x24
    add r3, sp, #0x28
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r9, #0xe8
    bl func_0209a338
    ldr r2, [sp, #0x24]
    ldr r3, [sp, #0x28]
    mov r1, r6
    add r0, r9, #0xe8
    bl func_0209a470
    ldr r1, [r9, #0x4]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r1, =sStrings+0x40
    mov r0, r4
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r9, #0x4]
    ldr r0, [r9, #0x0]
    add r0, r0, #0x1
    str r0, [r9, #0x0]
    b @L021eef80
@L021eef18:
    cmp r1, #0x4
    bne @L021eef80
    ldr r1, [r9, #0x4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021eef84
    ldr r1, [r9, #0x4]
    add r2, sp, #0x1c
    add r3, sp, #0x20
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r9, #0xf0
    bl func_0209a804
    ldr r2, [sp, #0x1c]
    ldr r3, [sp, #0x20]
    mov r1, r6
    add r0, r9, #0xf0
    bl func_0209a8b4
    ldr r1, [r9, #0x4]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mov r0, r9
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0x3
    b @L021eef84
@L021eef80:
    ldr r0, [r10, #0xeac]
@L021eef84:
    add sp, sp, #0xc0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif


void BattleEnd::Reset()
{
    step_ = 0;
    task_ = -1;
    task2_ = -1;
    skill_ = 0;
    newSkill_ = 0;
    next_ = -1;
}

int BattleScene::End_Victory()
{
    BattleEnd* end = sEnd;
    if (end->step_ == 0)
    {
        void* monsters = info_->monsters_;
        MessageSystem* messages = func_020421a0();
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        int load = 1;
        if (sEnd->task3_ > -1)
        {
            if (loader->GetTaskStatus(sEnd->task3_))
            {
                void* file;
                unsigned int size;
                loader->GetLoadedFileByID(sEnd->task3_, &file, &size);
                if (file != NULL)
                {
                    allocator_.Reset();
                    monsters = sEnd->monsters_;
                    func_0206efc4(monsters);
                    func_0206f200(monsters, &allocator_, file, size, victoryMonster_);
                }
                loader->RemoveTask(sEnd->task3_);
                sEnd->task3_ = -1;
                load = 0;
            }
            else
            {
                return endState_;
            }
        }
        if (load && victoryMonster_ != 0 && func_0206f4f0(monsters, victoryMonster_) == NULL)
        {
            monsters = sEnd->monsters_;
            if (func_0206f4f0(monsters, victoryMonster_) == NULL)
            {
                sEnd->task3_ = loader->QueueLoadFileInGP2(STRING(0x58, "data/prm/mon_data.gp2"), STRING(0x6e, "mon_data_<LG>.nat"), NULL);
                return endState_;
            }
        }
        GameResources* resources = func_ov017_0218b5b0();
        void* unk = NULL;
        Unknown_021b8478* unk2 = NULL;
        int kind = -1;
        if (resources != NULL)
            unk = resources->unknown_ptr_3718;
        if (unk != NULL)
            unk2 = func_ov017_021b8478(unk);
        MessageName name;
        if (unk2 != NULL)
            kind = unk2->unk_c;
        func_020e46c4(&name);
        MonsterEntry* monster = func_0206f4f0(monsters, victoryMonster_);
        if (kind == 0x36 || kind == 0x43 || kind == 0x50)
            monster = func_0206f4f0(monsters, 0x1fc);
        if (monster != NULL)
        {
            name = GetMonsterName(name, monster);
            messages->unk_20 = &name;
            messages->unk_10 = &name;
        }
        char text[0x12c];
        switch (victory_)
        {
        case 0:
            sprintf(text, func_02072a68(&texts_, 1));
            break;
        case 1:
            messages->unk_19d7 = 1;
            sprintf(text, func_02072a68(&texts_, 1));
            break;
        case 2:
            if (kind == 0x36 || kind == 0x43 || kind == 0x50)
                sprintf(text, func_02072a68(&texts_, 1));
            else
                sprintf(text, func_02072a68(&texts_, 0x32));
            break;
        case 3:
            sprintf(text, func_02072a68(&texts_, 3));
            break;
        case 4:
            messages->unk_19d7 = 1;
            sprintf(text, func_02072a68(&texts_, 3));
            break;
        case 5:
            sprintf(text, func_02072a68(&texts_, 0x34));
            break;
        case 6:
            sprintf(text, func_02072a68(&texts_, 2));
            break;
        case 7:
            messages->unk_19d7 = 1;
            sprintf(text, func_02072a68(&texts_, 2));
            break;
        case 8:
            sprintf(text, func_02072a68(&texts_, 0x33));
            break;
        }
        if (info_->legacyBoss_ != 0)
            strcat(text, func_02072a68(&texts_, 0x22));
        else if (end->nothing_ == 0)
            strcat(text, func_02072a68(&texts_, 0x22));
        func_0204500c(messages, text, 1, 0xe3);
        messages->unk_19b2 = 0;
        messages->busy_ = 1;
        if (data_->monsterCount_ > 0)
        {
            PlayRecords records;
            func_020ac4c0(&records);
            func_020a0330(&records, 1);
            func_020a0110(&records.unk_68, 1);
            func_020ac494(&records);
        }
        if (!func_0202c540(func_0202ae18()) || info_->legacyBoss_ == 0)
            func_0209c6d8(data_02109bf4, 0x36);
        end->step_++;
        if (info_->grotto_ != 0 || info_->legacyBoss_ != 0)
        {
            GrottoStruct* grotto = GameState::GetInstance()->GetGrottoStruct();
            unk_6e38 = 1;
            grotto->unknown_0[3] = 1;
            func_ov017_021cfc74(1);
        }
        func_0206efc4(sEnd->monsters_);
    }
    else if (end->step_ == 100)
    {
        timer_++;
        if (IsMessageDone() || timer_ > 30)
        {
            end->Reset();
            return 0x10;
        }
    }
    else if (end->step_ == 1)
    {
        if (IsMessageDone())
            end->step_ = 2;
    }
    else if (end->step_ == 2)
    {
        end->Reset();
        void* unk = func_0202ae18();
        ZoneData* zone = func_02012fe4();
        DetailedTreasureMapData* map = zone->grotto_.GetDetailedData();
        if (info_->legacyBoss_ != 0)
        {
            if (func_0201b588(zone->id_))
            {
                PlayRecords records;
                func_020ac4c0(&records);
                func_020a0388(&records, 1);
                if (map != NULL && map->mapType_ == 2 && map->legacy_.level_ > records.unk_c_7)
                    records.unk_c_7 = map->legacy_.level_;
                func_020ac494(&records);
            }
            return 4;
        }
        if (info_->grotto_ != 0)
        {
            DetailedTreasureMapData* map2 = func_02012fe4()->grotto_.GetDetailedData();
            GameState* gameState = GameState::GetInstance();
            if (func_0202c508(unk))
            {
                void* name = gameState->GetProtagonist()->baseStats_;
                char buffer[0xa];
                __clear(buffer, sizeof(buffer));
                func_020426bc(name, buffer, 1);
                map2->discoveryState_ = 3;
                VectorizedMemset(map2->clearedBy_, 0, sizeof(map2->clearedBy_));
                VectorizedInvertedMemcpy(buffer, map2->clearedBy_, sizeof(buffer));
                func_020117cc(gameState, map2);
                func_02011744(gameState);
            }
            if (func_0201b588(zone->id_))
            {
                PlayRecords records;
                func_020ac4c0(&records);
                func_020a0388(&records, 1);
                if (map != NULL && map->mapType_ == 1 && map->regular_.level_ > records.unk_c_0)
                    records.unk_c_0 = map->regular_.level_;
                func_020ac494(&records);
            }
        }
        return end->nothing_ ? 0xe : 6;
    }
    return endState_;
}


// NONMATCHING: the C matches 95.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_LegacyBoss()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    void* unk = func_0202ae18();
    DetailedTreasureMapData* map = func_02012fe4()->grotto_.GetDetailedData();
    char text[0x300];
    __clear(text, sizeof(text));
    MessageName name;
    if (end->step_ == 0)
    {
        if (!func_0202b7d8(unk) || info_->leader_ == func_0202c1a4(unk))
        {
            func_ov000_02163b60(this);
            end->step_ = 1;
        }
        else
        {
            end->Reset();
            return 5;
        }
    }
    else if (end->step_ == 1)
    {
        int count = 1;
        if (map->legacy_.bossID_ == 9)
            count = 3;
        for (int i = 0; i < count; i++)
        {
            GameObject* object = func_0200fea4(gameState, i + 0xc0);
            if (object != NULL && object->currentStats_ != NULL)
            {
                bosses_[bossCount_] = object->obj3D_.unknown_4_;
                bossCount_++;
            }
        }
        if ((map->legacy_.minTurns_ == 0 || turns_ < map->legacy_.minTurns_) && turns_ < 1000)
        {
            GameObject* boss = func_0200fea4(gameState, bosses_[0]);
            if (map->legacy_.bossID_ == 9)
                boss = func_0200fea4(gameState, bosses_[1]);
            func_020e4ce8(&name, boss, 1);
            sprintf(text, func_02072a68(&texts_, 0x23));
            messages->unk_20 = &name;
            func_020465c0(messages, 0, turns_);
            func_020465c0(messages, 1, map->legacy_.level_);
            func_0204500c(messages, text, 1, 0xe3);
            messages->unk_19b2 = 0;
            messages->busy_ = 1;
            end->step_ = 2;
        }
        else
        {
            end->step_ = 3;
        }
    }
    else if (end->step_ == 2)
    {
        if (!func_0209ca2c(data_02109bf4) && IsMessageDone())
            end->step_ = 3;
    }
    else if (end->step_ == 3)
    {
        func_ov000_0216d370(&camera_, 1, 1, 1);
        int factor = 0x3000;
        int radius = 0;
        if (map->legacy_.bossID_ == 9)
            factor = 0x2333;
        int height = radius;
        Vector3i center;
        Vector3i target;
        Vector3i position;
        SetVector(&center, radius, radius, radius);
        for (int i = 0; i < bossCount_; i++)
        {
            GameObject* boss = func_0200fea4(gameState, bosses_[i]);
            Vector3i bossPosition;
            func_02049b54(&bossPosition, boss);
            boss->obj3D_.position_ = bossPosition;
            boss->obj3D_.rotation_.x = 0;
            boss->obj3D_.rotation_.y = 0;
            boss->obj3D_.rotation_.z = 0;
            Vector3fix_Add(&center, &boss->obj3D_.position_, &center);
            radius += boss->obj3D_.GetRadius();
            if (height < boss->obj3D_.GetHeight())
                height = boss->obj3D_.GetHeight();
            boss->obj3D_.MaybeSetRegularAnimation(STRING(0x80, "stand"), 8);
            boss->obj3D_.TransitionInheritedAlpha(0x1f, 200);
            boss->obj3D_.MakeVisible();
            func_02049f28(boss);
        }
        center.x = fix32_Divide(center.x, bossCount_ << 12);
        center.y = fix32_Divide(center.y, bossCount_ << 12);
        center.z = fix32_Divide(center.z, bossCount_ << 12);
        func_ov000_02163b90(this, 0);
        SetVector(&target, center.x, center.y + fix32_Divide(height, 0x2000), center.z);
        SetVector(&position, target.x, target.y, target.z + FIX32_MULTIPLY(radius, factor));
        camera_.target_ = target;
        camera_.position_ = position;
        func_0202ea4c(&camera_);
        func_ov000_0216d50c(&camera_);
        sprintf(text, func_02072a68(&texts_, 0x1b));
        GameObject* boss = func_0200fea4(gameState, bosses_[0]);
        if (map->legacy_.bossID_ == 9)
            boss = func_0200fea4(gameState, bosses_[1]);
        func_020e4ce8(&name, boss, 1);
        messages->unk_20 = &name;
        func_0204500c(messages, text, 1, 0xe3);
        messages->unk_19b2 = 0;
        messages->busy_ = 1;
        end->step_ = 4;
    }
    else if (end->step_ == 4)
    {
        if (IsMessageDone())
        {
            if (map->legacy_.level_ >= sMaxLevel)
            {
                sprintf(text, func_02072a68(&texts_, 0x1d));
                GameObject* boss = func_0200fea4(gameState, bosses_[0]);
                if (map->legacy_.bossID_ == 9)
                    boss = func_0200fea4(gameState, bosses_[1]);
                func_020e4ce8(&name, boss, 1);
                messages->unk_20 = &name;
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
                end->step_ = 8;
            }
            else
            {
                sprintf(text, func_02072a68(&texts_, 0x1c), map->legacy_.bossName_);
                GameObject* boss = func_0200fea4(gameState, bosses_[0]);
                if (map->legacy_.bossID_ == 9)
                    boss = func_0200fea4(gameState, bosses_[1]);
                func_020e4ce8(&name, boss, 1);
                messages->unk_20 = &name;
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
                end->step_ = 5;
            }
        }
    }
    else if (end->step_ == 5)
    {
        if (IsMessageDone())
        {
            func_0200ff1c(gameState, func_020100a8(gameState));
            sprintf(text, func_02072a68(&texts_, 0x1e));
            GameObject* boss = func_0200fea4(gameState, bosses_[0]);
            if (map->legacy_.bossID_ == 9)
                boss = func_0200fea4(gameState, bosses_[1]);
            func_020e4ce8(&name, boss, 1);
            messages->unk_20 = &name;
            func_020465c0(messages, 0, earnedExperience_);
            func_0204500c(messages, text, 1, 0xe3);
            messages->unk_19b2 = 0;
            messages->busy_ = 1;
            messages->unk_2c8 = 1;
            end->step_ = 6;
        }
    }
    else if (end->step_ == 6)
    {
        if (messages->unk_9a0 != 3)
            return endState_;
        if (func_020457e0(messages) == 0)
            end->step_ = 7;
        else
            end->step_ = 8;
    }
    else if (end->step_ == 7)
    {
        if (IsMessageDone())
        {
            legacyBossLevelUp_ = 1;
            sprintf(text, func_02072a68(&texts_, 0x1f));
            GameObject* boss = func_0200fea4(gameState, bosses_[0]);
            if (map->legacy_.bossID_ == 9)
                boss = func_0200fea4(gameState, bosses_[1]);
            func_020e4ce8(&name, boss, 1);
            messages->unk_20 = &name;
            func_020465c0(messages, 0, map->legacy_.level_ + 1);
            func_0204500c(messages, text, 1, 0xe3);
            messages->unk_19b2 = 0;
            messages->busy_ = 1;
            func_0209c6d8(data_02109bf4, 0x35);
            map->UpdateFollowingCompletion(true, 0);
            func_020117cc(gameState, map);
            func_02011744(gameState);
            if (map->legacy_.GetLearnedMove(map->legacy_.level_, -1) != 0)
                end->step_ = 9;
            else
                end->step_ = 11;
        }
    }
    else if (end->step_ == 8)
    {
        FadeBosses(1500);
        map->UpdateFollowingCompletion(false, turns_);
        func_020117cc(gameState, map);
        func_02011744(gameState);
        end->step_ = 10;
    }
    else if (end->step_ == 9)
    {
        if (IsMessageDone())
        {
            unsigned short move = map->legacy_.GetLearnedMove(map->legacy_.level_, 1);
            if (move != 0)
            {
                const char** skill = func_02079e2c(func_020797dc(), move);
                sprintf(text, func_02072a68(&texts_, 0x20));
                GameObject* boss = func_0200fea4(gameState, bosses_[0]);
                if (map->legacy_.bossID_ == 9)
                    boss = func_0200fea4(gameState, bosses_[1]);
                func_020e4ce8(&name, boss, 1);
                messages->unk_20 = &name;
                func_02046574(messages, 1, *skill);
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
            }
            end->step_ = 11;
        }
    }
    else if (end->step_ == 10)
    {
        if (func_0200fea4(gameState, bosses_[0])->obj3D_.GetInheritedAlpha() == 0 || bossCount_ == 0)
            end->step_ = 11;
    }
    else if (end->step_ == 11)
    {
        if (IsMessageDone())
        {
            end->Reset();
            return 5;
        }
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11BattleScene10FadeBossesEi(); // BattleScene::FadeBosses
    void _ZN17ActiveGrottoClass15GetDetailedDataEv(); // ActiveGrottoClass::GetDetailedData
    void _ZN23DetailedTreasureMapData17LegacyBossMapData14GetLearnedMoveEhi(); // DetailedTreasureMapData::LegacyBossMapData::GetLearnedMove
    void _ZN23DetailedTreasureMapData25UpdateFollowingCompletionEbt(); // DetailedTreasureMapData::UpdateFollowingCompletion
    void _ZN8Object3D11MakeVisibleEv(); // Object3D::MakeVisible
    void _ZN8Object3D24MaybeSetRegularAnimationEPKci(); // Object3D::MaybeSetRegularAnimation
    void _ZN8Object3D24TransitionInheritedAlphaEii(); // Object3D::TransitionInheritedAlpha
    void _ZN8Vector3iaSERKS_(); // Vector3i::operator=
    void _ZN9BattleEnd5ResetEv(); // BattleEnd::Reset
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK8Object3D17GetInheritedAlphaEv(); // Object3D::GetInheritedAlpha
    void _ZNK8Object3D9GetHeightEv(); // Object3D::GetHeight
    void _ZNK8Object3D9GetRadiusEv(); // Object3D::GetRadius
}

asm int BattleScene::End_LegacyBoss()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x34c
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    mov r4, r0
    ldr r5, [r1, #0x0]
    bl func_020421a0
    mov r6, r0
    bl func_0202ae18
    mov r8, r0
    bl func_02012fe4
    add r0, r0, #0x3ec
    add r0, r0, #0x2000
    bl _ZN17ActiveGrottoClass15GetDetailedDataEv
    mov r7, r0
    add r0, sp, #0x4c
    mov r1, #0x300
    bl __clear
    ldr r0, [r5, #0x0]
    cmp r0, #0x0
    bne @L021ef798
    mov r0, r8
    bl func_0202b7d8
    cmp r0, #0x0
    beq @L021ef774
    mov r0, r8
    bl func_0202c1a4
    ldr r1, [r10, #0x2a0]
    ldrsb r1, [r1, #0x2a]
    cmp r1, r0
    bne @L021ef788
@L021ef774:
    mov r0, r10
    bl func_ov000_02163b60
    mov r0, #0x1
    str r0, [r5, #0x0]
    b @L021f00d4
@L021ef788:
    mov r0, r5
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0x5
    b @L021f00d8
@L021ef798:
    cmp r0, #0x1
    bne @L021ef908
    ldrb r0, [r7, #0x4c]
    mov r11, #0x1
    mov r9, #0x0
    cmp r0, #0x9
    add r0, r10, #0x2e
    add r8, r0, #0x6e00
    add r0, r10, #0x6000
    moveq r11, #0x3
    str r0, [sp, #0x8]
    b @L021ef80c
@L021ef7c8:
    mov r0, r4
    add r1, r9, #0xc0
    bl func_0200fea4
    cmp r0, #0x0
    ldrne r1, [r0, #0x138]
    cmpne r1, #0x0
    beq @L021ef808
    ldr r1, [sp, #0x8]
    ldrsh r2, [r0, #0x4]
    ldrb r1, [r1, #0xe2e]
    add r0, r10, r1, lsl #0x1
    add r0, r0, #0x6e00
    strh r2, [r0, #0x30]
    ldrb r0, [r8, #0x0]
    add r0, r0, #0x1
    strb r0, [r8, #0x0]
@L021ef808:
    add r9, r9, #0x1
@L021ef80c:
    cmp r9, r11
    blt @L021ef7c8
    ldrh r1, [r7, #0x58]
    cmp r1, #0x0
    beq @L021ef830
    add r0, r10, #0x5800
    ldrh r0, [r0, #0xcc]
    cmp r0, r1
    bhs @L021ef8fc
@L021ef830:
    add r0, r10, #0x5800
    ldrh r0, [r0, #0xcc]
    cmp r0, #0x3e8
    bhs @L021ef8fc
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    ldrb r2, [r7, #0x4c]
    mov r1, r0
    cmp r2, #0x9
    bne @L021ef874
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021ef874:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x23
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    add r1, sp, #0x40
    str r1, [r6, #0x20]
    add r2, r10, #0x5800
    ldrh r2, [r2, #0xcc]
    mov r0, r6
    mov r1, #0x0
    bl func_020465c0
    ldrb r2, [r7, #0x56]
    mov r0, r6
    mov r1, #0x1
    bl func_020465c0
    mov r0, r6
    add r1, sp, #0x4c
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x0
    add r0, r6, #0x1000
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    mov r0, #0x2
    str r0, [r5, #0x0]
    b @L021f00d4
@L021ef8fc:
    mov r0, #0x3
    str r0, [r5, #0x0]
    b @L021f00d4
@L021ef908:
    cmp r0, #0x2
    bne @L021ef934
    ldr r0, =data_02109bf4
    bl func_0209ca2c
    cmp r0, #0x0
    bne @L021f00d4
    bl IsMessageDone
    cmp r0, #0x0
    movne r0, #0x3
    strne r0, [r5, #0x0]
    b @L021f00d4
@L021ef934:
    cmp r0, #0x3
    bne @L021efbd4
    mov r1, #0x1
    add r0, r10, #0x18
    mov r2, r1
    mov r3, r1
    add r0, r0, #0xc00
    bl func_ov000_0216d370
    ldrb r0, [r7, #0x4c]
    mov r11, #0x3000
    cmp r0, #0x9
    mov r0, #0x0
    str r0, [sp, #0x4]
    ldr r1, [sp, #0x4]
    add r0, sp, #0x34
    mov r8, r1
    mov r2, r1
    mov r3, r1
    ldreq r11, =0x2333
    str r8, [sp, #0x0]
    bl SetVector
    add r0, r10, #0x6000
    mov r8, #0x0
    str r0, [sp, #0xc]
    b @L021efa50
@L021ef998:
    add r1, r10, r8, lsl #0x1
    add r1, r1, #0x6e00
    ldrh r1, [r1, #0x30]
    mov r0, r4
    bl func_0200fea4
    mov r9, r0
    add r0, sp, #0x10
    mov r1, r9
    bl func_02049b54
    add r0, r9, #0x44
    add r1, sp, #0x10
    bl _ZN8Vector3iaSERKS_
    mov r0, #0x0
    str r0, [r9, #0x50]
    str r0, [r9, #0x54]
    str r0, [r9, #0x58]
    add r0, sp, #0x34
    add r1, r9, #0x44
    mov r2, r0
    bl Vector3fix_Add
    mov r0, r9
    bl _ZNK8Object3D9GetRadiusEv
    ldr r1, [sp, #0x4]
    add r0, r1, r0
    str r0, [sp, #0x4]
    mov r0, r9
    bl _ZNK8Object3D9GetHeightEv
    ldr r1, [sp, #0x0]
    cmp r1, r0
    bge @L021efa1c
    mov r0, r9
    bl _ZNK8Object3D9GetHeightEv
    str r0, [sp, #0x0]
@L021efa1c:
    ldr r1, =sStrings+0x80
    mov r0, r9
    mov r2, #0x8
    bl _ZN8Object3D24MaybeSetRegularAnimationEPKci
    mov r0, r9
    mov r1, #0x1f
    mov r2, #0xc8
    bl _ZN8Object3D24TransitionInheritedAlphaEii
    mov r0, r9
    bl _ZN8Object3D11MakeVisibleEv
    mov r0, r9
    bl func_02049f28
    add r8, r8, #0x1
@L021efa50:
    ldr r0, [sp, #0xc]
    ldrb r1, [r0, #0xe2e]
    cmp r8, r1
    blt @L021ef998
    ldr r0, [sp, #0x34]
    mov r1, r1, lsl #0xc
    bl fix32_Divide
    str r0, [sp, #0x34]
    add r0, r10, #0x6000
    ldrb r1, [r0, #0xe2e]
    ldr r0, [sp, #0x38]
    mov r1, r1, lsl #0xc
    bl fix32_Divide
    str r0, [sp, #0x38]
    add r1, r10, #0x6000
    ldrb r1, [r1, #0xe2e]
    ldr r0, [sp, #0x3c]
    mov r1, r1, lsl #0xc
    bl fix32_Divide
    str r0, [sp, #0x3c]
    mov r0, r10
    mov r1, #0x0
    bl func_ov000_02163b90
    ldr r0, [sp, #0x0]
    mov r1, #0x2000
    bl fix32_Divide
    mov r8, r0
    ldr r2, [sp, #0x38]
    ldr r1, [sp, #0x34]
    ldr r3, [sp, #0x3c]
    add r0, sp, #0x28
    add r2, r2, r8
    bl SetVector
    ldr r0, [sp, #0x4]
    ldr r3, [sp, #0x30]
    smull r2, r1, r0, r11
    adds r2, r2, #0x800
    adc r0, r1, #0x0
    mov r8, r2, lsr #0xc
    orr r8, r8, r0, lsl #0x14
    ldr r1, [sp, #0x28]
    ldr r2, [sp, #0x2c]
    add r0, sp, #0x1c
    add r3, r3, r8
    bl SetVector
    add r0, r10, #0x28
    add r0, r0, #0xc00
    add r1, sp, #0x28
    bl _ZN8Vector3iaSERKS_
    add r0, r10, #0x1c
    add r0, r0, #0xc00
    add r1, sp, #0x1c
    bl _ZN8Vector3iaSERKS_
    add r0, r10, #0x18
    add r0, r0, #0xc00
    bl func_0202ea4c
    add r0, r10, #0x18
    add r0, r0, #0xc00
    bl func_ov000_0216d50c
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x1b
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    add r1, r10, #0x6e00
    ldrh r1, [r1, #0x30]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
    ldrb r0, [r7, #0x4c]
    cmp r0, #0x9
    bne @L021efb8c
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021efb8c:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r4, sp, #0x40
    add r1, sp, #0x4c
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    str r4, [r6, #0x20]
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    mov r0, #0x4
    str r0, [r5, #0x0]
    b @L021f00d4
@L021efbd4:
    cmp r0, #0x4
    bne @L021efd20
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f00d4
    ldrb r0, [r7, #0x56]
    cmp r0, #0x63
    add r0, r10, #0x104
    add r0, r0, #0x5800
    blo @L021efc8c
    mov r1, #0x1d
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    ldrb r2, [r7, #0x4c]
    mov r1, r0
    cmp r2, #0x9
    bne @L021efc44
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021efc44:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r4, sp, #0x40
    add r1, sp, #0x4c
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    str r4, [r6, #0x20]
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    mov r0, #0x8
    str r0, [r5, #0x0]
    b @L021f00d4
@L021efc8c:
    mov r1, #0x1c
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    add r2, r7, #0x5a
    bl sprintf
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    ldrb r2, [r7, #0x4c]
    mov r1, r0
    cmp r2, #0x9
    bne @L021efcd8
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021efcd8:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r4, sp, #0x40
    add r1, sp, #0x4c
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    str r4, [r6, #0x20]
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    mov r0, #0x5
    str r0, [r5, #0x0]
    b @L021f00d4
@L021efd20:
    cmp r0, #0x5
    bne @L021efdf8
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f00d4
    mov r0, r4
    bl func_020100a8
    mov r1, r0
    mov r0, r4
    bl func_0200ff1c
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x1e
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
    ldrb r0, [r7, #0x4c]
    cmp r0, #0x9
    bne @L021efd98
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021efd98:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r1, sp, #0x40
    str r1, [r6, #0x20]
    add r0, r10, #0x5000
    ldr r2, [r0, #0x8c0]
    mov r0, r6
    mov r1, #0x0
    bl func_020465c0
    add r1, sp, #0x4c
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    str r0, [r6, #0x2c8]
    mov r0, #0x6
    str r0, [r5, #0x0]
    b @L021f00d4
@L021efdf8:
    cmp r0, #0x6
    bne @L021efe30
    ldr r0, [r6, #0x9a0]
    cmp r0, #0x3
    ldrne r0, [r10, #0xeac]
    bne @L021f00d8
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x0
    moveq r0, #0x7
    streq r0, [r5, #0x0]
    movne r0, #0x8
    strne r0, [r5, #0x0]
    b @L021f00d4
@L021efe30:
    cmp r0, #0x7
    bne @L021eff48
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f00d4
    add r0, r10, #0x104
    add r2, r10, #0x5000
    mov r3, #0x1
    add r0, r0, #0x5800
    mov r1, #0x1f
    strb r3, [r2, #0x76c]
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    ldrb r2, [r7, #0x4c]
    mov r1, r0
    cmp r2, #0x9
    bne @L021efea0
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021efea0:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r1, sp, #0x40
    str r1, [r6, #0x20]
    ldrb r2, [r7, #0x56]
    mov r0, r6
    mov r1, #0x0
    add r2, r2, #0x1
    bl func_020465c0
    add r1, sp, #0x4c
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x0
    add r0, r6, #0x1000
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    ldr r0, =data_02109bf4
    mov r1, #0x35
    bl func_0209c6d8
    mov r0, r7
    mov r1, #0x1
    mov r2, #0x0
    bl _ZN23DetailedTreasureMapData25UpdateFollowingCompletionEbt
    mov r0, r4
    mov r1, r7
    bl func_020117cc
    mov r0, r4
    bl func_02011744
    ldrb r1, [r7, #0x56]
    add r0, r7, #0x4c
    mvn r2, #0x0
    bl _ZN23DetailedTreasureMapData17LegacyBossMapData14GetLearnedMoveEhi
    cmp r0, #0x0
    movne r0, #0x9
    strne r0, [r5, #0x0]
    moveq r0, #0xb
    streq r0, [r5, #0x0]
    b @L021f00d4
@L021eff48:
    cmp r0, #0x8
    bne @L021eff90
    ldr r1, =0x5dc
    mov r0, r10
    bl _ZN11BattleScene10FadeBossesEi
    add r0, r10, #0x5800
    ldrh r2, [r0, #0xcc]
    mov r0, r7
    mov r1, #0x0
    bl _ZN23DetailedTreasureMapData25UpdateFollowingCompletionEbt
    mov r0, r4
    mov r1, r7
    bl func_020117cc
    mov r0, r4
    bl func_02011744
    mov r0, #0xa
    str r0, [r5, #0x0]
    b @L021f00d4
@L021eff90:
    cmp r0, #0x9
    bne @L021f0078
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f00d4
    ldrb r1, [r7, #0x56]
    add r0, r7, #0x4c
    mov r2, #0x1
    bl _ZN23DetailedTreasureMapData17LegacyBossMapData14GetLearnedMoveEhi
    movs r8, r0
    beq @L021f006c
    bl func_020797dc
    mov r1, r8, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_02079e2c
    add r1, r10, #0x104
    mov r8, r0
    add r0, r1, #0x5800
    mov r1, #0x20
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
    ldrb r0, [r7, #0x4c]
    cmp r0, #0x9
    bne @L021f0020
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x32]
    mov r0, r4
    bl func_0200fea4
    mov r1, r0
@L021f0020:
    add r0, sp, #0x40
    mov r2, #0x1
    bl func_020e4ce8
    add r1, sp, #0x40
    str r1, [r6, #0x20]
    ldr r2, [r8, #0x0]
    mov r0, r6
    mov r1, #0x1
    bl func_02046574
    add r1, sp, #0x4c
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
@L021f006c:
    mov r0, #0xb
    str r0, [r5, #0x0]
    b @L021f00d4
@L021f0078:
    cmp r0, #0xa
    bne @L021f00b0
    add r0, r10, #0x6e00
    ldrh r1, [r0, #0x30]
    mov r0, r4
    bl func_0200fea4
    bl _ZNK8Object3D17GetInheritedAlphaEv
    cmp r0, #0x0
    addne r0, r10, #0x6000
    ldrneb r0, [r0, #0xe2e]
    cmpne r0, #0x0
    moveq r0, #0xb
    streq r0, [r5, #0x0]
    b @L021f00d4
@L021f00b0:
    cmp r0, #0xb
    bne @L021f00d4
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f00d4
    mov r0, r5
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0x5
    b @L021f00d8
@L021f00d4:
    ldr r0, [r10, #0xeac]
@L021f00d8:
    add sp, sp, #0x34c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static void SetVector(Vector3i* vector, int x, int y, int z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

int BattleScene::End_Experience()
{
    GameState* gameState = GameState::GetInstance();
    func_020421a0();
    void* unk = func_0202ae18();
    GameResources* resources = func_ov017_0218b5b0();
    if (!func_0202b7d8(unk) || info_->leader_ == func_0202c1a4(unk))
    {
        unsigned char alive[4];
        __clear(alive, sizeof(alive));
        if (legacyBossLevelUp_ != 0)
        {
            unsigned char members[4];
            int count = func_02010038(gameState, members);
            for (int i = 0; i < count; i++)
                alive[members[i]] = 1;
        }
        for (int i = 0; i < 4; i++)
        {
            if (func_020a35e0(info_, i) && alive[i] != 0)
            {
                BattleResultMember* member = sEnd->FindMember(i);
                PartyMember* partyMember = func_0200ff1c(gameState, i);
                if (member != NULL)
                    member->experience_ = GetMemberExperience(partyMember);
                experience_[i] = 0;
            }
        }
        func_ov017_021cd590(info_->unk_8, experience_, legacyBossLevelUp_, 0);
        func_ov017_021cd35c(info_->unk_8, drops_, dropCount_, memberMask_);
        if (map_ != 0)
            func_ov017_021cd4c8(info_->unk_8, mapItem_, memberMask_);
    }
    else
    {
        if (resources->unknown_42e2 != 0)
            func_ov000_02160fa8(this, 0x2000000);
        if (!func_ov000_02160fd4(this, 0x4000))
            return endState_;
        if (!func_ov000_02160fd4(this, 0x8000))
            return endState_;
    }
    sEnd->nothing_ = AddExperience(info_, experience_, &gold_, legacyBossLevelUp_) ? 1 : 0;
    int total = 0;
    for (int i = 0; i < 4; i++)
    {
        if (func_020a35e0(info_, i))
            total += experience_[i];
    }
    if (total > 0)
        return 6;
    return 0xb;
}


BattleResultMember* BattleEnd::FindMember(int id)
{
    BattleResultMember* member = members_;
    for (int i = 0; i < memberCount_; i++)
    {
        if (member->id_ == id)
            return member;
        member++;
    }
    return NULL;
}

// NONMATCHING: the C matches 97.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_ShowExperience()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    func_0202ae18();
    GameResources* resources = func_ov017_0218b5b0();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_02086ef0(func_02010828(gameState), end->current_);
    char buffer[0x100];
    MessageName name;
    char path[0x28];
    short objects[0xc];
    unsigned int size;
    void* file;
    if (end->step_ == 0)
    {
        if (legacyBossLevelUp_ != 0)
            FadeBosses(0);
        func_ov000_02163b90(this, 1);
        func_ov000_021626a0(this, 4, 0);
        func_ov000_02163a7c(this);
        func_ov000_021639b4(this);
        func_0203b4e8(resources, 0x400);
        func_ov000_02167dd8(this);
        BattleData* data = data_;
        GameState* gameState2 = GameState::GetInstance();
        int count = func_ov000_02153e40(data, objects, 0xc, 0);
        for (int i = 0; i < count; i++)
        {
            GameObject* object = gameState2->GetCombatantByIndex(objects[i]);
            if (object != NULL)
                func_02048cf0(object, 0);
        }
        func_ov000_0216e3c4(&camera_);
        void* unk = func_ov000_02163524(this);
        GameState* gameState3 = GameState::GetInstance();
        for (int i = 0; i < 4; i++)
        {
            if (!func_020a35e0(info_, i))
                continue;
            if (unk != NULL)
                func_020d7334(unk, i);
            GameObject* object = gameState3->GetCombatantByIndex(i);
            if (object != NULL && func_02010088((PartyMember*)object) == 0)
            {
                ((unsigned char*)object)[0xc1] &= ~0xf0;
                func_02033b88(object, 0);
                object->obj3D_.SkipAnimationTransition();
                func_0203400c(object);
                object->obj3D_.MakeVisible();
            }
        }
        for (int i = 0; i < 8; i++)
        {
            GameObject* object = func_0200fea4(gameState3, i + 0xc0);
            if (object != NULL && ((ObjectFlags*)((char*)object + 0xc2))->visible_ != 0)
                object->obj3D_.MakeVisible();
        }
        func_0205d6a0((TextWindow*)&menu_.unk_0[0x188], 1);
        func_ov000_02160fa8(this, 0x40000);
        allocator_.Reset();
        resultWindow_ = (BattleResultWindow*)allocator_.Allocate(sizeof(BattleResultWindow));
        resultWindow_->Initialize();
        resultWindow_->SetSource((BattleResultWindowSource*)&menu_);
        BattleEnd* results = sEnd;
        unsigned char count2 = results->memberCount_;
        BattleResultWindow* window = resultWindow_;
        window->members_ = results->members_;
        window->memberCount_ = count2;
        resultWindow_->SetMembers(sEnd->ids_, sEnd->idCount_);
        end->step_++;
    }
    else if (end->step_ == 1)
    {
        if (resultWindow_->loadStep_ == 0xff)
        {
            func_02046380(messages);
            resultWindow_->ShowExperience(experience_);
            const char* found = NULL;
            int i = 0;
            if (info_->legacyBoss_ != 0)
            {
                for (; i < 4 && found == NULL; i++)
                {
                    int id = func_02011518(gameState, i);
                    if (experience_[id] != 0)
                    {
                        PartyMember* member = func_0200ff1c(gameState, id);
                        func_020e4bf4(&name, id);
                        found = member->status_->name_;
                    }
                }
            }
            else
            {
                for (; i < 4; i++)
                {
                    int id = func_02011518(gameState, i);
                    PartyMember* member = func_0200ff1c(gameState, id);
                    if (member != NULL && func_020a35e0(info_, id) && func_02010088(member) == 0)
                    {
                        func_020e4bf4(&name, id);
                        found = member->status_->name_;
                        break;
                    }
                }
            }
            int count = 0;
            for (int j = 0; j < 4; j++)
            {
                if (experience_[j] != 0)
                    count++;
            }
            if (found == NULL)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (func_0200ff1c(gameState, j) != NULL && func_020a35e0(info_, j) &&
                        func_0200ff58(gameState, j) == 0)
                        func_020e4bf4(&name, j);
                }
            }
            messages->unk_10 = &name;
            int text = 0x19;
            if (count > 1)
                text = 0x1a;
            sprintf(buffer, func_02072a68(&texts_, text));
            strcat(buffer, func_02072a68(&texts_, 0x22));
            func_0204500c(messages, buffer, 1, 0xe3);
            messages->unk_19b2 = 0;
            messages->busy_ = 1;
            end->step_++;
        }
    }
    else if (end->step_ == 2)
    {
        BattleResultMember* member = sEnd->FindMember(end->member_);
        if (member == NULL)
        {
            end->member_++;
            if (end->member_ >= 4)
                end->step_ = 4;
            return endState_;
        }
        sprintf(path, func_02072a68(&texts_, 0), member->vocation_);
        end->task_ = loader->QueueLoadFile(path, NULL);
        end->step_++;
    }
    else if (end->step_ == 3)
    {
        if (!loader->GetTaskStatus(end->task_))
            return endState_;
        int id = end->member_;
        loader->GetLoadedFileByID(end->task_, &file, &size);
        loader->RemoveTask(end->task_);
        BattleResultMember* member = sEnd->FindMember(id);
        if (file != NULL && func_02082490(&levelUps_[id], file, size, member->level_,
                                member->experience_) &&
            member->dead_ == 0)
            end->learns_[id] = 1;
        end->member_++;
        if (end->member_ < 4)
        {
            end->step_ = 2;
            return endState_;
        }
        end->step_++;
    }
    else if (end->step_ == 4)
    {
        int learns = 0;
        for (int i = 0; i < 4; i++)
        {
            if (end->learns_[i] != 0)
            {
                learns = 1;
                break;
            }
        }
        int learning = HasDrops();
        if (learns == 0 && learning == 0 && gold_ == 0)
        {
            messages->unk_19ae = 0;
            messages->unk_19ca = 0;
            messages->unk_19af = 0;
        }
        if (IsMessageDone())
        {
            end->Reset();
            return 7;
        }
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11BattleScene8HasDropsEv(); // BattleScene::HasDrops
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN18BattleResultWindow10InitializeEv(); // BattleResultWindow::Initialize
    void _ZN18BattleResultWindow10SetMembersEPKhh(); // BattleResultWindow::SetMembers
    void _ZN18BattleResultWindow14ShowExperienceEPKi(); // BattleResultWindow::ShowExperience
    void _ZN18BattleResultWindow9SetSourceEP24BattleResultWindowSource(); // BattleResultWindow::SetSource
    void _ZN8Object3D23SkipAnimationTransitionEv(); // Object3D::SkipAnimationTransition
    void _ZN9BattleEnd10FindMemberEi(); // BattleEnd::FindMember
    void _ZN9GameState19GetCombatantByIndexEi(); // GameState::GetCombatantByIndex
}

asm int BattleScene::End_ShowExperience()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x158
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    mov r5, r0
    ldr r6, [r1, #0x0]
    bl func_020421a0
    mov r7, r0
    bl func_0202ae18
    bl func_ov017_0218b5b0
    mov r8, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r4, r0
    mov r0, r5
    bl func_02010828
    ldr r1, [r6, #0x18]
    bl func_02086ef0
    ldr r0, [r6, #0x0]
    cmp r0, #0x0
    bne @L021f063c
    add r0, r10, #0x5000
    ldrb r0, [r0, #0x76c]
    cmp r0, #0x0
    beq @L021f0410
    mov r0, r10
    mov r1, #0x0
    bl _ZN11BattleScene10FadeBossesEi
@L021f0410:
    mov r0, r10
    mov r1, #0x1
    bl func_ov000_02163b90
    mov r0, r10
    mov r1, #0x4
    mov r2, #0x0
    bl func_ov000_021626a0
    mov r0, r10
    bl func_ov000_02163a7c
    mov r0, r10
    bl func_ov000_021639b4
    mov r0, r8
    mov r1, #0x400
    bl func_0203b4e8
    mov r0, r10
    bl func_ov000_02167dd8
    ldr r4, [r10, #0x29c]
    bl _ZN9GameState11GetInstanceEv
    mov r7, r0
    mov r0, r4
    add r1, sp, #0xc
    mov r2, #0xc
    mov r3, #0x0
    bl func_ov000_02153e40
    mov r4, #0x0
    mov r5, r0
    mov r8, r4
    add r9, sp, #0xc
    b @L021f04a8
@L021f0484:
    mov r0, r4, lsl #0x1
    ldrsh r1, [r9, r0]
    mov r0, r7
    bl _ZN9GameState19GetCombatantByIndexEi
    cmp r0, #0x0
    beq @L021f04a4
    mov r1, r8
    bl func_02048cf0
@L021f04a4:
    add r4, r4, #0x1
@L021f04a8:
    cmp r4, r5
    blt @L021f0484
    add r0, r10, #0x18
    add r0, r0, #0xc00
    bl func_ov000_0216e3c4
    mov r0, r10
    bl func_ov000_02163524
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    mov r8, #0x0
    mov r7, r0
    mov r9, r8
    b @L021f0558
@L021f04dc:
    ldr r0, [r10, #0x2a0]
    and r1, r8, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f0554
    cmp r5, #0x0
    beq @L021f0504
    mov r0, r5
    mov r1, r8
    bl func_020d7334
@L021f0504:
    mov r0, r7
    mov r1, r8
    bl _ZN9GameState19GetCombatantByIndexEi
    movs r4, r0
    beq @L021f0554
    bl func_02010088
    cmp r0, #0x0
    bne @L021f0554
    ldrb r2, [r4, #0xc1]
    mov r0, r4
    mov r1, r9
    bic r2, r2, #0xf0
    strb r2, [r4, #0xc1]
    bl func_02033b88
    mov r0, r4
    bl _ZN8Object3D23SkipAnimationTransitionEv
    mov r0, r4
    bl func_0203400c
    mov r0, r4
    bl _ZN8Object3D11MakeVisibleEv
@L021f0554:
    add r8, r8, #0x1
@L021f0558:
    cmp r8, #0x4
    blt @L021f04dc
    mov r4, #0x0
    b @L021f0594
@L021f0568:
    mov r0, r7
    add r1, r4, #0xc0
    bl func_0200fea4
    cmp r0, #0x0
    beq @L021f0590
    ldrb r1, [r0, #0xc2]
    mov r1, r1, lsl #0x1b
    movs r1, r1, lsr #0x1f
    beq @L021f0590
    bl _ZN8Object3D11MakeVisibleEv
@L021f0590:
    add r4, r4, #0x1
@L021f0594:
    cmp r4, #0x8
    blt @L021f0568
    add r0, r10, #0xe8
    add r0, r0, #0x3800
    mov r1, #0x1
    bl func_0205d6a0
    mov r0, r10
    mov r1, #0x40000
    bl func_ov000_02160fa8
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x30
    mov r1, #0x12c
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x588]
    bl _ZN18BattleResultWindow10InitializeEv
    add r0, r10, #0x5000
    add r1, r10, #0x760
    ldr r0, [r0, #0x588]
    add r1, r1, #0x3000
    bl _ZN18BattleResultWindow9SetSourceEP24BattleResultWindowSource
    ldr r2, =sEnd
    add r1, r10, #0x5000
    ldr r5, [r2, #0x0]
    ldr r3, [r1, #0x588]
    add r0, r5, #0x2000
    ldrb r4, [r0, #0x788]
    add r0, r5, #0x118
    str r0, [r3, #0x120]
    strb r4, [r3, #0x11e]
    ldr r2, [r2, #0x0]
    ldr r0, [r1, #0x588]
    add r1, r2, #0x89
    add r2, r2, #0x2000
    ldrb r2, [r2, #0x78d]
    add r1, r1, #0x2700
    bl _ZN18BattleResultWindow10SetMembersEPKhh
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f0a4c
@L021f063c:
    cmp r0, #0x1
    bne @L021f086c
    add r0, r10, #0x5000
    ldr r0, [r0, #0x588]
    ldrb r0, [r0, #0x11b]
    cmp r0, #0xff
    bne @L021f0a4c
    mov r0, r7
    bl func_02046380
    add r0, r10, #0x5000
    add r1, r10, #0x358
    ldr r0, [r0, #0x588]
    add r1, r1, #0x5400
    bl _ZN18BattleResultWindow14ShowExperienceEPKi
    ldr r0, [r10, #0x2a0]
    mov r8, #0x0
    ldrb r0, [r0, #0x25]
    mov r9, r8
    cmp r0, #0x0
    beq @L021f0750
    add r11, sp, #0x4c
    b @L021f06dc
@L021f0694:
    mov r0, r5
    and r1, r9, #0xff
    bl func_02011518
    mov r4, r0
    add r0, r10, r4, lsl #0x2
    add r0, r0, #0x5000
    ldr r0, [r0, #0x758]
    cmp r0, #0x0
    beq @L021f06d8
    mov r0, r5
    mov r1, r4
    bl func_0200ff1c
    mov r8, r0
    mov r0, r11
    mov r1, r4
    bl func_020e4bf4
    ldr r8, [r8, #0x134]
@L021f06d8:
    add r9, r9, #0x1
@L021f06dc:
    cmp r9, #0x4
    bge @L021f0758
    cmp r8, #0x0
    beq @L021f0694
    b @L021f0758
@L021f06f0:
    mov r0, r5
    and r1, r9, #0xff
    bl func_02011518
    mov r11, r0
    mov r0, r5
    mov r1, r11
    bl func_0200ff1c
    movs r4, r0
    beq @L021f074c
    ldr r0, [r10, #0x2a0]
    and r1, r11, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f074c
    mov r0, r4
    bl func_02010088
    cmp r0, #0x0
    bne @L021f074c
    add r0, sp, #0x4c
    mov r1, r11
    bl func_020e4bf4
    ldr r8, [r4, #0x134]
    b @L021f0758
@L021f074c:
    add r9, r9, #0x1
@L021f0750:
    cmp r9, #0x4
    blt @L021f06f0
@L021f0758:
    mov r4, #0x0
    mov r1, r4
    b @L021f077c
@L021f0764:
    add r0, r10, r1, lsl #0x2
    add r0, r0, #0x5000
    ldr r0, [r0, #0x758]
    add r1, r1, #0x1
    cmp r0, #0x0
    addne r4, r4, #0x1
@L021f077c:
    cmp r1, #0x4
    blt @L021f0764
    cmp r8, #0x0
    bne @L021f07ec
    mov r9, #0x0
    add r8, sp, #0x4c
    b @L021f07e4
@L021f0798:
    mov r0, r5
    mov r1, r9
    bl func_0200ff1c
    cmp r0, #0x0
    beq @L021f07e0
    ldr r0, [r10, #0x2a0]
    and r1, r9, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f07e0
    mov r0, r5
    mov r1, r9
    bl func_0200ff58
    cmp r0, #0x0
    bne @L021f07e0
    mov r0, r8
    mov r1, r9
    bl func_020e4bf4
@L021f07e0:
    add r9, r9, #0x1
@L021f07e4:
    cmp r9, #0x4
    blt @L021f0798
@L021f07ec:
    add r0, sp, #0x4c
    str r0, [r7, #0x10]
    add r0, r10, #0x104
    mov r1, #0x19
    cmp r4, #0x1
    movgt r1, #0x1a
    add r0, r0, #0x5800
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x58
    bl sprintf
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x22
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x58
    bl strcat
    mov r0, r7
    add r1, sp, #0x58
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x0
    add r0, r7, #0x1000
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r7, #0x998]
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f0a4c
@L021f086c:
    cmp r0, #0x2
    bne @L021f08f4
    ldr r0, =sEnd
    ldrsb r1, [r6, #0x11]
    ldr r0, [r0, #0x0]
    bl _ZN9BattleEnd10FindMemberEi
    movs r5, r0
    bne @L021f08b0
    ldrsb r0, [r6, #0x11]
    add r0, r0, #0x1
    strb r0, [r6, #0x11]
    ldrsb r0, [r6, #0x11]
    cmp r0, #0x4
    movge r0, #0x4
    strge r0, [r6, #0x0]
    ldr r0, [r10, #0xeac]
    b @L021f0a50
@L021f08b0:
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x0
    bl func_02072a68
    mov r1, r0
    ldrb r2, [r5, #0x1]
    add r0, sp, #0x24
    bl sprintf
    add r1, sp, #0x24
    mov r0, r4
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r6, #0x4]
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f0a4c
@L021f08f4:
    cmp r0, #0x3
    bne @L021f09cc
    ldr r1, [r6, #0x4]
    mov r0, r4
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021f0a50
    ldr r1, [r6, #0x4]
    add r2, sp, #0x4
    add r3, sp, #0x8
    mov r0, r4
    ldrsb r5, [r6, #0x11]
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r1, [r6, #0x4]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r0, =sEnd
    mov r1, r5
    ldr r0, [r0, #0x0]
    bl _ZN9BattleEnd10FindMemberEi
    ldr r1, [sp, #0x4]
    mov r4, r0
    cmp r1, #0x0
    beq @L021f0998
    add r0, r10, #0x770
    add r2, r0, #0x5000
    mov r0, #0x54
    ldr r3, [r4, #0x4]
    mla r0, r5, r0, r2
    str r3, [sp, #0x0]
    ldrb r3, [r4, #0x2]
    ldr r2, [sp, #0x8]
    bl func_02082490
    cmp r0, #0x0
    beq @L021f0998
    ldrb r0, [r4, #0x3]
    cmp r0, #0x0
    addeq r0, r6, r5
    moveq r1, #0x1
    streqb r1, [r0, #0x12]
@L021f0998:
    ldrsb r0, [r6, #0x11]
    add r0, r0, #0x1
    strb r0, [r6, #0x11]
    ldrsb r0, [r6, #0x11]
    cmp r0, #0x4
    movlt r0, #0x2
    strlt r0, [r6, #0x0]
    ldrlt r0, [r10, #0xeac]
    blt @L021f0a50
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f0a4c
@L021f09cc:
    cmp r0, #0x4
    bne @L021f0a4c
    mov r4, #0x0
    mov r1, r4
    b @L021f09f8
@L021f09e0:
    add r0, r6, r1
    ldrb r0, [r0, #0x12]
    cmp r0, #0x0
    movne r4, #0x1
    bne @L021f0a00
    add r1, r1, #0x1
@L021f09f8:
    cmp r1, #0x4
    blt @L021f09e0
@L021f0a00:
    mov r0, r10
    bl _ZN11BattleScene8HasDropsEv
    cmp r4, #0x0
    cmpeq r0, #0x0
    addeq r0, r10, #0x5000
    ldreq r0, [r0, #0x768]
    cmpeq r0, #0x0
    addeq r0, r7, #0x1000
    moveq r1, #0x0
    streqb r1, [r0, #0x9ae]
    streqb r1, [r0, #0x9ca]
    streqb r1, [r0, #0x9af]
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f0a4c
    mov r0, r6
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0x7
    b @L021f0a50
@L021f0a4c:
    ldr r0, [r10, #0xeac]
@L021f0a50:
    add sp, sp, #0x158
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 95.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_LevelUp()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    func_02046380(messages);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    const char* more = func_02072a68(&texts_, 0x22);
    int inParty = func_02086ef0(func_02010828(gameState), end->current_);
    int step = end->step_;
    if (step == 0)
    {
        int id = ++end->current_;
        if (id >= 4)
        {
            end->Reset();
            return 0xb;
        }
        BattleResultMember* member = sEnd->FindMember(id);
        if (member == NULL)
            return endState_;
        char path[0x28];
        sprintf(path, func_02072a68(&texts_, 0), member->vocation_);
        end->task_ = loader->QueueLoadFile(path, NULL);
        end->step_++;
    }
    else if (step == 1)
    {
        if (!loader->GetTaskStatus(end->task_))
            return endState_;
        int id = end->current_;
        unsigned int size;
        void* file;
        loader->GetLoadedFileByID(end->task_, &file, &size);
        loader->RemoveTask(end->task_);
        int levelUp = 0;
        BattleResultMember* member = sEnd->FindMember(id);
        if (file != NULL && func_02082490(&levelUps_[id], file, size, member->level_,
                                member->experience_) &&
            member->dead_ == 0)
            levelUp = 1;
        BattleResultStats* stats = &levelUps_[id].unk_28;
        int wait = 0;
        int oldLevel = member->level_;
        int level = oldLevel + stats->level_;
        if (levelUp)
        {
            if (inParty)
            {
                PartyMember* partyMember = func_0200ff1c(gameState, id);
                if (partyMember != NULL)
                {
                    PartyMemberData* data = func_02053c6c(partyMember);
                    data->levels_[data->vocation_] = level;
                    unsigned short left = 0xa28 - data->unspentSkillPoints_;
                    if (left < stats->skillPoints_)
                        stats->skillPoints_ = left;
                    data->unspentSkillPoints_ += stats->skillPoints_;
                    func_02083cbc(data, &levelUps_[id].after_, &levelUps_[id].unk_3c);
                    func_02083e28(data, 0);
                    end->skillCounts_[id] = func_0209aa54(end->spellTable_, partyMember, &end->skills_[id], oldLevel);
                }
            }
        }
        else
        {
            end->step_ = 0;
            wait = 1;
        }
        if (inParty)
        {
            PartyMember* partyMember = func_0200ff1c(gameState, id);
            if (partyMember != NULL)
            {
                PartyMemberData* data = func_02053c6c(partyMember);
                if ((int)data->levels_[data->vocation_] >= sMaxLevel)
                {
                    int experience = levelUps_[id].before_.unk_0;
                    if (levelUp)
                        experience = levelUps_[id].after_.unk_0;
                    if (experience != 0 && experience <= GetMemberExperience(partyMember))
                    {
                        if (data != NULL)
                            data->unk_138[data->vocation_] = experience;
                        member->experience_ = experience;
                    }
                }
            }
        }
        if (wait)
            return endState_;
        end->step_++;
    }
    else if (step == 2)
    {
        if (resultWindow_ != NULL)
        {
            resultWindow_->Close();
            resultWindow_->Finish();
            resultWindow_ = NULL;
            return endState_;
        }
        allocator_.Reset();
        if (!inParty)
        {
            end->step_ = 4;
        }
        else
        {
            resultWindow_ = (BattleResultWindow*)allocator_.Allocate(sizeof(BattleResultWindow));
            resultWindow_->Initialize();
            resultWindow_->SetSource((BattleResultWindowSource*)&menu_);
            BattleEnd* results = sEnd;
            unsigned char count2 = results->memberCount_;
            BattleResultWindow* window = resultWindow_;
            window->members_ = results->members_;
            window->memberCount_ = count2;
            resultWindow_->SetMembers(sEnd->ids_, sEnd->idCount_);
            end->step_++;
        }
    }
    else if (step == 3)
    {
        if (resultWindow_->loadStep_ == 0xff)
            end->step_ = step + 1;
    }
    else if (step == 4)
    {
        int id = end->current_;
        BattleResultStats* after;
        BattleResultStats* before = &levelUps_[id].before_;
        if (resultWindow_ != NULL)
            resultWindow_->ShowLevelUp(id, before, &levelUps_[id].unk_28);
        if (sEnd->FindMember(id) != NULL)
        {
            after = &levelUps_[id].after_;
            char text[0x100];
            if ((int)(after->level_ - before->level_) > 1)
            {
                sprintf(text, func_02072a68(&texts_, 0x16));
                func_020465c0(messages, 0, before->level_);
                func_020465c0(messages, 1, after->level_);
            }
            else
            {
                sprintf(text, func_02072a68(&texts_, 0xa));
                func_020465c0(messages, 0, after->level_);
            }
            strcat(text, more);
            MessageName name;
            func_020e4bf4(&name, id);
            messages->unk_10 = &name;
            func_0204500c(messages, text, 1, 0xe3);
            messages->unk_19b2 = 0;
            messages->busy_ = 1;
        }
        if (!inParty)
        {
            end->step_ += 2;
        }
        else
        {
            func_0209c6d8(data_02109bf4, 0x35);
            func_ov017_021ce704(id);
            func_ov017_021cc730(id, 0, 0, 1);
            func_ov017_021c9e00(id, 0, 0, 0);
            end->step_++;
        }
    }
    else if (step == 5)
    {
        if (IsMessageDone())
        {
            int id = end->current_;
            if (sEnd->FindMember(id) != NULL)
            {
                char text[0x100];
                sprintf(text, func_02072a68(&texts_, 0x26));
                strcat(text, more);
                MessageName name;
                func_020e4bf4(&name, id);
                messages->unk_10 = &name;
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
            }
            end->step_++;
        }
    }
    else if (step == 6)
    {
        if (inParty)
        {
            int id = end->current_;
            BattleResultStats* stats = &levelUps_[id].unk_28;
            unsigned short points = 0;
            PartyMember* member = func_0200ff1c(gameState, id);
            if (member != NULL)
            {
                PartyMemberData* data = func_02053c6c(member);
                if (data != NULL)
                    points = data->unspentSkillPoints_;
            }
            func_02010828(gameState);
            if (end->skillCounts_[id] != 0)
            {
                end->next_ = 0xa;
            }
            else if (stats->skillPoints_ != 0)
            {
                end->next_ = 0xc;
            }
            else if (points != 0 && CanLearnSkill(id))
            {
                end->next_ = 8;
                void* unk = func_0205ec34();
                if (func_0206dfb0(unk, (char*)unk + 0x8c, 0x119c))
                    messages->unk_19ca = 0;
            }
        }
        end->step_++;
    }
    else if (step == 7)
    {
        if (func_0209ca2c(data_02109bf4))
            return endState_;
        if (IsMessageDone())
        {
            int next = end->next_;
            end->Reset();
            if (next >= 0)
                return next;
        }
        return endState_;
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN18BattleResultWindow10InitializeEv(); // BattleResultWindow::Initialize
    void _ZN18BattleResultWindow10SetMembersEPKhh(); // BattleResultWindow::SetMembers
    void _ZN18BattleResultWindow11ShowLevelUpEiPK17BattleResultStatsS2_(); // BattleResultWindow::ShowLevelUp
    void _ZN18BattleResultWindow5CloseEv(); // BattleResultWindow::Close
    void _ZN18BattleResultWindow6FinishEv(); // BattleResultWindow::Finish
    void _ZN18BattleResultWindow9SetSourceEP24BattleResultWindowSource(); // BattleResultWindow::SetSource
    void _ZN9BattleEnd10FindMemberEi(); // BattleEnd::FindMember
    void _ZN9BattleEnd5ResetEv(); // BattleEnd::Reset
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int BattleScene::End_LevelUp()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x264
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    str r0, [sp, #0x18]
    ldr r4, [r1, #0x0]
    bl func_020421a0
    mov r6, r0
    bl func_02046380
    bl _ZN16BackgroundLoader11GetInstanceEv
    add r1, r10, #0x104
    mov r7, r0
    add r0, r1, #0x5800
    mov r1, #0x22
    bl func_02072a68
    mov r11, r0
    ldr r0, [sp, #0x18]
    bl func_02010828
    ldr r1, [r4, #0x18]
    bl func_02086ef0
    ldr r1, [r4, #0x0]
    mov r5, r0
    cmp r1, #0x0
    bne @L021f0b40
    ldr r0, [r4, #0x18]
    add r1, r0, #0x1
    str r1, [r4, #0x18]
    cmp r1, #0x4
    blt @L021f0ae4
    mov r0, r4
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0xb
    b @L021f1218
@L021f0ae4:
    ldr r0, =sEnd
    ldr r0, [r0, #0x0]
    bl _ZN9BattleEnd10FindMemberEi
    movs r5, r0
    ldreq r0, [r10, #0xeac]
    beq @L021f1218
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x0
    bl func_02072a68
    mov r1, r0
    ldrb r2, [r5, #0x1]
    add r0, sp, #0x3c
    bl sprintf
    add r1, sp, #0x3c
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0x4]
    ldr r0, [r4, #0x0]
    add r0, r0, #0x1
    str r0, [r4, #0x0]
    b @L021f1214
@L021f0b40:
    cmp r1, #0x1
    bne @L021f0dac
    ldr r1, [r4, #0x4]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021f1218
    ldr r1, [r4, #0x4]
    add r2, sp, #0x1c
    add r3, sp, #0x20
    mov r0, r7
    ldr r6, [r4, #0x18]
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r1, [r4, #0x4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r0, =sEnd
    mov r1, r6
    ldr r0, [r0, #0x0]
    mov r11, #0x0
    bl _ZN9BattleEnd10FindMemberEi
    ldr r1, [sp, #0x1c]
    mov r7, r0
    cmp r1, #0x0
    beq @L021f0be0
    add r0, r10, #0x770
    add r2, r0, #0x5000
    mov r0, #0x54
    ldr r3, [r7, #0x4]
    mla r0, r6, r0, r2
    str r3, [sp, #0x0]
    ldrb r3, [r7, #0x2]
    ldr r2, [sp, #0x20]
    bl func_02082490
    cmp r0, #0x0
    beq @L021f0be0
    ldrb r0, [r7, #0x3]
    cmp r0, #0x0
    moveq r11, #0x1
@L021f0be0:
    mov r0, #0x54
    mul r0, r6, r0
    str r0, [sp, #0x4]
    add r0, r10, #0x398
    add r1, r0, #0x5400
    ldr r0, [sp, #0x4]
    cmp r11, #0x0
    add r8, r1, r0
    ldrh r1, [r8, #0x4]
    ldrb r0, [r7, #0x2]
    mov r9, #0x0
    mov r1, r1, lsl #0x19
    str r0, [sp, #0x14]
    add r0, r0, r1, lsr #0x19
    str r0, [sp, #0x10]
    beq @L021f0d08
    cmp r5, #0x0
    beq @L021f0d10
    ldr r0, [sp, #0x18]
    mov r1, r6
    bl func_0200ff1c
    str r0, [sp, #0xc]
    cmp r0, #0x0
    beq @L021f0d10
    bl func_02053c6c
    ldr r1, [r0, #0x950]
    str r0, [sp, #0x8]
    add r2, r0, #0x500
    add r0, r0, r1, lsl #0x1
    add r1, r0, #0x100
    ldr r0, [sp, #0x10]
    add r3, r10, #0x384
    strh r0, [r1, #0x6c]
    ldrh r1, [r2, #0x64]
    ldr r0, =0xa28
    ldrh r2, [r8, #0x4]
    sub r0, r0, r1
    mov r0, r0, lsl #0x10
    mov r1, r0, lsr #0x10
    mov r0, r2, lsl #0x10
    cmp r1, r0, lsr #0x17
    ldrlo r0, =0xffff007f
    movlo r1, r1, lsl #0x17
    andlo r0, r2, r0
    orrlo r0, r0, r1, lsr #0x10
    strloh r0, [r8, #0x4]
    mov r0, #0x54
    ldrh r1, [r8, #0x4]
    mul r2, r6, r0
    ldr r0, [sp, #0x8]
    mov r8, r1, lsl #0x10
    add r1, r0, #0x500
    ldrh r12, [r1, #0x64]
    add r8, r12, r8, lsr #0x17
    strh r8, [r1, #0x64]
    add r1, r3, #0x5400
    add r3, r10, #0x3ac
    add r3, r3, #0x5400
    add r1, r1, r2
    add r2, r3, r2
    bl func_02083cbc
    ldr r0, [sp, #0x8]
    mov r1, #0x0
    bl func_02083e28
    add r8, r4, #0x1c
    mov r2, #0x14
    mla r2, r6, r2, r8
    ldr r1, [sp, #0xc]
    ldr r3, [sp, #0x14]
    add r0, r4, #0xf0
    bl func_0209aa54
    add r1, r4, r6
    strb r0, [r1, #0x6c]
    b @L021f0d10
@L021f0d08:
    str r9, [r4, #0x0]
    mov r9, #0x1
@L021f0d10:
    cmp r5, #0x0
    beq @L021f0d90
    ldr r0, [sp, #0x18]
    mov r1, r6
    bl func_0200ff1c
    movs r5, r0
    beq @L021f0d90
    bl func_02053c6c
    mov r6, r0
    ldr r0, [r6, #0x950]
    add r0, r6, r0, lsl #0x1
    add r0, r0, #0x100
    ldrh r0, [r0, #0x6c]
    cmp r0, #0x63
    blt @L021f0d90
    ldr r0, [sp, #0x4]
    cmp r11, #0x0
    add r0, r10, r0
    add r0, r0, #0x5000
    ldr r8, [r0, #0x770]
    ldrne r8, [r0, #0x784]
    cmp r8, #0x0
    beq @L021f0d90
    mov r0, r5
    bl GetMemberExperience
    cmp r8, r0
    bhi @L021f0d90
    cmp r6, #0x0
    ldrne r0, [r6, #0x950]
    addne r0, r6, r0, lsl #0x2
    strne r8, [r0, #0x138]
    str r8, [r7, #0x4]
@L021f0d90:
    cmp r9, #0x0
    ldrne r0, [r10, #0xeac]
    bne @L021f1218
    ldr r0, [r4, #0x0]
    add r0, r0, #0x1
    str r0, [r4, #0x0]
    b @L021f1214
@L021f0dac:
    cmp r1, #0x2
    bne @L021f0e7c
    add r0, r10, #0x5000
    ldr r0, [r0, #0x588]
    cmp r0, #0x0
    beq @L021f0de8
    bl _ZN18BattleResultWindow5CloseEv
    add r0, r10, #0x5000
    ldr r0, [r0, #0x588]
    bl _ZN18BattleResultWindow6FinishEv
    add r0, r10, #0x5000
    mov r1, #0x0
    str r1, [r0, #0x588]
    ldr r0, [r10, #0xeac]
    b @L021f1218
@L021f0de8:
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    cmp r5, #0x0
    moveq r0, #0x4
    streq r0, [r4, #0x0]
    beq @L021f1214
    add r0, r10, #0x30
    mov r1, #0x12c
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x588]
    bl _ZN18BattleResultWindow10InitializeEv
    add r0, r10, #0x5000
    add r1, r10, #0x760
    ldr r0, [r0, #0x588]
    add r1, r1, #0x3000
    bl _ZN18BattleResultWindow9SetSourceEP24BattleResultWindowSource
    ldr r2, =sEnd
    add r1, r10, #0x5000
    ldr r6, [r2, #0x0]
    ldr r3, [r1, #0x588]
    add r0, r6, #0x2000
    ldrb r5, [r0, #0x788]
    add r0, r6, #0x118
    str r0, [r3, #0x120]
    strb r5, [r3, #0x11e]
    ldr r3, [r2, #0x0]
    ldr r0, [r1, #0x588]
    add r2, r3, #0x2000
    add r1, r3, #0x89
    ldrb r2, [r2, #0x78d]
    add r1, r1, #0x2700
    bl _ZN18BattleResultWindow10SetMembersEPKhh
    ldr r0, [r4, #0x0]
    add r0, r0, #0x1
    str r0, [r4, #0x0]
    b @L021f1214
@L021f0e7c:
    cmp r1, #0x3
    bne @L021f0ea0
    add r0, r10, #0x5000
    ldr r0, [r0, #0x588]
    ldrb r0, [r0, #0x11b]
    cmp r0, #0xff
    addeq r0, r1, #0x1
    streq r0, [r4, #0x0]
    b @L021f1214
@L021f0ea0:
    cmp r1, #0x4
    bne @L021f1054
    ldr r7, [r4, #0x18]
    mov r0, #0x54
    mul r3, r7, r0
    add r0, r10, #0x5000
    add r1, r10, #0x770
    ldr r0, [r0, #0x588]
    add r2, r1, #0x5000
    add r1, r10, #0x398
    cmp r0, #0x0
    add r9, r2, r3
    add r8, r1, #0x5400
    beq @L021f0ee8
    mov r1, r7
    mov r2, r9
    add r3, r8, r3
    bl _ZN18BattleResultWindow11ShowLevelUpEiPK17BattleResultStatsS2_
@L021f0ee8:
    ldr r0, =sEnd
    mov r1, r7
    ldr r0, [r0, #0x0]
    bl _ZN9BattleEnd10FindMemberEi
    cmp r0, #0x0
    beq @L021f0ff4
    add r0, r10, #0x384
    add r1, r0, #0x5400
    mov r0, #0x54
    mla r8, r7, r0, r1
    ldrh r0, [r9, #0x4]
    ldrh r1, [r8, #0x4]
    mov r0, r0, lsl #0x19
    mov r1, r1, lsl #0x19
    mov r0, r0, lsr #0x19
    rsb r0, r0, r1, lsr #0x19
    cmp r0, #0x1
    add r0, r10, #0x104
    add r0, r0, #0x5800
    ble @L021f0f80
    mov r1, #0x16
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x164
    bl sprintf
    ldrh r2, [r9, #0x4]
    mov r0, r6
    mov r1, #0x0
    mov r2, r2, lsl #0x19
    mov r2, r2, lsr #0x19
    bl func_020465c0
    ldrh r2, [r8, #0x4]
    mov r0, r6
    mov r1, #0x1
    mov r2, r2, lsl #0x19
    mov r2, r2, lsr #0x19
    bl func_020465c0
    b @L021f0fac
@L021f0f80:
    mov r1, #0xa
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x164
    bl sprintf
    ldrh r2, [r8, #0x4]
    mov r0, r6
    mov r1, #0x0
    mov r2, r2, lsl #0x19
    mov r2, r2, lsr #0x19
    bl func_020465c0
@L021f0fac:
    add r0, sp, #0x164
    mov r1, r11
    bl strcat
    add r0, sp, #0x30
    mov r1, r7
    bl func_020e4bf4
    add r1, sp, #0x30
    str r1, [r6, #0x10]
    mov r0, r6
    add r1, sp, #0x164
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
@L021f0ff4:
    cmp r5, #0x0
    ldreq r0, [r4, #0x0]
    addeq r0, r0, #0x2
    streq r0, [r4, #0x0]
    beq @L021f1214
    ldr r0, =data_02109bf4
    mov r1, #0x35
    bl func_0209c6d8
    mov r0, r7
    bl func_ov017_021ce704
    mov r1, #0x0
    mov r0, r7
    mov r2, r1
    mov r3, #0x1
    bl func_ov017_021cc730
    mov r1, #0x0
    mov r0, r7
    mov r2, r1
    mov r3, r1
    bl func_ov017_021c9e00
    ldr r0, [r4, #0x0]
    add r0, r0, #0x1
    str r0, [r4, #0x0]
    b @L021f1214
@L021f1054:
    cmp r1, #0x5
    bne @L021f10f8
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f1214
    ldr r0, =sEnd
    ldr r5, [r4, #0x18]
    ldr r0, [r0, #0x0]
    mov r1, r5
    bl _ZN9BattleEnd10FindMemberEi
    cmp r0, #0x0
    beq @L021f10e8
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x26
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x64
    bl sprintf
    add r0, sp, #0x64
    mov r1, r11
    bl strcat
    mov r1, r5
    add r0, sp, #0x24
    bl func_020e4bf4
    add r1, sp, #0x24
    str r1, [r6, #0x10]
    mov r0, r6
    add r1, sp, #0x64
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x0
    add r0, r6, #0x1000
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
@L021f10e8:
    ldr r0, [r4, #0x0]
    add r0, r0, #0x1
    str r0, [r4, #0x0]
    b @L021f1214
@L021f10f8:
    cmp r1, #0x6
    bne @L021f11cc
    cmp r5, #0x0
    beq @L021f11bc
    add r0, r10, #0x398
    add r1, r0, #0x5400
    ldr r8, [r4, #0x18]
    mov r0, #0x54
    mla r5, r8, r0, r1
    ldr r0, [sp, #0x18]
    mov r1, r8
    mov r7, #0x0
    bl func_0200ff1c
    cmp r0, #0x0
    beq @L021f1144
    bl func_02053c6c
    cmp r0, #0x0
    addne r0, r0, #0x500
    ldrneh r7, [r0, #0x64]
@L021f1144:
    ldr r0, [sp, #0x18]
    bl func_02010828
    add r0, r4, r8
    ldrb r0, [r0, #0x6c]
    cmp r0, #0x0
    movne r0, #0xa
    strneb r0, [r4, #0xe5]
    bne @L021f11bc
    ldrh r0, [r5, #0x4]
    mov r0, r0, lsl #0x10
    movs r0, r0, lsr #0x17
    movne r0, #0xc
    strneb r0, [r4, #0xe5]
    bne @L021f11bc
    cmp r7, #0x0
    beq @L021f11bc
    mov r0, r8
    bl CanLearnSkill
    cmp r0, #0x0
    beq @L021f11bc
    mov r0, #0x8
    strb r0, [r4, #0xe5]
    bl func_0205ec34
    ldr r2, =0x119c
    add r1, r0, #0x8c
    bl func_0206dfb0
    cmp r0, #0x0
    addne r0, r6, #0x1000
    movne r1, #0x0
    strneb r1, [r0, #0x9ca]
@L021f11bc:
    ldr r0, [r4, #0x0]
    add r0, r0, #0x1
    str r0, [r4, #0x0]
    b @L021f1214
@L021f11cc:
    cmp r1, #0x7
    bne @L021f1214
    ldr r0, =data_02109bf4
    bl func_0209ca2c
    cmp r0, #0x0
    ldrne r0, [r10, #0xeac]
    bne @L021f1218
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f120c
    ldrsb r5, [r4, #0xe5]
    mov r0, r4
    bl _ZN9BattleEnd5ResetEv
    cmp r5, #0x0
    movge r0, r5
    bge @L021f1218
@L021f120c:
    ldr r0, [r10, #0xeac]
    b @L021f1218
@L021f1214:
    ldr r0, [r10, #0xeac]
@L021f1218:
    add sp, sp, #0x264
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif


int BattleScene::End_SkillPoints()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    GameResources* resources = func_ov017_0218b5b0();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* unk = func_0205ec34();
    MessageSystem* messages = func_020421a0();
    int id = end->current_;
    int inParty = func_02086ef0(func_02010828(gameState), id);
    if (skillMenu_ == NULL)
    {
        if (resultWindow_ != NULL)
        {
            SetMenuHidden(&menu_, 1);
            resultWindow_->Close();
            resultWindow_->Finish();
            resultWindow_ = NULL;
        }
        func_0205d6a0((TextWindow*)&menu_.unk_0[0x188], 1);
        allocator_.Reset();
        skillMenu_ = (SkillPointMenu*)allocator_.Allocate(sizeof(SkillPointMenu));
        skillMenu_->Initialize((SkillPointMenuParent*)&menu_);
        skillMenu_->Setup(&allocator_);
        SkillPointMenu* menu = skillMenu_;
        menu->spriteRenderer_ = (SpriteRenderer*)&menu_.icons_[0x11c - 0xd0];
        menu->cursorAnimation_ = 0;
        unk_5584 = 0;
    }
    else if (skillMenu_ != NULL)
    {
        if (end->step_ == 0)
        {
            if (!func_0206dfb0(unk, (char*)unk + 0x8c, 0x119c))
            {
                func_0206df6c(unk, (char*)unk + 0x8c, 0x119c, 1);
                if (inParty)
                {
                    func_0204500c(messages, func_02072a68(&texts_, 0x24), 1, 0xe3);
                    messages->unk_19b2 = 0;
                    messages->busy_ = 1;
                }
                end->step_ = 100;
            }
            else
            {
                func_02043204(messages);
                SetMainBrightness(resources, -0x10, 0x10);
                end->step_++;
            }
        }
        else if (end->step_ == 100)
        {
            if (messages->unk_9a0 == 3)
                messages->unk_19af = 0;
            if (IsMessageDone())
            {
                func_02043204(messages);
                SetMainBrightness(resources, -0x10, 0x10);
                end->step_ = 1;
            }
        }
        else if (end->step_ == 1)
        {
            if (!IsMainBrightnessTransitionActive(resources))
            {
                end->step_++;
                func_02043204(messages);
                func_020de868(menu_.icons_);
                SafeAllocator* allocator = &menu_.unk_1ac8;
                allocator->Reset();
                abilities_ = (SkillAbilityList*)allocator->Allocate(sizeof(SkillAbilityList));
                abilities_->Initialize(0);
                abilities_->Setup(allocator);
                PartyMember* member = func_0200ff1c(gameState, id);
                if (member != NULL)
                {
                    skillMenu_->SetMember(member);
                    abilities_->member_ = *(short*)((char*)member + 4);
                }
            }
        }
        else if (end->step_ == 2)
        {
            if (abilities_->Load())
                end->step_++;
        }
        else if (end->step_ == 3)
        {
            SetMainBrightness(resources, 0, 0x10);
            end->step_++;
        }
        else if (end->step_ == 4)
        {
            if (!IsMainBrightnessTransitionActive(resources))
            {
                func_0205ea20(data_02108760, 100);
                end->step_++;
            }
        }
        else if (end->step_ == 5)
        {
            PartyMember* member = func_0200ff1c(gameState, id);
            if (skillMenu_->Update(gameState->GetTickCount()) == SkillPointMenu::State_End)
            {
                if (loader->GetNumQueuedTasks() > 0)
                    return endState_;
                end->step_++;
                return endState_;
            }
            int skill = skillMenu_->selection_;
            if (member != NULL)
                abilities_->Select((signed char)*(short*)((char*)member + 4), (unsigned char)skill);
        }
        else if (end->step_ == 6)
        {
            SetMainBrightness(resources, -0x10, 0);
            end->step_++;
        }
        else if (end->step_ == 7)
        {
            if (!IsMainBrightnessTransitionActive(resources))
                end->step_++;
        }
        else if (end->step_ == 8)
        {
            abilities_->Finish();
            abilities_ = NULL;
            end->step_++;
        }
        else if (end->step_ == 9)
        {
            SetMainBrightness(resources, 0, 0x10);
            end->step_++;
        }
        else if (end->step_ == 10)
        {
            if (!IsMainBrightnessTransitionActive(resources))
            {
                func_0205ea20(data_02108760, 0x65);
                func_0200ff1c(gameState, id);
                PartyMember* member = func_0200ff1c(gameState, id);
                if (member != NULL)
                {
                    skillMenu_->Apply(member);
                    end->newSkillCount_ = func_0209a678(end->skillTable_, member, end->newSkills_);
                    func_02083e28(func_02053c6c(member), 0);
                }
                func_ov017_021cc730(id, 0, 0, 1);
                func_ov017_021ccc34(id);
                func_ov017_021c9e00(id, 0, 0, 0);
                if (end->newSkillCount_ != 0)
                {
                    skillMenu_ = NULL;
                    end->Reset();
                    end->newSkill_ = 0;
                    func_ov017_021cd0d8(id, end->newSkills_, end->newSkillCount_);
                    return 9;
                }
                end->step_++;
            }
        }
        else if (end->step_ == 11)
        {
            void* music = func_02094a00();
            func_02094b40(music);
            func_02094b34(music, 0x65, 500, 0, 0);
            end->step_++;
        }
        else if (end->step_ == 12)
        {
            if (func_02094b4c(func_02094a00()))
            {
                skillMenu_ = NULL;
                end->Reset();
                return 7;
            }
        }
    }
    return endState_;
}

// Hides or shows the window of the menus on the sub screen
static void SetMenuHidden(BattleMenu* menu, int hidden)
{
    if (hidden)
    {
        menu->flags_ |= 0x80;
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x200;
        return;
    }
    menu->flags_ &= ~0x80;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1700;
}



// NONMATCHING: the C matches 74.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_SkillArts()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int id = end->current_;
    int inParty = func_02086ef0(func_02010828(gameState), id);
    char text[0x200];
    char buffer[0x80];
    MessageName name;
    TextTable names;
    char gp2[0x40];
    char inner[0x20];
    unsigned int size;
    unsigned int scriptSize;
    void* script;
    unsigned int namesSize;
    if (end->step_ == 0)
    {
        busy_ = 1;
        BackgroundLoader::AddLockGlobal();
        BackgroundLoader::FreeAllocationsGlobal();
        allocator_.Reset();
        void* file = LoadFileIntoMemory(STRING(0x28, "data/prm/skilltable.bin"), data_0211e33c, &size);
        func_0209a338(skillTable_);
        if (file != NULL)
            func_0209a470(skillTable_, &allocator_, file, size);
        const char* archive = func_02072a68(&texts_, 0x2b);
        file = ExtractFileFromGP2(archive, func_02072a68(&texts_, 0x21), &size);
        artNames_ = (TextList*)allocator_.Allocate(sizeof(TextList));
        func_020727d8(artNames_);
        if (file != NULL)
            func_020728ac(artNames_, &allocator_, file, size, 0, 0, 0);
        file = ExtractFileFromGP2(STRING(0x86, "data/prm/skl_art.gp2"), STRING(0x9b, "skl_art_<LG>.nat"), &size);
        titleNames_ = allocator_.Allocate(0xc);
        func_020e526c(titleNames_);
        if (file != NULL)
            func_020e5604(titleNames_, &allocator_, file, size);
        BackgroundLoader::RemoveLockGlobal();
        titles_ = NULL;
        end->task_ = loader->QueueLoadFile(STRING(0xac, "data/scenario/title_skl.stb"), NULL);
        end->step_++;
    }
    if (end->step_ == 1)
    {
        if (loader->GetTaskStatus(end->task_))
        {
            loader->GetLoadedFileByID(end->task_, &script, &scriptSize);
            titles_ = (TitleScript*)allocator_.Allocate(0xd0);
            func_0209fe9c(titles_);
            func_0209fee4(titles_, &allocator_, script, scriptSize);
            func_0209ff64(titles_, 100);
            do
            {
                func_0209ff6c(titles_);
            } while (!IsTitleScriptDone(titles_));
            loader->RemoveTask(end->task_);
            end->task_ = -1;
            end->step_++;
        }
    }
    else if (end->step_ == 2)
    {
        while (end->newSkill_ < end->newSkillCount_)
        {
            SkillEntry* entry = func_0209a594(skillTable_, end->newSkills_[end->newSkill_]);
            const char* art = NULL;
            if (entry != NULL)
                art = func_02072a68(artNames_, entry->kind_);
            if (art != NULL)
            {
            PartyMember* member = func_0200ff1c(GameState::GetInstance(), id);
            if (member != NULL)
            {
            __clear(text, sizeof(text));
            func_02042058(text, art);
            func_02042058(text, func_02072a68(&texts_, 0x22));
            func_02046380(messages);
            func_02046574(messages, 0, member->status_->name_);
            func_020e4bf4(&name, id);
            messages->arguments_ = &name;
            if (entry->kind_ == 1)
            {
                const char** title = func_020e5294(titleNames_, entry->id_);
                messages->unk_8 = title;
                __clear(buffer, sizeof(buffer));
                func_020e4864(*title, buffer, 1, 0, 0, 0);
                func_02046574(messages, 1, buffer);
            }
            else
            {
                func_02046574(messages, 1, func_02072a68(artNames_, (short)(entry->value_ + 100)));
            }
            int index = 2;
            if (entry->kind_ == 4 || entry->kind_ == 0x10)
                index = 1;
            func_02046574(messages, index, func_02072a68(artNames_, (short)(entry->vocation_ + 200)));
            func_020465c0(messages, 0, entry->points_);
            if (inParty)
            {
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
            }
            end->newSkill_++;
            end->step_++;
            return endState_;
            }
            }
            end->newSkill_++;
        }
        end->step_ = 4;
    }
    else if (end->step_ == 3)
    {
        if (end->newSkillCount_ <= end->newSkill_ && titles_->count_ > 0)
            messages->unk_19ca = 0;
        if (IsMessageDone())
        {
            if (end->newSkillCount_ <= end->newSkill_)
                end->step_++;
            else
                end->step_ = 2;
        }
    }
    else if (end->step_ == 4)
    {
        short* ids;
        int i;
        int count = titles_->count_;
        if (count > 0)
        {
            func_02043204(messages);
            SafeAllocator* idAllocator = &menu_.unk_1af8;
            idAllocator->Reset();
            count = titles_->count_;
            ids = (short*)idAllocator->Allocate(count * 2);
            for (int k = 0; k < count; k++)
                ids[k] = titles_->ids_[k];
            allocator_.Reset();
            artNames_ = NULL;
            titleNames_ = NULL;
            titles_ = NULL;
            titleTable_ = allocator_.Allocate(0x14);
            func_020a13c4(titleTable_);
            func_020a13e4(titleTable_, &allocator_, ids, count, 4);
            firstGuide_ = ((GuideWindow*)titleTable_)->SetShown(ids, count) & 1 ? 1 : 0;
            GameObject* hero = gameState->GetProtagonist();
            func_020dfc2c(&names);
            func_020dfc40(&names);
            BackgroundLoader::AddLockGlobal();
            namesSize = 0;
            __clear(gp2, sizeof(gp2));
            __clear(inner, sizeof(inner));
            sprintf(gp2, STRING(0xc8, "data/bin/ttlname%d.gp2"), hero->partyData_->appearance_.female_);
            sprintf(inner, STRING(0xdf, "ttlname%d_<LG>.nat"), hero->partyData_->appearance_.female_);
            void* file = ExtractFileFromGP2(gp2, inner, &namesSize);
            if (file != NULL)
                func_020e0028(&names, &allocator_, file, namesSize, ids, (unsigned short)count);
            BackgroundLoader::RemoveLockGlobal();
            pages_ = (GuidePage*)allocator_.Allocate(count * sizeof(GuidePage));
            for (i = 0; i < count; i++)
            {
                GuideEntry* entry = func_020a15bc(titleTable_, ids[i]);
                if (entry == NULL)
                    continue;
                const char* title = func_020e0434(&names, ids[i]);
                if (title == NULL)
                    continue;
                ClearPage(&pages_[i]);
                SetPage(&pages_[i], entry);
                SetPageTitle(&pages_[i], title);
            }
            titleTable_ = NULL;
            pageCount_ = count;
            idAllocator->Reset();
            end->step_++;
        }
        else if (count == 0)
        {
            allocator_.Reset();
            artNames_ = NULL;
            titleNames_ = NULL;
            titles_ = NULL;
            busy_ = 0;
            void* music = func_02094a00();
            func_02094b40(music);
            func_02094b34(music, 0x65, 500, 0, 0);
            end->step_ = 8;
        }
    }
    else if (end->step_ == 5)
    {
        guide_ = (GuideWindow*)allocator_.Allocate(sizeof(GuideWindow));
        guide_->Initialize(7);
        guide_->flags_ |= GUIDE_WINDOW_MAIN_SCREEN;
        guide_->CreateAllocators(&allocator_);
        guide_->SetPages(pages_, pageCount_);
        SetGuideUnk400(guide_, firstGuide_);
        end->step_++;
    }
    else if (end->step_ == 6)
    {
        if (guide_->flags_ & GUIDE_WINDOW_MESSAGE_WINDOW ? 1 : 0)
            end->step_++;
    }
    else if (end->step_ == 7)
    {
        guide_->Finish();
        allocator_.Reset();
        guide_ = NULL;
        pages_ = NULL;
        pageCount_ = 0;
        firstGuide_ = 0;
        busy_ = 0;
        SetMainBrightness(func_0200fb8c(gameState), 0, 0xf);
        void* music = func_02094a00();
        func_02094b40(music);
        func_02094b34(music, 0x65, 500, 0, 0);
        end->step_++;
    }
    else if (end->step_ == 8)
    {
        if (func_02094b4c(func_02094a00()))
            end->step_++;
    }
    else if (end->step_ == 9)
    {
        if (!IsBrightnessTransitionActive(func_0200fb8c(gameState)))
        {
            end->Reset();
            return 7;
        }
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11GuideWindow10InitializeEh(); // GuideWindow::Initialize
    void _ZN11GuideWindow16CreateAllocatorsEP13SafeAllocator(); // GuideWindow::CreateAllocators
    void _ZN11GuideWindow6FinishEv(); // GuideWindow::Finish
    void _ZN11GuideWindow8SetPagesEP9GuidePagei(); // GuideWindow::SetPages
    void _ZN11GuideWindow8SetShownEPKsi(); // GuideWindow::SetShown
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN9GameState14GetProtagonistEv(); // GameState::GetProtagonist
}

asm int BattleScene::End_SkillArts()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x32c
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    mov r4, r0
    ldr r6, [r1, #0x0]
    bl func_020421a0
    mov r7, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r5, r0
    ldr r0, [r6, #0x18]
    str r0, [sp, #0xc]
    mov r0, r4
    bl func_02010828
    ldr r1, [sp, #0xc]
    bl func_02086ef0
    mov r11, r0
    ldr r0, [r6, #0x0]
    cmp r0, #0x0
    bne @L021f1a10
    add r0, r10, #0x7000
    mov r1, #0x1
    strb r1, [r0, #0x7d1]
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, =sStrings+0x28
    ldr r1, =data_0211e33c
    add r2, sp, #0x24
    bl LoadFileIntoMemory
    mov r8, r0
    add r0, r10, #0x298
    add r0, r0, #0xc00
    bl func_0209a338
    cmp r8, #0x0
    beq @L021f1918
    add r0, r10, #0x298
    ldr r3, [sp, #0x24]
    mov r2, r8
    add r0, r0, #0xc00
    add r1, r10, #0x30
    bl func_0209a470
@L021f1918:
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x2b
    bl func_02072a68
    add r1, r10, #0x104
    mov r8, r0
    add r0, r1, #0x5800
    mov r1, #0x21
    bl func_02072a68
    mov r1, r0
    mov r0, r8
    add r2, sp, #0x24
    bl ExtractFileFromGP2
    mov r8, r0
    add r0, r10, #0x30
    mov r1, #0x8
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x57c]
    bl func_020727d8
    cmp r8, #0x0
    beq @L021f1998
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    add r0, r10, #0x5000
    ldr r0, [r0, #0x57c]
    ldr r3, [sp, #0x24]
    mov r2, r8
    add r1, r10, #0x30
    bl func_020728ac
@L021f1998:
    ldr r0, =sStrings+0x86
    ldr r1, =sStrings+0x9b
    add r2, sp, #0x24
    bl ExtractFileFromGP2
    mov r8, r0
    add r0, r10, #0x30
    mov r1, #0xc
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x580]
    bl func_020e526c
    cmp r8, #0x0
    beq @L021f19e4
    add r0, r10, #0x5000
    ldr r0, [r0, #0x580]
    ldr r3, [sp, #0x24]
    mov r2, r8
    add r1, r10, #0x30
    bl func_020e5604
@L021f19e4:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r3, r10, #0x5000
    mov r2, #0x0
    ldr r1, =sStrings+0xac
    mov r0, r5
    str r2, [r3, #0x5c4]
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r6, #0x4]
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
@L021f1a10:
    ldr r0, [r6, #0x0]
    cmp r0, #0x1
    bne @L021f1ac4
    ldr r1, [r6, #0x4]
    mov r0, r5
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021f21c4
    ldr r1, [r6, #0x4]
    add r2, sp, #0x1c
    add r3, sp, #0x20
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r10, #0x30
    mov r1, #0xd0
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x5c4]
    bl func_0209fe9c
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c4]
    ldr r2, [sp, #0x1c]
    ldr r3, [sp, #0x20]
    add r1, r10, #0x30
    bl func_0209fee4
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c4]
    mov r1, #0x64
    bl func_0209ff64
    add r4, r10, #0x5000
@L021f1a88:
    ldr r0, [r4, #0x5c4]
    bl func_0209ff6c
    ldr r0, [r4, #0x5c4]
    bl IsTitleScriptDone
    cmp r0, #0x0
    beq @L021f1a88
    ldr r1, [r6, #0x4]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r6, #0x4]
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f21c4
@L021f1ac4:
    cmp r0, #0x2
    bne @L021f1d0c
    add r5, r10, #0x298
    add r4, r10, #0x5000
    b @L021f1cf0
@L021f1ad8:
    ldrb r1, [r6, #0xe3]
    add r0, r5, #0xc00
    add r1, r6, r1, lsl #0x1
    ldrh r1, [r1, #0x74]
    bl func_0209a594
    movs r8, r0
    mov r9, #0x0
    beq @L021f1b10
    ldr r1, [r8, #0x4]
    ldr r0, [r4, #0x57c]
    mov r1, r1, lsl #0x7
    mov r1, r1, lsr #0x1b
    bl func_02072a68
    mov r9, r0
@L021f1b10:
    cmp r9, #0x0
    beq @L021f1ce4
    bl _ZN9GameState11GetInstanceEv
    ldr r1, [sp, #0xc]
    bl func_0200ff1c
    str r0, [sp, #0x10]
    cmp r0, #0x0
    beq @L021f1ce4
    add r0, sp, #0x12c
    mov r1, #0x200
    bl __clear
    add r0, sp, #0x12c
    mov r1, r9
    bl func_02042058
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x22
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x12c
    bl func_02042058
    mov r0, r7
    bl func_02046380
    ldr r0, [sp, #0x10]
    mov r1, #0x0
    ldr r2, [r0, #0x134]
    mov r0, r7
    bl func_02046574
    ldr r1, [sp, #0xc]
    add r0, sp, #0xa0
    bl func_020e4bf4
    add r0, sp, #0xa0
    str r0, [r7, #0x0]
    ldr r0, [r8, #0x4]
    mov r1, r0, lsl #0x7
    mov r1, r1, lsr #0x1b
    cmp r1, #0x1
    bne @L021f1bfc
    add r0, r10, #0x5000
    ldrsh r1, [r8, #0x2]
    ldr r0, [r0, #0x580]
    bl func_020e5294
    mov r4, r0
    add r0, sp, #0xac
    mov r1, #0x80
    str r4, [r7, #0x8]
    bl __clear
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r0, [r4, #0x0]
    add r1, sp, #0xac
    mov r2, #0x1
    bl func_020e4864
    mov r0, r7
    mov r1, #0x1
    add r2, sp, #0xac
    bl func_02046574
    b @L021f1c2c
@L021f1bfc:
    mov r0, r0, lsl #0x1b
    mov r1, r0, lsr #0x1b
    add r0, r10, #0x5000
    add r1, r1, #0x64
    mov r1, r1, lsl #0x10
    ldr r0, [r0, #0x57c]
    mov r1, r1, asr #0x10
    bl func_02072a68
    mov r2, r0
    mov r0, r7
    mov r1, #0x1
    bl func_02046574
@L021f1c2c:
    ldrh r1, [r8, #0x0]
    ldr r0, [r8, #0x4]
    mov r4, #0x2
    mov r0, r0, lsl #0x7
    mov r1, r1, lsl #0x10
    mov r0, r0, lsr #0x1b
    mov r1, r1, lsr #0x1b
    cmp r0, #0x4
    cmpne r0, #0x10
    add r0, r10, #0x5000
    add r1, r1, #0xc8
    mov r1, r1, lsl #0x10
    ldr r0, [r0, #0x57c]
    moveq r4, #0x1
    mov r1, r1, asr #0x10
    bl func_02072a68
    mov r2, r0
    mov r0, r7
    mov r1, r4
    bl func_02046574
    ldr r1, [r8, #0x4]
    mov r0, r7
    mov r1, r1, lsl #0xc
    mov r2, r1, lsr #0x18
    mov r1, #0x0
    bl func_020465c0
    cmp r11, #0x0
    beq @L021f1cc4
    add r1, sp, #0x12c
    mov r0, r7
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    add r0, r7, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r7, #0x998]
@L021f1cc4:
    ldrb r0, [r6, #0xe3]
    add r0, r0, #0x1
    strb r0, [r6, #0xe3]
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    ldr r0, [r10, #0xeac]
    b @L021f21c8
@L021f1ce4:
    ldrb r0, [r6, #0xe3]
    add r0, r0, #0x1
    strb r0, [r6, #0xe3]
@L021f1cf0:
    ldrb r1, [r6, #0xe3]
    ldrb r0, [r6, #0xe2]
    cmp r1, r0
    blo @L021f1ad8
    mov r0, #0x4
    str r0, [r6, #0x0]
    b @L021f21c4
@L021f1d0c:
    cmp r0, #0x3
    bne @L021f1d70
    ldrb r1, [r6, #0xe2]
    ldrb r0, [r6, #0xe3]
    cmp r1, r0
    bhi @L021f1d40
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c4]
    ldrsh r0, [r0, #0x68]
    cmp r0, #0x0
    addgt r0, r7, #0x1000
    movgt r1, #0x0
    strgtb r1, [r0, #0x9ca]
@L021f1d40:
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f21c4
    ldrb r1, [r6, #0xe2]
    ldrb r0, [r6, #0xe3]
    cmp r1, r0
    ldrls r0, [r6, #0x0]
    addls r0, r0, #0x1
    strls r0, [r6, #0x0]
    movhi r0, #0x2
    strhi r0, [r6, #0x0]
    b @L021f21c4
@L021f1d70:
    cmp r0, #0x4
    bne @L021f203c
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c4]
    ldrsh r0, [r0, #0x68]
    cmp r0, #0x0
    ble @L021f1fe4
    mov r0, r7
    bl func_02043204
    add r0, r10, #0x760
    add r0, r0, #0x3000
    add r5, r0, #0x2f8
    add r0, r5, #0x1800
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x5000
    ldr r1, [r0, #0x5c4]
    add r0, r5, #0x1800
    ldrsh r7, [r1, #0x68]
    mov r1, r7, lsl #0x1
    bl _ZN13SafeAllocator8AllocateEj
    mov r8, r0
    mov r3, #0x0
    add r0, r10, #0x5000
    b @L021f1de8
@L021f1dd0:
    ldr r1, [r0, #0x5c4]
    mov r2, r3, lsl #0x1
    add r1, r1, r3, lsl #0x1
    ldrsh r1, [r1, #0x6a]
    add r3, r3, #0x1
    strh r1, [r8, r2]
@L021f1de8:
    cmp r3, r7
    blt @L021f1dd0
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    add r2, r10, #0x5000
    mov r3, #0x0
    str r3, [r2, #0x57c]
    str r3, [r2, #0x580]
    add r0, r10, #0x30
    mov r1, #0x14
    str r3, [r2, #0x5c4]
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x5c8]
    bl func_020a13c4
    mov r0, #0x4
    str r0, [sp, #0x0]
    add r0, r10, #0x5000
    mov r3, r7, lsl #0x10
    ldr r0, [r0, #0x5c8]
    add r1, r10, #0x30
    mov r2, r8
    mov r3, r3, lsr #0x10
    bl func_020a13e4
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c8]
    mov r1, r8
    mov r2, r7
    bl _ZN11GuideWindow8SetShownEPKsi
    tst r0, #0x1
    movne r2, #0x1
    moveq r2, #0x0
    add r1, r10, #0x5000
    mov r0, r4
    strb r2, [r1, #0x5d5]
    bl _ZN9GameState14GetProtagonistEv
    mov r4, r0
    add r0, sp, #0x88
    bl func_020dfc2c
    add r0, sp, #0x88
    bl func_020dfc40
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x18]
    add r0, sp, #0x48
    mov r1, #0x40
    bl __clear
    add r0, sp, #0x28
    mov r1, #0x20
    bl __clear
    ldr r1, [r4, #0x150]
    add r0, sp, #0x48
    ldrb r2, [r1, #0x49c]
    ldr r1, =sStrings+0xc8
    mov r2, r2, lsl #0x1f
    mov r2, r2, lsr #0x1f
    bl sprintf
    ldr r1, [r4, #0x150]
    add r0, sp, #0x28
    ldrb r2, [r1, #0x49c]
    ldr r1, =sStrings+0xdf
    mov r2, r2, lsl #0x1f
    mov r2, r2, lsr #0x1f
    bl sprintf
    add r0, sp, #0x48
    add r1, sp, #0x28
    add r2, sp, #0x18
    bl ExtractFileFromGP2
    movs r2, r0
    beq @L021f1f20
    mov r0, r7, lsl #0x10
    str r8, [sp, #0x0]
    mov r0, r0, lsr #0x10
    str r0, [sp, #0x4]
    ldr r3, [sp, #0x18]
    add r0, sp, #0x88
    add r1, r10, #0x30
    bl func_020e0028
@L021f1f20:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    mov r0, #0x244
    mul r1, r7, r0
    add r0, r10, #0x30
    bl _ZN13SafeAllocator8AllocateEj
    add r4, r10, #0x5000
    str r0, [r4, #0x5d0]
    mov r9, #0x0
    b @L021f1fb4
@L021f1f44:
    mov r0, r9, lsl #0x1
    ldrsh r1, [r8, r0]
    ldr r0, [r4, #0x5c8]
    bl func_020a15bc
    movs r11, r0
    beq @L021f1fb0
    mov r0, r9, lsl #0x1
    ldrsh r1, [r8, r0]
    add r0, sp, #0x88
    bl func_020e0434
    str r0, [sp, #0x14]
    cmp r0, #0x0
    beq @L021f1fb0
    ldr r1, [r4, #0x5d0]
    mov r0, #0x244
    mla r0, r9, r0, r1
    bl ClearPage
    ldr r2, [r4, #0x5d0]
    mov r0, #0x244
    mla r0, r9, r0, r2
    mov r1, r11
    bl SetPage
    ldr r2, [r4, #0x5d0]
    mov r0, #0x244
    mla r0, r9, r0, r2
    ldr r1, [sp, #0x14]
    bl SetPageTitle
@L021f1fb0:
    add r9, r9, #0x1
@L021f1fb4:
    cmp r9, r7
    blt @L021f1f44
    add r0, r10, #0x5000
    mov r1, #0x0
    str r1, [r0, #0x5c8]
    strb r7, [r0, #0x5d4]
    add r0, r5, #0x1800
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f21c4
@L021f1fe4:
    bne @L021f21c4
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x5000
    mov r1, #0x0
    str r1, [r0, #0x57c]
    str r1, [r0, #0x580]
    str r1, [r0, #0x5c4]
    add r0, r10, #0x7000
    strb r1, [r0, #0x7d1]
    bl func_02094a00
    mov r4, r0
    bl func_02094b40
    mov r0, r4
    mov r3, #0x0
    str r3, [sp, #0x0]
    mov r1, #0x65
    mov r2, #0x1f4
    bl func_02094b34
    mov r0, #0x8
    str r0, [r6, #0x0]
    b @L021f21c4
@L021f203c:
    cmp r0, #0x5
    bne @L021f20b8
    ldr r1, =0x44c
    add r0, r10, #0x30
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x5cc]
    mov r1, #0x7
    bl _ZN11GuideWindow10InitializeEh
    add r2, r10, #0x5000
    ldr r0, [r2, #0x5cc]
    add r1, r10, #0x30
    add r0, r0, #0x400
    ldrh r3, [r0, #0x38]
    orr r3, r3, #0x8
    strh r3, [r0, #0x38]
    ldr r0, [r2, #0x5cc]
    bl _ZN11GuideWindow16CreateAllocatorsEP13SafeAllocator
    add r1, r10, #0x5000
    ldrb r2, [r1, #0x5d4]
    ldr r0, [r1, #0x5cc]
    ldr r1, [r1, #0x5d0]
    bl _ZN11GuideWindow8SetPagesEP9GuidePagei
    add r1, r10, #0x5000
    ldr r0, [r1, #0x5cc]
    ldrb r1, [r1, #0x5d5]
    bl SetGuideUnk400
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f21c4
@L021f20b8:
    cmp r0, #0x6
    bne @L021f20f0
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5cc]
    add r0, r0, #0x400
    ldrh r0, [r0, #0x38]
    tst r0, #0x4
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    ldrne r0, [r6, #0x0]
    addne r0, r0, #0x1
    strne r0, [r6, #0x0]
    b @L021f21c4
@L021f20f0:
    cmp r0, #0x7
    bne @L021f2174
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5cc]
    bl _ZN11GuideWindow6FinishEv
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    add r1, r10, #0x5000
    mov r2, #0x0
    str r2, [r1, #0x5cc]
    str r2, [r1, #0x5d0]
    strb r2, [r1, #0x5d4]
    mov r0, r4
    strb r2, [r1, #0x5d5]
    add r1, r10, #0x7000
    strb r2, [r1, #0x7d1]
    bl func_0200fb8c
    mov r1, #0x0
    mov r2, #0xf
    bl SetMainBrightness
    bl func_02094a00
    mov r4, r0
    bl func_02094b40
    mov r0, r4
    mov r3, #0x0
    str r3, [sp, #0x0]
    mov r1, #0x65
    mov r2, #0x1f4
    bl func_02094b34
    ldr r0, [r6, #0x0]
    add r0, r0, #0x1
    str r0, [r6, #0x0]
    b @L021f21c4
@L021f2174:
    cmp r0, #0x8
    bne @L021f2198
    bl func_02094a00
    bl func_02094b4c
    cmp r0, #0x0
    ldrne r0, [r6, #0x0]
    addne r0, r0, #0x1
    strne r0, [r6, #0x0]
    b @L021f21c4
@L021f2198:
    cmp r0, #0x9
    bne @L021f21c4
    mov r0, r4
    bl func_0200fb8c
    bl IsBrightnessTransitionActive
    cmp r0, #0x0
    bne @L021f21c4
    mov r0, r6
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0x7
    b @L021f21c8
@L021f21c4:
    ldr r0, [r10, #0xeac]
@L021f21c8:
    add sp, sp, #0x32c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// The script of the titles is done
static int IsTitleScriptDone(TitleScript* script)
{
    int done1 = script->unk_60 == -1 ? 1 : 0;
    int done2 = script->unk_64 == -1 ? 1 : 0;
    if (done1 & done2)
        return 1;
    return 0;
}

// Clears a guide page
static void ClearPage(GuidePage* page)
{
    page->unk_0_0 = 0;
    page->unk_0_9 = 0;
    page->unk_0_18 = 0;
    page->unk_0_27 = 0;
    page->layout_ = 0;
    page->text_ = NULL;
    page->unk_8 = 0;
    memset(page->title_, 0, sizeof(page->title_));
    memset(page->buffer_, 0, sizeof(page->buffer_));
    page->text_ = page->buffer_;
}

// Copies a guide to a page, with its own copy of the text
static void SetPage(GuidePage* page, GuideEntry* entry)
{
    if (entry == NULL)
        return;
    GuideEntry* header = (GuideEntry*)page;
    header->unk_0 = entry->unk_0;
    header->text_ = entry->text_;
    header->unk_8 = entry->unk_8;
    page->text_ = page->buffer_;
    const char* text = entry->text_;
    if (text == NULL)
        return;
    memset(page->buffer_, 0, sizeof(page->buffer_));
    sprintf(page->buffer_ + func_020d2ff0(page->buffer_), sFormat, text);
}

static void SetPageTitle(GuidePage* page, const char* title)
{
    if (title == NULL)
        return;
    memset(page->title_, 0, sizeof(page->title_));
    sprintf(page->title_ + func_020d2ff0(page->title_), sFormat, title);
}

static void SetGuideUnk400(GuideWindow* guide, unsigned char set)
{
    if (set)
        guide->flags_ |= GUIDE_WINDOW_UNK_400;
    else
        guide->flags_ &= ~GUIDE_WINDOW_UNK_400;
}

// NONMATCHING: the C matches 95.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Registers: the compiler assigns the loop's pointers differently
#ifdef NONMATCHING
int BattleScene::End_Spells()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    BackgroundLoader::GetInstance();
    int id = end->current_;
    int inParty = func_02086ef0(func_02010828(gameState), id);
    if (end->step_ == 0)
    {
        LearnedSkill* spell = func_0209a9dc(end->spellTable_, end->skills_[id].ids_[end->skill_]);
        if (spell != NULL)
        {
            const char** name = func_02079e2c(func_020797dc(), spell->name_);
            if (name != NULL && func_0200ff1c(gameState, id) != NULL && inParty)
            {
                char text[0x80];
                sprintf(text, func_02072a68(&texts_, 0xc));
                strcat(text, func_02072a68(&texts_, 0x22));
                MessageName memberName;
                func_020e4bf4(&memberName, id);
                messages->unk_10 = &memberName;
                func_02046574(messages, 1, *name);
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
            }
        }
        end->skill_++;
        if (end->skillCounts_[id] <= end->skill_)
        {
            Party* party = func_02010828(gameState);
            PartyMemberData* data = func_02053c6c(func_0200ff1c(gameState, id));
            if (levelUps_[id].unk_28.skillPoints_ != 0)
            {
                end->next_ = 0xc;
            }
            else if (func_02086ef0(party, id) && CanLearnSkill(id) && data->unspentSkillPoints_ != 0)
            {
                end->next_ = 8;
                void* unk = func_0205ec34();
                if (func_0206dfb0(unk, (char*)unk + 0x8c, 0x119c))
                    messages->unk_19ca = 0;
            }
            else
            {
                end->next_ = 7;
                int learns = 0;
                for (int i = end->current_ + 1; i < 4; i++)
                {
                    if (end->learns_[i] != 0)
                    {
                        learns = 1;
                        break;
                    }
                }
                int drops = HasDrops();
                if (learns == 0 && drops == 0 && gold_ == 0)
                {
                    messages->unk_19ae = 0;
                    messages->unk_19ca = 0;
                    messages->unk_19af = 0;
                }
            }
        }
        else
        {
            end->next_ = -1;
        }
        end->step_++;
    }
    else if (end->step_ == 1)
    {
        if (IsMessageDone())
        {
            int next = end->next_;
            if (next >= 0)
            {
                end->Reset();
                func_ov017_021ccea4(id, &end->skills_[id], end->skillCounts_[id]);
                return next;
            }
            end->step_ = 0;
        }
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11BattleScene8HasDropsEv(); // BattleScene::HasDrops
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN9BattleEnd5ResetEv(); // BattleEnd::Reset
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int BattleScene::End_Spells()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, lr}
    sub sp, sp, #0x8c
    mov r8, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    mov r4, r0
    ldr r5, [r1, #0x0]
    bl func_020421a0
    mov r6, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldr r7, [r5, #0x18]
    mov r0, r4
    bl func_02010828
    mov r1, r7
    bl func_02086ef0
    mov r10, r0
    ldr r0, [r5, #0x0]
    cmp r0, #0x0
    bne @L021f25d0
    mov r0, #0x14
    mla r2, r7, r0, r5
    ldr r1, [r5, #0x70]
    add r0, r5, #0xf0
    add r1, r2, r1
    ldrb r1, [r1, #0x1c]
    bl func_0209a9dc
    cmp r0, #0x0
    beq @L021f248c
    ldrsh r9, [r0, #0x2]
    bl func_020797dc
    mov r1, r9
    bl func_02079e2c
    movs r9, r0
    beq @L021f248c
    mov r0, r4
    mov r1, r7
    bl func_0200ff1c
    cmp r0, #0x0
    cmpne r10, #0x0
    beq @L021f248c
    add r0, r8, #0x104
    add r0, r0, #0x5800
    mov r1, #0xc
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0xc
    bl sprintf
    add r0, r8, #0x104
    add r0, r0, #0x5800
    mov r1, #0x22
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0xc
    bl strcat
    add r0, sp, #0x0
    mov r1, r7
    bl func_020e4bf4
    add r1, sp, #0x0
    str r1, [r6, #0x10]
    ldr r2, [r9, #0x0]
    mov r0, r6
    mov r1, #0x1
    bl func_02046574
    mov r0, r6
    add r1, sp, #0xc
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x0
    add r0, r6, #0x1000
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
@L021f248c:
    ldr r1, [r5, #0x70]
    add r0, r5, r7
    add r1, r1, #0x1
    str r1, [r5, #0x70]
    ldrb r0, [r0, #0x6c]
    cmp r0, r1
    bgt @L021f25b8
    mov r0, r4
    bl func_02010828
    mov r9, r0
    mov r0, r4
    mov r1, r7
    bl func_0200ff1c
    bl func_02053c6c
    mov r1, #0x54
    mla r1, r7, r1, r8
    add r1, r1, #0x5700
    ldrh r1, [r1, #0x9c]
    mov r4, r0
    mov r0, r1, lsl #0x10
    movs r0, r0, lsr #0x17
    movne r0, #0xc
    strneb r0, [r5, #0xe5]
    bne @L021f25c0
    mov r0, r9
    mov r1, r7
    bl func_02086ef0
    cmp r0, #0x0
    beq @L021f2548
    mov r0, r7
    bl CanLearnSkill
    cmp r0, #0x0
    addne r0, r4, #0x500
    ldrneh r0, [r0, #0x64]
    cmpne r0, #0x0
    beq @L021f2548
    mov r0, #0x8
    strb r0, [r5, #0xe5]
    bl func_0205ec34
    ldr r2, =0x119c
    add r1, r0, #0x8c
    bl func_0206dfb0
    cmp r0, #0x0
    addne r0, r6, #0x1000
    movne r1, #0x0
    strneb r1, [r0, #0x9ca]
    b @L021f25c0
@L021f2548:
    mov r0, #0x7
    strb r0, [r5, #0xe5]
    ldr r0, [r5, #0x18]
    mov r4, #0x0
    add r1, r0, #0x1
    b @L021f2578
@L021f2560:
    add r0, r5, r1
    ldrb r0, [r0, #0x12]
    cmp r0, #0x0
    movne r4, #0x1
    bne @L021f2580
    add r1, r1, #0x1
@L021f2578:
    cmp r1, #0x4
    blt @L021f2560
@L021f2580:
    mov r0, r8
    bl _ZN11BattleScene8HasDropsEv
    cmp r4, #0x0
    cmpeq r0, #0x0
    addeq r0, r8, #0x5000
    ldreq r0, [r0, #0x768]
    cmpeq r0, #0x0
    bne @L021f25c0
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9ae]
    strb r1, [r0, #0x9ca]
    strb r1, [r0, #0x9af]
    b @L021f25c0
@L021f25b8:
    mvn r0, #0x0
    strb r0, [r5, #0xe5]
@L021f25c0:
    ldr r0, [r5, #0x0]
    add r0, r0, #0x1
    str r0, [r5, #0x0]
    b @L021f2624
@L021f25d0:
    cmp r0, #0x1
    bne @L021f2624
    bl IsMessageDone
    cmp r0, #0x0
    beq @L021f2624
    ldrsb r4, [r5, #0xe5]
    cmp r4, #0x0
    blt @L021f261c
    mov r0, r5
    bl _ZN9BattleEnd5ResetEv
    add r2, r5, r7
    add r1, r5, #0x1c
    mov r0, #0x14
    mla r1, r7, r0, r1
    ldrb r2, [r2, #0x6c]
    mov r0, r7
    bl func_ov017_021ccea4
    mov r0, r4
    b @L021f2628
@L021f261c:
    mov r0, #0x0
    str r0, [r5, #0x0]
@L021f2624:
    ldr r0, [r8, #0xeac]
@L021f2628:
    add sp, sp, #0x8c
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

int BattleScene::End_Gold()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    func_02046380(messages);
    func_0202ae18();
    ZoneData* zone = func_02012fe4();
    int step = end->step_;
    if (step == 0)
    {
        if (gold_ != 0)
        {
            unsigned char members[4];
            int count = func_020114ec(gameState, members);
            unsigned char alive = 0;
            unsigned char total = 0;
            for (int i = 0; i < count; i++)
            {
                PartyMember* member = (PartyMember*)gameState->GetCombatantByIndex(members[i]);
                if (member != NULL && func_020a35e0(info_, members[i]))
                {
                    total++;
                    if (!(MEMBER_FLAGS(member) & 1))
                        alive++;
                }
            }
            messages->unk_30 = total;
            messages->unk_31 = alive;
            int drops = HasDrops();
            char text[0x100];
            sprintf(text, func_02072a68(&texts_, 0x10));
            func_020465c0(messages, 0, gold_);
            int last = 0;
            if (dropCount_ == 0 && map_ != 0 && func_0201b5d8(zone->id_))
                last = 1;
            if (drops && !last)
                strcat(text, func_02072a68(&texts_, 0x22));
            func_0204500c(messages, text, 1, 0xe3);
            messages->unk_19b2 = 0;
            messages->busy_ = 1;
        }
        else
        {
            end->step_ = 2;
            return endState_;
        }
        end->step_++;
    }
    else if (step == 1)
    {
        if (IsMessageDone() || messages->busy_ == 0)
            end->step_++;
    }
    else if (step == 2)
    {
        end->Reset();
        if (dropCount_ != 0 || map_ != 0)
        {
            if (HasDrops())
                return 0xd;
            map_ = 0;
        }
        return 0xe;
    }
    return endState_;
}

int BattleScene::End_NewSkillPoints()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    int id = end->current_;
    MessageSystem* messages = func_020421a0();
    func_02046380(messages);
    if (end->step_ == 0)
    {
        char text[0x100];
        sprintf(text, func_02072a68(&texts_, 0xd));
        strcat(text, func_02072a68(&texts_, 0x22));
        func_020465c0(messages, 0, levelUps_[id].unk_28.skillPoints_);
        func_0204500c(messages, text, 1, 0xe3);
        messages->unk_19b2 = 0;
        messages->busy_ = 1;
        end->step_++;
    }
    else if (end->step_ == 1)
    {
        Party* party = func_02010828(gameState);
        int skills = 0;
        if (func_02086ef0(party, id) && CanLearnSkill(id))
        {
            skills = 1;
            void* unk = func_0205ec34();
            if (func_0206dfb0(unk, (char*)unk + 0x8c, 0x119c))
                messages->unk_19ca = 0;
        }
        int learns = 0;
        for (int i = end->current_ + 1; i < 4; i++)
        {
            if (end->learns_[i] != 0)
            {
                learns = 1;
                break;
            }
        }
        int drops = HasDrops();
        if (learns == 0 && drops == 0 && gold_ == 0)
        {
            messages->unk_19ae = 0;
            messages->unk_19ca = 0;
            messages->unk_19af = 0;
        }
        if (IsMessageDone())
        {
            end->Reset();
            return skills ? 8 : 7;
        }
    }
    return endState_;
}

// NONMATCHING: the C matches 95.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_Drops()
{
    GameState* gameState = GameState::GetInstance();
    BattleEnd* end = sEnd;
    MessageSystem* messages = func_020421a0();
    func_02046380(messages);
    char itemName[0x80];
    char itemName2[0x80];
    char text[0x200];
    char bag[0x164];
    MessageName name;
    MessageName itemArgument;
    MessageName memberName;
    unsigned char members[4];
    MonsterRecord record;
    short id;
    if (end->step_ == 0)
    {
        end->drop_++;
        int index = end->drop_;
        if (dropCount_ <= index)
            return 0xe;
        BattleDrop* drop = &drops_[index];
        int item = drops_[index].item_;
        int full = drop->full_;
        int monsterId = drop->monster_;
        signed char member = drop->member_;
        func_020114ec(gameState, members);
        GameObject* found = NULL;
        for (int i = 0; i < 4; i++)
        {
            PartyMember* partyMember = (PartyMember*)gameState->GetCombatantByIndex(members[i]);
            if (partyMember != NULL && func_020a35e0(info_, members[i]) && !(MEMBER_FLAGS(partyMember) & 1))
            {
                found = gameState->GetPartyMemberByIndex(members[i]);
                break;
            }
        }
        if (found == NULL)
            return endState_;
        MonsterEntry* monster = func_0206f4f0(info_->monsters_, monsterId);
        if (monster == NULL)
            return endState_;
        func_020e46c4(&name);
        name = GetMonsterName(name, monster);
        messages->unk_20 = &name;
        __clear(itemName, sizeof(itemName));
        __clear(itemName2, sizeof(itemName2));
        func_020e46c4(&itemArgument);
        itemArgument.text_ = itemName;
        itemArgument.unk_4 = itemName2;
        func_020dcf7c(item, &itemArgument);
        messages->unk_18 = &itemArgument;
        __clear(text, sizeof(text));
        if (member >= 0)
        {
            func_0200ff1c(gameState, member);
            sprintf(text, func_02072a68(&texts_, 0x25));
            func_020e4bf4(&memberName, member);
            messages->arguments_ = &memberName;
        }
        else
        {
            __clear(bag, sizeof(bag));
            sprintf(text, func_02072a68(&texts_, 0x11));
            func_020e4c74(&memberName, found);
            messages->unk_10 = &memberName;
            if (full == 0)
                sprintf(bag, func_02072a68(&texts_, 0x12));
            else
                sprintf(bag, func_02072a68(&texts_, 0x13));
            strcat(text, bag);
            if (end->drop_ < dropCount_ - 1)
                strcat(text, func_02072a68(&texts_, 0x22));
        }
        func_0205eaa0(data_02108760, 0x15, 0);
        func_0204500c(messages, text, 1, 0xe3);
        messages->unk_19b2 = 0;
        messages->busy_ = 1;
        if (drops_[end->drop_].kind_ != 0)
        {
            ClearRecord(&record);
            id = monster->id_;
            if (func_020ac020(0, &id, &record, 1))
            {
                switch (drops_[end->drop_].kind_)
                {
                case 1:
                {
                    unsigned int drops = record.drops1_ + 1;
                    if (drops > 99)
                        drops = 99;
                    record.drops1_ = drops;
                    break;
                }
                case 2:
                {
                    unsigned int drops = record.drops2_ + 1;
                    if (drops > 99)
                        drops = 99;
                    record.drops2_ = drops;
                    break;
                }
                }
                func_020abe84(0, &id, &record, 1);
            }
        }
        end->step_++;
    }
    else if (end->step_ == 1)
    {
        if (IsMessageDone())
            end->step_ = 0;
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11MessageNameaSERKS_(); // MessageName::operator=
    void _ZN9GameState21GetPartyMemberByIndexEi(); // GameState::GetPartyMemberByIndex
}

asm int BattleScene::End_Drops()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x4b0
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, =sEnd
    mov r4, r0
    ldr r5, [r1, #0x0]
    bl func_020421a0
    mov r6, r0
    bl func_02046380
    ldr r0, [r5, #0x0]
    cmp r0, #0x0
    bne @L021f2e40
    ldrsb r1, [r5, #0xe4]
    add r0, r10, #0x5000
    add r1, r1, #0x1
    strb r1, [r5, #0xe4]
    ldrsb r1, [r5, #0xe4]
    ldrb r0, [r0, #0x900]
    cmp r0, r1
    movle r0, #0xe
    ble @L021f2e5c
    mov r0, #0x6
    mul r2, r1, r0
    add r0, r10, #0x8d0
    add r3, r0, #0x5000
    add r7, r3, r2
    ldrh r8, [r7, #0x2]
    ldrh r2, [r3, r2]
    add r1, sp, #0x18
    mov r9, r8, lsl #0x11
    mov r8, r8, lsl #0x10
    mov r8, r8, lsr #0x1f
    mov r0, r4
    mov r11, r9, lsr #0x11
    str r8, [sp, #0x4]
    str r2, [sp, #0x8]
    ldrsb r7, [r7, #0x5]
    bl func_020114ec
    mov r8, #0x0
    mov r9, r8
    b @L021f2b54
@L021f2af0:
    add r0, sp, #0x18
    ldrb r1, [r0, r9]
    mov r0, r4
    bl _ZN9GameState19GetCombatantByIndexEi
    str r0, [sp, #0xc]
    cmp r0, #0x0
    beq @L021f2b50
    add r0, sp, #0x18
    ldrb r1, [r0, r9]
    ldr r0, [r10, #0x2a0]
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f2b50
    ldr r0, [sp, #0xc]
    ldr r0, [r0, #0x130]
    ldr r0, [r0, #0x0]
    tst r0, #0x1
    bne @L021f2b50
    add r0, sp, #0x18
    ldrb r1, [r0, r9]
    mov r0, r4
    bl _ZN9GameState21GetPartyMemberByIndexEi
    mov r8, r0
    b @L021f2b5c
@L021f2b50:
    add r9, r9, #0x1
@L021f2b54:
    cmp r9, #0x4
    blt @L021f2af0
@L021f2b5c:
    cmp r8, #0x0
    ldreq r0, [r10, #0xeac]
    beq @L021f2e5c
    ldr r0, [r10, #0x2a0]
    mov r1, r11, lsl #0x10
    add r0, r0, #0x278
    add r0, r0, #0x400
    mov r1, r1, asr #0x10
    bl func_0206f4f0
    movs r9, r0
    ldreq r0, [r10, #0xeac]
    beq @L021f2e5c
    add r0, sp, #0x40
    bl func_020e46c4
    str r9, [sp, #0x0]
    add r1, sp, #0x40
    add r0, sp, #0x1c
    ldmia r1, {r1, r2, r3}
    bl GetMonsterName
    add r0, sp, #0x40
    add r1, sp, #0x1c
    bl _ZN11MessageNameaSERKS_
    add r1, sp, #0x40
    str r1, [r6, #0x20]
    add r0, sp, #0x430
    mov r1, #0x80
    bl __clear
    add r0, sp, #0x3b0
    mov r1, #0x80
    bl __clear
    add r0, sp, #0x34
    bl func_020e46c4
    ldr r0, [sp, #0x8]
    add r1, sp, #0x3b0
    mov r0, r0, lsl #0x10
    add r2, sp, #0x430
    str r1, [sp, #0x38]
    mov r0, r0, asr #0x10
    add r1, sp, #0x34
    str r2, [sp, #0x34]
    bl func_020dcf7c
    add r1, sp, #0x34
    str r1, [r6, #0x18]
    add r0, sp, #0x1b0
    mov r1, #0x200
    bl __clear
    cmp r7, #0x0
    blt @L021f2c5c
    mov r0, r4
    mov r1, r7
    bl func_0200ff1c
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x25
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x1b0
    bl sprintf
    add r0, sp, #0x28
    mov r1, r7
    bl func_020e4bf4
    add r0, sp, #0x28
    str r0, [r6, #0x0]
    b @L021f2d18
@L021f2c5c:
    add r0, sp, #0x4c
    mov r1, #0x164
    bl __clear
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x11
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x1b0
    bl sprintf
    add r0, sp, #0x28
    mov r1, r8
    bl func_020e4c74
    ldr r0, [sp, #0x4]
    add r1, sp, #0x28
    cmp r0, #0x0
    add r0, r10, #0x104
    str r1, [r6, #0x10]
    add r0, r0, #0x5800
    bne @L021f2cc4
    mov r1, #0x12
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
    b @L021f2cd8
@L021f2cc4:
    mov r1, #0x13
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x4c
    bl sprintf
@L021f2cd8:
    add r0, sp, #0x1b0
    add r1, sp, #0x4c
    bl strcat
    add r0, r10, #0x5000
    ldrb r0, [r0, #0x900]
    ldrsb r1, [r5, #0xe4]
    sub r0, r0, #0x1
    cmp r1, r0
    bge @L021f2d18
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x22
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x1b0
    bl strcat
@L021f2d18:
    ldr r0, =data_02108760
    mov r1, #0x15
    mov r2, #0x0
    bl func_0205eaa0
    add r1, sp, #0x1b0
    mov r0, r6
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r6, #0x998]
    ldrsb r1, [r5, #0xe4]
    mov r0, #0x6
    mla r0, r1, r0, r10
    add r0, r0, #0x5000
    ldrb r0, [r0, #0x8d4]
    cmp r0, #0x0
    beq @L021f2e30
    add r0, sp, #0x14
    bl ClearRecord
    ldrh r4, [r9, #0x10]
    add r1, sp, #0x10
    add r2, sp, #0x14
    mov r0, #0x0
    mov r3, #0x1
    strh r4, [sp, #0x10]
    bl func_020ac020
    cmp r0, #0x0
    beq @L021f2e30
    ldrsb r1, [r5, #0xe4]
    mov r0, #0x6
    mla r0, r1, r0, r10
    add r0, r0, #0x5000
    ldrb r0, [r0, #0x8d4]
    cmp r0, #0x1
    beq @L021f2dc0
    cmp r0, #0x2
    beq @L021f2df0
    b @L021f2e1c
@L021f2dc0:
    ldr r0, [sp, #0x14]
    ldr r1, [sp, #0x14]
    mov r0, r0, lsl #0xe
    mov r0, r0, lsr #0x19
    add r0, r0, #0x1
    cmp r0, #0x63
    movhi r0, #0x63
    mov r0, r0, lsl #0x19
    bic r1, r1, #0x3f800
    orr r0, r1, r0, lsr #0xe
    str r0, [sp, #0x14]
    b @L021f2e1c
@L021f2df0:
    ldr r0, [sp, #0x14]
    ldr r1, [sp, #0x14]
    mov r0, r0, lsl #0x7
    mov r0, r0, lsr #0x19
    add r0, r0, #0x1
    cmp r0, #0x63
    movhi r0, #0x63
    mov r0, r0, lsl #0x19
    bic r1, r1, #0x1fc0000
    orr r0, r1, r0, lsr #0x7
    str r0, [sp, #0x14]
@L021f2e1c:
    add r1, sp, #0x10
    add r2, sp, #0x14
    mov r0, #0x0
    mov r3, #0x1
    bl func_020abe84
@L021f2e30:
    ldr r0, [r5, #0x0]
    add r0, r0, #0x1
    str r0, [r5, #0x0]
    b @L021f2e58
@L021f2e40:
    cmp r0, #0x1
    bne @L021f2e58
    bl IsMessageDone
    cmp r0, #0x0
    movne r0, #0x0
    strne r0, [r5, #0x0]
@L021f2e58:
    ldr r0, [r10, #0xeac]
@L021f2e5c:
    add sp, sp, #0x4b0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// The camera's state that func_0202ed64 returns (0x54 bytes)
struct CameraState
{
    int unk_0[0x15];
};


// NONMATCHING: the C matches 87.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int BattleScene::End_Quest()
{
    BattleEnd* end = sEnd;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    QuestList* quests = func_02094d6c();
    MessageSystem* messages = func_020421a0();
    if (end->step_ == 0)
    {
        if (resultWindow_ != NULL)
        {
            resultWindow_->Close();
            resultWindow_->Finish();
            resultWindow_ = NULL;
        }
        questScript_ = NULL;
        questMessages_ = NULL;
        questLoaded_ = 0;
        questBattle_ = -1;
        allocator_.Reset();
        if (data_->quest_ > 0)
        {
            short type = 0;
            short item = 0;
            short monster = 0;
            func_ov000_0215fa84(data_, &type, &monster, &item);
            int accepted = func_02096134(quests, data_->quest_);
            if (item != 0 && accepted)
            {
                func_02046380(messages);
                int id = 0x29;
                if (type == 0x12)
                    id = 0x2a;
                const char* text = func_02072a68(&texts_, id);
                MessageName name;
                func_020e46c4(&name);
                GameState* gameState = GameState::GetInstance();
                for (int i = 0xc0; i <= 0xc7; i++)
                {
                    GameObject* object = func_0200fea4(gameState, i);
                    if (object == NULL)
                        continue;
                    MonsterEntry* entry = *(MonsterEntry**)((char*)object + 0x144);
                    if (monster == entry->unk_8)
                    {
                        name = GetMonsterName(name, entry);
                        messages->unk_20 = &name;
                        break;
                    }
                }
                char itemName[0x80];
                __clear(itemName, sizeof(itemName));
                char itemName2[0x80];
                __clear(itemName2, sizeof(itemName2));
                MessageName itemArgument;
                func_020e46c4(&itemArgument);
                itemArgument.unk_4 = itemName2;
                itemArgument.text_ = itemName;
                func_020dcf7c(item, &itemArgument);
                messages->unk_18 = &itemArgument;
                func_0209c6d8(data_02109bf4, 0x3e);
                func_0204500c(messages, text, 1, 0xe3);
                messages->unk_19b2 = 0;
                messages->busy_ = 1;
                func_ov000_0215fa70(data_, type, 0, 0);
                end->step_ = 10;
                return endState_;
            }
        }
        if (func_0202c540(func_0202ae18()))
            return 0xf;
        if (IsPartyDead() && data_->quest_ == 0)
            return 0xf;
        int found = 0;
        QuestEntry* entries = quests->quests_;
        int count = quests->count_;
        for (int i = 0; i < count; i++)
        {
            if (entries[i].accepted_ && !entries[i].done_)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            end->Reset();
            return 0xf;
        }
        questMessages_ = (QuestMessages*)allocator_.Allocate(sizeof(QuestMessages));
        questScript_ = (QuestScript*)allocator_.Allocate(0x8a0);
        func_020d784c(questMessages_);
        questAllocator_ = (SafeAllocator*)allocator_.Allocate(sizeof(SafeAllocator));
        questAllocator_->CreateTypeA(allocator_.Allocate(sQuestHeapSize), sQuestHeapSize);
        void* music = func_02094a00();
        func_02094b40(music);
        func_02094b30(music, 0x210, 1);
        end->step_ = 1;
    }
    else if (end->step_ == 10)
    {
        if (IsMessageDone())
            end->step_ = 0;
    }
    else if (end->step_ == 11)
    {
        end->task2_ = loader->QueueLoadFileInGP2(STRING(0xf2, "data/scenario/btl_qmes.gp2"), STRING(0x10d, "btl_qmes_<LG>.bin"), NULL);
        end->step_++;
        return endState_;
    }
    else if (end->step_ == 12)
    {
        if (loader->GetTaskStatus(end->task2_))
        {
            unsigned int size;
            void* file;
            loader->GetLoadedFileByID(end->task2_, &file, &size);
            func_020d784c(questMessages_);
            QuestEntry* entries = quests->quests_;
            int count = quests->count_;
            for (int i = 0; i < count; i++)
            {
                if (entries[i].accepted_ && !entries[i].done_)
                {
                    QuestMessages* questMessages = questMessages_;
                    int id = entries[i].id_;
                    questMessages->ids_[questMessages->count_++] = id;
                }
            }
            func_020d7870(questMessages_, &allocator_, file, size, 0);
            loader->RemoveTask(end->task2_);
            end->task2_ = -1;
            end->step_ = 4;
            questLoaded_ = 1;
        }
    }
    else if (end->step_ == 1)
    {
        if (func_02094b4c(func_02094a00()))
        {
            void* icons = menu_.icons_;
            if (func_020deb08(icons) <= 0)
            {
                func_020de868(icons);
                SafeAllocator* iconAllocator = &menu_.unk_1ac8;
                iconAllocator->Reset();
                BackgroundLoader::AddLockGlobal();
                unsigned int size;
                void* file = ExtractFileFromGP2(data_020f2a38, data_020f2a30, &size);
                if (file != NULL)
                    func_020dea64(icons, iconAllocator, file, size, sIconIds, sIconCount);
                BackgroundLoader::RemoveLockGlobal();
            }
            end->step_ = 2;
        }
    }
    else if (end->step_ == 2)
    {
        QuestEntry* entries = quests->quests_;
        int count = quests->count_;
        int found = 0;
        for (short i = questBattle_ + 1; i < count; i++)
        {
            if (((!func_0202c540(func_0202ae18()) && !IsPartyDead()) || data_->quest_ == entries[i].id_) &&
                entries[i].accepted_ && !entries[i].done_)
            {
                questBattle_ = i;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            end->Reset();
            return 0xf;
        }
        char path[0x40];
        sprintf(path, STRING(0x11f, "data/scenario/quest_btl_%d.stb"), entries[questBattle_].id_ / 50 + 1);
        end->task_ = loader->QueueLoadFile(path, NULL);
        end->step_ = 3;
    }
    else if (end->step_ == 3)
    {
        if (loader->GetTaskStatus(end->task_))
        {
            unsigned int size;
            void* file = NULL;
            loader->GetLoadedFileByID(end->task_, &file, &size);
            if (file == NULL)
            {
                end->Reset();
                return 0xf;
            }
            QuestEntry* entries = quests->quests_;
            questAllocator_->Reset();
            void* copy = questAllocator_->Allocate(size);
            memcpy(copy, file, size);
            loader->RemoveTask(end->task_);
            end->task_ = -1;
            func_0209e3dc(questScript_, data_);
            func_0209fd64(questScript_, questAllocator_, copy, size);
            func_0209e46c(questScript_);
            func_0209fe10(questScript_, entries[questBattle_].id_);
            end->step_ = 4;
        }
    }
    else if (end->step_ == 4)
    {
        if (questLoaded_ == 1)
            questLoaded_ = 2;
        else
            func_0209fe18(questScript_);
        const char* text = NULL;
        int message = questScript_->message_;
        if (message > 0)
        {
            if (questLoaded_ == 2)
            {
                text = func_020d794c(questMessages_, message);
            }
            else
            {
                end->step_ = 11;
                return endState_;
            }
        }
        if (IsQuestScriptDone(questScript_) || text != NULL)
        {
        if (IsQuestScriptDone(questScript_))
        {
            QuestEntry* entries = quests->quests_;
            if (entries[questBattle_].cleared_)
                entries[questBattle_].done_ = 1;
        }
        if (text != NULL)
        {
        func_02046380(messages);
        for (int i = 0; i < 4; i++)
            func_020465c0(messages, i, questScript_->values_[i]);
        func_0204500c(messages, func_020d794c(questMessages_, questScript_->message_), 1, 0xe3);
        messages->unk_19b2 = 0;
        messages->busy_ = 1;
        if (questScript_->unk_84 > 0)
        {
            void* unk = func_ov000_02162d88(this, questScript_->unk_84);
            if (unk != NULL)
            {
                GameState* gameState = GameState::GetInstance();
                int index = 0xc0;
                for (int i = 0xc0; i <= 0xc7; i++)
                {
                    GameObject* object = func_0200fea4(gameState, i);
                    if (object != NULL && object->currentStats_ != NULL)
                    {
                        index = i;
                        break;
                    }
                }
                GameObject* object = func_0200fea4(gameState, index);
                ModifiableCombatStats* stats = object->currentStats_;
                if (object != NULL && stats != NULL)
                {
                    void* unk2 = *(void**)((char*)object + 0x13c);
                    void* unk3 = *(void**)((char*)object + 0x144);
                    func_02048614(object);
                    object->obj3D_.unknown_4_ = index;
                    func_02049c88(object, unk2);
                    func_02048850(object, unk3);
                    func_02048588(unk, object);
                    object->currentStats_ = stats;
                    object->obj3D_.SetField06(unk_ec8);
                    func_02033b88(object, 0);
                    ((unsigned char*)object)[0xc2] |= 0x20;
                    object->obj3D_.SetInheritedAlpha(0x1f);
                    object->obj3D_.MakeVisible();
                    func_02049f28(object);
                    BattleCamera* camera = func_ov000_02160f14(this);
                    func_ov000_0216d370(camera, 1, 1, 1);
                    func_ov000_0216d530(camera, index);
                    int height = object->obj3D_.GetHeight();
                    int y = FIX32_MULTIPLY(height, 0x4cc);
                    if (y < 0)
                        y = 0;
                    func_0202e5c8(camera, 0, y, 0);
                    int z = FIX32_MULTIPLY(height, 0x2333) + 0x4000;
                    int y2 = y + 0x800;
                    if (y2 < 0)
                        y2 = 0;
                    func_0202e5d8(camera, 0, y2, z);
                    func_ov000_02163b90(this, 0);
                    questObject_ = index;
                }
            }
        }
        end->step_++;
        }
        else
        {
            end->step_ = 6;
        }
        }
    }
    else if (end->step_ == 5)
    {
        int next = 0;
        if (IsMessageDone() || questFading_ != 0)
        {
            QuestScript* script = questScript_;
            if (script->unk_84 > 0 && questObject_ > 0)
            {
                if (script->unk_88 != 0)
                {
                    GameObject* object = GameState::GetInstance()->GetGameObjectByIndex(questObject_);
                    if (object != NULL)
                    {
                        int alpha = object->obj3D_.GetInheritedAlpha();
                        if (questFading_ == 0 && alpha == 0x1f)
                        {
                            object->obj3D_.TransitionInheritedAlpha(0, 500);
                            questFading_ = 1;
                        }
                        if (alpha <= 0)
                        {
                            object->obj3D_.MakeHidden();
                            func_02049f3c(object);
                            questFading_ = 0;
                            BattleCamera* camera = func_ov000_02160f14(this);
                            CameraState state = *(CameraState*)func_0202ed64();
                            func_ov000_0216d2d0(camera);
                            func_0202ed0c(camera, &state);
                            func_02048614(object);
                            questObject_ = 0;
                            next = 1;
                        }
                    }
                }
            }
            else
            {
                next = 1;
            }
        }
        if (next)
        {
            if (IsQuestScriptDone(questScript_))
            {
                end->step_++;
            }
            else
            {
                questScript_->message_ = -1;
                questScript_->unk_84 = 0;
                end->step_ = 4;
            }
        }
    }
    else if (end->step_ == 6)
    {
        int reward = questScript_->unk_8c;
        if (reward != 0)
        {
            questRewards_[questRewardCount_] = reward;
            questRewardCount_++;
        }
        end->step_ = 2;
    }
    return endState_;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN8Object3D10MakeHiddenEv(); // Object3D::MakeHidden
    void _ZN8Object3D10SetField06Et(); // Object3D::SetField06
    void _ZN8Object3D17SetInheritedAlphaEi(); // Object3D::SetInheritedAlpha
    void _ZN9GameState20GetGameObjectByIndexEi(); // GameState::GetGameObjectByIndex
    void _u32_div_f();
}

asm int BattleScene::End_Quest()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x1dc
    ldr r1, =sEnd
    mov r10, r0
    ldr r5, [r1, #0x0]
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r6, r0
    bl func_02094d6c
    mov r7, r0
    bl func_020421a0
    ldr r1, [r5, #0x0]
    mov r4, r0
    cmp r1, #0x0
    bne @L021f31a8
    add r0, r10, #0x5000
    ldr r0, [r0, #0x588]
    cmp r0, #0x0
    beq @L021f2ed0
    bl _ZN18BattleResultWindow5CloseEv
    add r0, r10, #0x5000
    ldr r0, [r0, #0x588]
    bl _ZN18BattleResultWindow6FinishEv
    add r0, r10, #0x5000
    mov r1, #0x0
    str r1, [r0, #0x588]
@L021f2ed0:
    mov r1, #0x0
    add r0, r10, #0x5000
    str r1, [r0, #0x590]
    str r1, [r0, #0x594]
    add r0, r10, #0x5500
    strh r1, [r0, #0xbc]
    sub r1, r1, #0x1
    strh r1, [r0, #0x8c]
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r10, #0x29c]
    add r0, r0, #0x8e00
    ldrsh r0, [r0, #0x4a]
    cmp r0, #0x0
    ble @L021f308c
    mov r0, #0x0
    strh r0, [sp, #0xc]
    strh r0, [sp, #0xa]
    strh r0, [sp, #0x8]
    ldr r0, [r10, #0x29c]
    add r1, sp, #0xc
    add r2, sp, #0x8
    add r3, sp, #0xa
    bl func_ov000_0215fa84
    ldr r1, [r10, #0x29c]
    mov r0, r7
    add r1, r1, #0x8e00
    ldrsh r1, [r1, #0x4a]
    bl func_02096134
    ldrsh r1, [sp, #0xa]
    cmp r1, #0x0
    cmpne r0, #0x0
    beq @L021f308c
    mov r0, r4
    bl func_02046380
    ldrsh r0, [sp, #0xc]
    mov r1, #0x29
    cmp r0, #0x12
    add r0, r10, #0x104
    moveq r1, #0x2a
    add r0, r0, #0x5800
    bl func_02072a68
    mov r6, r0
    add r0, sp, #0x7c
    bl func_020e46c4
    bl _ZN9GameState11GetInstanceEv
    mov r7, r0
    mov r8, #0xc0
    b @L021f2fec
@L021f2f94:
    mov r0, r7
    mov r1, r8
    bl func_0200fea4
    cmp r0, #0x0
    beq @L021f2fe8
    ldr r2, [r0, #0x144]
    ldrsh r1, [sp, #0x8]
    ldrsh r0, [r2, #0x8]
    cmp r1, r0
    bne @L021f2fe8
    add r1, sp, #0x7c
    str r2, [sp, #0x0]
    add r0, sp, #0x24
    ldmia r1, {r1, r2, r3}
    bl GetMonsterName
    add r0, sp, #0x7c
    add r1, sp, #0x24
    bl _ZN11MessageNameaSERKS_
    add r0, sp, #0x7c
    str r0, [r4, #0x20]
    b @L021f2ff4
@L021f2fe8:
    add r8, r8, #0x1
@L021f2fec:
    cmp r8, #0xc7
    ble @L021f2f94
@L021f2ff4:
    add r0, sp, #0x15c
    mov r1, #0x80
    bl __clear
    add r0, sp, #0xdc
    mov r1, #0x80
    bl __clear
    add r0, sp, #0x70
    bl func_020e46c4
    add r0, sp, #0xdc
    str r0, [sp, #0x74]
    add r1, sp, #0x15c
    str r1, [sp, #0x70]
    ldrsh r0, [sp, #0xa]
    add r1, sp, #0x70
    bl func_020dcf7c
    add r1, sp, #0x70
    str r1, [r4, #0x18]
    ldr r0, =data_02109bf4
    mov r1, #0x3e
    bl func_0209c6d8
    mov r1, r6
    mov r0, r4
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r2, #0x0
    add r0, r4, #0x1000
    strb r2, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r4, #0x998]
    ldrsh r1, [sp, #0xc]
    ldr r0, [r10, #0x29c]
    mov r3, r2
    bl func_ov000_0215fa70
    mov r0, #0xa
    str r0, [r5, #0x0]
    ldr r0, [r10, #0xeac]
    b @L021f3a5c
@L021f308c:
    bl func_0202ae18
    bl func_0202c540
    cmp r0, #0x0
    movne r0, #0xf
    bne @L021f3a5c
    bl IsPartyDead
    cmp r0, #0x0
    beq @L021f30c4
    ldr r0, [r10, #0x29c]
    add r0, r0, #0x8e00
    ldrsh r0, [r0, #0x4a]
    cmp r0, #0x0
    moveq r0, #0xf
    beq @L021f3a5c
@L021f30c4:
    mov r4, #0x0
    mov r6, r4
    add r3, r7, #0x4
    ldrb r2, [r7, #0x0]
    b @L021f30fc
@L021f30d8:
    ldr r0, [r3, r6, lsl #0x4]
    mov r1, r0, lsl #0xf
    movs r1, r1, lsr #0x1f
    beq @L021f30f8
    mov r0, r0, lsl #0x10
    movs r0, r0, lsr #0x1f
    moveq r4, #0x1
    beq @L021f3104
@L021f30f8:
    add r6, r6, #0x1
@L021f30fc:
    cmp r6, r2
    blt @L021f30d8
@L021f3104:
    cmp r4, #0x0
    bne @L021f311c
    mov r0, r5
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0xf
    b @L021f3a5c
@L021f311c:
    add r0, r10, #0x30
    mov r1, #0x18
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x594]
    add r0, r10, #0x30
    mov r1, #0x8a0
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x590]
    ldr r0, [r1, #0x594]
    bl func_020d784c
    add r0, r10, #0x30
    mov r1, #0x14
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, #0x5000
    str r0, [r1, #0x5c0]
    add r0, r10, #0x30
    mov r1, #0xf000
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c0]
    mov r2, #0xf000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    bl func_02094a00
    mov r4, r0
    bl func_02094b40
    mov r0, r4
    mov r1, #0x210
    mov r2, #0x1
    bl func_02094b30
    mov r0, #0x1
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f31a8:
    cmp r1, #0xa
    bne @L021f31c4
    bl IsMessageDone
    cmp r0, #0x0
    movne r0, #0x0
    strne r0, [r5, #0x0]
    b @L021f3a58
@L021f31c4:
    cmp r1, #0xb
    bne @L021f31f8
    ldr r1, =sStrings+0xf2
    ldr r2, =sStrings+0x10d
    mov r0, r6
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r5, #0x8]
    ldr r0, [r5, #0x0]
    add r0, r0, #0x1
    str r0, [r5, #0x0]
    ldr r0, [r10, #0xeac]
    b @L021f3a5c
@L021f31f8:
    cmp r1, #0xc
    bne @L021f32dc
    ldr r1, [r5, #0x8]
    mov r0, r6
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021f3a58
    ldr r1, [r5, #0x8]
    add r2, sp, #0x1c
    add r3, sp, #0x20
    mov r0, r6
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r10, #0x5000
    ldr r0, [r0, #0x594]
    bl func_020d784c
    add r1, r7, #0x4
    ldrb r0, [r7, #0x0]
    mov r2, #0x0
    add r3, r10, #0x5000
    b @L021f3288
@L021f3248:
    ldr r7, [r1, r2, lsl #0x4]
    mov r4, r7, lsl #0xf
    movs r4, r4, lsr #0x1f
    beq @L021f3284
    mov r4, r7, lsl #0x10
    movs r4, r4, lsr #0x1f
    bne @L021f3284
    ldr r8, [r3, #0x594]
    mov r4, r7, lsl #0x17
    ldrsh r7, [r8, #0x14]
    mov r9, r4, lsr #0x17
    add r4, r7, #0x1
    strh r4, [r8, #0x14]
    add r4, r8, r7, lsl #0x1
    strh r9, [r4, #0x4]
@L021f3284:
    add r2, r2, #0x1
@L021f3288:
    cmp r2, r0
    blt @L021f3248
    mov r0, #0x0
    str r0, [sp, #0x0]
    add r0, r10, #0x5000
    ldr r0, [r0, #0x594]
    ldr r2, [sp, #0x1c]
    ldr r3, [sp, #0x20]
    add r1, r10, #0x30
    bl func_020d7870
    ldr r1, [r5, #0x8]
    mov r0, r6
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r5, #0x8]
    mov r0, #0x4
    str r0, [r5, #0x0]
    add r0, r10, #0x5500
    mov r1, #0x1
    strh r1, [r0, #0xbc]
    b @L021f3a58
@L021f32dc:
    cmp r1, #0x1
    bne @L021f3370
    bl func_02094a00
    bl func_02094b4c
    cmp r0, #0x0
    beq @L021f3a58
    add r6, r10, #0x830
    add r0, r6, #0x3000
    bl func_020deb08
    cmp r0, #0x0
    bgt @L021f3364
    add r0, r6, #0x3000
    bl func_020de868
    add r4, r10, #0x228
    add r0, r4, #0x5000
    bl _ZN13SafeAllocator5ResetEv
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    ldr r0, =data_020f2a38
    ldr r1, =data_020f2a30
    ldr r0, [r0, #0x0]
    ldr r1, [r1, #0x0]
    add r2, sp, #0x18
    bl ExtractFileFromGP2
    movs r2, r0
    beq @L021f3360
    ldr r1, =sIconIds
    mov r0, #0x3
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    ldr r3, [sp, #0x18]
    add r0, r6, #0x3000
    add r1, r4, #0x5000
    bl func_020dea64
@L021f3360:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
@L021f3364:
    mov r0, #0x2
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f3370:
    cmp r1, #0x2
    bne @L021f3478
    add r0, r10, #0x5500
    ldrsh r0, [r0, #0x8c]
    add r4, r7, #0x4
    ldrb r7, [r7, #0x0]
    add r0, r0, #0x1
    mov r0, r0, lsl #0x10
    mov r9, r0, asr #0x10
    mov r8, #0x0
    b @L021f3408
@L021f339c:
    bl func_0202ae18
    bl func_0202c540
    cmp r0, #0x0
    bne @L021f33b8
    bl IsPartyDead
    cmp r0, #0x0
    beq @L021f33d4
@L021f33b8:
    ldr r0, [r10, #0x29c]
    ldr r1, [r4, r9, lsl #0x4]
    add r0, r0, #0x8e00
    ldrsh r2, [r0, #0x4a]
    mov r0, r1, lsl #0x17
    cmp r2, r0, lsr #0x17
    bne @L021f33fc
@L021f33d4:
    ldr r0, [r4, r9, lsl #0x4]
    mov r1, r0, lsl #0xf
    movs r1, r1, lsr #0x1f
    beq @L021f33fc
    mov r0, r0, lsl #0x10
    movs r0, r0, lsr #0x1f
    addeq r0, r10, #0x5500
    streqh r9, [r0, #0x8c]
    moveq r8, #0x1
    beq @L021f3410
@L021f33fc:
    add r0, r9, #0x1
    mov r0, r0, lsl #0x10
    mov r9, r0, asr #0x10
@L021f3408:
    cmp r9, r7
    blt @L021f339c
@L021f3410:
    cmp r8, #0x0
    bne @L021f3428
    mov r0, r5
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0xf
    b @L021f3a5c
@L021f3428:
    add r0, r10, #0x5500
    ldrsh r0, [r0, #0x8c]
    mov r1, #0x32
    ldr r0, [r4, r0, lsl #0x4]
    mov r0, r0, lsl #0x17
    mov r0, r0, lsr #0x17
    bl _u32_div_f
    mov r2, r0
    ldr r1, =sStrings+0x11f
    add r0, sp, #0x30
    add r2, r2, #0x1
    bl sprintf
    add r1, sp, #0x30
    mov r0, r6
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r5, #0x4]
    mov r0, #0x3
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f3478:
    cmp r1, #0x3
    bne @L021f3570
    ldr r1, [r5, #0x4]
    mov r0, r6
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021f3a58
    mov r0, #0x0
    str r0, [sp, #0x10]
    ldr r1, [r5, #0x4]
    add r2, sp, #0x10
    add r3, sp, #0x14
    mov r0, r6
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x10]
    cmp r0, #0x0
    bne @L021f34cc
    mov r0, r5
    bl _ZN9BattleEnd5ResetEv
    mov r0, #0xf
    b @L021f3a5c
@L021f34cc:
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c0]
    add r4, r7, #0x4
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x5000
    ldr r0, [r0, #0x5c0]
    ldr r1, [sp, #0x14]
    bl _ZN13SafeAllocator8AllocateEj
    ldr r1, [sp, #0x10]
    ldr r2, [sp, #0x14]
    mov r7, r0
    bl memcpy
    mov r0, r6
    ldr r1, [r5, #0x4]
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r5, #0x4]
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    ldr r1, [r10, #0x29c]
    bl func_0209e3dc
    mov r2, r7
    add r1, r10, #0x5000
    ldr r0, [r1, #0x590]
    ldr r1, [r1, #0x5c0]
    ldr r3, [sp, #0x14]
    bl func_0209fd64
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    bl func_0209e46c
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    add r1, r10, #0x5500
    ldrsh r1, [r1, #0x8c]
    ldr r1, [r4, r1, lsl #0x4]
    mov r1, r1, lsl #0x17
    mov r1, r1, lsr #0x17
    bl func_0209fe10
    mov r0, #0x4
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f3570:
    cmp r1, #0x4
    bne @L021f3898
    add r0, r10, #0x5500
    ldrsh r1, [r0, #0xbc]
    cmp r1, #0x1
    moveq r1, #0x2
    streqh r1, [r0, #0xbc]
    beq @L021f359c
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    bl func_0209fe18
@L021f359c:
    add r2, r10, #0x5000
    ldr r0, [r2, #0x590]
    mov r6, #0x0
    ldr r1, [r0, #0x6c]
    cmp r1, #0x0
    ble @L021f35ec
    add r0, r10, #0x5500
    ldrsh r0, [r0, #0xbc]
    cmp r0, #0x2
    bne @L021f35dc
    mov r1, r1, lsl #0x10
    ldr r0, [r2, #0x594]
    mov r1, r1, asr #0x10
    bl func_020d794c
    mov r6, r0
    b @L021f35ec
@L021f35dc:
    mov r0, #0xb
    str r0, [r5, #0x0]
    ldr r0, [r10, #0xeac]
    b @L021f3a5c
@L021f35ec:
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    bl IsQuestScriptDone
    cmp r0, #0x0
    cmpeq r6, #0x0
    beq @L021f3a58
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    add r7, r7, #0x4
    bl IsQuestScriptDone
    cmp r0, #0x0
    beq @L021f3638
    add r0, r10, #0x5500
    ldrsh r2, [r0, #0x8c]
    ldr r0, [r7, r2, lsl #0x4]
    mov r1, r0, lsl #0x11
    movs r1, r1, lsr #0x1f
    orrne r0, r0, #0x8000
    strne r0, [r7, r2, lsl #0x4]
@L021f3638:
    cmp r6, #0x0
    beq @L021f388c
    mov r0, r4
    bl func_02046380
    mov r7, #0x0
    add r6, r10, #0x5000
    b @L021f3670
@L021f3654:
    ldr r1, [r6, #0x590]
    mov r0, r4
    add r1, r1, r7, lsl #0x2
    ldr r2, [r1, #0x70]
    mov r1, r7
    bl func_020465c0
    add r7, r7, #0x1
@L021f3670:
    cmp r7, #0x4
    blt @L021f3654
    add r0, r10, #0x5000
    ldr r1, [r0, #0x590]
    ldr r0, [r0, #0x594]
    ldr r1, [r1, #0x6c]
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_020d794c
    mov r1, r0
    mov r0, r4
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    add r0, r4, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x1
    str r0, [r4, #0x998]
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    ldr r0, [r0, #0x84]
    cmp r0, #0x0
    ble @L021f387c
    mov r1, r0, lsl #0x10
    mov r0, r10
    mov r1, r1, lsr #0x10
    bl func_ov000_02162d88
    movs r11, r0
    beq @L021f387c
    bl _ZN9GameState11GetInstanceEv
    mov r6, #0xc0
    mov r4, r0
    mov r7, r6
    b @L021f3720
@L021f36fc:
    mov r0, r4
    mov r1, r7
    bl func_0200fea4
    cmp r0, #0x0
    ldrne r0, [r0, #0x138]
    cmpne r0, #0x0
    movne r6, r7
    bne @L021f3728
    add r7, r7, #0x1
@L021f3720:
    cmp r7, #0xc7
    ble @L021f36fc
@L021f3728:
    mov r0, r4
    mov r1, r6
    bl func_0200fea4
    movs r4, r0
    ldr r7, [r4, #0x138]
    cmpne r7, #0x0
    beq @L021f387c
    ldr r8, [r4, #0x13c]
    ldr r9, [r4, #0x144]
    bl func_02048614
    mov r0, r4
    mov r1, r8
    strh r6, [r4, #0x4]
    bl func_02049c88
    mov r1, r9
    mov r0, r4
    bl func_02048850
    mov r0, r11
    mov r1, r4
    bl func_02048588
    str r7, [r4, #0x138]
    add r1, r10, #0xe00
    ldrh r1, [r1, #0xc8]
    mov r0, r4
    bl _ZN8Object3D10SetField06Et
    mov r0, r4
    mov r1, #0x0
    bl func_02033b88
    ldrb r2, [r4, #0xc2]
    mov r0, r4
    mov r1, #0x1f
    orr r2, r2, #0x20
    strb r2, [r4, #0xc2]
    bl _ZN8Object3D17SetInheritedAlphaEi
    mov r0, r4
    bl _ZN8Object3D11MakeVisibleEv
    mov r0, r4
    bl func_02049f28
    mov r0, r10
    bl func_ov000_02160f14
    mov r1, #0x1
    mov r7, r0
    mov r2, r1
    mov r3, r1
    bl func_ov000_0216d370
    mov r0, r7
    mov r1, r6
    bl func_ov000_0216d530
    mov r0, r4
    bl _ZNK8Object3D9GetHeightEv
    ldr r1, =0x4cc
    mov r8, r0, asr #0x1f
    umull r4, r3, r0, r1
    mla r3, r8, r1, r3
    adds r1, r4, #0x800
    mov r9, r0
    mov r4, r1, lsr #0xc
    adc r0, r3, #0x0
    orrs r4, r4, r0, lsl #0x14
    mov r2, #0x0
    movmi r4, r2
    mov r1, #0x0
    mov r0, r7
    mov r2, r4
    mov r3, r1
    bl func_0202e5c8
    ldr r0, =0x2333
    mov r1, #0x0
    umull r3, r2, r9, r0
    adds r3, r3, #0x800
    mla r2, r8, r0, r2
    adc r0, r2, #0x0
    mov r3, r3, lsr #0xc
    orr r3, r3, r0, lsl #0x14
    adds r2, r4, #0x800
    movmi r2, r1
    mov r0, r7
    add r3, r3, #0x4000
    mov r1, #0x0
    bl func_0202e5d8
    mov r0, r10
    mov r1, #0x0
    bl func_ov000_02163b90
    add r0, r10, #0x5500
    strh r6, [r0, #0xba]
@L021f387c:
    ldr r0, [r5, #0x0]
    add r0, r0, #0x1
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f388c:
    mov r0, #0x6
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f3898:
    cmp r1, #0x5
    bne @L021f3a14
    mov r4, #0x0
    bl IsMessageDone
    cmp r0, #0x0
    addeq r0, r10, #0x5000
    ldreqb r0, [r0, #0x5be]
    cmpeq r0, #0x0
    beq @L021f39c4
    add r0, r10, #0x5000
    ldr r1, [r0, #0x590]
    ldr r0, [r1, #0x84]
    cmp r0, #0x0
    addgt r0, r10, #0x5500
    ldrgtsh r0, [r0, #0xba]
    cmpgt r0, #0x0
    ble @L021f39c0
    ldr r0, [r1, #0x88]
    cmp r0, #0x0
    beq @L021f39c4
    bl _ZN9GameState11GetInstanceEv
    add r1, r10, #0x5500
    ldrsh r1, [r1, #0xba]
    bl _ZN9GameState20GetGameObjectByIndexEi
    movs r6, r0
    beq @L021f39c4
    bl _ZNK8Object3D17GetInheritedAlphaEv
    add r1, r10, #0x5000
    ldrb r1, [r1, #0x5be]
    mov r7, r0
    cmp r1, #0x0
    cmpeq r7, #0x1f
    bne @L021f3938
    mov r0, r6
    mov r1, #0x0
    mov r2, #0x1f4
    bl _ZN8Object3D24TransitionInheritedAlphaEii
    add r0, r10, #0x5000
    mov r1, #0x1
    strb r1, [r0, #0x5be]
@L021f3938:
    cmp r7, #0x0
    bgt @L021f39c4
    mov r0, r6
    bl _ZN8Object3D10MakeHiddenEv
    mov r0, r6
    bl func_02049f3c
    mov r0, r10
    add r1, r10, #0x5000
    mov r2, #0x0
    strb r2, [r1, #0x5be]
    bl func_ov000_02160f14
    mov r4, r0
    bl func_0202ed64
    add r8, sp, #0x88
    mov r9, r0
    mov r7, #0x5
@L021f3978:
    ldmia r9!, {r0, r1, r2, r3}
    stmia r8!, {r0, r1, r2, r3}
    subs r7, r7, #0x1
    bne @L021f3978
    ldr r1, [r9, #0x0]
    mov r0, r4
    str r1, [r8, #0x0]
    bl func_ov000_0216d2d0
    add r1, sp, #0x88
    mov r0, r4
    bl func_0202ed0c
    mov r0, r6
    bl func_02048614
    add r0, r10, #0x5500
    mov r1, #0x0
    strh r1, [r0, #0xba]
    mov r4, #0x1
    b @L021f39c4
@L021f39c0:
    mov r4, #0x1
@L021f39c4:
    cmp r4, #0x0
    beq @L021f3a58
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    bl IsQuestScriptDone
    cmp r0, #0x0
    ldrne r0, [r5, #0x0]
    addne r0, r0, #0x1
    strne r0, [r5, #0x0]
    bne @L021f3a58
    add r0, r10, #0x5000
    ldr r1, [r0, #0x590]
    mvn r2, #0x0
    str r2, [r1, #0x6c]
    ldr r0, [r0, #0x590]
    mov r1, #0x0
    str r1, [r0, #0x84]
    mov r0, #0x4
    str r0, [r5, #0x0]
    b @L021f3a58
@L021f3a14:
    cmp r1, #0x6
    bne @L021f3a58
    add r0, r10, #0x5000
    ldr r0, [r0, #0x590]
    ldr r2, [r0, #0x8c]
    cmp r2, #0x0
    beq @L021f3a50
    add r1, r10, #0x5500
    ldrsh r0, [r1, #0xb8]
    add r0, r10, r0, lsl #0x2
    add r0, r0, #0x5000
    str r2, [r0, #0x598]
    ldrsh r0, [r1, #0xb8]
    add r0, r0, #0x1
    strh r0, [r1, #0xb8]
@L021f3a50:
    mov r0, #0x2
    str r0, [r5, #0x0]
@L021f3a58:
    ldr r0, [r10, #0xeac]
@L021f3a5c:
    add sp, sp, #0x1dc
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static int IsQuestScriptDone(QuestScript* script)
{
    if (script->unk_64 == -1 && script->unk_68 == -1)
        return 1;
    return 0;
}

int BattleScene::End_Titles()
{
    BattleEnd* end = sEnd;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int step = end->step_;
    if (step == 0)
    {
        func_02043204(func_020421a0());
        if (resultWindow_ != NULL)
        {
            SetMenuHidden(&menu_, 1);
            resultWindow_->Close();
            resultWindow_->Finish();
            resultWindow_ = NULL;
        }
        busy_ = 1;
        titles_ = NULL;
        end->task_ = loader->QueueLoadFile(STRING(0x13e, "data/scenario/title_btl.stb"), NULL);
        end->step_++;
    }
    else if (step == 1)
    {
        BackgroundLoader* loader2 = BackgroundLoader::GetInstance();
        if (loader2->GetTaskStatus(end->task_))
        {
            unsigned int size;
            void* file;
            loader2->GetLoadedFileByID(end->task_, &file, &size);
            allocator_.Reset();
            void* copy = allocator_.Allocate(size);
            memcpy(copy, file, size);
            titles_ = (TitleScript*)allocator_.Allocate(0xd0);
            func_0209fe9c(titles_);
            func_0209fee4(titles_, &allocator_, copy, size);
            loader2->RemoveTask(end->task_);
            end->task_ = -1;
            func_0209ff64(titles_, 100);
            end->step_++;
        }
    }
    else if (step == 2)
    {
        func_0209ff6c(titles_);
        if (IsTitleScriptDone(titles_))
            end->step_++;
    }
    else if (step == 3)
    {
        short* ids;
        int i;
        int count = titles_->count_;
        if (count > 0)
        {
            SafeAllocator* idAllocator = &menu_.unk_1af8;
            idAllocator->Reset();
            count = titles_->count_;
            ids = (short*)idAllocator->Allocate(count * 2);
            for (int k = 0; k < count; k++)
                ids[k] = titles_->ids_[k];
            allocator_.Reset();
            titles_ = NULL;
            titleTable_ = allocator_.Allocate(0x14);
            func_020a13c4(titleTable_);
            func_020a13e4(titleTable_, &allocator_, NULL, 0, 2);
            firstGuide_ = ((GuideWindow*)titleTable_)->SetShown(ids, count) & 1 ? 1 : 0;
            GameObject* hero = GameState::GetInstance()->GetProtagonist();
            TextTable names;
            func_020dfc2c(&names);
            func_020dfc40(&names);
            BackgroundLoader::AddLockGlobal();
            unsigned int size = 0;
            char gp2[0x40];
            __clear(gp2, sizeof(gp2));
            char inner[0x20];
            __clear(inner, sizeof(inner));
            sprintf(gp2, STRING(0xc8, "data/bin/ttlname%d.gp2"), hero->partyData_->appearance_.female_);
            sprintf(inner, STRING(0xdf, "ttlname%d_<LG>.nat"), hero->partyData_->appearance_.female_);
            void* file = ExtractFileFromGP2(gp2, inner, &size);
            if (file != NULL)
                func_020e0028(&names, &allocator_, file, size, ids, (unsigned short)count);
            BackgroundLoader::RemoveLockGlobal();
            pages_ = (GuidePage*)allocator_.Allocate(count * sizeof(GuidePage));
            for (i = 0; i < count; i++)
            {
                GuideEntry* entry = func_020a15bc(titleTable_, ids[i]);
                if (entry == NULL)
                    continue;
                const char* title = func_020e0434(&names, ids[i]);
                if (title == NULL)
                    continue;
                ClearPage(&pages_[i]);
                SetPage(&pages_[i], entry);
                SetPageTitle(&pages_[i], title);
            }
            titleTable_ = NULL;
            pageCount_ = count;
            idAllocator->Reset();
            end->step_++;
        }
        else if (count == 0)
        {
            allocator_.Reset();
            titles_ = NULL;
            busy_ = 0;
            return 0x10;
        }
    }
    else if (step == 4)
    {
        guide_ = (GuideWindow*)allocator_.Allocate(sizeof(GuideWindow));
        guide_->Initialize(2);
        guide_->CreateAllocators(&allocator_);
        guide_->SetPages(pages_, pageCount_);
        SetGuideUnk400(guide_, firstGuide_);
        end->step_++;
    }
    else if (step == 5)
    {
        if (guide_->flags_ & GUIDE_WINDOW_MESSAGE_WINDOW)
            end->step_ = step + 1;
    }
    else if (step == 6)
    {
        guide_->Finish();
        allocator_.Reset();
        guide_ = NULL;
        pages_ = NULL;
        pageCount_ = 0;
        firstGuide_ = 0;
        busy_ = 0;
        return 0x10;
    }
    return endState_;
}

int BattleScene::End_Finish()
{
    if (func_0209ca2c(data_02109bf4))
        return endState_;
    if (resultWindow_ != NULL)
    {
        resultWindow_->Finish();
        resultWindow_ = NULL;
    }
    if (func_0202b7d8(func_0202ae18()))
    {
        Party* party = func_02010828(GameState::GetInstance());
        for (int i = 0; i < party->count_; i++)
            func_ov017_021cc730(party->members_[i], 0, 0, 1);
    }
    MessageSystem* messages = func_020421a0();
    func_02043204(messages);
    func_02043124(messages);
    func_020466f4(func_020d6c00(), 0x20000);
    func_ov000_02160d80(this, 4);
    func_0209c678(data_02109bf4, 0);
    func_020a1f4c(1);
    return endState_;
}

int BattleScene::GetExperience(int member, unsigned int base)
{
    GameState* gameState = GameState::GetInstance();
    void* unk = func_0202ae18();
    PartyMember* partyMember = func_0200ff1c(gameState, member);
    if (partyMember == NULL || func_02061bd8(partyMember))
        return 0;
    if (func_02053c6c(partyMember) == NULL)
        return 0;
    float experience = earnedExperience_;
    float turns = turns_;
    float levels[4];
    __clear(levels, sizeof(levels));
    float weights[4];
    __clear(weights, sizeof(weights));
    for (int i = 0; i < 4; i++)
    {
        if (!func_020a35e0(info_, i))
            continue;
        PartyMember* other = func_0200ff1c(gameState, i);
        if (other != NULL && !func_02061bd8(other))
        {
            weights[i] = func_02053dfc(other);
            levels[i] = func_0202053c(other);
        }
    }
    float members = 1.0f;
    if (func_0202b7d8(unk))
    {
        members = 0.0f;
        for (int i = 0; i < 4; i++)
        {
            if (func_020a35e0(info_, i) && func_0202c1c0(unk, i))
                members += 1.0f;
        }
    }
    if (base != 0)
        experience = base;
    int bonus = sEnd->experience_.GetMultiplier(experience * (1.0f + (members - 1.0f) / 10.0f), 4);
    float total = weights[0] * (levels[0] + bonus) + weights[1] * (levels[1] + bonus) +
        weights[2] * (levels[2] + bonus) + weights[3] * (levels[3] + bonus);
    if (total == 0.0f)
        total = 1.0f;
    float result =
        experience * (1.0f + (members - 1.0f) / 10.0f) * ((levels[member] + bonus) * weights[member] / total);
    if (func_0208538c(partyMember->data_))
        result *= 1.05f;
    if (0.0f < result - (int)result)
        result += 1.0f;
    if (base == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (func_020a35e0(info_, i))
                func_0200ff1c(gameState, i);
        }
    }
    return result;
}

int BattleScene::HasDrops()
{
    int drops = 0;
    if (dropCount_ != 0 || map_ != 0)
    {
        GameState* gameState = GameState::GetInstance();
        void* unk = func_0202ae18();
        drops = 1;
        if (func_0202b7d8(unk))
        {
            Party* party = func_02010828(gameState);
            int found = 0;
            for (int i = 0; i < party->count_; i++)
            {
                if (memberMask_ & (1 << party->members_[i]))
                {
                    found = 1;
                    break;
                }
            }
            if (!found)
                drops = 0;
        }
    }
    return drops;
}

int BattleScene::GetGold()
{
    GameState::GetInstance();
    float gold = earnedGold_;
    float turns = turns_;
    gold *= unk_58ce / turns;
    if (0.0f < gold && gold < 1.0f)
        gold = 1.0f;
    return gold;
}

// The chances of the drops, by the rarities of the items
static const int sDropRates[] = {1, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0};

// NONMATCHING: the C matches 71.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
void BattleScene::ComputeDrops()
{
    GameState* gameState = GameState::GetInstance();
    void* drops = info_->drops_;
    func_0202ae18();
    DetailedTreasureMapData* map = func_02012fe4()->grotto_.GetDetailedData();
    unsigned short boss = 0;
    BattleInfo* info = info_;
    if (info->grotto_ != 0 || info->legacyBoss_ != 0)
    {
        if (map->mapType_ == 1)
            boss = map->regular_.bossMonsterID_;
        else if (map->mapType_ == 2)
            boss = map->legacy_.MaybeGetCurrentAlternateID();
    }
    dropCount_ = 0;
    memberMask_ = 0;
    BattleMonster* monsters = data_->monsters_;
    int count = data_->monsterCount_;
    BattleDrop* drop = drops_;
    float turns = turns_;
    for (int k = 0; k < 5; k++)
    {
        int rate = 100;
        if (k > 0)
        {
            int id = func_02011518(gameState, k - 1);
            PartyMember* member = func_0200ff1c(gameState, id);
            if (member == NULL || !func_020a35e0(info_, id) || func_02010088(member) != 0 ||
                func_02053dfc(member) / turns < 0.5f || !func_02083b00(member->data_, 0xa4))
                continue;
            rate = func_0202053c(member);
            drop->member_ = id;
        }
        else
        {
            drop->member_ = -1;
        }
        if (info_->grotto_ != 0 || info_->legacyBoss_ != 0)
        {
            int j;
            for (j = 0; j < count; j++)
            {
                if (boss == monsters[j].id_)
                    break;
            }
            BattleMonster* bossMonster = NULL;
            if (j < count)
                bossMonster = &monsters[j];
            Random* random = GetBTRandom();
            unsigned char* rates = map->treasureDropRates_;
            for (int t = 2; t >= 0; t--)
            {
                int chance = rates[t];
                if (k > 0)
                {
                    int scaled = chance * rate / 100;
                    chance = (unsigned int)chance >= 100 ? 0 : scaled;
                }
                else if (bossMonster != NULL)
                {
                    if (bossMonster->dropsFirst_ && t == 2)
                        chance = 100;
                    if (bossMonster->dropsSecond_ && t == 1)
                        chance = 100;
                }
                if (NextRandomMax(random, 100) >= chance)
                    continue;
                map->discoveredTreasures_[t] = 1;
                TreasureMapType type;
                if (GetTreasureMapTypeFromItemID(map->treasureItemIDs_[t], (unsigned char*)&type))
                {
                    if (map_ == 0)
                    {
                        map_ = 1;
                        mapItem_ = map->treasureItemIDs_[t];
                        mapKind_ = type.type_;
                        mapBoss_ = type.boss_;
                        mapLegacy_ = type.legacy_;
                    }
                    continue;
                }
                drop->item_ = map->treasureItemIDs_[t];
                drop->monster_ = boss;
                MonsterDrops* monsterDrops = func_02070fd0(drops, boss);
                if (monsterDrops != NULL)
                {
                    if (monsterDrops->item1_ == drop->item_)
                        drop->kind_ = 2;
                    else if (monsterDrops->item2_ == drop->item_)
                        drop->kind_ = 1;
                    else
                        drop->kind_ = 0;
                }
                dropCount_++;
                if (dropCount_ >= 8)
                    break;
                signed char member = drop->member_;
                drop++;
                drop->member_ = member;
            }
        }
        if (dropCount_ >= 8)
            break;
        for (int j = 0; j < count; j++)
        {
            BattleMonster* monster = &monsters[j];
            if (monster->count_ == monster->unk_9)
                continue;
            int id = monster->id_;
            MonsterDrops* monsterDrops = func_02070fd0(drops, id);
            if (monsterDrops == NULL)
                continue;
            if ((info_->grotto_ != 0 || info_->legacyBoss_ != 0) && boss == id)
                continue;
            int rarity = monsterDrops->rarity1_;
            int chance = sDropRates[rarity];
            if (chance > 0)
            {
                if (k > 0)
                {
                    chance = chance * 100 / rate;
                    if (rarity == 0)
                        chance = 0;
                }
                else if (monster->dropsFirst_)
                {
                    chance = 1;
                }
                if (chance > 0 && func_02032370(chance) == 0)
                {
                    drop->item_ = monsterDrops->item1_;
                    drop->monster_ = id;
                    drop->kind_ = 2;
                    dropCount_++;
                    if (dropCount_ >= 8)
                        break;
                    signed char member = drop->member_;
                    drop++;
                    drop->member_ = member;
                    continue;
                }
            }
            rarity = monsterDrops->rarity2_;
            chance = sDropRates[rarity];
            if (chance > 0)
            {
                if (k > 0)
                {
                    chance = chance * 100 / rate;
                    if (rarity == 0)
                        chance = 0;
                }
                else if (monster->dropsSecond_)
                {
                    chance = 1;
                }
                if (chance > 0 && func_02032370(chance) == 0)
                {
                    drop->item_ = monsterDrops->item2_;
                    drop->monster_ = id;
                    drop->kind_ = 1;
                    dropCount_++;
                    if (dropCount_ >= 8)
                        break;
                    signed char member = drop->member_;
                    drop++;
                    drop->member_ = member;
                }
            }
        }
        if (dropCount_ >= 8)
            break;
    }
    if (dropCount_ == 0 && map_ == 0)
        return;
    for (int i = 0; i < 4; i++)
    {
        if (!func_020a35e0(info_, i))
            continue;
        PartyMember* member = func_0200ff1c(gameState, i);
        if (member != NULL && !(func_02053dfc(member) / turns < 0.5f))
            memberMask_ |= 1 << i;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZNK23DetailedTreasureMapData17LegacyBossMapData26MaybeGetCurrentAlternateIDEv(); // DetailedTreasureMapData::LegacyBossMapData::MaybeGetCurrentAlternateID
    void _s32_div_f();
}

asm void BattleScene::ComputeDrops()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x50
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    ldr r1, [r10, #0x2a0]
    str r0, [sp, #0x28]
    add r0, r1, #0x284
    str r0, [sp, #0x38]
    bl func_0202ae18
    bl func_02012fe4
    add r0, r0, #0x3ec
    add r0, r0, #0x2000
    bl _ZN17ActiveGrottoClass15GetDetailedDataEv
    ldr r2, [r10, #0x2a0]
    mov r6, r0
    ldrb r1, [r2, #0x24]
    mov r0, #0x0
    str r0, [sp, #0x24]
    cmp r1, #0x0
    ldreqb r0, [r2, #0x25]
    cmpeq r0, #0x0
    beq @L021f45cc
    ldrb r0, [r6, #0x1]
    cmp r0, #0x1
    ldreqh r0, [r6, #0x54]
    streq r0, [sp, #0x24]
    beq @L021f45cc
    cmp r0, #0x2
    bne @L021f45cc
    add r0, r6, #0x4c
    bl _ZNK23DetailedTreasureMapData17LegacyBossMapData26MaybeGetCurrentAlternateIDEv
    str r0, [sp, #0x24]
@L021f45cc:
    add r0, r10, #0x5000
    mov r1, #0x0
    strb r1, [r0, #0x900]
    strb r1, [r0, #0x901]
    ldr r1, [r10, #0x29c]
    add r0, r10, #0x5800
    add r2, r1, #0x8000
    add r1, r1, #0x66
    add r1, r1, #0x8d00
    str r1, [sp, #0x8]
    ldr r1, [r2, #0xe30]
    add r3, r10, #0x8d0
    ldrh r0, [r0, #0xcc]
    add r9, r3, #0x5000
    str r1, [sp, #0x20]
    bl _ffltu
    str r0, [sp, #0x1c]
    mov r7, #0x0
    b @L021f4b60
@L021f4618:
    mov r0, #0x64
    cmp r7, #0x0
    str r0, [sp, #0x18]
    ble @L021f46bc
    sub r1, r7, #0x1
    ldr r0, [sp, #0x28]
    and r1, r1, #0xff
    bl func_02011518
    mov r5, r0
    ldr r0, [sp, #0x28]
    mov r1, r5
    bl func_0200ff1c
    movs r4, r0
    beq @L021f4b5c
    ldr r0, [r10, #0x2a0]
    and r1, r5, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f4b5c
    mov r0, r4
    bl func_02010088
    cmp r0, #0x0
    bne @L021f4b5c
    mov r0, r4
    bl func_02053dfc
    bl _ffltu
    ldr r1, [sp, #0x1c]
    bl _fdiv
    mov r1, #0x3f000000
    bl _fls
    blo @L021f4b5c
    ldr r0, [r4, #0x150]
    mov r1, #0xa4
    bl func_02083b00
    cmp r0, #0x0
    beq @L021f4b5c
    mov r0, r4
    bl func_0202053c
    str r0, [sp, #0x18]
    strb r5, [r9, #0x5]
    b @L021f46c4
@L021f46bc:
    sub r0, r0, #0x65
    strb r0, [r9, #0x5]
@L021f46c4:
    ldr r1, [r10, #0x2a0]
    ldrb r0, [r1, #0x24]
    cmp r0, #0x0
    ldreqb r0, [r1, #0x25]
    cmpeq r0, #0x0
    beq @L021f4904
    mov r0, #0x0
    mov r2, #0xa
    b @L021f4704
@L021f46e8:
    ldr r1, [sp, #0x8]
    mla r1, r0, r2, r1
    ldrh r3, [r1, #0x2]
    ldr r1, [sp, #0x24]
    cmp r1, r3
    beq @L021f4710
    add r0, r0, #0x1
@L021f4704:
    ldr r1, [sp, #0x20]
    cmp r0, r1
    blt @L021f46e8
@L021f4710:
    ldr r1, [sp, #0x20]
    mov r11, #0x0
    cmp r0, r1
    ldrlt r1, [sp, #0x8]
    movlt r2, #0xa
    mlalt r11, r0, r2, r1
    bl GetBTRandom
    str r0, [sp, #0x14]
    add r0, r6, #0x46
    str r0, [sp, #0x2c]
    add r0, r10, #0x5900
    str r0, [sp, #0x34]
    ldr r1, =0x7fff
    ldr r0, [sp, #0x24]
    mov r5, #0x2
    and r0, r0, r1
    str r0, [sp, #0x30]
    mov r0, #0x8000
    rsb r0, r0, #0x0
    str r0, [sp, #0x40]
    add r0, r10, #0x5000
    str r0, [sp, #0x44]
    add r0, r10, #0x6e00
    add r4, r10, #0x6000
    str r0, [sp, #0x3c]
    b @L021f48fc
@L021f4778:
    ldr r0, [sp, #0x2c]
    cmp r7, #0x0
    ldrb r8, [r0, r5]
    ble @L021f47a8
    ldr r0, [sp, #0x18]
    mov r1, #0x64
    mul r0, r8, r0
    bl _s32_div_f
    cmp r8, #0x64
    mov r8, r0
    movhs r8, #0x0
    b @L021f47e0
@L021f47a8:
    cmp r11, #0x0
    beq @L021f47e0
    ldrh r0, [r11, #0x0]
    mov r0, r0, lsl #0x11
    movs r0, r0, lsr #0x1f
    beq @L021f47c8
    cmp r5, #0x2
    moveq r8, #0x64
@L021f47c8:
    ldrh r0, [r11, #0x0]
    mov r0, r0, lsl #0x10
    movs r0, r0, lsr #0x1f
    beq @L021f47e0
    cmp r5, #0x1
    moveq r8, #0x64
@L021f47e0:
    ldr r0, [sp, #0x14]
    mov r1, #0x64
    bl NextRandomMax
    cmp r0, r8
    bge @L021f48f8
    add r1, r6, r5
    mov r0, #0x1
    strb r0, [r1, #0x3d]
    add r0, r6, r5, lsl #0x1
    ldrh r0, [r0, #0x40]
    add r1, sp, #0x4c
    bl GetTreasureMapTypeFromItemID
    cmp r0, #0x0
    beq @L021f485c
    ldr r0, [r4, #0xe24]
    cmp r0, #0x0
    bne @L021f48f8
    mov r0, #0x1
    str r0, [r4, #0xe24]
    add r0, r6, r5, lsl #0x1
    ldrh r1, [r0, #0x40]
    ldr r0, [sp, #0x3c]
    strh r1, [r0, #0x28]
    ldrb r0, [sp, #0x4c]
    strb r0, [r4, #0xe2a]
    ldrb r0, [sp, #0x4d]
    strb r0, [r4, #0xe2b]
    ldrh r1, [sp, #0x4e]
    ldr r0, [sp, #0x3c]
    strh r1, [r0, #0x2c]
    b @L021f48f8
@L021f485c:
    add r0, r6, r5, lsl #0x1
    ldrh r2, [r0, #0x40]
    ldr r1, [sp, #0x24]
    ldr r0, [sp, #0x38]
    strh r2, [r9, #0x0]
    ldrh r3, [r9, #0x2]
    ldr r2, [sp, #0x40]
    add r0, r0, #0x400
    and r3, r3, r2
    ldr r2, [sp, #0x30]
    orr r2, r3, r2
    strh r2, [r9, #0x2]
    bl func_02070fd0
    cmp r0, #0x0
    beq @L021f48c8
    ldrh r2, [r9, #0x0]
    ldrh r1, [r0, #0x6]
    cmp r1, r2
    moveq r0, #0x2
    streqb r0, [r9, #0x4]
    beq @L021f48c8
    ldrh r0, [r0, #0x4]
    cmp r0, r2
    moveq r0, #0x1
    streqb r0, [r9, #0x4]
    movne r0, #0x0
    strneb r0, [r9, #0x4]
@L021f48c8:
    ldr r0, [sp, #0x34]
    ldrb r0, [r0, #0x0]
    add r1, r0, #0x1
    ldr r0, [sp, #0x34]
    strb r1, [r0, #0x0]
    ldr r0, [sp, #0x44]
    ldrb r0, [r0, #0x900]
    cmp r0, #0x8
    bhs @L021f4904
    ldrsb r0, [r9, #0x5]
    add r9, r9, #0x6
    strb r0, [r9, #0x5]
@L021f48f8:
    sub r5, r5, #0x1
@L021f48fc:
    cmp r5, #0x0
    bge @L021f4778
@L021f4904:
    add r0, r10, #0x5000
    str r0, [sp, #0x48]
    ldrb r0, [r0, #0x900]
    cmp r0, #0x8
    bhs @L021f4b68
    mov r0, #0x0
    mov r4, #0x8000
    str r0, [sp, #0x10]
    add r5, r10, #0x5900
    rsb r4, r4, #0x0
    b @L021f4b3c
@L021f4930:
    ldr r1, [sp, #0x10]
    mov r0, #0xa
    mul r2, r1, r0
    ldr r0, [sp, #0x8]
    ldrh r1, [r0, r2]
    add r8, r0, r2
    ldrb r0, [r8, #0x9]
    mov r1, r1, lsl #0x12
    mov r1, r1, lsr #0x15
    cmp r1, r0
    beq @L021f4b30
    ldrh r0, [r8, #0x2]
    str r0, [sp, #0xc]
    ldr r0, [sp, #0x38]
    ldr r1, [sp, #0xc]
    add r0, r0, #0x400
    bl func_02070fd0
    movs r11, r0
    beq @L021f4b30
    ldr r1, [r10, #0x2a0]
    ldrb r0, [r1, #0x24]
    cmp r0, #0x0
    ldreqb r0, [r1, #0x25]
    cmpeq r0, #0x0
    beq @L021f49a4
    ldr r1, [sp, #0x24]
    ldr r0, [sp, #0xc]
    cmp r1, r0
    beq @L021f4b30
@L021f49a4:
    ldrb r0, [r11, #0x3]
    ldr r1, =sDropRates
    ldr r1, [r1, r0, lsl #0x2]
    str r0, [sp, #0x4]
    cmp r1, #0x0
    ble @L021f4a6c
    cmp r7, #0x0
    ble @L021f49e8
    mov r0, #0x64
    mul r0, r1, r0
    ldr r1, [sp, #0x18]
    bl _s32_div_f
    ldr r1, [sp, #0x4]
    cmp r1, #0x0
    mov r1, r0
    moveq r1, #0x0
    b @L021f49f8
@L021f49e8:
    ldrh r0, [r8, #0x0]
    mov r0, r0, lsl #0x11
    movs r0, r0, lsr #0x1f
    movne r1, #0x1
@L021f49f8:
    cmp r1, #0x0
    ble @L021f4a6c
    mov r0, r1
    bl func_02032370
    cmp r0, #0x0
    bne @L021f4a6c
    ldrh r1, [r11, #0x6]
    ldr r0, [sp, #0xc]
    strh r1, [r9, #0x0]
    ldrh r1, [r9, #0x2]
    mov r0, r0, lsl #0x10
    mov r0, r0, lsr #0x10
    and r0, r0, r4, lsr #0x11
    and r1, r1, r4
    orr r0, r1, r0
    strh r0, [r9, #0x2]
    mov r0, #0x2
    strb r0, [r9, #0x4]
    ldrb r0, [r5, #0x0]
    add r0, r0, #0x1
    strb r0, [r5, #0x0]
    ldr r0, [sp, #0x48]
    ldrb r0, [r0, #0x900]
    cmp r0, #0x8
    bhs @L021f4b4c
    ldrsb r0, [r9, #0x5]
    add r9, r9, #0x6
    strb r0, [r9, #0x5]
    b @L021f4b30
@L021f4a6c:
    ldrb r0, [r11, #0x2]
    ldr r1, =sDropRates
    ldr r1, [r1, r0, lsl #0x2]
    str r0, [sp, #0x0]
    cmp r1, #0x0
    ble @L021f4b30
    cmp r7, #0x0
    ble @L021f4ab0
    mov r0, #0x64
    mul r0, r1, r0
    ldr r1, [sp, #0x18]
    bl _s32_div_f
    ldr r1, [sp, #0x0]
    cmp r1, #0x0
    mov r1, r0
    moveq r1, #0x0
    b @L021f4ac0
@L021f4ab0:
    ldrh r0, [r8, #0x0]
    mov r0, r0, lsl #0x10
    movs r0, r0, lsr #0x1f
    movne r1, #0x1
@L021f4ac0:
    cmp r1, #0x0
    ble @L021f4b30
    mov r0, r1
    bl func_02032370
    cmp r0, #0x0
    bne @L021f4b30
    ldrh r1, [r11, #0x4]
    ldr r0, [sp, #0xc]
    strh r1, [r9, #0x0]
    ldrh r1, [r9, #0x2]
    mov r0, r0, lsl #0x10
    mov r0, r0, lsr #0x10
    and r0, r0, r4, lsr #0x11
    and r1, r1, r4
    orr r0, r1, r0
    strh r0, [r9, #0x2]
    mov r0, #0x1
    strb r0, [r9, #0x4]
    ldrb r0, [r5, #0x0]
    add r0, r0, #0x1
    strb r0, [r5, #0x0]
    ldr r0, [sp, #0x48]
    ldrb r0, [r0, #0x900]
    cmp r0, #0x8
    bhs @L021f4b4c
    ldrsb r0, [r9, #0x5]
    add r9, r9, #0x6
    strb r0, [r9, #0x5]
@L021f4b30:
    ldr r0, [sp, #0x10]
    add r0, r0, #0x1
    str r0, [sp, #0x10]
@L021f4b3c:
    ldr r1, [sp, #0x10]
    ldr r0, [sp, #0x20]
    cmp r1, r0
    blt @L021f4930
@L021f4b4c:
    add r0, r10, #0x5000
    ldrb r0, [r0, #0x900]
    cmp r0, #0x8
    bhs @L021f4b68
@L021f4b5c:
    add r7, r7, #0x1
@L021f4b60:
    cmp r7, #0x5
    blt @L021f4618
@L021f4b68:
    add r0, r10, #0x5000
    ldrb r0, [r0, #0x900]
    cmp r0, #0x0
    addeq r0, r10, #0x6000
    ldreq r0, [r0, #0xe24]
    cmpeq r0, #0x0
    beq @L021f4bf4
    add r0, r10, #0x1
    mov r4, #0x0
    add r6, r0, #0x5900
    mov r5, #0x1
    mov r7, #0x3f000000
    b @L021f4bec
@L021f4b9c:
    ldr r0, [r10, #0x2a0]
    and r1, r4, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f4be8
    ldr r0, [sp, #0x28]
    mov r1, r4
    bl func_0200ff1c
    cmp r0, #0x0
    beq @L021f4be8
    bl func_02053dfc
    bl _ffltu
    ldr r1, [sp, #0x1c]
    bl _fdiv
    mov r1, r7
    bl _fls
    ldrhssb r0, [r6, #0x0]
    orrhs r0, r0, r5, lsl r4
    strhsb r0, [r6, #0x0]
@L021f4be8:
    add r4, r4, #0x1
@L021f4bec:
    cmp r4, #0x4
    blt @L021f4b9c
@L021f4bf4:
    add sp, sp, #0x50
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

#define GAME_STATE_UNK_5728(gameState) (((unsigned char*)(gameState))[0x5728])

// NONMATCHING: the C matches 97.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
void BattleScene::UpdateDefeat()
{
    GameState* gameState = GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    GameResources* resources = func_0200fb8c(gameState);
    func_02012fe4();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* unk = func_020d6c00();
    Party* party = func_02010828(gameState);
    void* unk2 = func_0202ae18();
    unsigned int time = sTimer + gameState->GetEffectiveDeltaTime();
    int state = endState_;
    sTimer = time;
    if (state == 0)
    {
        func_0201075c(gameState, 1);
        for (int i = 0; i < 4; i++)
        {
            PartyMember* member = (PartyMember*)gameState->GetPartyMemberByIndex(i);
            if (member != NULL && !(MEMBER_FLAGS(member) & 1) && !func_020a35e0(info_, i))
                func_0201075c(gameState, 0);
        }
        if (func_02010750(gameState) && func_0202b7d8(unk2))
            func_ov017_021d2400();
        func_0209c678(data_02109bf4, 0x1e);
        func_ov000_02160fa8(this, 0x800000);
        func_020466f4(unk, 0x40000);
        endState_ = 1;
        sTimer = 0;
    }
    else if (state == 1)
    {
        if (time >= 1000 && loader->GetNumQueuedTasks() <= 0)
        {
            allocator_.Reset();
            func_020727d8(&texts_);
            BackgroundLoader::AddLockGlobal();
            unsigned int size = 0;
            void* file = ExtractFileFromGP2(STRING(0x0, "data/bin/str_bres.gp2"), STRING(0x16, "str_bres_<LG>.bin"), &size);
            if (file != NULL)
                func_020728ac(&texts_, &allocator_, file, size, 0, 0, 0);
            BackgroundLoader::RemoveLockGlobal();
            ResetMembers();
            int id = info_->unk_8;
            if (func_ov000_02163c80(this, 1))
            {
                unsigned char* unk3 = (unsigned char*)func_ov017_021a278c(resources, id);
                if (unk3 != NULL)
                {
                    func_ov017_021c9b20(id, 1);
                    func_02076ccc(unk3, 1);
                    unk3[0x17d] &= ~0x80;
                }
            }
            else
            {
                func_ov017_021c9b20(id, 0);
                func_ov017_021a23b0(resources, id);
            }
            unsigned char members[4];
            int count = func_020114ec(gameState, members);
            unsigned char total = 0;
            unsigned char alive = 0;
            for (int i = 0; i < count; i++)
            {
                PartyMember* member = (PartyMember*)gameState->GetCombatantByIndex(members[i]);
                if (member != NULL && func_020a35e0(info_, members[i]))
                {
                    total++;
                    if (!(MEMBER_FLAGS(member) & 1))
                        alive++;
                }
            }
            messages->unk_30 = total;
            messages->unk_31 = alive;
            func_ov000_0216d370(&camera_, 0, 0, 1);
            gameState->GetProtagonist();
            char text[0xb4];
            sprintf(text, func_02072a68(&texts_, 0x14));
            func_0204500c(messages, text, 1, 0xe3);
            messages->busy_ = 1;
            func_0209c6d8(data_02109bf4, 0x3a);
            endState_ = 2;
        }
    }
    else if (state == 2)
    {
        if (func_ov017_021959b4() || GAME_STATE_UNK_5728(gameState) != 0 || messages->busy_ == 0)
        {
            if (func_02086ef0(party, info_->leader_))
                func_ov017_021cbfb8(info_->unk_8, 1);
            GAME_STATE_UNK_5728(gameState) = 0;
            func_0209c7fc(data_02109bf4);
            func_02043204(messages);
            func_02043124(messages);
            func_ov000_02160d80(this, 4);
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader17GetNumQueuedTasksEv(); // BackgroundLoader::GetNumQueuedTasks
    void _ZN9GameState14GetProtagonistEv(); // GameState::GetProtagonist
    void _ZN9GameState19GetCombatantByIndexEi(); // GameState::GetCombatantByIndex
    void _ZN9GameState21GetPartyMemberByIndexEi(); // GameState::GetPartyMemberByIndex
    void _ZNK9GameState21GetEffectiveDeltaTimeEv(); // GameState::GetEffectiveDeltaTime
}

asm void BattleScene::UpdateDefeat()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xc8
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_020421a0
    mov r5, r0
    mov r0, r4
    bl func_0200fb8c
    mov r6, r0
    bl func_02012fe4
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r11, r0
    bl func_020d6c00
    mov r7, r0
    mov r0, r4
    bl func_02010828
    mov r8, r0
    bl func_0202ae18
    mov r9, r0
    mov r0, r4
    bl _ZNK9GameState21GetEffectiveDeltaTimeEv
    ldr r1, =sEnd
    ldr r2, [r10, #0xeac]
    ldr r3, [r1, #0x4]
    cmp r2, #0x0
    add r0, r3, r0
    str r0, [r1, #0x4]
    bne @L021f4d40
    mov r0, r4
    mov r1, #0x1
    bl func_0201075c
    mov r5, #0x0
    mov r6, r5
    b @L021f4cd8
@L021f4c90:
    mov r0, r4
    mov r1, r5
    bl _ZN9GameState21GetPartyMemberByIndexEi
    cmp r0, #0x0
    beq @L021f4cd4
    ldr r0, [r0, #0x130]
    ldr r0, [r0, #0x0]
    tst r0, #0x1
    bne @L021f4cd4
    ldr r0, [r10, #0x2a0]
    and r1, r5, #0xff
    bl func_020a35e0
    cmp r0, #0x0
    bne @L021f4cd4
    mov r0, r4
    mov r1, r6
    bl func_0201075c
@L021f4cd4:
    add r5, r5, #0x1
@L021f4cd8:
    cmp r5, #0x4
    blt @L021f4c90
    mov r0, r4
    bl func_02010750
    cmp r0, #0x0
    beq @L021f4d04
    mov r0, r9
    bl func_0202b7d8
    cmp r0, #0x0
    beq @L021f4d04
    bl func_ov017_021d2400
@L021f4d04:
    ldr r0, =data_02109bf4
    mov r1, #0x1e
    bl func_0209c678
    mov r0, r10
    mov r1, #0x800000
    bl func_ov000_02160fa8
    mov r0, r7
    mov r1, #0x40000
    bl func_020466f4
    mov r1, #0x1
    ldr r0, =sEnd
    mov r2, #0x0
    str r2, [r0, #0x4]
    str r1, [r10, #0xeac]
    b @L021f4fb0
@L021f4d40:
    cmp r2, #0x1
    bne @L021f4f2c
    cmp r0, #0x3e8
    blo @L021f4fb0
    mov r0, r11
    bl _ZN16BackgroundLoader17GetNumQueuedTasksEv
    cmp r0, #0x0
    bgt @L021f4fb0
    add r0, r10, #0x30
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x104
    add r0, r0, #0x5800
    bl func_020727d8
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x10]
    ldr r0, =sStrings
    ldr r1, =sStrings+0x16
    add r2, sp, #0x10
    bl ExtractFileFromGP2
    movs r2, r0
    beq @L021f4dbc
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    add r0, r10, #0x104
    ldr r3, [sp, #0x10]
    add r0, r0, #0x5800
    add r1, r10, #0x30
    bl func_020728ac
@L021f4dbc:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    bl ResetMembers
    ldr r2, [r10, #0x2a0]
    mov r0, r10
    mov r1, #0x1
    ldrh r7, [r2, #0x8]
    bl func_ov000_02163c80
    cmp r0, #0x0
    beq @L021f4e20
    mov r0, r6
    mov r1, r7
    bl func_ov017_021a278c
    movs r6, r0
    beq @L021f4e3c
    mov r0, r7, lsl #0x10
    mov r0, r0, lsr #0x10
    mov r1, #0x1
    bl func_ov017_021c9b20
    mov r0, r6
    mov r1, #0x1
    bl func_02076ccc
    ldrb r0, [r6, #0x17d]
    bic r0, r0, #0x80
    strb r0, [r6, #0x17d]
    b @L021f4e3c
@L021f4e20:
    mov r0, r7, lsl #0x10
    mov r0, r0, lsr #0x10
    mov r1, #0x0
    bl func_ov017_021c9b20
    mov r0, r6
    mov r1, r7
    bl func_ov017_021a23b0
@L021f4e3c:
    add r1, sp, #0xc
    mov r0, r4
    bl func_020114ec
    mov r7, #0x0
    mov r6, r0
    mov r8, r7
    mov r9, r7
    b @L021f4eac
@L021f4e5c:
    add r0, sp, #0xc
    ldrb r1, [r0, r9]
    mov r0, r4
    bl _ZN9GameState19GetCombatantByIndexEi
    movs r11, r0
    beq @L021f4ea8
    add r0, sp, #0xc
    ldrb r1, [r0, r9]
    ldr r0, [r10, #0x2a0]
    bl func_020a35e0
    cmp r0, #0x0
    beq @L021f4ea8
    ldr r0, [r11, #0x130]
    add r1, r7, #0x1
    ldr r0, [r0, #0x0]
    and r7, r1, #0xff
    tst r0, #0x1
    addeq r0, r8, #0x1
    andeq r8, r0, #0xff
@L021f4ea8:
    add r9, r9, #0x1
@L021f4eac:
    cmp r9, r6
    blt @L021f4e5c
    add r0, r10, #0x18
    mov r1, #0x0
    strb r7, [r5, #0x30]
    mov r2, r1
    add r0, r0, #0xc00
    mov r3, #0x1
    strb r8, [r5, #0x31]
    bl func_ov000_0216d370
    mov r0, r4
    bl _ZN9GameState14GetProtagonistEv
    add r0, r10, #0x104
    add r0, r0, #0x5800
    mov r1, #0x14
    bl func_02072a68
    mov r1, r0
    add r0, sp, #0x14
    bl sprintf
    mov r0, r5
    add r1, sp, #0x14
    mov r2, #0x1
    mov r3, #0xe3
    bl func_0204500c
    mov r0, #0x1
    str r0, [r5, #0x998]
    ldr r0, =data_02109bf4
    mov r1, #0x3a
    bl func_0209c6d8
    mov r0, #0x2
    str r0, [r10, #0xeac]
    b @L021f4fb0
@L021f4f2c:
    cmp r2, #0x2
    bne @L021f4fb0
    bl func_ov017_021959b4
    cmp r0, #0x0
    addeq r0, r4, #0x5000
    ldreqb r0, [r0, #0x728]
    cmpeq r0, #0x0
    bne @L021f4f58
    ldr r0, [r5, #0x998]
    cmp r0, #0x0
    bne @L021f4fb0
@L021f4f58:
    ldr r1, [r10, #0x2a0]
    mov r0, r8
    ldrsb r1, [r1, #0x2a]
    bl func_02086ef0
    cmp r0, #0x0
    beq @L021f4f80
    ldr r0, [r10, #0x2a0]
    mov r1, #0x1
    ldrh r0, [r0, #0x8]
    bl func_ov017_021cbfb8
@L021f4f80:
    ldr r0, =data_02109bf4
    add r1, r4, #0x5000
    mov r2, #0x0
    strb r2, [r1, #0x728]
    bl func_0209c7fc
    mov r0, r5
    bl func_02043204
    mov r0, r5
    bl func_02043124
    mov r0, r10
    mov r1, #0x4
    bl func_ov000_02160d80
@L021f4fb0:
    add sp, sp, #0xc8
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Whether the message is done, or skipped with a button or the touch screen
static int IsMessageDone()
{
    MessageSystem* messages = func_020421a0();
    int state = messages->unk_9a0;
    int skipped = 0;
    if (state == 3 || state == 0)
    {
        if (func_02012444(data_02114e30, 1) || func_02012444(data_02114e30, 2) ||
            func_02012444(data_02114e30, 0x200) || func_02012444(data_02114e30, 0x100) ||
            func_02012444(data_02114e30, 0x400) || func_02012444(data_02114e30, 0x40) ||
            func_02012444(data_02114e30, 0x80) || func_02012444(data_02114e30, 0x20) ||
            func_02012444(data_02114e30, 0x10))
            skipped = 1;
        if (*(unsigned char*)(data_02114e54 + 0x54) != 0)
            skipped = 1;
    }
    if (skipped)
    {
        func_0205eaa0(data_02108760, 1, 0);
        return 1;
    }
    if (messages->busy_ == 0 ? 1 : 0)
        return 1;
    return 0;
}

static void ResetMembers()
{
    GameState* gameState = GameState::GetInstance();
    Party* party = func_02010828(gameState);
    for (int i = 0; i < party->count_; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, party->members_[i]);
        if (member != NULL)
            func_02053ec8(member, 2);
    }
}

int BattleScene::AddExperience(BattleInfo* info, int* experience, int* gold, int legacyBoss)
{
    GameState* gameState = GameState::GetInstance();
    Party* party = func_02010828(gameState);
    func_0202ae18();
    int total = 0;
    for (int i = 0; i < 4; i++)
    {
        if (!func_020a35e0(info, i))
            continue;
        total += experience[i];
        PartyMember* member = func_0200ff1c(gameState, i);
        if (member != NULL)
        {
            PartyMemberData* data = func_02053c6c(member);
            if (data != NULL)
                data->unk_138[data->vocation_] += experience[i];
        }
    }
    *gold = GetGold();
    if (9999999 - party->gold_ < (unsigned int)*gold)
        party->gold_ = 9999999;
    else
        party->gold_ += *gold;
    if (total == 0 && *gold == 0)
        return 1;
    return 0;
}

static int CanLearnSkill(int member)
{
    PartyMember* partyMember = func_0200ff1c(GameState::GetInstance(), member);
    if (partyMember == NULL)
        return 0;
    PartyMemberData* data = func_02053c6c(partyMember);
    if (data == NULL)
        return 0;
    unsigned char vocation = partyMember->data_->vocation_;
    for (int i = 0; i < 5; i++)
    {
        if (data->skillPoints_[func_020dd11c(vocation, i)] < 100)
            return 1;
    }
    return 0;
}
