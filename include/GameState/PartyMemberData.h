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

// A part of a party member's data
struct PartyMemberDetails
{
    char unk_0[0xb0];
    // For each vocation
    int unk_b0[0xd];
    // The level of each vocation
    unsigned short levels_[0xd];
    // For each vocation
    unsigned char unk_fe[0xd];
    char unk_10b;
    // The equipment: copies of the entries of the parts' names (overlay 9 copies them from its table)
    PartEntry equipment_[11];
    char unk_26c[0x3dc - 0x26c];
    // The points spent on each skill
    unsigned char skillPoints_[0x24];
    PartyMemberAppearance appearance_;
    char unk_41c[0x4dc - 0x41c];
    // The skill points that aren't spent yet
    unsigned short unspentSkillPoints_;
    char unk_4de[2];
    short unk_4e0;
    unsigned char unk_4e2;
    char unk_4e3[0x8c8 - 0x4e3];
};

// A party member's data, which func_02053c6c returns
struct PartyMemberData
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
    char unk_10[0x3c - 0x10];
    // The name, which overlay 9 writes when a character is created
    char name_[0x30];
    unsigned short unk_6c;
    unsigned short unk_6e;
    unsigned short unk_70;
    unsigned short unk_72;
    char unk_74[0x88 - 0x74];
    PartyMemberDetails details_;
    int vocation_;
};
