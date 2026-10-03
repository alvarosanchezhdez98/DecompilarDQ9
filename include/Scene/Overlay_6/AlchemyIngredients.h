#pragma once

#include "GameState/PlayRecords.h"

// A recipe of the alchemy pot (0x20 bytes), in a RecipeTable
struct Recipe
{
    // The ID of the item that it makes
    short id_;
    short unk_2;
    // The items that it needs, and how many of each
    short ingredients_[3];
    unsigned short amount0_ : 4;
    unsigned short amount1_ : 4;
    unsigned short amount2_ : 4;
    // The stat that the success rate depends on (1-7: values of the party member's data, 8 and 9: maximum HP and MP)
    unsigned short stat_ : 4;
    // The success rate (0-100) between the two values of the stat
    unsigned int minRate_ : 10;
    unsigned int maxRate_ : 10;
    // The kind of the item that it makes, which tells where its sprite and texts are
    unsigned int kind_ : 8;
    unsigned int unk_c_28 : 4;
    unsigned int minStat_ : 10;
    unsigned int maxStat_ : 10;
    unsigned int unk_10_20 : 2;
    // The recipe has been learnt or made
    unsigned int known_ : 1;
    unsigned int unk_10_23 : 9;
    short unk_14;
    short unk_16;
    short unk_18;
    short unk_1a;
    int unk_1c;
};

// The recipes of the alchemy pot (0xc bytes), which a script fills
struct RecipeTable
{
    Recipe* unk_0;
    Recipe* entries_;
    unsigned short capacity_;
    unsigned short count_;

    Recipe* GetEntry(short index)
    {
        return &entries_[index];
    }
};

// The record of a recipe that the player has learnt or made (4 bytes), which func_020ac2d4 reads
struct RecipeRecord
{
    short id_;
    unsigned short known_ : 1;
    unsigned short made_ : 1;
    unsigned short unk_2_2 : 14;

    void Initialize();
};

// The items that alchemy made: a recipe and maybe another one
struct AlchemyResult
{
    short recipe_;
    short unk_2;
    short extra_;
    short unk_6;
};

extern "C"
{
    Recipe* func_02071d60(RecipeTable* table, short id);
}

// What the player has for the alchemy pot (0x28 bytes): the items of each of the 9 categories, the recipe that is
// chosen and where its ingredients are, and the records of the recipes
class AlchemyIngredients
{
public:
    RecipeTable* table_;
    // For each category, its items, how many of each and the number of items
    short** items_;
    unsigned char** counts_;
    unsigned short* sizes_;
    // The chosen recipe, and the index and category of each of its ingredients
    Recipe* recipe_;
    short index_[3];
    signed char category_[3];
    RecipeRecord* records_;
    unsigned short recordCount_;

    void Initialize();
    void Finish();
    void SetTable(RecipeTable* table);
    void MarkKnownRecipes(RecipeTable* table, RecipeRecord* records, int count);
    void SetItems(short** items, unsigned char** counts, unsigned short* sizes);
    int SetRecipe(short id);
    int HasIngredients(int times);
    void GetAmounts(short id, unsigned char* amounts);
    void SetRecords(RecipeRecord* records, unsigned short count);
    RecipeRecord* FindRecord(short id);
    void AddResult(AlchemyResult result, RecipeTable* table);
    void UpdateRecord(RecipeRecord* record);
    short GetSuccessRate(short id);
    short CountRecipes();
};
