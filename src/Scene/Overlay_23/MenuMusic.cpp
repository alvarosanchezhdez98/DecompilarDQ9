// The objects of type 0xe of the menus (see MenuObjects.h), which pause and resume the music
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"

extern "C"
{
    void func_020dc2bc();
    void func_020dc2d0(int);
}

int MenuObjectClassE::Initialize(MenuScript* script, int id, int heap)
{
    MenuObjectClass::Initialize();
    type_ = 0xe;
    id_ = id;
    heap_ = heap;
    return 1;
}

void MenuObjectClassE::Finish(MenuObjectList* list)
{
}

void MenuObjectClassE::Update(MenuScript* script)
{
    int (MenuObjectClassE::*states[4])(MenuScript*) = {&MenuObjectClassE::State_Load, &MenuObjectClassE::State_Wait,
                                                         &MenuObjectClassE::State_Loaded, 0};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClassE::State_Load(MenuScript* script)
{
    return 1;
}

int MenuObjectClassE::State_Wait(MenuScript* script)
{
    return 2;
}

int MenuObjectClassE::State_Loaded(MenuScript* script)
{
    return state_;
}

void MenuObjectClassE::Vd0()
{
    func_020dc2d0(0);
}

void MenuObjectClassE::Vd4()
{
    func_020dc2bc();
}
