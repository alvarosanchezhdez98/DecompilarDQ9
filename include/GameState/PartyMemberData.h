#pragma once

#include "Resource/PartNameTable.h"

// How a party member looks (0x1c bytes), which overlay 9 sets when a character is created
struct PartyMemberAppearance
{
    // The IDs of the models of the parts: 2 is the hair style's and 3 is the face's
    short models_[10];
    // The party member is a woman (overlay 12 sets the profile's sex from it)
    unsigned char female_ : 1;
    unsigned char eyeColor_ : 3;
    unsigned char skinColor_ : 4;
    unsigned char hairColor_ : 4;
    unsigned char unk_15_4 : 4;
    short unk_16;
    // The body's scale, which the body type sets
    short width_;
    short height_;
};

// Three words of 10-bit values: the 9 stats of a party member
struct BattleResultStatWord
{
    unsigned int first_ : 10;
    unsigned int second_ : 10;
    unsigned int third_ : 10;
    unsigned int unk_30 : 2;
};

// A party member's data (0x964 bytes), which func_02053c6c returns. The battle's results copy it with its implicit
// operator=, which copies each member in turn: the anonymous structs and the arrays are the blocks of that copy
struct PartyMemberData
{
    struct
    {
        unsigned int unk_0_0 : 10;
        unsigned int unk_0_10 : 10;
        unsigned int unk_0_20 : 10;
        unsigned int unk_0_30 : 2;
        unsigned int unk_4_0 : 10;
        unsigned int unk_4_10 : 10;
        unsigned int unk_4_20 : 10;
        unsigned int unk_4_30 : 2;
        unsigned int unk_8_0 : 10;
        unsigned int unk_8_10 : 22;
        unsigned int unk_c_0 : 10;
        unsigned int unk_c_10 : 22;
        int unk_10[2];
    };
    int unk_18[9];
    struct
    {
        // The name, which overlay 9 writes when a character is created
        char name_[0x30];
        unsigned short unk_6c;
        unsigned short unk_6e;
        unsigned short unk_70;
        unsigned short unk_72;
        int unk_74[8];
    };
    int unk_94[0x29];
    // For each vocation
    int unk_138[0xd];
    // The level of each vocation
    unsigned short levels_[0xd];
    // For each vocation
    unsigned char unk_186[0xd];
    // The equipment: copies of the entries of the parts' names (overlay 9 copies them from its table)
    PartEntry equipment_[11];
    int unk_2f4[0x58];
    unsigned short unk_454[8];
    // The points spent on each skill
    unsigned char skillPoints_[0x1b];
    unsigned long long unk_480;
    PartyMemberAppearance appearance_;
    unsigned short unk_4a4[0x60];
    // The skill points that aren't spent yet
    unsigned short unspentSkillPoints_;
    unsigned short unk_566;
    short unk_568;
    unsigned char unk_56a;
    unsigned char unk_56b;
    unsigned char unk_56c;
    unsigned char unk_56d;
    unsigned char unk_56e;
    unsigned char unk_56f;
    unsigned char unk_570[0x180];
    int unk_6f0[0x58];
    // The bonus of each vocation to the stats
    BattleResultStatWord bonuses_[13][3];
    unsigned char unk_8ec[0x24];
    unsigned char unk_910[9];
    int unk_91c[6];
    unsigned char unk_934[0x18];
    int unk_94c;
    int vocation_;
    unsigned short unk_954;
    short unk_956;
    short unk_958;
    short unk_95a;
    short unk_95c;
    short unk_95e;
    unsigned short unk_960;
    unsigned short unk_962;
};

typedef char PartyMemberDataSizeCheck[sizeof(PartyMemberData) == 0x964 ? 1 : -1];
