#pragma once

// Loads the graphics of a background (func_0204af64 initializes it)
struct BackgroundGraphics
{
    char unk_0[0x1c];
    unsigned char unk_1c_0_ : 4;
    unsigned char unk_1c_4_ : 4;
    unsigned char unk_1d;
    char unk_1e[2];
};

// A surface that text is drawn to (func_0204c684 initializes it)
struct Canvas
{
    // The canvas that this one is drawn over? (overlay 23's MenuObjectClass6)
    Canvas* unk_0;
    BackgroundGraphics* background_;
    void* pixels_;
    char unk_c[0x94];
    int unk_a0;
    int unk_a4;
    // In tiles
    short width_;
    short height_;
    short x_;
    short y_;
    char unk_b0[4];
    short unk_b4;
    short unk_b6;
    short unk_b8;
    short unk_ba;
    short unk_bc;
    short unk_be;
    short unk_c0;
    unsigned short unk_c2;
    // *Likely* the canvas' item (overlay 12)
    unsigned char unk_c4;
    // 0x2: hidden?, 0x20: ?, 0x40: ?
    unsigned char flags_;
    char unk_c6[0xd8 - 0xc6];
    // 0x4: ?
    unsigned char unk_d8;
    char unk_d9[0xe0 - 0xd9];
};
