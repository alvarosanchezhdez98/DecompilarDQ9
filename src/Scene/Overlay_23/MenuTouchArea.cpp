// The areas of the touch screen of the menus (see MenuObjects.h), which run a callback of the script when they're
// touched
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "System/TouchScreen.h"

extern "C"
{
    extern TouchState data_02114e54;

    void __clear(void* buffer, unsigned long size);

    void func_02012a84(TouchState* touch, int* x, int* y);
}

int MenuTouchArea::Initialize(MenuScript* script, int id, int heap, int x, int y, int width, int height, int unk2c)
{
    MenuObjectClass::Initialize();
    type_ = 0x13;
    id_ = id;
    heap_ = heap;
    state_ = 2;
    unk_20 = id;
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
    callback_ = 0;
    unk_2c = unk2c;
    return 1;
}

void MenuTouchArea::Finish(MenuObjectList* list)
{
}

void MenuTouchArea::SetPosition(Vector3fix* position)
{
    x_ = position->x / 4096.0f;
    y_ = position->y / 4096.0f;
}

Vector3fix MenuTouchArea::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    position.y = y_ << 12;
    return position;
}

void MenuTouchArea::GetRect(unsigned short* left, unsigned short* top, unsigned short* right, unsigned short* bottom)
{
    *left = x_;
    *top = y_;
    *right = *left + width_;
    *bottom = *top + height_;
}

void MenuTouchArea::Va4(int callback)
{
    callback_ = callback;
}

int MenuTouchArea::GetTouchCallback()
{
    return callback_;
}

int MenuTouchArea::IsTouched()
{
    if (flags_ & 0x10)
        return 0;
    unsigned short left;
    unsigned short top;
    unsigned short right;
    unsigned short bottom;
    GetRect(&left, &top, &right, &bottom);
    int x;
    int y;
    func_02012a84(&data_02114e54, &x, &y);
    if (left <= x && x < right && top <= y && y < bottom)
        return 1;
    return 0;
}

int MenuTouchArea::ContainsTouch()
{
    return IsTouched();
}
