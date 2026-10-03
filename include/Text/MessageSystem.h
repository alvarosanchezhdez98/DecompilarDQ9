#pragma once

// The text system: it formats texts and shows them in the message window. func_020421a0 returns it
struct MessageSystem
{
    // The names that the texts write (see MessageName in BattleEnd.h)
    void* arguments_;
    char unk_4[4];
    void* unk_8;
    char unk_c[4];
    void* unk_10;
    char unk_14[4];
    void* unk_18;
    char unk_1c[4];
    void* unk_20;
    char unk_24[0x30 - 0x24];
    // The numbers of the members in the battle, and of the ones alive
    unsigned char unk_30;
    unsigned char unk_31;
    char unk_32[0x5c - 0x32];
    // 0x960 bytes, which TitleScreen clears before writing the library versions to it
    void* unk_5c;
    char unk_60[0x14c - 0x60];
    // 2 or more: the menus' buttons use their second cell (see MenuObjectClass1)
    int unk_14c;
    char unk_150[0x2c8 - 0x150];
    int unk_2c8;
    char unk_2cc[0x2d8 - 0x2cc];
    // The sprites that the texts can show (a SpriteRenderer, its sprites and its animations)
    void* unk_2d8;
    void* unk_2dc;
    void* unk_2e0;
    short unk_2e4;
    unsigned char unk_2e6;
    // TitleScreen waits for 2 after func_02043368
    unsigned char unk_2e7;
    char unk_2e8[0x998 - 0x2e8];
    // While the message is shown
    int busy_;
    int unk_99c;
    // The state of the message window: SaveErrorScreen waits for 4 before deleting the save data and for 3 before
    // checking the buttons
    int unk_9a0;
    char unk_9a4[0x195a - 0x9a4];
    unsigned char unk_195a;
    union
    {
        unsigned char unk_195b;
        struct
        {
            unsigned char unk_195b_0 : 7;
            unsigned char unk_195b_7 : 1;
        };
    };
    char unk_195c[0x19ae - 0x195c];
    unsigned char unk_19ae;
    unsigned char unk_19af;
    unsigned char unk_19b0;
    char unk_19b1;
    unsigned char unk_19b2;
    char unk_19b3[0x19be - 0x19b3];
    unsigned char unk_19be;
    char unk_19bf[0x19c5 - 0x19bf];
    unsigned char unk_19c5;
    char unk_19c6[2];
    unsigned char unk_19c8;
    char unk_19c9;
    unsigned char unk_19ca;
    char unk_19cb[0x19d2 - 0x19cb];
    unsigned char unk_19d2;
    char unk_19d3[0x19d7 - 0x19d3];
    unsigned char unk_19d7;
    char unk_19d8[0x1e28 - 0x19d8];
    void* unk_1e28;
};
