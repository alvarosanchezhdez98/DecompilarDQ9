#pragma once

#include "Graphics/Background.h"
#include "Memory/SafeAllocator.h"

#define LAYOUT_ELEMENT_FLAG_VISIBLE 1
// The element's items are buttons (Layout::GetTouchedButton())
#define LAYOUT_ELEMENT_FLAG_BUTTONS 2
// Its texts are centered, or aligned to the right
#define LAYOUT_ELEMENT_FLAG_CENTERED 8
#define LAYOUT_ELEMENT_FLAG_4 0x10

// An element of a layout: a group of items, in a tree of elements (0x18 bytes)
struct LayoutElement
{
    short id_;
    unsigned short count_;
    // The IDs of its items
    short* items_;
    short x_;
    short y_;
    // The IDs of the parent, of the first child and of the previous and next siblings, or -1
    short parent_;
    short child_;
    short previous_;
    short next_;
    short unk_14;
    // LAYOUT_ELEMENT_FLAG_*
    unsigned char flags_;
    unsigned char unk_17;
};

// What an item of a layout shows
enum LayoutItemType
{
    LayoutItemType_Box,
    LayoutItemType_Text,
    LayoutItemType_Number,
    LayoutItemType_Icon,
};

// An item of a layout (0x14 bytes)
struct LayoutItem
{
    short id_;
    // LayoutItemType
    unsigned char type_;
    unsigned char color_ : 4;
    unsigned char shadow_ : 4;
    short x_;
    short y_;
    short width_;
    short height_;
    // The text, the number or the icon's tiles
    int value_;
    // How the number is shown
    unsigned char digits_ : 4;
    unsigned char unk_10_4 : 1;
    unsigned char unk_10_5 : 1;
    unsigned char unk_10_6 : 1;
    unsigned char unk_10_7 : 1;
    char unk_11[3];
};

// A layout of the menus (a .lia file, "NDS"): elements and the items that they show on a canvas (0x4c bytes)
struct Layout
{
    int unk_0;
    Canvas* canvas_;
    LayoutElement* elements_;
    LayoutItem* items_;
    short unk_10;
    short unk_12;
    unsigned short numElements_;
    unsigned short numItems_;
    char unk_18[0x48 - 0x18];
    // The height of the texts, if not 0
    short textHeight_;
    // The height of the texts of color 12, if not 0
    short textHeight12_;

    void SetCanvas(Canvas* canvas)
    {
        canvas_ = canvas;
        unk_12 = 1;
    }

    void Initialize();
    int Load(SafeAllocator* allocator, void* file, unsigned int size);
    void SetText(short id, const char* text, unsigned char color, unsigned char shadow);
    LayoutItem* GetItem(short id);
    LayoutItem* FindItem(short id);
    void SetNumber(short id, int value, unsigned char color, unsigned char shadow, unsigned char unk4, unsigned char digits,
                   unsigned char unk5, unsigned char unk6);
    void SetIcon(short id, int icon);
    void Draw();
    LayoutElement* FindElementOfItem(short item);
    short GetTouchedButton();
    void SetType(short id, unsigned char type);
    short GetTouchedElement();
    void AddPosition(short id, short* x, short* y);
    void GetItemPosition(short item, short* x, short* y);
    void GetPosition(short id, short* x, short* y);
    int IsVisible(short id);
    void SetPosition(short id, short x, short y);
    void SetSize(short id, short width, short height);
    // In another file of overlay 23
    LayoutElement* FindElement(short id);
};
