// The layouts of the menus (.lia files): trees of elements, whose items are boxes, texts, numbers and icons drawn on a
// canvas
#include "Scene/Overlay_23/Layout.h"
#include "System/TouchScreen.h"
#include <std_library_functions.h>

// An element of a .lia file (0x1c bytes)
struct LayoutFileElement
{
    int unk_0;
    // The offset of its items' IDs in the IDs
    int items_;
    short x_;
    short y_;
    short unk_c;
    unsigned short count_;
    unsigned short id_;
    unsigned short parent_;
    unsigned short child_;
    unsigned short previous_;
    unsigned short next_;
    char unk_1a[2];
};

// An item of a .lia file (0x28 bytes)
struct LayoutFileItem
{
    int type_;
    short x_;
    short y_;
    short id_;
    char unk_a[2];
    union
    {
        struct
        {
            unsigned short width_;
            unsigned short height_;
        };
        int unk_c;
    };
    unsigned short width2_;
    unsigned short height2_;
    char unk_14[0x28 - 0x14];
};

// The start of a .lia file
struct LayoutFile
{
    int unk_0;
    int elements_;
    char magic_[4];
    // Offsets in the file, which Layout::Load() makes pointers
    LayoutFileItem* items_;
    int unk_10;
    short* ids_;
    int count_;
};

extern "C"
{
    int memcmp(const void* a, const void* b, unsigned long size);

    void func_02012a84(TouchState* touch, int* x, int* y);
    int func_020420e8(const char* text, int large);
    // The tiles of an icon
    int func_020421b0(unsigned char icon);
    void func_0204e1c8(Canvas* canvas, int tiles, short x, short y, int width, int height, int, int);
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, int color, int shadow, short* width,
                       short* height, int);
    void func_0204f7e8(Canvas* canvas, short x, short y, int value, int color, int shadow, short* width,
                       short* height, int, int digits, int, int);
    void func_0204f914(Canvas* canvas, int color, short left, short top, short right, short bottom);

    // The touch screen
    extern TouchState data_02114e54;
}

// Draws an icon of 2x2 tiles
static void DrawIcon(Canvas* canvas, short x, short y, int tiles)
{
    for (int row = 0; row < 2; row++)
    {
        for (int column = 0; column < 2; column++)
        {
            func_0204e1c8(canvas, tiles, (short)(x + column * 8), (short)(y + row * 8), 8, 8, 0xf0, 0xf);
            tiles += 0x20;
        }
    }
}

void Layout::Initialize()
{
    unk_0 = 0;
    canvas_ = NULL;
    elements_ = NULL;
    items_ = NULL;
    unk_10 = 0;
    unk_12 = 0;
    numElements_ = 0;
    numItems_ = 0;
    textHeight_ = 0;
    textHeight12_ = 0;
}

int Layout::Load(SafeAllocator* allocator, void* file, unsigned int size)
{
    if (allocator == NULL)
        return 1;
    if (file == NULL)
        return 1;
    if (size == 0)
        return 1;
    LayoutFile* header = (LayoutFile*)file;
    if (memcmp(header->magic_, "NDS", 3) != 0)
        return 1;
    header->items_ = (LayoutFileItem*)((char*)file + (int)header->items_);
    LayoutItem* item;
    header->ids_ = (short*)((char*)file + (int)header->ids_);

    numElements_ = 0;
    numItems_ = 0;
    LayoutFileElement* sources;
    numElements_ = header->count_;
    elements_ = (LayoutElement*)allocator->Allocate(numElements_ * sizeof(LayoutElement));
    unsigned short count = numElements_;
    sources = (LayoutFileElement*)((char*)file + header->elements_);
    for (unsigned short i = 0; i < count; i++)
    {
        LayoutFileElement* source;
        LayoutElement* element = &elements_[i];
        element->id_ = -1;
        element->count_ = 0;
        source = &sources[i];
        element->items_ = NULL;
        element->x_ = element->y_ = 0;
        element->parent_ = -1;
        element->child_ = -1;
        element->previous_ = -1;
        element->next_ = -1;
        element->unk_14 = 0;
        element->flags_ = 3;
        element->unk_17 = 0xff;
        element->x_ = source->x_;
        element->y_ = source->y_;
        element->count_ = source->count_;
        element->items_ = (short*)allocator->Allocate(source->count_ * sizeof(short));
        short* ids = (short*)((char*)header->ids_ + source->items_);
        if (ids != NULL)
            memcpy(element->items_, ids, source->count_ * sizeof(short));
        element->id_ = source->id_;
        element->parent_ = source->parent_;
        element->child_ = source->child_;
        element->previous_ = source->previous_;
        element->next_ = source->next_;
        numItems_ += element->count_;
    }

    LayoutFileItem* itemSources;
    LayoutFileItem* source;
    items_ = (LayoutItem*)allocator->Allocate(numItems_ * sizeof(LayoutItem));
    itemSources = header->items_;
    for (unsigned short i = 0; i < numItems_; i++)
    {
        source = &itemSources[i];
        item = &items_[i];
        item->id_ = -1;
        item->type_ = LayoutItemType_Box;
        item->color_ = 0xa;
        item->shadow_ = 0xf;
        item->x_ = item->y_ = 0;
        item->width_ = item->height_ = 0;
        item->value_ = 0;
        *((unsigned char*)item + 0x10) = 0;
        item->x_ = source->x_;
        item->y_ = source->y_;
        item->id_ = source->id_;
        switch (source->type_)
        {
        case 0:
            item->type_ = LayoutItemType_Number;
            item->width_ = source->width_;
            item->height_ = source->height_;
            break;
        case 1:
            item->type_ = LayoutItemType_Text;
            item->width_ = source->width_;
            item->height_ = source->height_;
            break;
        case 2:
            break;
        case 3:
            if (source->unk_c == 0)
            {
                item->width_ = source->width2_;
                item->height_ = source->height2_;
            }
            break;
        }
    }
    return 0;
}

