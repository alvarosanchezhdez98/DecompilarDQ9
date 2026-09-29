// The objects of type 8 of the menus (see MenuObjects.h): a text that a MenuObjectClass6 draws on its canvas
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Scene/Overlay_11/MenuScript.h"

int MenuObjectClass8::Initialize(MenuScript* script, int id, int heap, int canvas, int texts, int textId, int x, int y,
                                 int font, int color)
{
    MenuObjectClass::Initialize();
    type_ = 8;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    state_ = 2;
    alignment_ = 0;
    unk_42 = 0;
    formatted_ = 0;
    text_ = NULL;
    unk_24.x = -0x10000;
    unk_24.y = -0x3000;
    unk_24.z = 0;
    unk_30 = 0;
    unk_32 = 0;
    canvas_ = canvas;
    texts_ = texts;
    textId_ = textId;
    x_ = x;
    y_ = y;
    font_ = font;
    color_ = color;
    selected_ = 0;
    unk_46 = 0;
    unk_48 = 0;
    unk_4a = 0;
    unk_4c = 0;
    return 1;
}

void MenuObjectClass8::Finish(MenuObjectList* list)
{
}

void MenuObjectClass8::SetPosition(Vector3fix* position)
{
    x_ = position->x / 4096.0f;
    y_ = position->y / 4096.0f;
}

Vector3fix MenuObjectClass8::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    position.y = y_ << 12;
    return position;
}

Vector3fix MenuObjectClass8::GetScreenPosition(MenuScript* script)
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    position.y = y_ << 12;
    MenuObjectClass* canvas = script->GetObjects()->Find(canvas_);
    if (canvas != NULL)
    {
        Vector3fix offset = canvas->GetPosition();
        position.x += offset.x;
        position.y += offset.y;
    }
    return position;
}

Vector3fix MenuObjectClass::GetPosition()
{
    Vector3fix zero = {0};
    return zero;
}

void MenuObjectClass8::SetWidth(unsigned short width)
{
    width_ = width;
}

unsigned short MenuObjectClass8::GetWidth()
{
    return width_;
}

void MenuObjectClass8::SetHeight(unsigned short height)
{
    height_ = height;
}

unsigned short MenuObjectClass8::GetHeight()
{
    return height_;
}

void MenuObjectClass8::V3c(short value)
{
    unk_46 = value;
}

int MenuObjectClass8::V40()
{
    return unk_46;
}

void MenuObjectClass8::V44(short value)
{
    unk_48 = value;
}

int MenuObjectClass8::V48()
{
    return unk_48;
}

void MenuObjectClass8::V4c(int value)
{
    unk_4a = value;
}

int MenuObjectClass8::V50()
{
    return unk_4a;
}

void MenuObjectClass8::V7c(int value)
{
    unk_4c = value;
}

int MenuObjectClass8::V80()
{
    return unk_4c;
}

int MenuObjectClass8::ContainsTouch()
{
    if (selected_)
        return 1;
    return 0;
}
