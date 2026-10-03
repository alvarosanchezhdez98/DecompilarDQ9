#pragma once

#include "Scene/Overlay_6/AlchemyIngredients.h"
#include "Scene/Overlay_6/AlchemyPot.h"
#include "Text/TextTable.h"

// AlchemyMenu::flags_
// The menu's 3D scene isn't shown (overlay 17's other mode)
#define ALCHEMY_MENU_NO_SCENE 2
// The list of items has more than one page
#define ALCHEMY_MENU_PAGES 4
// The count of an ingredient is being chosen
#define ALCHEMY_MENU_COUNT 8
// The list of the items of a category is shown
#define ALCHEMY_MENU_ITEMS 0x10
// A message is shown
#define ALCHEMY_MENU_MESSAGE 0x20
// The alchemy succeeded greatly
#define ALCHEMY_MENU_GREAT 0x40
// The buttons of the recipe book are shown
#define ALCHEMY_MENU_BOOK 0x80
#define ALCHEMY_MENU_100 0x100
// The game is being saved
#define ALCHEMY_MENU_SAVING 0x200

// The states of AlchemyMenu (AlchemyMenu::state_)
enum AlchemyMenuState
{
    AlchemyMenuState_Load,
    AlchemyMenuState_FadeIn,
    AlchemyMenuState_Book,
    AlchemyMenuState_BookList,
    AlchemyMenuState_Main,
    AlchemyMenuState_Ingredient1,
    AlchemyMenuState_Ingredient2,
    AlchemyMenuState_Ingredient3,
    AlchemyMenuState_Make,
    AlchemyMenuState_Recipes,
    AlchemyMenuState_RecipeList,
    AlchemyMenuState_MakeRecipe,
    AlchemyMenuState_FadeOut,
    AlchemyMenuState_End,
};

// The repetition of the held buttons of a menu (0xc bytes): func_02081ee4 initializes it, func_02081f20 updates it
struct KeyRepeat
{
    unsigned short* buttons_;
    char unk_4[8];
};

// Overlay 6's alchemy menu (0x438 bytes), which overlay 17 runs: the pot's scene, the choice of up to three
// ingredients, and the recipe book with its categories and filters
class AlchemyMenu
{
public:
    // Of the scrolling of the message, in sixteenths of a character
    int textPosition_;
    // 16 buffers of 0x80 bytes for the texts of the menu
    char** texts_;
    void* canvasBuffer_;
    // The 10 allocators of the menu's files
    SafeAllocator* allocators_;
    AlchemyPot* pot_;
    Menu* menu_;
    // The choice of yes or no (0x24 bytes)
    void* choice_;
    BackgroundGraphics* backgrounds_;
    Canvas* canvases_;
    Sprite* sprites_;
    SpriteAnimationList* animations_;
    // The recipes that the book lists, linked by Recipe::next_, and the first one of the page
    Recipe* recipes_;
    Recipe* pageStart_;
    // The recipe that alchemy makes
    Recipe* recipe_;
    RecipeRecord* records_;
    // What func_020a9ea4 saves
    char save_[8];
    // The cursor that is moving
    short* cursor_;
    // For each of the 9 categories, the items, how many of each and how many items
    short** items_;
    unsigned char** counts_;
    unsigned short* sizes_;
    BackgroundGraphics subBackground_;
    AlchemyIngredients ingredients_;
    KeyRepeat repeat_;
    unsigned short buttons_;
    unsigned char unk_aa;
    SpriteRenderer renderer_;
    Layout layout_;
    RecipeTable table_;
    TextTable menuTexts_;
    // The names of the items
    char itemNames_[0xc];
    // The item that alchemy makes, and the ingredients' items
    PotIngredient results_[4];
    int ticks_;
    int menuResult_;
    int task_;
    int unk_358;
    short unk_35c;
    short previousCursor_;
    // The cursors of the menus
    short mainCursor_;
    short categoryCursor_;
    short itemCursor_;
    short bookCursor_;
    short filterCursor_;
    short recipeCursor_;
    short choiceCursor_;
    // The group of the menu that the cursor is in
    short group_;
    short item_;
    // The chosen ingredients: their categories, their items and how many
    unsigned short categories_[3];
    short chosenItems_[3];
    // The message, or -1, and how far it's shown
    short message_;
    unsigned short messageLength_;
    // The success rate of the recipe
    short successRate_;
    // The filters of the book, and its order
    signed char filterCategory_;
    signed char filterKind_;
    unsigned char sort_;
    // How many times alchemy makes the recipe
    unsigned char times_;
    unsigned char page_;
    unsigned char pages_;
    unsigned char category_;
    unsigned char count_;
    unsigned char chosenCounts_[3];
    // AlchemyMenuState
    unsigned char state_;
    unsigned char step_;
    unsigned char unk_391;
    unsigned char messageStep_;
    unsigned char repeatDelay_;
    // ALCHEMY_MENU_*
    unsigned short flags_;
    // 1 when the protagonist is a woman
    unsigned char female_;
    // The background of the sub screen
    unsigned char background_;
    // How many of each ingredient of the recipe the player has
    unsigned char amounts_[3];
    int textSound_;
    int unk_3a0;
    int textSoundOn_;
    unsigned int textSoundTimer_;
    int textSoundPlaying_;
    int textSoundState_;
    int showResult_;
    // The sprite of the item that alchemy made
    Unknown_02075cdc resultSprite_;
    int resultTask_;
    signed char arrowTimer_;
    unsigned char fadeTimer_;
    unsigned char nextStep_;
    unsigned char saved_;
    unsigned char arrowUp_;
    unsigned char arrowDown_;
    unsigned char resetBlend_;
    unsigned char closing_;
    unsigned char closeRequested_;

