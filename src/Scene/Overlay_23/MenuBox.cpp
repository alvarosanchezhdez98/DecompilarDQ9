// The objects of type 0x13 of the menus (see MenuObjects.h): a box that a MenuObjectClass6 draws on its canvas
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"

extern "C"
{
    void __clear(void* buffer, unsigned long size);
}

int MenuObjectClass13::Initialize(MenuScript* script, int id, int heap, int canvas, int x, int y, int width, int height,
                                  int color)
{
    MenuObjectClass::Initialize();
    type_ = 0x13;
    id_ = id;
    heap_ = heap;
    state_ = 2;
    canvas_ = canvas;
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
    color_ = color;
    return 1;
}

void MenuObjectClass13::Finish(MenuObjectList* list)
{
}

void MenuObjectClass13::SetPosition(Vector3fix* position)
{
    x_ = position->x / 4096.0f;
    y_ = position->y / 4096.0f;
}

Vector3fix MenuObjectClass13::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    position.y = y_ << 12;
    return position;
}

unsigned short MenuObjectClass13::GetWidth()
{
    return width_;
}

unsigned short MenuObjectClass13::GetHeight()
{
    return height_;
}
