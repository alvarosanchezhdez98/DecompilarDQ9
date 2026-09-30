#pragma once

#include "Memory/SafeAllocator.h"
#include "Scene/Overlay_13/SkillUpScreen.h"
#include "Scene/Overlay_23/BattleResultWindow.h"
#include "Scene/Overlay_23/ExperienceTable.h"
#include "Scene/Overlay_23/GuideWindow.h"
#include "System/Matrix.h"
#include "Text/TextTable.h"

struct PartyMember;

// A name that the message system writes, e.g. a monster's (0xc bytes): func_020e46c4 initializes it
struct MessageName
{
    const char* text_;
    const char* unk_4;
    unsigned int unk_8_0 : 6;
    unsigned int unk_8_6 : 6;
    unsigned int unk_8_12 : 6;
    unsigned int unk_8_18 : 6;
    unsigned int unk_8_24 : 2;
    unsigned int unk_8_26 : 1;
    unsigned int unk_8_27 : 1;
    unsigned int unk_8_28 : 1;
    unsigned int unk_8_29 : 2;
    unsigned int unk_8_31 : 1;

    // The ROM has it after End_Start, where the compiler put the implicit one
    MessageName& operator=(const MessageName& other);
};

// An entry of the monsters' data (mon_data), found by the monster's ID: the name that the texts write
struct MonsterEntry
{
    const char* name_;
    char unk_4[4];
    short unk_8;
    char unk_a[6];
    // The monster's ID in the monster list
    unsigned short id_;
    char unk_12[2];
    const char* unk_14;
    unsigned int unk_18_0 : 6;
    unsigned int unk_18_6 : 6;
    unsigned int unk_18_12 : 6;
    unsigned int unk_18_18 : 6;
    unsigned int unk_18_24 : 2;
    unsigned int unk_18_26 : 1;
    unsigned int unk_18_27 : 1;
    unsigned int unk_18_28 : 1;
    unsigned int unk_18_29 : 3;
};

// A monster that the party defeated (10 bytes)
struct BattleMonster
{
    unsigned short unk_0_0 : 3;
    // How many
    unsigned short count_ : 11;
    // It drops its first or its second item for sure
    unsigned short dropsFirst_ : 1;
    unsigned short dropsSecond_ : 1;
    unsigned short id_;
    // Its record in the monster list
    short record_;
    unsigned char unk_6;
    char unk_7[2];
    unsigned char unk_9;
};

// The state of the battle of overlay 0 (at 0x29c in BattleScene)
struct BattleData
{
    char unk_0[0x81b0];
    unsigned char unk_81b0;
    unsigned char unk_81b1_0 : 6;
    unsigned char unk_81b1_6 : 2;
    char unk_81b2[0x81fe - 0x81b2];
    unsigned short unk_81fe;
    char unk_8200[0x8d66 - 0x8200];
    // The monsters defeated
    BattleMonster monsters_[17];
    char unk_8e10[5];
    unsigned char unk_8e15;
    char unk_8e16[0x8e20 - 0x8e16];
    int unk_8e20;
    char unk_8e24[4];
    // The experience and the gold earned
    int experience_;
    int gold_;
    int monsterCount_;
    unsigned int unk_8e34;
    char unk_8e38[4];
    float experienceMultiplier_;
    float goldMultiplier_;
    char unk_8e44[0x8e4a - 0x8e44];
    short quest_;
    char unk_8e4c[0x8e97 - 0x8e4c];
    unsigned char unk_8e97;
};

// What overlay 0 knows of the battle (at 0x2a0 in BattleScene)
struct BattleInfo
{
    char unk_0[8];
    unsigned short unk_8;
    char unk_a[2];
    int unk_c;
    char unk_10[0x24 - 0x10];
    // A battle in a grotto, against its boss
    unsigned char grotto_;
    unsigned char legacyBoss_;
    char unk_26[0x2a - 0x26];
    signed char leader_;
    char unk_2b[0x678 - 0x2b];
    // The monsters' entries (see MonsterEntry)
    char monsters_[0xc];
    // The monsters' items
    char drops_[4];
};

// The camera of the battle (at 0xc18 in BattleScene)
struct BattleCamera
{
    int unk_0;
    Vector3i position_;
    Vector3i target_;
};

// The menus of the battle on the sub screen (at 0x3760 in BattleScene): BattleResultWindow and SkillPointMenu copy
// its window
struct BattleMenu
{
    char unk_0[0xd0];
    // The items' icons
    char icons_[0x1ac8 - 0xd0];
    SafeAllocator unk_1ac8;
    char unk_1adc[0x1af8 - 0x1adc];
    SafeAllocator unk_1af8;
    char unk_1b0c[0x1d72 - 0x1b0c];
    unsigned short flags_;
};

// A list of the battle's messages of a quest (btl_qmes), 0x18 bytes
struct QuestMessages
{
    char unk_0[4];
    short ids_[8];
    short count_;
    char unk_16[2];
};

// The script of a quest's battle (quest_btl_%d.stb), 0x8a0 bytes
struct QuestScript
{
    char unk_0[0x64];
    int unk_64;
    int unk_68;
    int message_;
    int values_[4];
    char unk_80[4];
    int unk_84;
    int unk_88;
    int unk_8c;
};

// A script of titles (title_btl.stb or title_skl.stb), 0xd0 bytes
struct TitleScript
{
    char unk_0[0x60];
    int unk_60;
    int unk_64;
    // The titles earned
    short count_;
    short ids_[1];
};

