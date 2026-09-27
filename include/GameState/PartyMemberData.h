#pragma once

// A part of a party member's data
struct PartyMemberDetails
{
    char unk_0[0xe4];
    // The level of each vocation
    unsigned short levels_[0xd];
    // For each vocation
    unsigned char unk_fe[0xd];
    char unk_10b[0x3dc - 0x10b];
    // The points spent on each skill
    unsigned char skillPoints_[0x38];
    // The party member is a woman (overlay 12 sets the profile's sex from it)
    unsigned char female_ : 1;
    char unk_415[0x4dc - 0x415];
    // The skill points that aren't spent yet
    unsigned short unspentSkillPoints_;
    char unk_4de[0x8c8 - 0x4de];
};

// A party member's data, which func_02053c6c returns
struct PartyMemberData
{
    char unk_0[0x3c];
    // *Likely* the name
    char name_[0x4c];
    PartyMemberDetails details_;
    int vocation_;
};
