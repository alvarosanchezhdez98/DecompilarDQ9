#pragma once

// A time played, up to 9999:59:59
struct PlayTime
{
    unsigned short hours_;
    unsigned char minutes_;
    unsigned char seconds_;
};

// The records of the game (0xb0 bytes, at 0x7540 in GameState): the play time and the counts that the scripts of the
// menus show. func_020ac4c0 copies them and func_020ac494 writes them back. What each field counts isn't known yet
struct PlayRecords
{
    PlayTime playTime_;
    PlayTime unk_4;
    unsigned int unk_8_0 : 24;
    unsigned int unk_8_24 : 8;
    unsigned int unk_c_0 : 7;
    unsigned int unk_c_7 : 7;
    unsigned int unk_c_14 : 14;
    unsigned int unk_c_28 : 4;
    unsigned int unk_10_0 : 9;
    unsigned int unk_10_9 : 14;
    unsigned int unk_10_23 : 9;
    unsigned int unk_14;
    unsigned int unk_18_0 : 9;
    unsigned int unk_18_9 : 7;
    unsigned int unk_18_16 : 4;
    unsigned int unk_18_20 : 12;
    unsigned int unk_1c_0 : 16;
    unsigned int unk_1c_16 : 16;
    unsigned int unk_20_0 : 16;
    unsigned int unk_20_16 : 16;
    unsigned int unk_24_0 : 16;
    unsigned int unk_24_16 : 16;
    unsigned int unk_28_0 : 12;
    unsigned int unk_28_12 : 10;
    unsigned int unk_28_22 : 10;
    unsigned int unk_2c_0 : 24;
    unsigned int unk_2c_24 : 8;
    unsigned int unk_30_0 : 24;
    unsigned int unk_30_24 : 8;
    unsigned int unk_34_0 : 24;
    unsigned int unk_34_24 : 8;
    unsigned int unk_38_0 : 24;
    unsigned int unk_38_24 : 8;
    unsigned int unk_3c_0 : 24;
    unsigned int unk_3c_24 : 8;
    unsigned int unk_40_0 : 24;
    unsigned int unk_40_24 : 8;
    unsigned int unk_44;
    unsigned int unk_48;
    // Flags, by their number
    unsigned int flags_[7];
    PlayTime unk_68;
    PlayTime unk_6c;
    unsigned int unk_70_0 : 16;
    unsigned int unk_70_16 : 16;
    unsigned int unk_74_0 : 16;
    unsigned int unk_74_16 : 16;
    unsigned int unk_78_0 : 16;
    unsigned int unk_78_16 : 16;
    unsigned int unk_7c_0 : 10;
    unsigned int unk_7c_10 : 10;
    unsigned int unk_7c_20 : 12;
    unsigned int unk_80_0 : 16;
    unsigned int unk_80_16 : 16;
    unsigned int unk_84_0 : 10;
    unsigned int unk_84_10 : 16;
    unsigned int unk_84_26 : 6;
    unsigned int unk_88_0 : 24;
    unsigned int unk_88_24 : 8;
    unsigned int unk_8c_0 : 24;
    unsigned int unk_8c_24 : 8;
    PlayTime unk_90;
    PlayTime unk_94;
    unsigned int unk_98_0 : 17;
    unsigned int unk_98_17 : 7;
    unsigned int unk_98_24 : 7;
    unsigned int unk_98_31 : 1;
    unsigned int unk_9c_0 : 17;
    unsigned int unk_9c_17 : 7;
    unsigned int unk_9c_24 : 7;
    unsigned int unk_9c_31 : 1;
    unsigned int unk_a0_0 : 9;
    unsigned int unk_a0_9 : 14;
    unsigned int unk_a0_23 : 9;
    unsigned int unk_a4_0 : 8;
    unsigned int unk_a4_8 : 14;
    unsigned int unk_a4_22 : 10;
    unsigned int unk_a8_0 : 24;
    unsigned int unk_a8_24 : 8;
    unsigned int unk_ac;
};

// Flags of the game, by their number (0x3c bytes, at 0x7504 in GameState): func_020ac460 copies them
struct GameFlags
{
    unsigned int flags_[15];
};

extern "C"
{
    // Copy the flags and the records, and write the records back
    int func_020ac460(GameFlags* flags);
    int func_020ac494(const PlayRecords* records);
    int func_020ac4c0(PlayRecords* records);
    // Add hours or minutes to a time, up to 9999:59:59
    void func_020ac614(PlayTime* time, unsigned short hours);
    void func_020ac644(PlayTime* time, unsigned char minutes);
}
