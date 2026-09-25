#pragma once

#include "System/Matrix.h"

struct Sprite
{
    char unk_0[8];
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
    char unk_44[8];
    short numSprites_;
    unsigned short capacity_;
    unsigned char unk_50;
    char unk_51[3];

    void SetSprites(Sprite* sprites, short numSprites)
    {
        sprites_ = sprites;
        numSprites_ = numSprites;
    }
};
