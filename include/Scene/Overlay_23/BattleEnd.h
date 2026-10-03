#pragma once

#include "Graphics/VRAMManagerState.h"
#include "Memory/SafeAllocator.h"
#include "Resource/MonsterEntry.h"
#include "Scene/Overlay_13/SkillUpScreen.h"
#include "Scene/Overlay_23/BattleResultWindow.h"
#include "Scene/Overlay_23/ExperienceTable.h"
#include "Scene/Overlay_23/GuideWindow.h"
#include "System/Matrix.h"
#include "Text/MessageName.h"
#include "Text/TextTable.h"
#include "World/Object3D.h"

struct PartyMember;

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

// A group of monsters of the same kind in a battle (0x18 bytes)
struct BattleGroup
{
    unsigned short kind_;
    // Their objects (GameState::GetGameObjectByIndex() - 0xc0)
    short objects_[4];
    unsigned char count_ : 4;
    unsigned char unk_a_4 : 4;
    char unk_b[0x18 - 0xb];
};

// The state of the battle of overlay 0 (at 0x29c in BattleScene)
struct BattleData
{
    char unk_0[0x81b0];
    unsigned char unk_81b0;
    unsigned char unk_81b1_0 : 4;
    // How many groups of monsters there are
    unsigned char groupCount_ : 2;
    unsigned char unk_81b1_6 : 2;
    char unk_81b2[2];
    BattleGroup groups_[3];
    char unk_81fc[2];
    unsigned short unk_81fe;
    char unk_8200[0x8d66 - 0x8200];
    // The monsters defeated
    BattleMonster monsters_[17];
    char unk_8e10[4];
    unsigned char unk_8e14;
    unsigned char unk_8e15;
    char unk_8e16[2];
    void* unk_8e18;
    char unk_8e1c[4];
    int unk_8e20;
    int unk_8e24;
    // The experience and the gold earned
    int experience_;
    int gold_;
    int monsterCount_;
    unsigned int unk_8e34;
    char unk_8e38[4];
    float experienceMultiplier_;
    float goldMultiplier_;
    char unk_8e44[3];
    unsigned char unk_8e47;
    char unk_8e48;
    unsigned char unk_8e49;
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
    char unk_1c[0x70 - 0x1c];
    Vector3i unk_70;
    char unk_7c[0x220 - 0x7c];
    unsigned char unk_220;
    unsigned char unk_221;
    char unk_222[0x240 - 0x222];
    // Where the monsters are
    Vector3i center_;
};

// A party member in the menus of the battle (0x448 bytes)
struct BattleMenuMember
{
    char unk_0[0x18];
    // The offset of its current panel
    signed char panel_;
    char unk_19[3];
    signed char unk_1c;
    char unk_1d[7];
    unsigned char unk_24;
    char unk_25[3];
    int unk_28;
    char unk_2c[0x4c - 0x2c];
    // Which party member it is, or -1
    int member_;
    char unk_50[0x87 - 0x50];
    unsigned char unk_87;
    char unk_88[0x448 - 0x88];

    // Its current panel
    void SetPanelUnk10(int value)
    {
        ((unsigned char*)this + panel_)[0x10] = value;
    }
};

// A name in the menus of the battle (0x18 bytes)
struct BattleMenuName
{
    char unk_0[0x18];
};

// The menus of the battle on the sub screen (at 0x3760 in BattleScene): BattleResultWindow and SkillPointMenu copy
// its window
struct BattleMenu
{
    char unk_0[0xd0];
    // The items' icons
    char icons_[0x17c - 0xd0];
    int unk_17c;
    char unk_180[0x950 - 0x180];
    int unk_950;
    unsigned char unk_954;
    char unk_955[3];
    BattleMenuMember members_[4];
    char unk_1a78[0x1ac8 - 0x1a78];
    SafeAllocator unk_1ac8;
    char unk_1adc[0x1af8 - 0x1adc];
    SafeAllocator unk_1af8;
    BattleMenuName unk_1b0c[8];
    char unk_1bcc[0x1c5c - 0x1bcc];
    BattleMenuName unk_1c5c[8];
    int unk_1d1c[8];
    int unk_1d3c[8];
    signed char unk_1d5c;
    char unk_1d5d[3];
    unsigned char unk_1d60[8];
    int unk_1d68;
    char unk_1d6c[0x1d72 - 0x1d6c];
    unsigned short flags_;

