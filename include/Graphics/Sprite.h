#pragma once

#include "System/Matrix.h"

// A sprite's cell: its tiles start at the character name unk_4 & 0x3ff
struct SpriteCell
{
    char unk_0[4];
    unsigned short unk_4;
};

// The start of a Sprite, which overlay 23 copies
struct SpriteImage
{
    int unk_0;
    SpriteCell* cell_;
};

struct Sprite
{
    SpriteImage image_;
    // The OAM attributes
    void* unk_8;
    char unk_c[8];
    fix32_t x_;
    fix32_t y_;
    char unk_1c[6];
    unsigned char unk_22;
    char unk_23[2];
    unsigned char unk_25;
    unsigned char unk_26;
    char unk_27;
};

// The animated sprites of a SpriteRenderer
struct SpriteAnimation
{
    char unk_0[4];
    short x_;
    short y_;
    char unk_8[0xd];
    unsigned char flags_;
};

struct SpriteAnimationList
{
    char unk_0[8];
};

struct SpriteRenderer
{
    char unk_0[0x3c];
    SpriteAnimationList* animations_;
    Sprite* sprites_;
    char unk_44[4];
    unsigned int unk_48;
    short numSprites_;
    unsigned short capacity_;
    // The screen: 0 for the main one, 1 for the sub one
    unsigned char unk_50;
    char unk_51[3];

    void SetSprites(Sprite* sprites, short numSprites)
    {
        sprites_ = sprites;
        numSprites_ = numSprites;
    }
    // The game's compiler didn't inline it: overlay 23's menus call its copy after MenuObjectClassA::Finish()
    Sprite* GetSprite(unsigned short index)
    {
        Sprite* sprite = 0;
        if (sprites_ != 0 && index < capacity_)
            sprite = &sprites_[index];
        return sprite;
    }
};
