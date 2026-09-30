// The objects of type 0x10 of the menus (see MenuObjects.h): the window of the information on an item
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Scene/Overlay_11/MenuScript.h"

int MenuObjectClass10::Initialize(MenuScript* script, int id, int heap, int flags, int names, unsigned char background)
{
    MenuObjectClass::Initialize();
    type_ = 0x10;
    id_ = id;
    heap_ = heap;
    MenuHeap* menuHeap = script->FindHeap(heap_);
    if (menuHeap == NULL)
        return 0;
    window_.Initialize(-1, 0);
    window_.flags_ |= (unsigned short)(flags | ITEM_INFO_WINDOW_NO_UPDATE);
    window_.CreateAllocators(&menuHeap->allocator_);
    window_.names_ = (PartNameTable*)names;
    window_.background_ = background;
    return 1;
}

void MenuObjectClass10::Update(MenuScript* script)
{
    window_.Update();
    state_ = 2;
}

void MenuObjectClass10::Draw3()
{
    window_.Draw();
}

void MenuObjectClass10::Finish(MenuObjectList* list)
{
    window_.Finish();
}

void MenuObjectClass10::SetItem(short item)
{
    window_.SetItem(item);
}

void MenuObjectClass10::Close()
{
    window_.Close();
}

ItemInfoWindow* MenuObjectClass10::GetWindow()
{
    return &window_;
}

void MenuObjectClass10::SetMember(signed char member)
{
    window_.member_ = member;
    window_.DrawStats();
}