    BattleMenuMember* FindMember(int member);
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

// What overlay 0 shows of a party member in the battle (func_ov000_02162c14, 0xa bytes)
struct BattleMemberState
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned char unk_2;
    unsigned char unk_3;
    signed char unk_4;
    char unk_5;
    unsigned short unk_6;
    unsigned short unk_8;
};

// Where a party member was in the battle (0x10 bytes)
struct BattleMemberPosition
{
    Vector3i position_;
    short angle_;
    char unk_e[2];
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
    char unk_44[0x14c - 0x44];
    VRAMManagerState vram_;
    char unk_1bc[0x29c - 0x1bc];
    BattleData* data_;
    BattleInfo* info_;
    char unk_2a4[0xc18 - 0x2a4];
    BattleCamera camera_;
    char unk_e64[0xe98 - 0xe64];
    // skilltable.bin and spelltable.bin
    char skillTable_[8];
    char spellTable_[4];
    int unk_ea4;
    char unk_ea8[4];
    // The state of the end (see End_Start()), and of the victory before it (see Victory_Update())
    int endState_;
    char unk_eb0[4];
    unsigned char unk_eb4;
    unsigned char unk_eb5;
    char unk_eb6[0xec8 - 0xeb6];
    unsigned short unk_ec8;
    char unk_eca[0x3760 - 0xeca];
    BattleMenu menu_;
    char unk_54d4[4];
    unsigned char unk_54d8;
    char unk_54d9[0x54e0 - 0x54d9];
    unsigned char unk_54e0;
    unsigned char unk_54e1;
    char unk_54e2[2];
    BattleMemberState memberState_;
    char unk_54ee[2];
    // The party member whose state memberState_ is
    int stateMember_;
    int unk_54f4[4];
    char unk_5504[0x5574 - 0x5504];
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
    char unk_55d6[2];
    int unk_55d8;
    char unk_55dc[0x55f4 - 0x55dc];
    int unk_55f4;
    char unk_55f8[0x5728 - 0x55f8];
    Vector3i unk_5728[4];
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
    BattleMemberPosition positions_[4];
    // The result of the victory (see GetVictoryResult())
    unsigned char victoryResult_;
    char unk_5951[3];
    Object3D unk_5954;
    Object3D unk_5a00;
    char unk_5aac[0x5c3c - 0x5aac];
    char unk_5c3c[4][0x70];
    char unk_5dfc[0x6e24 - 0x5dfc];
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
    // The state of the battle's random numbers
    int randomHi_;
    int randomLo_;
    char unk_6e44[0x6e4a - 0x6e44];
    unsigned char timer_;
    char unk_6e4b[0x6ffc - 0x6e4b];
    char unk_6ffc[0x7710 - 0x6ffc];
    // Overlay 26's victory
    unsigned char unk_7710;
    unsigned char unk_7711;
    signed char unk_7712;
    char unk_7713;
    short unk_7714;
    short unk_7716[4];
    short unk_771e;
    short unk_7720;
    short unk_7722;
    short unk_7724;
    short unk_7726;
    signed char unk_7728;
    char unk_7729;
    short unk_772a;
    short unk_772c;
    signed char unk_772e;
    unsigned char unk_772f;
    char unk_7730[4];
    int unk_7734;
    int unk_7738;
    char unk_773c[0x7748 - 0x773c];
    unsigned char unk_7748;
    unsigned char unk_7749;
    unsigned char unk_774a;
    char unk_774b;
    SafeAllocator unk_774c;
    VRAMManagerState unk_7760;
    char unk_77d0;
    unsigned char busy_;
    char unk_77d2[0x77f0 - 0x77d2];
    // The camera of the victory: the action that it's for, or -1, and where it looks from and at
    int cameraAction_;
    Vector3i cameraTarget_;
    Vector3i cameraPosition_;

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

    // Overlay 26
    void SetVictoryCamera(int turn, int multiplayer);
    void Victory_Update();
    void ShowEndMessage();
    void UpdateSpecialEffect();
    void UpdateSpecialScene();
    void EndSpecialScene();
    void RemoveMember(int member, unsigned char update);
    void ShowMembers();
    void ResetMembersState();
};
