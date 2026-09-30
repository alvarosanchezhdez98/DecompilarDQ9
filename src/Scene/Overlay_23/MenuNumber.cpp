// The objects of type 0xf of the menus (see MenuObjects.h): a number that a MenuObjectClass6 draws on its canvas
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"

extern "C"
{
    void __clear(void* buffer, unsigned long size);
}

int MenuObjectClassF::Initialize(MenuScript* script, int id, int heap, int canvas, int x, int y, int font, int unk3b,
                                 int unk3c, int color)
{
    MenuObjectClass::Initialize();
    type_ = 0xf;
    value_ = 0;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = 0;
    state_ = 2;
    unk_20.x = -0x10000;
    unk_20.y = -0x3000;
    unk_20.z = 0;
    canvas_ = canvas;
    x_ = x;
    y_ = y;
    font_ = font;
    unk_3b = unk3b;
    unk_3c = unk3c;
    unk_3d = 0;
    color_ = color;
    return 1;
}

void MenuObjectClassF::Finish(MenuObjectList* list)
{
}

void MenuObjectClassF::SetPosition(Vector3fix* position)
{
    x_ = position->x / 4096.0f;
    y_ = position->y / 4096.0f;
}

Vector3fix MenuObjectClassF::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    position.y = y_ << 12;
    return position;
}

void MenuObjectClassF::SetWidth(unsigned short width)
{
    width_ = width;
}

void MenuObjectClassF::SetHeight(unsigned short height)
{
    height_ = height;
}

Vector3fix MenuObjectClassF::Vcc()
{
    return unk_20;
}

void MenuObjectClassF::Vc8(Vector3fix* value)
{
    unk_20.x = value->x;
    unk_20.y = value->y;
    unk_20.z = value->z;
}
