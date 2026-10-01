#pragma once

#include "GameState/PartyMemberData.h"
#include "Graphics/TextWindow.h"
#include "Text/TextTable.h"

// The stats of a party member before or after a level up (0x14 bytes)
struct BattleResultStats
{
    int unk_0;
    unsigned short level_ : 7;
    // The skill points earned
    unsigned short skillPoints_ : 9;
    short unk_6;
    BattleResultStatWord stats_[3];
};

// What func_02082490 computes when a party member levels up (0x54 bytes)
struct BattleLevelUp
{
    BattleResultStats before_;
    BattleResultStats after_;
    BattleResultStats unk_28;
    BattleResultStats unk_3c;
    char unk_50[4];
};

// A party member as the battle's results know them (0x99c bytes)
struct BattleResultMember
{
    unsigned char id_;
    unsigned char vocation_;
    unsigned char level_;
    // The member is dead
    unsigned char dead_;
    // The experience after the battle
    int experience_;
    char name_[0x30];
    // A copy of the member's data, which func_02085fb4 and the next functions read the base stats from
    PartyMemberData data_;
};

// What BattleResultWindow copies its window and texts from
struct BattleResultWindowSource
{
    char unk_0[0xb8];
    TextTable texts_;
    char unk_d0[0x188 - 0xd0];
    TextWindow window_;
};

// The window of the results of a battle on the bottom screen (0x12c bytes): the experience that each party member
// earns, then the stats of a member that levels up
struct BattleResultWindow
{
    TextTable* texts_;
    // 0x960 bytes, the message system's
    char* text_;
    char unk_8[0x10];
    unsigned char unk_18;
    unsigned char unk_19;
    // The planes that the bottom screen showed before
    int planes_;
    TextWindow window_;
    // The experience of each member of ids_
    int values_[4];
    // The member that levels up
    int member_;
    BattleResultStats before_;
    BattleResultStats after_;
    // The lines of the text shown so far
    unsigned char lines_;
    // The members with experience
    unsigned char count_;
    // 0: loading, 1: experience, 2: level up
    unsigned char state_;
    // 0xff when loaded
    unsigned char loadStep_;
    unsigned char step_;
    signed char timer_;
    unsigned char memberCount_;
    BattleResultMember* members_;
    unsigned char ids_[4];
    unsigned char idCount_;

    void Initialize();
    void Finish();
    void Close();
    int Update();
    void Draw1();
    void Draw2();
    void SetSource(BattleResultWindowSource* source);
    void ShowExperience(const int* values);
    void ShowLevelUp(int member, const BattleResultStats* before, const BattleResultStats* after);
    void State_Load();
    void State_Experience();
    void State_LevelUp();
    void OpenWindow(char* text, short width, short height);
    void WriteExperience(char* text, unsigned char lines);
    void WriteLevelUp(char* text, unsigned char lines);
    BattleResultMember* FindMember(int id);
    void SetMembers(const unsigned char* ids, unsigned char count);
};
