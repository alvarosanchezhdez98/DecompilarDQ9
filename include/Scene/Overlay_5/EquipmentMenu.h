#pragma once

#include "Graphics/Background.h"
#include "System/Matrix.h"
#include "Graphics/TextWindow.h"
#include "Graphics/VRAMManagerState.h"
#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"
#include "Scene/Overlay_5/CursorFrame.h"
#include "Scene/Overlay_23/EquipmentModelTable.h"
#include "Scene/Overlay_23/ItemInfoWindow.h"
#include "Scene/Overlay_23/ItemSortList.h"
#include "Scene/Overlay_23/Layout.h"
#include "Scene/Overlay_23/MemberScreen.h"
#include "Text/TextTable.h"

// A 3D model of the menus (0x88 bytes): func_0204719c initializes it, func_02047b40 loads it, func_02047554 draws it
// and func_02047230 destroys it
struct MenuModel
{
    char unk_0[0x1c];
    // func_0203a46c sets it
    Vector3fix position_;
    char unk_28[0x80 - 0x28];
    short alpha_;
    short unk_82;
    char unk_84[4];

    void SetPosition(const Vector3fix* position);
};

// A place of an item in the equipment menu (0x1c bytes): the 8 equipped items, then the 16 of a page of the list
struct EquipmentSlot
{
    // The item, or -1
    short item_;
    signed char count_;
    unsigned char equipped_;
    VRAMManagerState* vramState_;
    MenuModel* model_;
    // The position of the model
    int x_;
    int y_;
    // Where the model's file was loaded, or -1
    int offset_;
    // The item whose model is loaded
    short loadedItem_;

    void Unload();
};

// Overlay 5, the equipment menu, which overlay 23's MemberScreen runs in its mode 3 (0x428c bytes): the 8 equipped
// items of a party member at the top of the touch screen, the pages of the items of a kind under them as 3D models,
// and the information on the chosen item
struct EquipmentMenu
{
    SafeAllocator allocator_;
    SafeAllocator modelAllocator_;
    // The models of the equipped items, and of the items of the page
    SafeAllocator equippedAllocators_[8];
    SafeAllocator itemAllocators_[16];
    SafeAllocator dragAllocator_;
    SafeAllocator textAllocator_;
    SafeAllocator unk_230;
    SafeAllocator infoAllocator_;
    SafeAllocator sortAllocator_;
    SafeAllocator modelTableAllocator_;
    SafeAllocator unk_280;
    VRAMManagerState vramState_;
    VRAMManagerState slotVramStates_[24];
    VRAMManagerState dragVramState_;
    PartNameTable* items_;
    // The texts (str_eq)
    TextTable texts_;
    // The message system's buffer of encoded text (0x960 bytes)
    unsigned short* text_;
    char unk_e14[4];
    Layout layout_;
    void* unk_e64;
    int unk_e68;
    // What func_02074af4 saves and func_02074bd0 restores
    char screenState_[0x10];
    unsigned char unk_e7c;
    unsigned char unk_e7d;
    char unk_e7e[2];
    // The main screen's layers before the menu changed them
    int layers_;
    BackgroundGraphics backgrounds_[3];
    TextWindow window_;
    Canvas canvases_[3];
    void* pixels_;
    ItemInfoWindow infoWindow_;
    ItemSortList sortList_;
    EquipmentModelTable modelTable_;
    WindowCursor cursor_;
    CursorFrame frame_;
    MenuModel models_[36];
    EquipmentSlot slots_[24];
    MenuModel slotModels_[24];
    // The model of the item that's dragged
    MenuModel dragModel_;
    // The slot of the item that's dragged, or -1
    short dragged_;
    char unk_3d7a[2];
    int unk_3d7c;
    int unk_3d80;
    int unk_3d84;
    // The files of the models: of the page, of the dragged item, of the equipped items and of the chosen item
    char* pageFiles_;
    char* dragFile_;
    char* equippedFiles_;
    char* itemFile_;
    // The number of items of each kind
    short itemCounts_[8];
    unsigned char unk_3da8;
    unsigned char equippedStep_;
    unsigned char pageStep_;
    unsigned char dragStep_;
    unsigned short unk_3dac;
    unsigned short equippedStart_;
    unsigned short equippedEnd_;
    unsigned short pageStart_;
    unsigned short pageEnd_;
    char unk_3db6;
    unsigned char loading_;
    // The state, the previous one and the step of the state
    unsigned char state_;
    unsigned char lastState_;
    unsigned char step_;
    // The chosen slot, kind of item and page
    signed char slot_;
    unsigned char kind_;
    signed char page_;
    unsigned char unk_3dbe;
    signed char lastPage_;
    signed char unk_3dc0;
    char unk_3dc1;
    unsigned short unk_3dc2;
    unsigned char loadStep_;
    char unk_3dc5[3];
    int task_;
    unsigned int flags_;
    unsigned char unk_3dd0;
    unsigned char unk_3dd1;
    unsigned char unk_3dd2;
    unsigned char unk_3dd3;
    // How the items of each kind are sorted
    unsigned char sortOrders_[8];
    // The menu of an item: its step, what its window returned, the chosen option and its state
    unsigned char menuStep_;
    unsigned char menuResult_;
    signed char menuChoice_;
    unsigned char menuState_;
    short swapped_;
    // The opening animation: where it is, the ticks that it waits, and its phase
    short animationX_;
    int ticks_;
    int animationTime_;
    int animationPhase_;
    signed char blinks_;
    signed char blinkTimer_;
    signed char blinkTimer2_;
    unsigned char fadeStep_;
    // The number of pages of each kind of item, and the page that's shown
    unsigned char pageCounts_[8];
    unsigned char pages_[8];
    signed char unk_3e04;
    signed char touchTime_;
    signed char tapTimer_;
    signed char tappedSlot_;
    short touchX_;
    short touchY_;
    // The digits that the levels are written with
    unsigned short digits_[20][3];
    // The names of the equipped items
    unsigned short names_[8][0x40];
    unsigned char longNames_[8];

