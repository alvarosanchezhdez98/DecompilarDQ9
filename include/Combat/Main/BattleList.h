#pragma once

struct PrimaryCombatStats {
    unsigned short currHP;
    unsigned short currMP;
    unsigned short maxHP;
    unsigned short maxMP;
    unsigned short attack;
    unsigned short defense;
    unsigned short agility;
    unsigned short unk;
    unsigned int charm : 10;
    unsigned int magicalMight : 10;
    unsigned int magicalMending : 10;
    // The party member is in the back row
    unsigned int backRow : 1;
    unsigned int unk31 : 1;
};

struct BaseCombatStats {
    char unk[0x2C];
    struct PrimaryCombatStats primaryStats;
};

struct ModifiableCombatStats {
    struct PrimaryCombatStats primaryStats; // 0xE
    // Status flags: 0x8, 0x80019...
    int status_;
    // More of them: 0x1000, 0x2000...
    int status2_;
    char unk1c[6];
    unsigned short unk22;
    char unk24[0xa];
    // The party member that the monster is (see func_0200ff1c)
    signed char member_;
    char unk2f[0x58 - 0x2f];
    signed int attackBuff : 3;
    signed int defenseBuff : 3;
    signed int agilityBuff : 3;
    signed int charmBuff : 3;
    signed int magicalMightBuff : 3;
    signed int magicalMendingBuff : 3;
};