#pragma once

#include "Bestiary/MonsterListScreen.h"
#include "Graphics/Background.h"
#include "Graphics/Sprite.h"
#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"
#include "Scene/Overlay_6/AlchemyIngredients.h"
#include "Scene/Overlay_23/ItemInfoWindow.h"
#include "Scene/Overlay_23/Layout.h"
#include "Scene/Overlay_23/MenuObjects.h"
#include "World/Object3D.h"

// AlchemyPot::flags_
// The background of the sub screen is loading
#define ALCHEMY_POT_LOAD_BACKGROUND 1
// The recipe's item is loading
#define ALCHEMY_POT_LOAD_ITEM 2
// The item window shows a recipe
#define ALCHEMY_POT_RECIPE 4
// No 3D scene: only the item window and the menu
#define ALCHEMY_POT_NO_3D 8
// Alchemy is being done: the item window is hidden
#define ALCHEMY_POT_MAKING 0x10
// The item window is shown
#define ALCHEMY_POT_ITEM_SHOWN 0x40
// The animations of the alchemy: the ingredients going in, the pot working, the item coming out
#define ALCHEMY_POT_ANIMATION_IN 0x80
#define ALCHEMY_POT_ANIMATION_WORK 0x100
#define ALCHEMY_POT_ANIMATION_OUT 0x200
#define ALCHEMY_POT_ANIMATION_END 0x400
#define ALCHEMY_POT_ANIMATION_DONE 0x800
// The 3D scene is loaded
#define ALCHEMY_POT_LOADED 0x1000
#define ALCHEMY_POT_ANIMATION_OPEN 0x2000

// The sprite of an ingredient that goes into the pot (0x7c bytes)
struct IngredientSprite
{
    Unknown_02075cdc graphics_;
    // Of its file
    int task_;
    // The item
    short item_;
    short x_;
    short y_;
    unsigned char loading_;

    void Initialize();
};

// An ingredient that the menu passes to AlchemyPot::LoadIngredients() (0x74 bytes): a copy of the item's entry
struct PotIngredient
{
    PartEntry entry_;
    // What entry_'s pointers point to
    char model_[0x20];
    char unk_40[0x30];
    // The item, or -1
    short item_;

    void Initialize();
};

// An effect of the sub screen (0x18 bytes): func_020dbd9c initializes it, func_020dbf18 loads it
struct Unknown_020dbd9c
{
    char unk_0[0x10];
    int state_;
    unsigned char unk_14;
};

// The alchemy pot (0x12c0 bytes): the 3D scene of the pot on the main screen, with the protagonist and the
// ingredients going in, and the window of the recipe's item on the sub screen
class AlchemyPot
{
public:
    // The names of the ingredients
    char names_[3][0x80];
    // The 6 allocators of the files of the scene
    SafeAllocator* allocators_;
    // The item's sprites: the one that is shown and the next one
    SafeAllocator* itemAllocator_;
    SafeAllocator* nextItemAllocator_;
    // The effect of the pot
    SafeAllocator effectAllocator_;
    // The camera before the scene's
    void* previousCamera_;
    // The canvases' buffer
    void* canvasBuffer_;
    // How many of each ingredient the player has
    unsigned char* amounts_;
    // The names of the items
    void* itemNames_;
    // The texts of the menu
    void* texts_;
    // The recipe that is shown, and the next one
    Recipe* recipe_;
    Recipe* nextRecipe_;
    int unk_1bc;
    RecipeRecord* record_;
    unsigned char* unk_1c4;
    Layout* layout_;
    BackgroundGraphics* backgrounds_;
    Canvas* canvases_;
    Menu* menu_;
    PartEntry* item_;
    PartEntry* nextItem_;
    Sprite* sprites_;
    SpriteRenderer renderer_;
    // The protagonist, the pot and its parts, and the effect
    Object3D protagonist_;
    Object3D pot_;
    Object3D lid_;
    Object3D effect_;
    Object3D steam_;
    char unk_594[0x38];
    char camera_[0x2c8];
    IngredientSprite ingredients_[4];
    SafeAllocator ingredientAllocators_[4];
    // Of the scene's files and of the item's files
    int task_;
    int backgroundTask_;
    // 0 while it loads, 1 when it's loaded, 2 if a file failed
    unsigned char state_;
    unsigned char loadStep_;
    unsigned char itemStep_;
    unsigned char backgroundStep_;
    unsigned char unk_ae0;
    unsigned char animationStep_;
    // ALCHEMY_POT_*
    unsigned short flags_;
    ItemInfoWindow window_;
    SafeAllocator* windowAllocator_;
    SafeAllocator* windowSpriteAllocator_;
    PartNameTable partNames_;
    Unknown_020dbd9c subEffect_;
    // The item that the window shows
    short itemId_;
    signed char itemSprites_;
    unsigned char numIngredients_;
    unsigned char effectMode_;
    unsigned char resetBlend_;

    void Allocate(SafeAllocator* allocator, void* buffer);
    void Initialize();
    void Finish();
    void Update(int ticks);
    void Draw();
    void Draw3D();
    void DrawSub();
    void UpdateAnimation();
    void SetNo3D();
    void SetIngredients(short* items, unsigned char* amounts);
    void OpenWindow();
    void ResetItem();
    void ShowRecipe(Recipe* recipe, RecipeRecord* record, unsigned char* amounts);
    void LoadRecipe(Recipe* recipe, RecipeRecord* record, unsigned char* amounts);
    void ShowItem(short item, signed char sprites);
    void UpdateItem();
    void UpdateLoad();
    void UpdateLoaded();
    void UpdateBackground();
    void UpdateEffect();
    void ResetIngredients();
    void LoadIngredients(PotIngredient* ingredients);
    void UpdateIngredients();
    int IsLoadingIngredients();
    int ShowNames(int show);
    void CloseWindow();
    void SetMultiplier(unsigned char multiplier);
    void DrawNames();
    void StartEffect();
    void StopEffect();
};