    void CreateAllocators(SafeAllocator* allocator, SafeAllocator* allocator2);
    void LoadVRAM();
    void Initialize();
    void Finish();
    int Load();
    void LoadModelTable(void* file, unsigned int size);
    void Update();
    void Draw2D();
    void DrawSub();
    void Reload();
    void SetMember(int member, int change);
    void DrawLevel(int level, short x, int y, unsigned short color);
    void GetSlotPosition(int slot, int* x, int* y);
    void InitializeSlots();
    void LoadEquipped();
    void LoadPage();
    int GetTouchedSlot(int x, int y);
    void UpdateLoading();
    void UpdateModels();
    void UpdateTouch();
    void TouchTop(int x, int y);
    void TouchPage(int x, int y);
    void TouchModel(int x, int y);
    void Drag(int x, int y);
    void Drop(int x, int y);
    int IsConfirmed();
    void SetCursor();
    void UpdateKeys();
    void UpdateKinds();
    void UpdateEquipped();
    void UpdatePage();
    void SetState(unsigned char state);
    void MoveFrame(unsigned int state, unsigned char slot);
    // 0xffff removes the item of the chosen kind
    void Equip(int item, int keep);
    int RemoveUnwearable(int member);
    unsigned char GetTouchedPart(int x, int y);
    void OpenDialog();
    int WriteMessage(unsigned short* text);
    int CanEquip(int member);
    unsigned char GetPart(int kind);
    unsigned char GetCategory(int kind);
    unsigned char GetList(int kind);
    int SetKind(unsigned char kind, int silent);
    int TurnPage(int direction);
    void UpdateDialog(int ticks);
    int UpdateFade();
    void UpdateMenu(int ticks);
    void UpdateMenuText();
    void Menu_Open();
    void Menu_Equip();
    void Menu_Close();
    void Menu_Discard();
    void Menu_Cancel();
    void OpenMenu();
    void WriteMenu(unsigned short* text, int touched);
    void OpenChoice();
    void CreateChoice(SpriteAnimationList* animations, SpriteRenderer* renderer);
    void DrawModels();
    void DrawPageArrows();
    void DrawKindArrows();
    void DrawSortButton();
    void DrawKinds();
    void DrawSortIcon();
    void DrawTabs();
    void DrawCursor();
    void WriteDigits();
    void DrawPageNumber();
    void DrawCounts();
    void WriteNames();
    void DrawNames();
    void State_Start();
    void State_Open();
    void State_Kinds();
    void State_Equipped();
    void State_Page();
    void State_Menu();
    void State_Move();
    void State_Sort();
};

typedef char EquipmentMenuSizeCheck[sizeof(EquipmentMenu) == 0x428c ? 1 : -1];
