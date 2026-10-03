// The ingredients of overlay 6's alchemy pot: which items of each category the player has, whether there are enough
// of them for a recipe, the success rate of a recipe, and the records of the recipes that the player has learnt or made

#include "Scene/Overlay_6/AlchemyIngredients.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "GameState/PartyMemberData.h"
#include <std_library_functions.h>

extern "C"
{
    void func_020a0228(PlayTime* time, int);
    void func_020ac08c(unsigned int* count);
    int func_020ac0b4(unsigned int* count);
    void func_020ac104(void* buffer, RecipeRecord* records, int count);
    int func_020ac2d4(int, short* ids, RecipeRecord* records, int count);
}

void AlchemyIngredients::Initialize()
{
    table_ = 0;
    items_ = 0;
    counts_ = 0;
    sizes_ = 0;
    recipe_ = 0;
    memset(index_, -1, sizeof(index_));
    memset(category_, -1, sizeof(category_));
    records_ = 0;
    recordCount_ = 0;
}

void AlchemyIngredients::Finish()
{
    Initialize();
}

void AlchemyIngredients::SetTable(RecipeTable* table)
{
    table_ = table;
}

void AlchemyIngredients::MarkKnownRecipes(RecipeTable* table, RecipeRecord* records, int count)
{
    for (int i = 0; i < count; i++, records++)
    {
        Recipe* recipe = func_02071d60(table, records->id_);
        if (recipe != 0)
            recipe->known_ = records->known_ || records->made_;
    }
}

void AlchemyIngredients::SetItems(short** items, unsigned char** counts, unsigned short* sizes)
{
    items_ = items;
    counts_ = counts;
    sizes_ = sizes;
}

int AlchemyIngredients::SetRecipe(short id)
{
    if (sizes_ == 0)
        return 0;
    recipe_ = func_02071d60(table_, id);
    if (recipe_ == 0)
        return 0;
    if (recipe_->ingredients_[0] > 0 && recipe_->amount0_ != 0)
    {
        index_[0] = -1;
        category_[0] = -1;
        for (signed char category = 0; category < 9; category++)
        {
            short* items = items_[category];
            unsigned short size = sizes_[category];
            for (unsigned short i = 0; i < size; i++)
            {
                if (recipe_->ingredients_[0] == items[i])
                {
                    index_[0] = i;
                    category_[0] = category;
                    break;
                }
            }
        }
        if (index_[0] < 0)
            return 0;
        if (recipe_->amount0_ > counts_[category_[0]][index_[0]])
            return 0;
    }
    if (recipe_->ingredients_[1] > 0 && recipe_->amount1_ != 0)
    {
        index_[1] = -1;
        category_[1] = -1;
        for (signed char category = 0; category < 9; category++)
        {
            short* items = items_[category];
            unsigned short size = sizes_[category];
            for (unsigned short i = 0; i < size; i++)
            {
                if (recipe_->ingredients_[1] == items[i])
                {
                    index_[1] = i;
                    category_[1] = category;
                    break;
                }
            }
        }
        if (index_[1] < 0)
            return 0;
        if (recipe_->amount1_ > counts_[category_[1]][index_[1]])
            return 0;
    }
    if (recipe_->ingredients_[2] > 0 && recipe_->amount2_ != 0)
    {
        index_[2] = -1;
        category_[2] = -1;
        for (signed char category = 0; category < 9; category++)
        {
            short* items = items_[category];
            unsigned short size = sizes_[category];
            for (unsigned short i = 0; i < size; i++)
            {
                if (recipe_->ingredients_[2] == items[i])
                {
                    index_[2] = i;
                    category_[2] = category;
                    break;
                }
            }
        }
        if (index_[2] < 0)
            return 0;
        if (recipe_->amount2_ > counts_[category_[2]][index_[2]])
            return 0;
    }
    return 1;
}

int AlchemyIngredients::HasIngredients(int times)
{
    Recipe* recipe = recipe_;
    if (recipe == 0)
        return 0;
    if (recipe->ingredients_[0] > 0 && recipe->amount0_ != 0)
    {
        if (index_[0] < 0)
            return 0;
        if (category_[0] < 0)
            return 0;
        if (recipe->amount0_ * times > counts_[category_[0]][index_[0]])
            return 0;
    }
    if (recipe->ingredients_[1] > 0 && recipe->amount1_ != 0)
    {
        if (index_[1] < 0)
            return 0;
        if (category_[1] < 0)
            return 0;
        if (recipe->amount1_ * times > counts_[category_[1]][index_[1]])
            return 0;
    }
    if (recipe->ingredients_[2] > 0 && recipe->amount2_ != 0)
    {
        if (index_[2] < 0)
            return 0;
        if (category_[2] < 0)
            return 0;
        if (recipe->amount2_ * times > counts_[category_[2]][index_[2]])
            return 0;
    }
    return 1;
}

void AlchemyIngredients::GetAmounts(short id, unsigned char* amounts)
{
    memset(amounts, 0, 3);
    Recipe* recipe = func_02071d60(table_, id);
    if (recipe == 0)
        return;
    for (int category = 0; category < 9; category++)
    {
        short* items = items_[category];
        unsigned char* counts = counts_[category];
        short size = sizes_[category];
        for (short i = 0; i < size; i++)
        {
            short item = items[i];
            if (item > 0)
            {
                if (item == recipe->ingredients_[0])
                    amounts[0] = counts[i];
                else if (item == recipe->ingredients_[1])
                    amounts[1] = counts[i];
                else if (item == recipe->ingredients_[2])
                    amounts[2] = counts[i];
            }
        }
    }
}

