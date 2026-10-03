#pragma once

#include "System/Matrix.h"

// What func_02057fb4 creates a game object with. Its callers set every member with the same stores, in the same
// order, and a constructor with them isn't inlined, so they're written at each call
struct GameObjectParams
{
    unsigned char unk_0;
    char unk_1[0xf];
    unsigned char unk_10;
    unsigned char unk_11_0 : 1;
    unsigned char unk_11_1 : 1;
    unsigned char unk_11_2 : 1;
    unsigned char unk_11_3 : 1;
    unsigned char unk_11_4 : 1;
    unsigned char unk_11_5 : 1;
    unsigned char unk_11_6 : 1;
    unsigned char unk_11_7 : 1;
    short unk_12;
    short unk_14[4];
    short unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    Vector3fix position_;
    Vector3fix rotation_;
    Vector3fix scale_;
};