void Layout::SetText(short id, const char* text, unsigned char color, unsigned char shadow)
{
    LayoutItem* item = GetItem(id);
    if (item == NULL)
        return;
    item->value_ = (int)text;
    item->color_ = color;
    item->shadow_ = shadow;
}

LayoutItem* Layout::GetItem(short id)
{
    LayoutElement* element = FindElement(id);
    if (element == NULL || element->count_ == 0 || element->items_ == NULL)
        return NULL;
    return FindItem(element->items_[0]);
}

LayoutItem* Layout::FindItem(short id)
{
    LayoutItem* items = items_;
    if (items == NULL)
        return NULL;
    unsigned short count = numItems_;
    if (count == 0)
        return NULL;
    for (unsigned short i = 0; i < count; i++)
    {
        LayoutItem* item = &items[i];
        if (item->id_ == id)
            return item;
    }
    return NULL;
}

void Layout::SetNumber(short id, int value, unsigned char color, unsigned char shadow, unsigned char unk4, unsigned char digits,
                       unsigned char unk5, unsigned char unk6)
{
    LayoutItem* item = GetItem(id);
    if (item == NULL)
        return;
    item->value_ = value;
    item->color_ = color;
    item->shadow_ = shadow;
    item->unk_10_4 = unk4;
    item->digits_ = digits;
    item->unk_10_5 = unk5;
    item->unk_10_6 = unk6;
}

void Layout::SetIcon(short id, int icon)
{
    LayoutItem* item = GetItem(id);
    if (item == NULL)
        return;
    item->value_ = func_020421b0(icon * 4 + 0x28);
}

void Layout::Draw()
{
    if (canvas_ == NULL)
        return;
    for (unsigned short i = 0; i < numItems_; i++)
    {
        LayoutItem* item = &items_[i];
        LayoutElement* element = FindElementOfItem(item->id_);
        if (element == NULL || !IsVisible(element->id_))
            continue;
        short x, y;
        GetItemPosition(item->id_, &x, &y);
        short height = textHeight_;
        int color = item->color_;
        Canvas* canvas = canvas_;
        if (height == 0)
            height = color + 1;
        if (color == 0xc)
        {
            height = textHeight12_;
            if (height == 0)
                height = 0x14;
        }
        canvas->unk_b4 = color;
        canvas->unk_b6 = height;
        switch (item->type_)
        {
        case LayoutItemType_Box:
            func_0204f914(canvas_, item->shadow_, x, y, (short)(x + item->width_), (short)(y + item->height_));
            break;
        case LayoutItemType_Text:
            if (element->flags_ & LAYOUT_ELEMENT_FLAG_CENTERED)
                x -= func_020420e8((const char*)item->value_, 0) >> 1;
            if (element->flags_ & LAYOUT_ELEMENT_FLAG_4)
                x -= func_020420e8((const char*)item->value_, 0);
            func_0204f41c(canvas_, x, y, (const char*)item->value_, item->color_, item->shadow_, &item->width_,
                          &item->height_, 0);
            break;
        case LayoutItemType_Number:
        {
            int unk5, unk6;
            if (item->unk_10_5)
                unk5 = 1;
            else
                unk5 = 0;
            if (item->unk_10_6)
                unk6 = 1;
            else
                unk6 = 0;
            func_0204f7e8(canvas_, x, y, item->value_, item->color_, item->shadow_, &item->width_, &item->height_,
                          item->unk_10_4, item->digits_, unk5, unk6);
        }
            break;
        case LayoutItemType_Icon:
            DrawIcon(canvas_, x, y, item->value_);
            break;
        }
    }
}

