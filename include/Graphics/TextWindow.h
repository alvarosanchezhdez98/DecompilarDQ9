#pragma once

#include "Graphics/Background.h"

extern "C"
{
    void func_0205ba68(void*, int columns, int rows, int);
    void func_0205bacc(void*, int count);
    void func_0205bb04(void*, int);
    void func_0205bcdc(void*, int);
}

// The frame of a window's items (func_0205bbcc initializes it). It's a union because the compiler copies a struct of
// several members with a function, but the game copies the frame inline, like an array
union WindowFrame
{
    int words_[0x14];
    struct
    {
        char unk_0[4];
        int unk_4;
    };
};

// The cursor of a window's items (func_0205bef8 initializes it), a union like WindowFrame
union WindowCursor
{
    int words_[0x10];
    struct
    {
        char unk_0[4];
        int unk_4;
    };
};

// What TextWindow and TextMenu have in common (func_0205c53c initializes it): the grid of their items, their frame and
// their cursor
struct WindowBase
{
    char unk_0[4];
    WindowFrame frame_;
    WindowCursor cursor_;
    unsigned char unk_94;
    unsigned char unk_95;
    unsigned char unk_96;
    unsigned char unk_97;
};

// A menu of text items, which main's code runs (func_0205c790 initializes it, func_0205cb74 adds an item)
struct TextMenu
{
    char unk_0[4];
    char unk_4[0x18];
    WindowBase base_;
    short x_;
    short y_;
    short width_;
    short height_;
    char unk_bc[0x233 - 0xbc];
    unsigned char unk_233;
    unsigned char unk_234;
    char unk_235[3];

    // Sets the number of columns and rows of the items
    void SetGrid(int columns, int rows);

    void SetPosition(short x, short y)
    {
        x_ = x;
        y_ = y;
    }
};

// What func_0205cfd4 initializes, *likely* a text window: StartupScene draws the library versions with it
struct TextWindow
{
    WindowBase base_;
    BackgroundGraphics* background_;
    int unk_9c;
    // In tiles
    short width_;
    short height_;
    short unk_a4;
    short unk_a6;
    short unk_a8;
    short unk_aa;
    short unk_ac;
    short unk_ae;
    unsigned char unk_b0;
    unsigned char unk_b1;
    unsigned char unk_b2;
    unsigned char unk_b3;
    unsigned char unk_b4;
    unsigned char unk_b5;
    unsigned char unk_b6;
    unsigned char unk_b7;
    unsigned char unk_b8;
    unsigned char unk_b9;
    unsigned char unk_ba;
    unsigned char unk_bb;
};
