#pragma once

// Loads the graphics of a background (func_0204af64 initializes it)
struct BackgroundGraphics
{
    char unk_0[0x1c];
    unsigned char unk_1c_0_ : 4;
    unsigned char unk_1c_4_ : 4;
    char unk_1d[3];
};

// A surface that text is drawn to (func_0204c684 initializes it)
struct Canvas
{
    char unk_0[4];
    BackgroundGraphics* background_;
    void* pixels_;
    char unk_c[0x94];
    int unk_a0;
    char unk_a4[4];
    // In tiles
    short width_;
    short height_;
    short x_;
    short y_;
    char unk_b0[4];
    short unk_b4;
    short unk_b6;
    char unk_b8[0x28];
};
