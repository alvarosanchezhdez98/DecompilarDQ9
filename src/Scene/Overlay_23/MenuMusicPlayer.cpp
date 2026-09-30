// The objects of type 0xd of the menus (see MenuObjects.h), which play a music
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"

extern "C"
{
    // Returns the music player
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b34(void* music, int id, int, int, int);
    void func_02094b40(void* music);
    bool func_02094b4c(void* music);
}

int MenuObjectClassD::Initialize(MenuScript* script, int id, int heap, const MenuMusicParams* params,
                                 const MenuMusicFlags* flags)
{
    MenuObjectClass::Initialize();
    type_ = 0xd;
    id_ = id;
    heap_ = heap;
    params_.music_ = params->music_;
    params_.unk_4 = params->unk_4;
    flags2_.unk_0 = flags->unk_0;
    flags2_.unk_1 = flags->unk_1;
    return 1;
}

void MenuObjectClassD::Finish(MenuObjectList* list)
{
}

void MenuObjectClassD::Update(MenuScript* script)
{
    int (MenuObjectClassD::*states[4])(MenuScript*) = {&MenuObjectClassD::State_Load, &MenuObjectClassD::State_Wait,
                                                         &MenuObjectClassD::State_Loaded, 0};
    state_ = (this->*states[state_])(script);
}

int MenuObjectClassD::State_Load(MenuScript* script)
{
    void* music = func_02094a00();
    func_02094ab0(music);
    func_02094b40(music);
    func_02094b34(music, params_.music_, params_.unk_4, flags2_.unk_0, flags2_.unk_1);
    return 1;
}

int MenuObjectClassD::State_Wait(MenuScript* script)
{
    if (func_02094b4c(func_02094a00()))
        return 2;
    return state_;
}

int MenuObjectClassD::State_Loaded(MenuScript* script)
{
    return state_;
}