LayoutElement* Layout::FindElementOfItem(short item)
{
    LayoutElement* elements = elements_;
    unsigned short count = numElements_;
    for (unsigned short i = 0; i < count; i++)
    {
        LayoutElement* element = &elements[i];
        unsigned short itemCount = element->count_;
        for (unsigned short j = 0; j < itemCount; j++)
        {
            if (item == element->items_[j])
                return element;
        }
    }
    return NULL;
}

short Layout::GetTouchedButton()
{
    if (data_02114e54.unk_5f == 0 || data_02114e54.unk_24 == 0)
        return 0;
    int x, y;
    func_02012a84(&data_02114e54, &x, &y);
    LayoutElement* element = elements_;
    for (unsigned short i = 0; i < numElements_; i++, element = &elements_[i])
    {
        if (element->child_ == 0 || !(element->flags_ & LAYOUT_ELEMENT_FLAG_BUTTONS))
            continue;
        LayoutElement* button = FindElement(element->child_);
        while (button != NULL)
        {
            LayoutItem* item = GetItem(button->id_);
            if (item == NULL)
            {
                button = FindElement(button->next_);
                continue;
            }
            short itemX, itemY;
            GetItemPosition(item->id_, &itemX, &itemY);
            if (itemX > x || x > itemX + item->width_)
            {
                button = FindElement(button->next_);
                continue;
            }
            if (itemY > y || y > itemY + item->height_)
            {
                button = FindElement(button->next_);
                continue;
            }
            return button->id_;
        }
    }
    return 0;
}

void Layout::SetType(short id, unsigned char type)
{
    LayoutItem* item = GetItem(id);
    if (item != NULL)
        item->type_ = type;
}

short Layout::GetTouchedElement()
{
    if (data_02114e54.touching_ == 0)
        return -1;
    int x, y;
    func_02012a84(&data_02114e54, &x, &y);
    unsigned short count = numElements_;
    LayoutElement* elements = elements_;
    for (unsigned short i = 0; i < count; i++)
    {
        if (!IsVisible(elements[i].id_))
            continue;
        LayoutItem* item = GetItem(elements[i].id_);
        if (item == NULL || item->type_ == LayoutItemType_Box)
            continue;
        short itemX, itemY;
        GetItemPosition(item->id_, &itemX, &itemY);
        short right = itemX + item->width_;
        short bottom = itemY + item->height_;
        if (itemY <= y && y < bottom && itemX <= x && x < right)
            return elements[i].id_;
    }
    return -1;
}

void Layout::AddPosition(short id, short* x, short* y)
{
    LayoutElement* element = FindElement(id);
    *x += element->x_;
    *y += element->y_;
    while (element != NULL)
    {
        if (element->previous_ > 0)
        {
            element = FindElement(element->previous_);
            continue;
        }
        if (element->parent_ < 0)
            return;
        LayoutElement* parent = FindElement(element->parent_);
        if (parent == NULL)
            return;
        AddPosition(parent->id_, x, y);
        return;
    }
}

void Layout::GetItemPosition(short item, short* x, short* y)
{
    if (elements_ == NULL || numElements_ == 0 || items_ == NULL || numItems_ == 0)
        return;
    LayoutItem* found = FindItem(item);
    if (found == NULL)
        return;
    *x = found->x_;
    *y = found->y_;
    LayoutElement* element = FindElementOfItem(item);
    if (element == NULL)
        return;
    AddPosition(element->id_, x, y);
}

void Layout::GetPosition(short id, short* x, short* y)
{
    LayoutElement* element = FindElement(id);
    if (element != NULL && element->count_ != 0 && element->items_ != NULL)
    {
        short itemX, itemY;
        GetItemPosition(element->items_[0], &itemX, &itemY);
        *x = itemX;
        *y = itemY;
    }
}

int Layout::IsVisible(short id)
{
    int visible = 1;
    LayoutElement* element = FindElement(id);
    while (element != NULL)
    {
        if (element->flags_ & LAYOUT_ELEMENT_FLAG_VISIBLE)
            visible = 1;
        else
            visible = 0;
        if (!visible)
            break;
        while (element->previous_ > 0)
            element = FindElement(element->previous_);
        if (element->parent_ >= 0)
            element = FindElement(element->parent_);
    }
    return visible;
}

void Layout::SetPosition(short id, short x, short y)
{
    LayoutItem* item = GetItem(id);
    if (item != NULL)
    {
        item->x_ = x;
        item->y_ = y;
    }
}

void Layout::SetSize(short id, short width, short height)
{
    LayoutItem* item = GetItem(id);
    if (item != NULL)
    {
        item->width_ = width;
        item->height_ = height;
    }
}
