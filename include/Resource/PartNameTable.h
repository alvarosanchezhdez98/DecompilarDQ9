#pragma once

// A table of the names of the parts of the characters' models (func_020de848 initializes it, func_020de9a4 loads it
// and func_020dedd0 returns a name)
struct PartNameTable
{
    char unk_0[0x18];
};

// The start of the file of a PartNameTable, and where its parts are (0x14 bytes)
struct PartNameHeader
{
    unsigned short count_;
    unsigned short count2_ : 15;
    unsigned short unk_2_15 : 1;
    int unk_4;
    unsigned int unk_8_0 : 31;
    // The entries' pointers were fixed (func_020de574)
    unsigned int fixed_ : 1;
    // After the header
    struct PartEntry* entries_;
    void* unk_10;
};

// The information of a model that a PartEntry points to
struct PartModelInfo
{
    unsigned int unk_0_0 : 7;
    unsigned int unk_0_7 : 4;
    unsigned int unk_0_11 : 16;
    // The sound that the equipment menu plays when the item is equipped (1 or 2)
    unsigned int sound_ : 2;
    unsigned int unk_0_29 : 1;
    unsigned int unk_0_30 : 2;
    unsigned int unk_4_0 : 12;
    // The number of the model's animation files (md<number><number><m/w>.nsbca and .bcfg)
    unsigned int animations_ : 8;
    unsigned int unk_4_20 : 7;
    unsigned int unk_4_27 : 1;
    unsigned int unk_4_28 : 1;
    unsigned int unk_4_29 : 1;
    unsigned int unk_4_30 : 2;
    // The item's stats (see ItemInfoWindow::DrawStats()): the last three of unk_8 and unk_c are tenths
    int unk_8_0 : 10;
    int unk_8_10 : 10;
    unsigned int unk_8_20 : 10;
    unsigned int unk_8_30 : 2;
    unsigned int unk_c_0 : 10;
    unsigned int unk_c_10 : 10;
    unsigned int unk_c_20 : 12;
    int unk_10_0 : 10;
    int unk_10_10 : 10;
    int unk_10_20 : 10;
    int unk_10_30 : 2;
    int unk_14_0 : 10;
    int unk_14_10 : 10;
    int unk_14_20 : 10;
    int unk_14_30 : 2;
    // The item's bonuses (overlay 23's commands add them up)
    int unk_18_0 : 10;
    int unk_18_10 : 10;
    int unk_18_20 : 10;
    int unk_18_30 : 2;
    int unk_1c_0 : 10;
    int unk_1c_10 : 10;
    int unk_1c_20 : 10;
    int unk_1c_30 : 2;
};

// An entry of a PartNameTable, for an item or a part of a character's look (func_020dedd0 returns it)
struct PartEntry
{
    PartModelInfo* model_;
    int unk_4;
    // The category of an item
    unsigned int category_ : 4;
    // 6 for the items that the character holds with the arms (arm2R and arm2L)
    unsigned int type_ : 5;
    // The stars of its rank (5 for the rarest ones, which sparkle)
    unsigned int rank_ : 3;
    unsigned int unk_8_12 : 6;
    // The item can't be removed once it's equipped
    unsigned int cursed_ : 1;
    unsigned int unk_8_19 : 13;
    unsigned int unk_c_0 : 12;
    // The flag that tells whether the player has the item (overlay 23's ItemSortList checks it)
    unsigned int flag_ : 11;
    unsigned int unk_c_23 : 9;
    unsigned int unk_10_0 : 20;
    // The letter of its model files (d_<letter><number>...)
    unsigned int letter_ : 8;
    unsigned int unk_10_28 : 4;
    int unk_14;
    // 1000 when the model file's number depends on unk_4e2 of the party member's data
    short unk_18;
    // The price, *likely*: overlay 23 multiplies it by a random factor for the downloaded files' sales
    unsigned short price_;
    char unk_1c[0x20 - 0x1c];
};
