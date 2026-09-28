#pragma once

// The state of the touch screen (data_02114e54)
struct TouchState
{
    char unk_0[0x24];
    unsigned short unk_24;
    char unk_26[0x38 - 0x26];
    // The touched point
    int x_;
    int y_;
    char unk_40[0x54 - 0x40];
    unsigned char unk_54;
    // The screen is touched
    unsigned char touching_;
    char unk_56[0x5f - 0x56];
    unsigned char unk_5f;
};
