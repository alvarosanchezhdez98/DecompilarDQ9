#pragma once

// A table of the names of the parts of the characters' models (func_020de848 initializes it, func_020de9a4 loads it
// and func_020dedd0 returns a name)
struct PartNameTable
{
    char unk_0[0x18];
};

// The information of a model that a PartEntry points to
struct PartModelInfo
{
    int unk_0;
    unsigned int unk_4_0 : 12;
    // The number of the model's animation files (md<number><number><m/w>.nsbca and .bcfg)
    unsigned int animations_ : 8;
    unsigned int unk_4_20 : 12;
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
    unsigned int unk_8_9 : 23;
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
};
