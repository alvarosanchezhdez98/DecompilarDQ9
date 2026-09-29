// The objects of type 9 of the menus (see MenuObjects.h), which move other objects, such as the menus' cursor
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "System/Matrix.h"

void MenuMove::Clear()
{
    id_ = 0;
    kind_ = 0;
    phase_ = 0;
}

int MenuObjectClass9::Initialize(MenuScript* script, int id, int heap, int count)
{
    MenuObjectClass::Initialize();
    type_ = 9;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    state_ = 2;
    count_ = count;
    MenuHeap* menuHeap = script->FindHeap(heap_);
    if (menuHeap == NULL)
        return 0;
    moves_ = (MenuMove*)menuHeap->allocator_.Allocate(count_ * sizeof(MenuMove));
    if (moves_ == NULL)
        return 0;
    for (int i = 0; i < count_; i++)
        moves_[i].Clear();
    return 1;
}

void MenuObjectClass9::Update(MenuScript* script)
{
    void (MenuObjectClass9::*steps[3])(MenuScript*, MenuMove*) = {NULL, &MenuObjectClass9::Step, NULL};
    for (int i = 0; i < count_; i++)
    {
        if (moves_[i].kind_ != 0)
            (this->*steps[moves_[i].kind_])(script, &moves_[i]);
    }
}

void MenuObjectClass9::Finish(MenuObjectList* list)
{
}

MenuMove* MenuObjectClass9::FindFreeMove()
{
    for (int i = 0; i < count_; i++)
    {
        MenuMove* move = &moves_[i];
        if (move->kind_ == 0)
            return move;
    }
    return NULL;
}

void MenuObjectClass9::Move(MenuScript* script, unsigned short id, Vector3fix* target, int maxSpeed, int acceleration)
{
    MenuMove* move = FindFreeMove();
    if (move == NULL)
        return;
    move->Clear();
    move->kind_ = 1;
    move->id_ = id;
    MenuObjectClass* object = script->GetObjects()->Find(move->id_);
    if (object == NULL)
        return;
    move->speed_ = 0;
    move->acceleration_ = acceleration;
    move->maxSpeed_ = maxSpeed;
    move->position_ = object->GetPosition();
    move->target_ = *target;
}

void MenuObjectClass9::Step(MenuScript* script, MenuMove* move)
{
    Vector3fix direction;
    Vector3fix_Subtract(&move->target_, &move->position_, &direction);
    Vector3fix_Normalize(&direction, &direction);
    int done = 0;
    if (move->phase_ == 0)
    {
        move->speed_ += move->acceleration_;
        if (move->maxSpeed_ < move->speed_)
            move->speed_ = move->maxSpeed_;
        Vector3fix step;
        Vector3fixMultiplyScalar(&direction, move->speed_, &step);
        Vector3fix_Add(&move->position_, &step, &move->position_);
        int distance = Vector3fix_Distance(&move->target_, &move->position_);
        float speed = move->speed_ / 4096.0f;
        // The distance that it takes to stop
        if (distance < (int)(4096.0f * (speed * speed / (2.0f * (move->acceleration_ / 4096.0f)))))
            move->phase_ = 1;
    }
    else if (move->phase_ == 1)
    {
        int distance = Vector3fix_Distance(&move->target_, &move->position_);
        if (move->acceleration_ < move->speed_ && move->speed_ - move->acceleration_ < distance)
        {
            move->speed_ = move->speed_ - move->acceleration_;
            Vector3fix step;
            Vector3fixMultiplyScalar(&direction, move->speed_, &step);
            Vector3fix_Add(&move->position_, &step, &move->position_);
        }
        else
        {
            move->position_ = move->target_;
            done = 1;
        }
    }
    MenuObjectClass* object = script->GetObjects()->Find(move->id_);
    if (object != NULL)
        object->SetPosition(&move->position_);
    if (done)
        move->Clear();
}