void AlchemyIngredients::SetRecords(RecipeRecord* records, unsigned short count)
{
    records_ = records;
    recordCount_ = count;
}

RecipeRecord* AlchemyIngredients::FindRecord(short id)
{
    if (id < 0)
        return 0;
    unsigned short count = recordCount_;
    for (unsigned short i = 0; i < count; i++)
    {
        RecipeRecord* entry = &records_[i];
        if (entry->id_ == id)
            return entry;
    }
    return 0;
}

void AlchemyIngredients::AddResult(short recipe, short extra, RecipeTable* table)
{
    RecipeRecord record;
    unsigned int count;
    PlayRecords records;

    BackgroundLoader::AddLockGlobal();
    BackgroundLoader::FreeAllocationsGlobal();
    record.Initialize();
    if (func_020ac2d4(0, &recipe, &record, 1))
    {
        record.known_ = 1;
        record.made_ = 1;
        func_020ac104(data_0211e33c, &record, 1);
        UpdateRecord(&record);
        if (table != 0)
        {
            Recipe* entry = func_02071d60(table, recipe);
            if (entry != 0)
                entry->known_ = 1;
        }
    }
    if (extra > 0)
    {
        record.Initialize();
        if (func_020ac2d4(0, &extra, &record, 1))
        {
            record.id_ = extra;
            record.made_ = 1;
            func_020ac104(data_0211e33c, &record, 1);
            UpdateRecord(&record);
            if (table != 0)
            {
                Recipe* entry = func_02071d60(table, extra);
                if (entry != 0)
                    entry->known_ = 1;
            }
            CountRecipes();
        }
    }
    count = 0;
    if (func_020ac0b4(&count))
    {
        count++;
        if (count > 99999)
            count = 99999;
        func_020ac08c(&count);
        func_020ac4c0(&records);
        func_020a0228(&records.unk_68, 1);
        func_020ac494(&records);
    }
    BackgroundLoader::RemoveLockGlobal();
}

void RecipeRecord::Initialize()
{
    id_ = -1;
    known_ = 0;
    made_ = 0;
    unk_2_2 = 0;
}

#pragma always_inline on
void AlchemyIngredients::UpdateRecord(RecipeRecord* record)
{
    short id = record->id_;
    unsigned short count = recordCount_;
    unsigned short i;
    for (i = 0; i < count; i++)
    {
        RecipeRecord* entry = &records_[i];
        if (entry->id_ == id)
        {
            *entry = *record;
            return;
        }
    }
    for (i = 0; i < count; i++)
    {
        RecipeRecord* entry = &records_[i];
        if (entry->id_ <= 0)
        {
            *entry = *record;
            return;
        }
    }
}
#pragma always_inline reset

short AlchemyIngredients::GetSuccessRate(short id)
{
    Recipe* recipe = func_02071d60(table_, id);
    if (recipe == 0)
        return 0;
    short rate = 100;
    if (recipe->stat_ != 0)
    {
        GameObject* protagonist = GameState::GetInstance()->GetProtagonist();
        if (protagonist != 0)
        {
            unsigned short value = 0;
            switch (recipe->stat_)
            {
            case 1:
                value = protagonist->partyData_->unk_0_0;
                break;
            case 2:
                value = protagonist->partyData_->unk_0_10;
                break;
            case 3:
                value = protagonist->partyData_->unk_0_20;
                break;
            case 4:
                value = protagonist->partyData_->unk_4_0;
                break;
            case 5:
                value = protagonist->partyData_->unk_4_10;
                break;
            case 6:
                value = protagonist->partyData_->unk_4_20;
                break;
            case 7:
                value = protagonist->partyData_->unk_8_0;
                break;
            case 8:
                value = protagonist->baseStats_->primaryStats.maxHP;
                break;
            case 9:
                value = protagonist->baseStats_->primaryStats.maxMP;
                break;
            }
            unsigned int minRate = recipe->minRate_;
            unsigned int maxRate = recipe->maxRate_;
            float rateRange = maxRate - minRate;
            unsigned int minStat = recipe->minStat_;
            float statRange = recipe->maxStat_ - minStat;
            rate = (int)(((float)value - minStat) * (rateRange / statRange)) + minRate;
            if (rate > 100)
                rate = 100;
            else if (rate < 0)
                rate = 0;
            if (rate <= minRate)
                rate = minRate;
            if (maxRate <= rate)
                rate = maxRate;
        }
    }
    return rate;
}

short AlchemyIngredients::CountRecipes()
{
    if (table_ == 0)
        return 0;
    unsigned short count = 0;
    char flags[0x1d8] = {0};
    PlayRecords records;
    for (unsigned short i = 0; i < recordCount_; i++)
        flags[records_[i].id_] |= records_[i].known_;
    for (unsigned short j = 0; j < table_->count_; j++)
    {
        Recipe* recipe = table_->GetEntry(j);
        if (recipe != 0 && recipe->unk_16 < 0)
            flags[recipe->id_] |= 2;
    }
    for (unsigned short k = 1; k < 0x1d8; k++)
    {
        if (flags[k] == 3)
            count++;
    }
    func_020ac4c0(&records);
    records.unk_10_23 = count;
    func_020ac494(&records);
    return count;
}
