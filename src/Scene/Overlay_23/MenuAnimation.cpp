// The objects of type 0xb of the menus (see MenuObjects.h): an animation of the sprites of a MenuObjectClassA
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "GameState/GameState.h"
#include "Scene/Overlay_11/MenuScript.h"

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    void func_0205a254(SpriteAnimationList* animations, unsigned char animation, int ticks);
    void func_0205a370(SpriteAnimationList* animations, unsigned short animation);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* animations, unsigned short animation);
    void func_0205a42c(SpriteAnimationList* animations, unsigned short animation, unsigned char slot);
    void func_0205addc(SpriteRenderer* renderer, unsigned char animation);
}

int MenuObjectClassB::Initialize(MenuScript* script, int id, int heap, int sprites, int animation)
{
    MenuObjectClass::Initialize();
    type_ = 0xb;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    state_ = 2;
    sprites_ = sprites;
    MenuObjectList* objects = script->GetObjects();
    MenuObjectClassA* object = (MenuObjectClassA*)objects->Find(sprites_);
    if (object == NULL)
        return 0;
    unsigned char screen = object->GetRenderer()->unk_50;
    animation_ = animation;
    slots_ = objects->FindSlots(screen, 1);
    objects->SetSlots(screen, slots_, 1);
    unk_26 = 0;
    x_ = 0;
    y_ = 0;
    return 1;
}

void MenuObjectClassB::Finish(MenuObjectList* list)
{
    MenuObjectClassA* object = (MenuObjectClassA*)list->Find(sprites_);
    if (object == NULL)
        return;
    SpriteRenderer* renderer = object->GetRenderer();
    list->ClearSlots(renderer->unk_50, slots_, 1);
    SpriteAnimationList* animations = renderer->animations_;
    if (animations == NULL)
        return;
    SpriteAnimation* entry = func_0205a3d0(animations, animation_);
    if (entry != NULL)
        entry->flags_ &= ~8;
}

void MenuObjectClassB::Update(MenuScript* script)
{
    if (flags_ & 8)
        return;
    GameState* gameState = GameState::GetInstance();
    SpriteRenderer* renderer = ((MenuObjectClassA*)script->GetObjects()->Find(sprites_))->GetRenderer();
    SpriteAnimationList* animations = renderer->animations_;
    if (animations == NULL)
        return;
    func_0205a370(animations, animation_);
    SpriteAnimation* entry = func_0205a3d0(animations, animation_);
    if (entry != NULL)
        entry->flags_ |= 8;
    func_0205a42c(animations, animation_, slots_);
    func_0205a254(animations, animation_, gameState->GetTickCount());
    short x;
    short y;
    y = y_;
    x = x_;
    entry = func_0205a3d0(animations, animation_);
    if (entry != NULL)
    {
        entry->x_ = x;
        entry->y_ = y;
    }
    func_0205addc(renderer, animation_);
}

void MenuObjectClassB::SetPosition(Vector3fix* position)
{
    x_ = position->x / 4096.0f;
    y_ = position->y / 4096.0f;
}

Vector3fix MenuObjectClassB::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    // Not y: a bug of the game
    position.z = y_ << 12;
    return position;
}

void MenuObjectClassB::V3c(short value)
{
    unk_26 = value;
}

int MenuObjectClassB::V40()
{
    return unk_26;
}
