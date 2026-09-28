#pragma once

#include "GameState/GameState.h"

// The profile of the player in the save data (GameState + 0x569c), which the profile editor edits
struct ProfileData
{
    unsigned int year_ : 12;
    unsigned int month_ : 4;
    unsigned int day_ : 5;
    // The protagonist's sex, twice
    unsigned int unk_0_21 : 4;
    unsigned int female_ : 1;
    // Overlay 12 initialized the profile
    unsigned int initialized_ : 1;
    // The card's design, the birthday and the accolade were chosen
    unsigned int designChosen_ : 1;
    unsigned int birthdayChosen_ : 1;
    unsigned int accoladeChosen_ : 1;
    // The accolade is the vocation's
    unsigned int vocationAccolade_ : 1;
    // The birthday is shown
    unsigned int showBirthday_ : 1;
    // What func_02098f20 returns for the birthday
    unsigned int unk_4_0 : 9;
    // The title (0 to 511)
    int title_ : 10;
    // The accolade: under 700, a text of profsen_<LG>.bin, else of profstr_<LG>.bin
    int accolade_ : 11;
    // The profile was edited once
    int edited_ : 1;
    unsigned int unk_4_31 : 1;
    char unk_8[0x74];
};

// The profile's data
static inline ProfileData* GetProfile(GameState* gameState)
{
    return (ProfileData*)((char*)gameState + 0x569c);
}
