#pragma once

// An entry of the monsters' data (mon_data), found by the monster's ID: the name that the texts write
struct MonsterEntry
{
    const char* name_;
    // The character viewer (overlay 15) writes it after its first character
    const char* unk_4;
    short unk_8;
    short unk_a;
    // The size of the box that the character viewer (overlay 15) draws around it: its width and depth divided by 4,
    // and its height
    short boxWidth_;
    short boxHeight_;
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