// The spells and the skills that a party member learns (0x14 bytes)
struct BattleEndSkills
{
    unsigned char ids_[0x14];
};

// The state of the end of a battle (0x2790 bytes, allocated by BattleScene::End_Start())
struct BattleEnd
{
    int step_;
    int task_;
    int task2_;
    int task3_;
    // No member earned experience nor gold
    unsigned char nothing_;
    signed char member_;
    // The members who learn something
    unsigned char learns_[4];
    char unk_16[2];
    int current_;
    // What each member learns
    BattleEndSkills skills_[4];
    unsigned char skillCounts_[4];
    int skill_;
    // The skills learned with the skill points
    unsigned short newSkills_[55];
    unsigned char newSkillCount_;
    unsigned char newSkill_;
    signed char drop_;
    // The state after the current one, or -1
    signed char next_;
    char unk_e6[2];
    char skillTable_[8];
    char spellTable_[4];
    ExperienceTable experience_;
    char monsters_[0xc];
    BattleResultMember members_[4];
    unsigned char memberCount_;
    unsigned char ids_[4];
    unsigned char idCount_;
    char unk_278e[2];

    void Reset();
    BattleResultMember* FindMember(int id);
};

// An item that a monster drops (6 bytes)
struct BattleDrop
{
    unsigned short item_;
    unsigned short monster_ : 15;
    // The bag was full
    unsigned short full_ : 1;
    // 2: the monster's first item, 1: its second one
    unsigned char kind_;
    // Who gets it, or -1
    signed char member_;
};

// The scene of the battles (overlay 0): overlay 23 has its end, the results of a victory and the end of a defeat
struct BattleScene
{
    typedef int (BattleScene::*StateFunction)();

    // The highest level, how many icons the quests' items have, and the size of the quests' heap
    static const short sMaxLevel;
    static const int sIconCount;
    static const unsigned int sQuestHeapSize;

    char unk_0[0x30];
    SafeAllocator allocator_;
    char unk_44[0x29c - 0x44];
    BattleData* data_;
    BattleInfo* info_;
    char unk_2a4[0xc18 - 0x2a4];
    BattleCamera camera_;
    char unk_c34[0xe98 - 0xc34];
    char skillTable_[0xc];
    int unk_ea4;
    char unk_ea8[4];
    // The state of the end (see End_Start())
    int endState_;
    char unk_eb0[0xec8 - 0xeb0];
    unsigned short unk_ec8;
    char unk_eca[0x3760 - 0xeca];
    BattleMenu menu_;
    char unk_54d4[0x5574 - 0x54d4];
    SkillPointMenu* skillMenu_;
    SkillAbilityList* abilities_;
    TextList* artNames_;
    void* titleNames_;
    unsigned char unk_5584;
    char unk_5585[3];
    BattleResultWindow* resultWindow_;
    short questBattle_;
    char unk_558e[2];
    QuestScript* questScript_;
    QuestMessages* questMessages_;
    int questRewards_[8];
    short questRewardCount_;
    short questObject_;
    short questLoaded_;
    unsigned char questFading_;
    char unk_55bf;
    SafeAllocator* questAllocator_;
    TitleScript* titles_;
    void* titleTable_;
    GuideWindow* guide_;
    GuidePage* pages_;
    unsigned char pageCount_;
    unsigned char firstGuide_;
    char unk_55d6[0x5758 - 0x55d6];
    // The experience that each member earns
    int experience_[4];
    int gold_;
    unsigned char legacyBossLevelUp_;
    char unk_576d[3];
    // The stats of each member before and after leveling up
    BattleLevelUp levelUps_[4];
    unsigned int earnedExperience_;
    unsigned int earnedGold_;
    unsigned char monsterMask_;
    // What the victory's text says: one monster, several of one kind, several kinds...
    unsigned char victory_;
    unsigned short victoryMonster_;
    // The turns of the battle
    unsigned short turns_;
    unsigned short unk_58ce;
    // The items that the monsters drop
    BattleDrop drops_[8];
    unsigned char dropCount_;
    // The members who get the items
    signed char memberMask_;
    char unk_5902[2];
    // str_bres
    TextList texts_;
    void* itemNames_;
    char unk_5910[0x6e24 - 0x5910];
    // A treasure map dropped
    int map_;
    unsigned short mapItem_;
    unsigned char mapKind_;
    unsigned char mapBoss_;
    unsigned short mapLegacy_;
    unsigned char bossCount_;
    char unk_6e2f;
    unsigned short bosses_[4];
    int unk_6e38;
    char unk_6e3c[0x6e4a - 0x6e3c];
    unsigned char timer_;
    char unk_6e4b[0x6ffc - 0x6e4b];
    char unk_6ffc[0x77d1 - 0x6ffc];
    unsigned char busy_;

    void FadeBosses(int frames);
    void UpdateVictory();
    int End_Start();
    int End_Results();
    int End_Load();
    int End_Victory();
    int End_LegacyBoss();
    int End_Experience();
    int End_ShowExperience();
    int End_LevelUp();
    int End_SkillPoints();
    int End_SkillArts();
    int End_Spells();
    int End_Gold();
    int End_NewSkillPoints();
    int End_Drops();
    int End_Quest();
    int End_Titles();
    int End_Finish();
    int GetExperience(int member, unsigned int base);
    int HasDrops();
    int GetGold();
    void ComputeDrops();
    void UpdateDefeat();
    int AddExperience(BattleInfo* info, int* experience, int* gold, int legacyBoss);
};
