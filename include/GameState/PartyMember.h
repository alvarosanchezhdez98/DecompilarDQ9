#pragma once

#include "GameState/PartyMemberData.h"

// A party member's name and status
struct PartyMemberStatus
{
    char name_[0x30];
    unsigned short unk_30;
    unsigned short unk_32;
    unsigned short unk_34;
    unsigned short unk_36;
    unsigned short unk_38;
};

// A party member, which func_0200ff1c returns: func_02053c6c returns their data
struct PartyMember
{
    char unk_0[0x130];
    // [2] is *likely* the HP (the member is down at 0)
    unsigned short* unk_130;
    PartyMemberStatus* status_;
    unsigned short* unk_138;
    char unk_13c[0x150 - 0x13c];
    PartyMemberData* data_;
};
