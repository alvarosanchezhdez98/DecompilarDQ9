// The objects of type 0x10 of the menus (see MenuObjects.h), which have an Unknown_021dc134
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Scene/Overlay_11/MenuScript.h"

extern "C"
{
    void func_ov023_021dbfd0(Unknown_021dc134* object, SafeAllocator* allocator);
    void func_ov023_021dc134(Unknown_021dc134* object, int, int);
    void func_ov023_021dc354(Unknown_021dc134* object);
    void func_ov023_021dc488(Unknown_021dc134* object);
    void func_ov023_021dca88(Unknown_021dc134* object);
    void func_ov023_021dcae0(Unknown_021dc134* object);
    void func_ov023_021ddf5c(Unknown_021dc134* object);
    void func_ov023_021dfad8(Unknown_021dc134* object);
}

int MenuObjectClass10::Initialize(MenuScript* script, int id, int heap, int flags, int unk48, unsigned char unk778)
{
    MenuObjectClass::Initialize();
    type_ = 0x10;
    id_ = id;
    heap_ = heap;
    MenuHeap* menuHeap = script->FindHeap(heap_);
    if (menuHeap == NULL)
        return 0;
    func_ov023_021dc134(&unk_20, -1, 0);
    unk_20.unk_774 |= (unsigned short)(flags | 0x4000);
    func_ov023_021dbfd0(&unk_20, &menuHeap->allocator_);
    unk_20.unk_48 = unk48;
    unk_20.unk_778 = unk778;
    return 1;
}

void MenuObjectClass10::Update(MenuScript* script)
{
    func_ov023_021dc488(&unk_20);
    state_ = 2;
}

void MenuObjectClass10::Draw3()
{
    func_ov023_021dfad8(&unk_20);
}

void MenuObjectClass10::Finish(MenuObjectList* list)
{
    func_ov023_021dc354(&unk_20);
}

void MenuObjectClass10::Func021fbdcc()
{
    func_ov023_021dcae0(&unk_20);
}

void MenuObjectClass10::Func021fbddc()
{
    func_ov023_021dca88(&unk_20);
}

Unknown_021dc134* MenuObjectClass10::GetUnk20()
{
    return &unk_20;
}

void MenuObjectClass10::SetUnk77a(signed char value)
{
    unk_20.unk_77a = value;
    func_ov023_021ddf5c(&unk_20);
}