    void Allocate(SafeAllocator* allocator, void* buffer);
    void Initialize();
    void Finish();
    int Update(int ticks);
    void Draw3D();
    void Draw();
    void DrawSub();
    void RequestClose();
    void DrawChoice();
    void DrawButtons();
    void DrawCountArrows();
    void DrawBookButtons();
    unsigned char IsConfirmed();
    unsigned char IsCancelled();
    void CheckClose();
    unsigned char IsMessageAdvanced();
    void CountPages();
    void SetPage(Recipe* recipe);
    Recipe* GetPageStart(unsigned char page);
    Recipe* GetRecipe(short index);
    void LoadInventory();
    void AddItem(unsigned int category, short item, unsigned char count);
    void ReturnIngredient();
    void TakeIngredient(short category, short item, unsigned char count);
    short* GetCategoryItems();
    unsigned char* GetCategoryCounts();
    unsigned short GetCategorySize();
    int HasCategoryItems();
    void GetSelectedItem(unsigned char* category, short* item, unsigned char* count);
    void IncreaseCount();
    void DecreaseCount();
    void OpenItems();
    void CountItemPages();
    int UpdateItems();
    int UpdateItemButtons();
    void OpenCount();
    int UpdateCount();
    unsigned char UpdateTimes();
    unsigned char GetRecipeButton();
    void ChangeSort();
    void OpenChoice();
    signed char UpdateChoice();
    void PlayTextSound();
    void StopTextSound();
    void UpdateTextSound();
    void UpdateMessage();
    void LoadResult(int great);
    unsigned char UpdateResult(int great);
    void UpdateMultiplier();
    void State_Load();
    void State_FadeIn();
    void State_Book();
    void State_BookList();
    void State_Main();
    void State_Ingredient1();
    void State_Ingredient2();
    void State_Ingredient3();
    void State_Make();
    void State_Recipes();
    void State_RecipeList();
    void SetListShown(Menu* menu, int shown, unsigned char* background);
    void State_MakeRecipe();
    void State_FadeOut();
    void DrawMainTexts();
    void UpdateItemPage();
    void DrawItems();
    void ShowSelectedItem();
    void DrawRecipes();
    void DrawTimes();
    void DrawBookTitle(int total);
    void DrawFilter();
    void DrawSort();
    Recipe* FindRecipe(short* items, unsigned char* counts, unsigned char* times);
    void LoadResultSprite(PotIngredient* result);
    unsigned char UpdateResultSprite();
};
